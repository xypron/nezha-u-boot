# SPDX-License-Identifier: GPL-2.0+

dtb-$(CONFIG_TARGET_AX25_AE350) += ae350_32.dtb ae350_64.dtb
dtb-$(CONFIG_TARGET_MICROCHIP_ICICLE) += microchip-mpfs-icicle-kit.dtb
dtb-$(CONFIG_TARGET_QEMU_VIRT) += qemu-virt32.dtb qemu-virt64.dtb
dtb-$(CONFIG_TARGET_OPENPITON_RISCV64) += openpiton-riscv64.dtb
dtb-$(CONFIG_TARGET_SIFIVE_UNLEASHED) += hifive-unleashed-a00.dtb
dtb-$(CONFIG_TARGET_SIFIVE_UNMATCHED) += hifive-unmatched-a00.dtb
dtb-$(CONFIG_TARGET_SIPEED_MAIX) += k210-maix-bit.dtb
dtb-$(CONFIG_TARGET_SUN20I_D1) += sun20i-d1-clockworkpi-v3.14.dtb
dtb-$(CONFIG_TARGET_SUN20I_D1) += sun20i-d1-devterm-v3.14.dtb
dtb-$(CONFIG_TARGET_SUN20I_D1) += sun20i-d1-dongshan-nezha-stu.dtb
dtb-$(CONFIG_TARGET_SUN20I_D1) += sun20i-d1-lichee-rv-86-panel-480p.dtb
dtb-$(CONFIG_TARGET_SUN20I_D1) += sun20i-d1-lichee-rv-86-panel-720p.dtb
dtb-$(CONFIG_TARGET_SUN20I_D1) += sun20i-d1-lichee-rv-dock.dtb
dtb-$(CONFIG_TARGET_SUN20I_D1) += sun20i-d1-lichee-rv.dtb
dtb-$(CONFIG_TARGET_SUN20I_D1) += sun20i-d1-mangopi-mq-pro.dtb
dtb-$(CONFIG_TARGET_SUN20I_D1) += sun20i-d1-nezha.dtb

include $(srctree)/scripts/Makefile.dts

targets += $(dtb-y)

DTC_FLAGS += -R 4 -p 0x1000

PHONY += dtbs
dtbs: $(addprefix $(obj)/, $(dtb-y))
	@:

clean-files := *.dtb
