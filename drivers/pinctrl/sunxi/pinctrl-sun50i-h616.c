// SPDX-License-Identifier: GPL-2.0

#include "pinctrl-sunxi.h"

static const struct sunxi_pinctrl_function sun50i_h616_pinctrl_functions[] = {
	{ "emac0",	2 },	/* PI0-PI16 */
	{ "gpio_in",	0 },
	{ "gpio_out",	1 },
	{ "mmc0",	2 },	/* PF0-PF5 */
	{ "mmc1",	2 },	/* PG0-PG5 */
	{ "mmc2",	3 },	/* PC0-PC16 */
	{ "spi0",	4 },	/* PC0-PC7, PC15-PC16 */
#if IS_ENABLED(CONFIG_UART0_PORT_F)
	{ "uart0",	3 },	/* PF2-PF4 */
#else
	{ "uart0",	2 },	/* PH0-PH1 */
#endif
	{ "uart1",	2 },	/* PG6-PG7 */
};

const struct sunxi_pinctrl_desc sun50i_h616_pinctrl_desc = {
	.functions	= sun50i_h616_pinctrl_functions,
	.num_functions	= ARRAY_SIZE(sun50i_h616_pinctrl_functions),
	.first_bank	= SUNXI_GPIO_A,
	.num_banks	= 9,
};