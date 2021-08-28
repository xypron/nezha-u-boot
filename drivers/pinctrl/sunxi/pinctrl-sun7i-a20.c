// SPDX-License-Identifier: GPL-2.0

#include "pinctrl-sunxi.h"

static const struct sunxi_pinctrl_function sun7i_a20_pinctrl_functions[] = {
	{ "emac",	2 },	/* PA0-PA17 */
	{ "gmac",	5 },	/* PA0-PA17 */
	{ "gpio_in",	0 },
	{ "gpio_out",	1 },
#if IS_ENABLED(CONFIG_UART0_PORT_F)
	{ "uart0",	4 },	/* PF2-PF4 */
#else
	{ "uart0",	2 },	/* PB22-PB23 */
#endif
};

const struct sunxi_pinctrl_desc sun7i_a20_pinctrl_desc = {
	.functions	= sun7i_a20_pinctrl_functions,
	.num_functions	= ARRAY_SIZE(sun7i_a20_pinctrl_functions),
	.first_bank	= SUNXI_GPIO_A,
	.num_banks	= 9,
};
