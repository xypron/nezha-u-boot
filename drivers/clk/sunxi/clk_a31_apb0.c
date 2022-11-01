// SPDX-License-Identifier: (GPL-2.0+ OR MIT)
/*
 * Copyright (C) Samuel Holland <samuel@sholland.org>
 */

#include <clk-uclass.h>
#include <dm.h>
#include <clk/sunxi.h>
#include <linux/bitops.h>

static struct ccu_clk_gate sun6i_apb0_gates[] = {
	[0]	= GATE(0x028, BIT(0)),
	[1]	= GATE(0x028, BIT(1)),
	[2]	= GATE(0x028, BIT(2)),
	[3]	= GATE(0x028, BIT(3)),
	[4]	= GATE(0x028, BIT(4)),
	[5]	= GATE(0x028, BIT(5)),
	[6]	= GATE(0x028, BIT(6)),
	[7]	= GATE(0x028, BIT(7)),
};

static struct ccu_reset sun6i_apb0_resets[] = {
	[0]	= RESET(0x0b0, BIT(0)),
	[1]	= RESET(0x0b0, BIT(1)),
	[2]	= RESET(0x0b0, BIT(2)),
	[3]	= RESET(0x0b0, BIT(3)),
	[4]	= RESET(0x0b0, BIT(4)),
	[5]	= RESET(0x0b0, BIT(5)),
	[6]	= RESET(0x0b0, BIT(6)),
	[7]	= RESET(0x0b0, BIT(7)),
};

const struct ccu_desc sun6i_apb0_clk_desc = {
	.gates = sun6i_apb0_gates,
	.resets = sun6i_apb0_resets,
	.num_gates = ARRAY_SIZE(sun6i_apb0_gates),
	.num_resets = ARRAY_SIZE(sun6i_apb0_resets),
};

static int sun6i_apb0_of_to_plat(struct udevice *dev)
{
	struct ccu_plat *plat = dev_get_plat(dev);

	plat->base = dev_read_addr_ptr(dev->parent);
	if (!plat->base)
		return -ENOMEM;

	plat->desc = (const struct ccu_desc *)dev_get_driver_data(dev);
	if (!plat->desc)
		return -EINVAL;

	return 0;
}

static const struct udevice_id sun6i_apb0_clk_ids[] = {
	{ .compatible = "allwinner,sun6i-a31-apb0-gates-clk",
	  .data = (ulong)&sun6i_apb0_clk_desc },
	{ .compatible = "allwinner,sun8i-a23-apb0-gates-clk",
	  .data = (ulong)&sun6i_apb0_clk_desc },
	{ }
};

U_BOOT_DRIVER(sun6i_apb0_clk) = {
	.name		= "sun6i_apb0_clk",
	.id		= UCLASS_CLK,
	.of_match	= sun6i_apb0_clk_ids,
	.of_to_plat	= sun6i_apb0_of_to_plat,
	.plat_auto	= sizeof(struct ccu_plat),
	.ops		= &sunxi_clk_ops,
};

static const struct udevice_id sun6i_apb0_reset_ids[] = {
	{ .compatible = "allwinner,sun6i-a31-clock-reset",
	  .data = (ulong)&sun6i_apb0_clk_desc },
	{ }
};

U_BOOT_DRIVER(sun6i_apb0_reset) = {
	.name		= "sun6i_apb0_reset",
	.id		= UCLASS_RESET,
	.of_match	= sun6i_apb0_reset_ids,
	.of_to_plat	= sun6i_apb0_of_to_plat,
	.plat_auto	= sizeof(struct ccu_plat),
	.ops		= &sunxi_reset_ops,
};

static const struct udevice_id sun6i_prcm_mfd_ids[] = {
	{ .compatible = "allwinner,sun6i-a31-prcm" },
	{ .compatible = "allwinner,sun8i-a23-prcm" },
	{ }
};

U_BOOT_DRIVER(sun6i_prcm_mfd) = {
	.name		= "sun6i_prcm_mfd",
	.id		= UCLASS_SIMPLE_BUS,
	.of_match	= sun6i_prcm_mfd_ids,
};
