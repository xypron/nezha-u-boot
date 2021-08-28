// SPDX-License-Identifier: GPL-2.0

#include "pinctrl-sunxi.h"

static const struct sunxi_pinctrl_function sun9i_a80_pinctrl_functions[] = {
	{ "gpio_in",	0 },
	{ "gpio_out",	1 },
#if IS_ENABLED(CONFIG_UART0_PORT_F)
	{ "uart0",	4 },	/* PF2-PF4 */
#else
	{ "uart0",	2 },	/* PH12-PH13 */
#endif
};

const struct sunxi_pinctrl_desc sun9i_a80_pinctrl_desc = {
	.functions	= sun9i_a80_pinctrl_functions,
	.num_functions	= ARRAY_SIZE(sun9i_a80_pinctrl_functions),
	.first_bank	= SUNXI_GPIO_A,
	.num_banks	= 8,
};
