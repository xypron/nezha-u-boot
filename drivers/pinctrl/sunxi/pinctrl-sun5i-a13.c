// SPDX-License-Identifier: GPL-2.0

#include "pinctrl-sunxi.h"

static const struct sunxi_pinctrl_function sun5i_a13_pinctrl_functions[] = {
	{ "emac",	2 },	/* PA0-PA17 */
	{ "gpio_in",	0 },
	{ "gpio_out",	1 },
	{ "i2c0",	2 },	/* PB0-PB1 */
	{ "i2c1",	2 },	/* PB15-PB16 */
	{ "mmc0",	2 },	/* PF0-PF5 */
	{ "mmc1",	2 },	/* PG3-PG8 */
	{ "mmc2",	3 },	/* PC6-PC15 */
#if IS_ENABLED(CONFIG_UART0_PORT_F)
	{ "uart0",	4 },	/* PF2-PF4 */
#else
	{ "uart0",	2 },	/* PB19-PB20 */
#endif
	{ "uart1",	4 },	/* PG3-PG4 */
};

const struct sunxi_pinctrl_desc sun5i_a13_pinctrl_desc = {
	.functions	= sun5i_a13_pinctrl_functions,
	.num_functions	= ARRAY_SIZE(sun5i_a13_pinctrl_functions),
	.first_bank	= SUNXI_GPIO_A,
	.num_banks	= 7,
};
