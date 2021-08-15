// SPDX-License-Identifier: GPL-2.0+

#include <axp_pmic.h>
#include <dm.h>
#include <i2c.h>
#include <asm/arch/rsb.h>

#if CONFIG_IS_ENABLED(DM_I2C)

/*
 * The mapping from hardware address to runtime address is fixed, and shared
 * among all RSB drivers. See the comment in drivers/bus/sunxi-rsb.c in Linux.
 */
static int sun8i_rsb_get_runtime_address(u16 device_addr)
{
	if (device_addr == AXP_PMIC_PRI_DEVICE_ADDR)
		return AXP_PMIC_PRI_RUNTIME_ADDR;
	if (device_addr == AXP_PMIC_SEC_DEVICE_ADDR)
		return AXP_PMIC_SEC_RUNTIME_ADDR;

	return -ENOTSUPP;
}

static int sun8i_rsb_xfer(struct udevice *bus, struct i2c_msg *msg, int nmsgs)
{
	int rtaddr = sun8i_rsb_get_runtime_address(msg->addr);

	if (rtaddr < 0)
		return rtaddr;

	/* The hardware only supports SMBus-style transfers. */
	if (nmsgs == 2 && msg[1].flags == I2C_M_RD && msg[1].len == 1)
		return rsb_read(rtaddr, msg[0].buf[0], msg[1].buf);

	if (nmsgs == 1 && msg[0].len == 2)
		return rsb_write(rtaddr, msg[0].buf[0], msg[0].buf[1]);

	return -EINVAL;
}

static int sun8i_rsb_probe_chip(struct udevice *bus, uint chip_addr,
				uint chip_flags)
{
	int rtaddr = sun8i_rsb_get_runtime_address(chip_addr);

	if (rtaddr < 0)
		return rtaddr;

	return rsb_set_device_address(chip_addr, rtaddr);
}

static int sun8i_rsb_probe(struct udevice *bus)
{
	return rsb_init();
}

static int sun8i_rsb_child_pre_probe(struct udevice *child)
{
	struct dm_i2c_chip *chip = dev_get_parent_plat(child);

	/* Ensure each transfer is for a single register. */
	chip->flags |= DM_I2C_CHIP_RD_ADDRESS | DM_I2C_CHIP_WR_ADDRESS;

	return 0;
}

static const struct dm_i2c_ops sun8i_rsb_ops = {
	.xfer		= sun8i_rsb_xfer,
	.probe_chip	= sun8i_rsb_probe_chip,
};

static const struct udevice_id sun8i_rsb_ids[] = {
	{ .compatible = "allwinner,sun8i-a23-rsb" },
	{ /* sentinel */ }
};

U_BOOT_DRIVER(sun8i_rsb) = {
	.name			= "sun8i_rsb",
	.id			= UCLASS_I2C,
	.of_match		= sun8i_rsb_ids,
	.probe			= sun8i_rsb_probe,
	.child_pre_probe	= sun8i_rsb_child_pre_probe,
	.ops			= &sun8i_rsb_ops,
};

#endif /* CONFIG_IS_ENABLED(DM_I2C) */
