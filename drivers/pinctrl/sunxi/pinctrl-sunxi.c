// SPDX-License-Identifier: GPL-2.0

#include <dm.h>
#include <dm/device-internal.h>
#include <dm/lists.h>
#include <dm/pinctrl.h>
#include <malloc.h>

#include "pinctrl-sunxi.h"

extern U_BOOT_DRIVER(gpio_sunxi);

struct sunxi_pinctrl_plat {
	struct sunxi_gpio __iomem *base;
};

static int sunxi_pinctrl_get_pins_count(struct udevice *dev)
{
	const struct sunxi_pinctrl_desc *desc = dev_get_priv(dev);

	return desc->num_banks * SUNXI_GPIOS_PER_BANK;
}

static const char *sunxi_pinctrl_get_pin_name(struct udevice *dev,
					      unsigned pin_selector)
{
	const struct sunxi_pinctrl_desc *desc = dev_get_priv(dev);
	static char pin_name[5];

	snprintf(pin_name, sizeof(pin_name), "P%c%d",
		 pin_selector / SUNXI_GPIOS_PER_BANK + desc->first_bank + 'A',
		 pin_selector % SUNXI_GPIOS_PER_BANK);

	return pin_name;
}

static int sunxi_pinctrl_get_functions_count(struct udevice *dev)
{
	const struct sunxi_pinctrl_desc *desc = dev_get_priv(dev);

	return desc->num_functions;
}

static const char *sunxi_pinctrl_get_function_name(struct udevice *dev,
						   unsigned func_selector)
{
	const struct sunxi_pinctrl_desc *desc = dev_get_priv(dev);

	return desc->functions[func_selector].name;
}

static int sunxi_pinctrl_pinmux_set(struct udevice *dev, unsigned pin_selector,
				    unsigned func_selector)
{
	const struct sunxi_pinctrl_desc *desc = dev_get_priv(dev);
	struct sunxi_pinctrl_plat *plat = dev_get_plat(dev);
	int bank = pin_selector / SUNXI_GPIOS_PER_BANK;
	int pin	 = pin_selector % SUNXI_GPIOS_PER_BANK;

	debug("set mux: %-4s => %s (%d)\n",
	      sunxi_pinctrl_get_pin_name(dev, pin_selector),
	      sunxi_pinctrl_get_function_name(dev, func_selector),
	      desc->functions[func_selector].mux);

	sunxi_gpio_set_cfgbank(plat->base + bank, pin,
			       desc->functions[func_selector].mux);

	return 0;
}

static const struct pinconf_param sunxi_pinctrl_pinconf_params[] = {
	{ "bias-disable",	PIN_CONFIG_BIAS_DISABLE,	 0 },
	{ "bias-pull-down",	PIN_CONFIG_BIAS_PULL_DOWN,	 2 },
	{ "bias-pull-up",	PIN_CONFIG_BIAS_PULL_UP,	 1 },
	{ "drive-strength",	PIN_CONFIG_DRIVE_STRENGTH,	10 },
};

static int sunxi_pinctrl_pinconf_set_pull(struct sunxi_pinctrl_plat *plat,
					  unsigned bank, unsigned pin,
					  unsigned bias)
{
	struct sunxi_gpio *regs = &plat->base[bank];

	sunxi_gpio_set_pull_bank(regs, pin, bias);

	return 0;
}

static int sunxi_pinctrl_pinconf_set_drive(struct sunxi_pinctrl_plat *plat,
					   unsigned bank, unsigned pin,
					   unsigned drive)
{
	struct sunxi_gpio *regs = &plat->base[bank];

	if (drive < 10 || drive > 40)
		return -EINVAL;

	/* Convert mA to the register value, rounding down. */
	sunxi_gpio_set_drv_bank(regs, pin, drive / 10 - 1);

	return 0;
}

static int sunxi_pinctrl_pinconf_set(struct udevice *dev, unsigned pin_selector,
				     unsigned param, unsigned val)
{
	struct sunxi_pinctrl_plat *plat = dev_get_plat(dev);
	int bank = pin_selector / SUNXI_GPIOS_PER_BANK;
	int pin  = pin_selector % SUNXI_GPIOS_PER_BANK;

	switch (param) {
	case PIN_CONFIG_BIAS_DISABLE:
	case PIN_CONFIG_BIAS_PULL_DOWN:
	case PIN_CONFIG_BIAS_PULL_UP:
		return sunxi_pinctrl_pinconf_set_pull(plat, bank, pin, val);
	case PIN_CONFIG_DRIVE_STRENGTH:
		return sunxi_pinctrl_pinconf_set_drive(plat, bank, pin, val);
	}

	return -EINVAL;
}

