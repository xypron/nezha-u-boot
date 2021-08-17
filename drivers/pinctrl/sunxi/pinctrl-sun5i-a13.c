// SPDX-License-Identifier: GPL-2.0

#include "pinctrl-sunxi.h"

static const struct sunxi_pinctrl_function sun5i_a13_pinctrl_functions[] = {
	{ "gpio_in",	0 },
	{ "gpio_out",	1 },
};

const struct sunxi_pinctrl_desc sun5i_a13_pinctrl_desc = {
	.functions	= sun5i_a13_pinctrl_functions,
	.num_functions	= ARRAY_SIZE(sun5i_a13_pinctrl_functions),
	.first_bank	= SUNXI_GPIO_A,
	.num_banks	= 7,
};
