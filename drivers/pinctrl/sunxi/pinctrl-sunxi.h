// SPDX-License-Identifier: GPL-2.0

//#include <asm/gpio.h>
#include <common.h>
#include "../../../arch/arm/include/asm/arch-sunxi/gpio.h"

/* "gpio_out" including the null terminator */
#define FUNCTION_NAME_MAX		9

struct sunxi_pinctrl_function {
	const char	name[FUNCTION_NAME_MAX];
	u8		mux;
};

struct sunxi_pinctrl_desc {
	const struct sunxi_pinctrl_function	*functions;
	u8					num_functions;
	u8					first_bank;
	u8					num_banks;
};

extern const struct sunxi_pinctrl_desc sun4i_a10_pinctrl_desc;
extern const struct sunxi_pinctrl_desc sun5i_a13_pinctrl_desc;
extern const struct sunxi_pinctrl_desc sun6i_a31_pinctrl_desc;
extern const struct sunxi_pinctrl_desc sun6i_a31_r_pinctrl_desc;
extern const struct sunxi_pinctrl_desc sun7i_a20_pinctrl_desc;
extern const struct sunxi_pinctrl_desc sun8i_a23_pinctrl_desc;
extern const struct sunxi_pinctrl_desc sun8i_a23_r_pinctrl_desc;
extern const struct sunxi_pinctrl_desc sun8i_a33_pinctrl_desc;
extern const struct sunxi_pinctrl_desc sun8i_a83t_pinctrl_desc;
extern const struct sunxi_pinctrl_desc sun8i_a83t_r_pinctrl_desc;
extern const struct sunxi_pinctrl_desc sun8i_h3_pinctrl_desc;
extern const struct sunxi_pinctrl_desc sun8i_h3_r_pinctrl_desc;
extern const struct sunxi_pinctrl_desc sun8i_v3s_pinctrl_desc;
extern const struct sunxi_pinctrl_desc sun9i_a80_pinctrl_desc;
extern const struct sunxi_pinctrl_desc sun9i_a80_r_pinctrl_desc;
extern const struct sunxi_pinctrl_desc sun20i_d1_pinctrl_desc;
extern const struct sunxi_pinctrl_desc sun50i_a64_pinctrl_desc;
extern const struct sunxi_pinctrl_desc sun50i_a64_r_pinctrl_desc;
extern const struct sunxi_pinctrl_desc sun50i_h5_pinctrl_desc;
extern const struct sunxi_pinctrl_desc sun50i_h6_pinctrl_desc;
extern const struct sunxi_pinctrl_desc sun50i_h6_r_pinctrl_desc;
extern const struct sunxi_pinctrl_desc sun50i_h616_pinctrl_desc;
extern const struct sunxi_pinctrl_desc sun50i_h616_r_pinctrl_desc;