static int sunxi_pinctrl_get_pin_muxing(struct udevice *dev,
					unsigned pin_selector,
					char *buf, int size)
{
	struct sunxi_pinctrl_plat *plat = dev_get_plat(dev);
	int bank = pin_selector / SUNXI_GPIOS_PER_BANK;
	int pin	 = pin_selector % SUNXI_GPIOS_PER_BANK;
	int mux  = sunxi_gpio_get_cfgbank(plat->base + bank, pin);

	switch (mux) {
	case SUNXI_GPIO_INPUT:
		strlcpy(buf, "gpio in", size);
		break;
	case SUNXI_GPIO_OUTPUT:
		strlcpy(buf, "gpio out", size);
		break;
	case SUNXI_GPIO_DISABLE:
		strlcpy(buf, "disabled", size);
		break;
	default:
		snprintf(buf, size, "function %d", mux);
		break;
	}

	return 0;
}

static const struct pinctrl_ops sunxi_pinctrl_ops = {
	.get_pins_count		= sunxi_pinctrl_get_pins_count,
	.get_pin_name		= sunxi_pinctrl_get_pin_name,
	.get_functions_count	= sunxi_pinctrl_get_functions_count,
	.get_function_name	= sunxi_pinctrl_get_function_name,
	.pinmux_set		= sunxi_pinctrl_pinmux_set,
	.pinconf_num_params	= ARRAY_SIZE(sunxi_pinctrl_pinconf_params),
	.pinconf_params		= sunxi_pinctrl_pinconf_params,
	.pinconf_set		= sunxi_pinctrl_pinconf_set,
	.set_state		= pinctrl_generic_set_state,
	.get_pin_muxing		= sunxi_pinctrl_get_pin_muxing,
};

static int sunxi_pinctrl_bind(struct udevice *dev)
{
	struct sunxi_pinctrl_plat *plat = dev_get_plat(dev);
	struct sunxi_pinctrl_desc *desc;
	struct sunxi_gpio_plat *gpio_plat;
	struct udevice *gpio_dev;
	int i, ret;

	desc = (void *)dev_get_driver_data(dev);
	if (!desc)
		return -EINVAL;
	dev_set_priv(dev, desc);

	plat->base = dev_read_addr_ptr(dev);

	ret = device_bind_driver_to_node(dev, "gpio_sunxi", dev->name,
					 dev_ofnode(dev), &gpio_dev);
	if (ret)
		return ret;

	for (i = 0; i < desc->num_banks; ++i) {
		gpio_plat = malloc(sizeof(*gpio_plat));
		if (!gpio_plat)
			return -ENOMEM;

		gpio_plat->regs = plat->base + i;
		gpio_plat->bank_name[0] = 'P';
		gpio_plat->bank_name[1] = 'A' + desc->first_bank + i;
		gpio_plat->bank_name[2] = '\0';

		ret = device_bind(gpio_dev, DM_DRIVER_REF(gpio_sunxi),
				  gpio_plat->bank_name, gpio_plat,
				  ofnode_null(), NULL);
		if (ret)
			return ret;
	}

	return 0;
}

