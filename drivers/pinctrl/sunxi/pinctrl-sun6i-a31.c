// SPDX-License-Identifier: GPL-2.0

#include "pinctrl-sunxi.h"

static const struct sunxi_pinctrl_function sun6i_a31_pinctrl_functions[] = {
	{ "gmac",	2 },	/* PA0-PA27 */
	{ "gpio_in",	0 },
	{ "gpio_out",	1 },
	{ "i2c0",	2 },	/* PH14-PH15 */
	{ "i2c1",	2 },	/* PH16-PH17 */
	{ "mmc0",	2 },	/* PF0-PF5 */
	{ "mmc1",	2 },	/* PG0-PG5 */
	{ "mmc2",	3 },	/* PC6-PC15, PC24 */
	{ "mmc3",	4 },	/* PC6-PC15, PC24 */
	{ "spi0",	3 },	/* PC0-PC2, PC27 */
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