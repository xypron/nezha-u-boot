// SPDX-License-Identifier: GPL-2.0

#include "pinctrl-sunxi.h"

static const struct sunxi_pinctrl_function sun6i_a31_pinctrl_functions[] = {
	{ "gmac",	2 },	/* PA0-PA27 */
	{ "gpio_in",	0 },
	{ "gpio_out",	1 },
#if IS_ENABLED(CONFIG_UART0_PORT_F)
	{ "uart0",	3 },	/* PF2-PF4 */
#else
	{ "uart0",	2 },	/* PH20-PH21 */
#endif
};

const struct sunxi_pinctrl_desc sun6i_a31_pinctrl_desc = {
	.functions	= sun6i_a31_pinctrl_functions,
	.num_functions	= ARRAY_SIZE(sun6i_a31_pinctrl_functions),
	.first_bank	= SUNXI_GPIO_A,
	.num_banks	= 8,
};