static const struct udevice_id sunxi_pinctrl_ids[] = {
#if IS_ENABLED(CONFIG_PINCTRL_SUN4I_A10)
	{
		.compatible = "allwinner,sun4i-a10-pinctrl",
		.data = (ulong)&sun4i_a10_pinctrl_desc,
	},
#endif
#if IS_ENABLED(CONFIG_PINCTRL_SUN5I_A13)
	{
		.compatible = "allwinner,sun5i-a10s-pinctrl",
		.data = (ulong)&sun5i_a13_pinctrl_desc,
	},
	{
		.compatible = "allwinner,sun5i-a13-pinctrl",
		.data = (ulong)&sun5i_a13_pinctrl_desc,
	},
#endif
#if IS_ENABLED(CONFIG_PINCTRL_SUN6I_A31)
	{
		.compatible = "allwinner,sun6i-a31-pinctrl",
		.data = (ulong)&sun6i_a31_pinctrl_desc,
	},
	{
		.compatible = "allwinner,sun6i-a31s-pinctrl",
		.data = (ulong)&sun6i_a31_pinctrl_desc,
	},
#endif
#if IS_ENABLED(CONFIG_PINCTRL_SUN6I_A31_R)
	{
		.compatible = "allwinner,sun6i-a31-r-pinctrl",
		.data = (ulong)&sun6i_a31_r_pinctrl_desc,
	},
#endif
#if IS_ENABLED(CONFIG_PINCTRL_SUN7I_A20)
	{
		.compatible = "allwinner,sun7i-a20-pinctrl",
		.data = (ulong)&sun7i_a20_pinctrl_desc,
	},
	{
		.compatible = "allwinner,sun8i-r40-pinctrl",
		.data = (ulong)&sun7i_a20_pinctrl_desc,
	},
#endif
#if IS_ENABLED(CONFIG_PINCTRL_SUN8I_A23)
	{
		.compatible = "allwinner,sun8i-a23-pinctrl",
		.data = (ulong)&sun8i_a23_pinctrl_desc,
	},
#endif
#if IS_ENABLED(CONFIG_PINCTRL_SUN8I_A23_R)
	{
		.compatible = "allwinner,sun8i-a23-r-pinctrl",
		.data = (ulong)&sun8i_a23_r_pinctrl_desc,
	},
#endif
#if IS_ENABLED(CONFIG_PINCTRL_SUN8I_A33)
	{
		.compatible = "allwinner,sun8i-a33-pinctrl",
		.data = (ulong)&sun8i_a33_pinctrl_desc,
	},
#endif
#if IS_ENABLED(CONFIG_PINCTRL_SUN8I_A83T)
	{
		.compatible = "allwinner,sun8i-a83t-pinctrl",
		.data = (ulong)&sun8i_a83t_pinctrl_desc,
	},
#endif
#if IS_ENABLED(CONFIG_PINCTRL_SUN8I_A83T_R)
	{
		.compatible = "allwinner,sun8i-a83t-r-pinctrl",
		.data = (ulong)&sun8i_a83t_r_pinctrl_desc,
	},
#endif
#if IS_ENABLED(CONFIG_PINCTRL_SUN8I_H3)
	{
		.compatible = "allwinner,sun8i-h3-pinctrl",
		.data = (ulong)&sun8i_h3_pinctrl_desc,
	},
#endif
#if IS_ENABLED(CONFIG_PINCTRL_SUN8I_H3_R)
	{
		.compatible = "allwinner,sun8i-h3-r-pinctrl",
		.data = (ulong)&sun8i_h3_r_pinctrl_desc,
	},
#endif
#if IS_ENABLED(CONFIG_PINCTRL_SUN8I_V3S)
	{
		.compatible = "allwinner,sun8i-v3-pinctrl",
		.data = (ulong)&sun8i_v3s_pinctrl_desc,
	},
	{
		.compatible = "allwinner,sun8i-v3s-pinctrl",
		.data = (ulong)&sun8i_v3s_pinctrl_desc,
	},
#endif
#if IS_ENABLED(CONFIG_PINCTRL_SUN9I_A80)
	{
		.compatible = "allwinner,sun9i-a80-pinctrl",
		.data = (ulong)&sun9i_a80_pinctrl_desc,
	},
#endif
#if IS_ENABLED(CONFIG_PINCTRL_SUN9I_A80_R)
	{
		.compatible = "allwinner,sun9i-a80-r-pinctrl",
		.data = (ulong)&sun9i_a80_r_pinctrl_desc,
	},
#endif
#if IS_ENABLED(CONFIG_PINCTRL_SUN20I_D1)
	{
		.compatible = "allwinner,sun20i-d1-pinctrl",
		.data = (ulong)&sun20i_d1_pinctrl_desc,
	},
#endif
#if IS_ENABLED(CONFIG_PINCTRL_SUN50I_A64)
	{
		.compatible = "allwinner,sun50i-a64-pinctrl",
		.data = (ulong)&sun50i_a64_pinctrl_desc,
	},
#endif
#if IS_ENABLED(CONFIG_PINCTRL_SUN50I_A64_R)
	{
		.compatible = "allwinner,sun50i-a64-r-pinctrl",
		.data = (ulong)&sun50i_a64_r_pinctrl_desc,
	},
#endif
#if IS_ENABLED(CONFIG_PINCTRL_SUN50I_H5)
	{
		.compatible = "allwinner,sun50i-h5-pinctrl",
		.data = (ulong)&sun50i_h5_pinctrl_desc,
	},
#endif
#if IS_ENABLED(CONFIG_PINCTRL_SUN50I_H6)
	{
		.compatible = "allwinner,sun50i-h6-pinctrl",
		.data = (ulong)&sun50i_h6_pinctrl_desc,
	},
#endif
#if IS_ENABLED(CONFIG_PINCTRL_SUN50I_H6_R)
	{
		.compatible = "allwinner,sun50i-h6-r-pinctrl",
		.data = (ulong)&sun50i_h6_r_pinctrl_desc,
	},
#endif
#if IS_ENABLED(CONFIG_PINCTRL_SUN50I_H616)
	{
		.compatible = "allwinner,sun50i-h616-pinctrl",
		.data = (ulong)&sun50i_h616_pinctrl_desc,
	},
#endif
#if IS_ENABLED(CONFIG_PINCTRL_SUN50I_H616_R)
	{
		.compatible = "allwinner,sun50i-h616-r-pinctrl",
		.data = (ulong)&sun50i_h616_r_pinctrl_desc,
	},
#endif
	{ }
};

U_BOOT_DRIVER(sunxi_pinctrl) = {
	.name		= "sunxi-pinctrl",
	.id		= UCLASS_PINCTRL,
	.of_match	= sunxi_pinctrl_ids,
	.bind		= sunxi_pinctrl_bind,
	.plat_auto	= sizeof(struct sunxi_pinctrl_plat),
	.ops		= &sunxi_pinctrl_ops,
};
