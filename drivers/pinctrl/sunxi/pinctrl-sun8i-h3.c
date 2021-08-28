// SPDX-License-Identifier: GPL-2.0

#include "pinctrl-sunxi.h"

static const struct sunxi_pinctrl_function sun8i_h3_pinctrl_functions[] = {
	{ "emac",	2 },	/* PD0-PD17 */
	{ "gpio_in",	0 },
	{ "gpio_out",	1 },
	{ "i2c0",	2 },	/* PA11-PA12 */
	{ "i2c1",	3 },	/* PA18-PA19 */
#if IS_ENABLED(CONFIG_UART0_PORT_F)
	{ "uart0",	3 },	/* PF2-PF4 */
#else
	{ "uart0",	2 },	/* PA4-PA5 */
#endif
	{ "uart1",	2 },	/* PG6-PG7 */
	{ "uart2",	2 },	/* PA0-PA1 */
};

const struct sunxi_pinctrl_desc sun8i_h3_pinctrl_desc = {
	.functions	= sun8i_h3_pinctrl_functions,
	.num_functions	= ARRAY_SIZE(sun8i_h3_pinctrl_functions),
	.first_bank	= SUNXI_GPIO_A,
	.num_banks	= 7,
};
