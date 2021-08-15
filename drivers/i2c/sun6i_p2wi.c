// SPDX-License-Identifier: GPL-2.0+

#include <axp_pmic.h>
#include <dm.h>
#include <i2c.h>
#include <asm/arch/p2wi.h>

#if CONFIG_IS_ENABLED(DM_I2C)

static int sun6i_p2wi_xfer(struct udevice *bus, struct i2c_msg *msg, int nmsgs)
{
	/* The hardware only supports SMBus-style transfers. */
	if (nmsgs == 2 && msg[1].flags == I2C_M_RD && msg[1].len == 1)
		return p2wi_read(msg[0].buf[0], msg[1].buf);

	if (nmsgs == 1 && msg[0].len == 2)
		return p2wi_write(msg[0].buf[0], msg[0].buf[1]);

	return -EINVAL;
}

static int sun6i_p2wi_probe_chip(struct udevice *bus, uint chip_addr,
				 uint chip_flags)
{
	return p2wi_change_to_p2wi_mode(chip_addr,
					AXP_PMIC_MODE_REG,
					AXP_PMIC_MODE_P2WI);
}

static int sun6i_p2wi_probe(struct udevice *bus)
{
	p2wi_init();

	return 0;
}

static int sun6i_p2wi_child_pre_probe(struct udevice *child)
{
	struct dm_i2c_chip *chip = dev_get_parent_plat(child);

	/* Ensure each transfer is for a single register. */
	chip->flags |= DM_I2C_CHIP_RD_ADDRESS | DM_I2C_CHIP_WR_ADDRESS;

	return 0;
}

static const struct dm_i2c_ops sun6i_p2wi_ops = {
	.xfer		= sun6i_p2wi_xfer,
	.probe_chip	= sun6i_p2wi_probe_chip,
};

static const struct udevice_id sun6i_p2wi_ids[] = {
	{ .compatible = "allwinner,sun6i-a31-p2wi" },
	{ /* sentinel */ }
};

U_BOOT_DRIVER(sun6i_p2wi) = {
	.name			= "sun6i_p2wi",
	.id			= UCLASS_I2C,
	.of_match		= sun6i_p2wi_ids,
	.probe			= sun6i_p2wi_probe,
	.child_pre_probe	= sun6i_p2wi_child_pre_probe,
	.ops			= &sun6i_p2wi_ops,
};

#endif /* CONFIG_IS_ENABLED(DM_I2C) */
