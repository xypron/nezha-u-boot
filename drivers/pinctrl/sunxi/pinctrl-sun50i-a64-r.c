// SPDX-License-Identifier: GPL-2.0

#include <common.h>

#include "pinctrl-sunxi.h"

static const struct sunxi_pinctrl_function sun50i_a64_r_pinctrl_functions[] = {
	{ "gpio_in",	0 },
	{ "gpio_out",	1 },
	{ "s_rsb",	2 },	/* PL0-PL1 */
	{ "s_i2c",	3 },	/* PL0-PL1 */
};

const struct sunxi_pinctrl_desc sun50i_a64_r_pinctrl_desc = {
	.functions	= sun50i_a64_r_pinctrl_functions,
	.num_functions	= ARRAY_SIZE(sun50i_a64_r_pinctrl_functions),
	.first_bank	= SUNXI_GPIO_L,
	.num_banks	= 1,
};
