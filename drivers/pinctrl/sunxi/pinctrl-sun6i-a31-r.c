// SPDX-License-Identifier: GPL-2.0

#include "pinctrl-sunxi.h"

static const struct sunxi_pinctrl_function sun6i_a31_r_pinctrl_functions[] = {
	{ "gpio_in",	0 },
	{ "gpio_out",	1 },
};

const struct sunxi_pinctrl_desc sun6i_a31_r_pinctrl_desc = {
	.functions	= sun6i_a31_r_pinctrl_functions,
	.num_functions	= ARRAY_SIZE(sun6i_a31_r_pinctrl_functions),
	.first_bank	= SUNXI_GPIO_L,
	.num_banks	= 2,
};
