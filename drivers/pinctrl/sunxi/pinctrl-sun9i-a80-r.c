// SPDX-License-Identifier: GPL-2.0

#include "pinctrl-sunxi.h"

static const struct sunxi_pinctrl_function sun9i_a80_r_pinctrl_functions[] = {
	{ "gpio_in",	0 },
	{ "gpio_out",	1 },
	{ "s_uart",	3 },	/* PL0-PL1 */
};

const struct sunxi_pinctrl_desc sun9i_a80_r_pinctrl_desc = {
	.functions	= sun9i_a80_r_pinctrl_functions,
	.num_functions	= ARRAY_SIZE(sun9i_a80_r_pinctrl_functions),
	.first_bank	= SUNXI_GPIO_L,
	.num_banks	= 3,
};
