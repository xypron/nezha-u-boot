// SPDX-License-Identifier: GPL-2.0

#include "pinctrl-sunxi.h"

static const struct sunxi_pinctrl_function sun8i_v3s_pinctrl_functions[] = {
	{ "gpio_in",	0 },
	{ "gpio_out",	1 },
#if IS_ENABLED(CONFIG_UART0_PORT_F)
	{ "uart0",	3 },	/* PF2-PF4 */
#else
	{ "uart0",	3 },	/* PB8-PB9 */
#endif
	{ "uart1",	2 },	/* PG6-PG7 */
	{ "uart2",	2 },	/* PB0-PB1 */
};

const struct sunxi_pinctrl_desc sun8i_v3s_pinctrl_desc = {
	.functions	= sun8i_v3s_pinctrl_functions,
	.num_functions	= ARRAY_SIZE(sun8i_v3s_pinctrl_functions),
	.first_bank	= SUNXI_GPIO_A,
	.num_banks	= 7,
};
