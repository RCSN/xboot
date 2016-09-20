#ifndef __RK3288_IRQ_H__
#define __RK3288_IRQ_H__

#ifdef __cplusplus
extern "C" {
#endif

#define RK3288_IRQ_HYPERVISOR_TIMER			(26)
#define RK3288_IRQ_VIRTUAL_TIMER			(27)
#define RK3288_IRQ_SECURE_PHYSICAL_TIMER	(29)
#define RK3288_IRQ_NONSECURE_PHYSICAL_TIMER	(30)

#define RK3288_IRQ_DMAC_BUS0				(32)
#define RK3288_IRQ_DMAC_BUS1				(33)
#define RK3288_IRQ_DMAC_PERI0				(34)
#define RK3288_IRQ_DMAC_PERI1				(35)
#define RK3288_IRQ_UPCTL0					(36)
#define RK3288_IRQ_UPCTL1					(37)
#define RK3288_IRQ_GPU_IRQJOB				(38)
#define RK3288_IRQ_GPU_IRQMMU				(39)
#define RK3288_IRQ_GPU_IRQGPU				(40)
#define RK3288_IRQ_VIDEO_ENCODER			(41)
#define RK3288_IRQ_VIDEO_DEECODER			(42)
#define RK3288_IRQ_VIDEO_MMU				(43)
#define RK3288_IRQ_HEVC						(44)
#define RK3288_IRQ_VIP						(45)
#define RK3288_IRQ_ISP						(46)
#define RK3288_IRQ_VOP_BIG					(47)
#define RK3288_IRQ_VOP_LIT					(48)
#define RK3288_IRQ_IEP						(49)
#define RK3288_IRQ_RGA						(50)
#define RK3288_IRQ_DSI0						(51)
#define RK3288_IRQ_DSI1						(52)
#define RK3288_IRQ_CSI0						(53)
#define RK3288_IRQ_CSI1						(54)
#define RK3288_IRQ_USBOTG					(55)
#define RK3288_IRQ_USBHOST0_EHCI			(56)
#define RK3288_IRQ_USBHOST1					(57)
#define RK3288_IRQ_HSIC						(58)
#define RK3288_IRQ_GMAC						(59)
#define RK3288_IRQ_GMAC_PMT					(60)
#define RK3288_IRQ_GPS						(61)
#define RK3288_IRQ_GPS_TIMER				(62)
#define RK3288_IRQ_TSI						(63)
#define RK3288_IRQ_SDMMC					(64)
#define RK3288_IRQ_SDIO0					(65)
#define RK3288_IRQ_SDIO1					(66)
#define RK3288_IRQ_EMMC						(67)
#define RK3288_IRQ_SARADC					(68)
#define RK3288_IRQ_TSADC					(69)
#define RK3288_IRQ_NANDC0					(70)
#define RK3288_IRQ_PERIMMU					(71)
#define RK3288_IRQ_NANDC1					(72)
#define RK3288_IRQ_USBHOST0_OHCI			(73)
#define RK3288_IRQ_TPS						(74)
#define RK3288_IRQ_SCR						(75)
#define RK3288_IRQ_SPI0						(76)
#define RK3288_IRQ_SPI1						(77)
#define RK3288_IRQ_SPI2						(78)
#define RK3288_IRQ_PS2C						(79)
#define RK3288_IRQ_CRYPTO					(80)
#define RK3288_IRQ_HOST_PULSE0				(81)
#define RK3288_IRQ_HOST_PULSE1				(82)
#define RK3288_IRQ_HOST0					(83)
#define RK3288_IRQ_HOST1					(84)
#define RK3288_IRQ_I2S						(85)
#define RK3288_IRQ_SPDIF					(86)
#define RK3288_IRQ_UART_BT					(87)
#define RK3288_IRQ_UART_BB					(88)
#define RK3288_IRQ_UART_DBG					(89)
#define RK3288_IRQ_UART_GPS					(90)
#define RK3288_IRQ_UART_EXP					(91)
#define RK3288_IRQ_I2C_PMU					(92)
#define RK3288_IRQ_I2C_AUDIO				(93)
#define RK3288_IRQ_I2C_SENSOR				(94)
#define RK3288_IRQ_I2C_CAM					(95)
#define RK3288_IRQ_I2C_TP					(96)
#define RK3288_IRQ_I2C_HDMI					(97)
#define RK3288_IRQ_TIMER6CH0				(98)
#define RK3288_IRQ_TIMER6CH1				(99)
#define RK3288_IRQ_TIMER6CH2				(100)
#define RK3288_IRQ_TIMER6CH3				(101)
#define RK3288_IRQ_TIMER6CH4				(102)
#define RK3288_IRQ_TIMER6CH5				(103)
#define RK3288_IRQ_TIMER2CH0				(104)
#define RK3288_IRQ_TIMER2CH1				(105)
#define RK3288_IRQ_PWM0						(106)
#define RK3288_IRQ_PWM1						(107)
#define RK3288_IRQ_PWM2						(108)
#define RK3288_IRQ_PWM3						(109)
#define RK3288_IRQ_RKPWM					(110)
#define RK3288_IRQ_WDT						(111)
#define RK3288_IRQ_PMU						(112)
#define RK3288_IRQ_GPIO0					(113)
#define RK3288_IRQ_GPIO1					(114)
#define RK3288_IRQ_GPIO2					(115)
#define RK3288_IRQ_GPIO3					(116)
#define RK3288_IRQ_GPIO4					(117)
#define RK3288_IRQ_GPIO5					(118)
#define RK3288_IRQ_GPIO6					(119)
#define RK3288_IRQ_GPIO7					(120)
#define RK3288_IRQ_GPIO8					(121)
#define RK3288_IRQ_AHB_ARBITER0				(122)
#define RK3288_IRQ_AHB_ARBITER1				(123)
#define RK3288_IRQ_AHB_ARBITER2				(124)
#define RK3288_IRQ_USBOTG_ID				(125)
#define RK3288_IRQ_USBOTG_BVALID			(126)
#define RK3288_IRQ_USBOTG_LINESTATE			(127)
#define RK3288_IRQ_USBHOST0_LINESTATE		(128)
#define RK3288_IRQ_USBHOST1_LINESTATE		(129)
#define RK3288_IRQ_USBOTG_EDP				(130)
#define RK3288_IRQ_SDMMC_DETECT				(131)
#define RK3288_IRQ_SDIO0_DETECT				(132)
#define RK3288_IRQ_SDIO1_DETECT				(133)
#define RK3288_IRQ_HDMI_WAKEUP				(134)
#define RK3288_IRQ_HDMI						(135)
#define RK3288_IRQ_CCP						(136)
#define RK3288_IRQ_CCS						(137)
#define RK3288_IRQ_SDMMC_DETECT_DUAL_EDGE	(138)
#define RK3288_IRQ_GPIO_B3_DUAL_EDGE		(139)
#define RK3288_IRQ_GPIO_C6_DUAL_EDGE		(140)
#define RK3288_IRQ_GPIO_A2_DUAL_EDGE		(141)
#define RK3288_IRQ_EDP_HDMI					(142)
#define RK3288_IRQ_HEVC_MMU					(143)

#define RK3288_IRQ_PMUIRQ0					(186)
#define RK3288_IRQ_PMUIRQ1					(187)
#define RK3288_IRQ_PMUIRQ2					(188)
#define RK3288_IRQ_PMUIRQ3					(189)

#ifdef __cplusplus
}
#endif

#endif /* __RK3288_IRQ_H__ */
