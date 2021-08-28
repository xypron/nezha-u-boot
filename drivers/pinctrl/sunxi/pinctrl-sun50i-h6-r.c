// SPDX-License-Identifier: GPL-2.0

#include "pinctrl-sunxi.h"

static const struct sunxi_pinctrl_function sun50i_h6_r_pinctrl_functions[] = {
	{ "gpio_in",	0 },
	{ "gpio_out",	1 },
	{ "s_uart",	2 },	/* PL2-PL3 */
};

const struct sunxi_pinctrl_desc sun50i_h6_r_pinctrl_desc = {
	.functions	= sun50i_h6_r_pinctrl_functions,
	.num_functions	= ARRAY_SIZE(sun50i_h6_r_pinctrl_functions),
	.first_bank	= SUNXI_GPIO_L,
	.num_banks	= 2,
};
