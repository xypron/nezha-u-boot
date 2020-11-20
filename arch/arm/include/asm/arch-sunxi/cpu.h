/* SPDX-License-Identifier: GPL-2.0+ */
/*
 * (C) Copyright 2015 Hans de Goede <hdegoede@redhat.com>
 */

#ifndef _SUNXI_CPU_H
#define _SUNXI_CPU_H

#if defined(CONFIG_MACH_SUN9I)
#include <asm/arch/cpu_sun9i.h>
#elif defined(CONFIG_MACH_SUN50I_H6)
#include <asm/arch/cpu_sun50i_h6.h>
#else
#include <asm/arch/cpu_sun4i.h>
#endif

#if defined(CONFIG_MACH_SUN4I)
#define SUNXI_SRAM_A2_BASE	0x00004000
#elif defined(CONFIG_MACH_SUN6I) || \
      defined(CONFIG_MACH_SUN8I) || \
      defined(CONFIG_MACH_SUN50I) || \
      defined(CONFIG_MACH_SUN50I_H5)
#define SUNXI_SRAM_A2_BASE	0x00040000
#endif

#define SOCID_A64	0x1689
#define SOCID_H3	0x1680
#define SOCID_V3S	0x1681
#define SOCID_H5	0x1718
#define SOCID_R40	0x1701

#endif /* _SUNXI_CPU_H */
