// SPDX-License-Identifier: GPL-2.0

#include <common.h>

#include "pinctrl-sunxi.h"

const struct sunxi_pinctrl_desc sun50i_h5_pinctrl_desc = {
	.first_bank	= SUNXI_GPIO_A,
	.num_banks	= 7,
};
