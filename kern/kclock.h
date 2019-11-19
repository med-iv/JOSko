/* See COPYRIGHT for copyright information. */

#ifndef JOS_KERN_KCLOCK_H
#define JOS_KERN_KCLOCK_H
#ifndef JOS_KERNEL
# error "This is a JOS kernel header; user programs should not #include it"
#endif

#define	IO_RTC		0x070		/* RTC port */

#define	IO_RTC_CMND		0x070		/* RTC control port */
#define	IO_RTC_DATA		0x071		/* RTC data port */

#define RTC_AREG	0x0A
#define RTC_BREG	0x0B
#define RTC_CREG	0x0C
#define RTC_DREG	0x0D

#define RTC_PIE		0x40
#define RTC_AIE		0x20
#define RTC_UIE		0x10

void rtc_init(void);
uint8_t rtc_check_status(void);

#define	MC_NVRAM_START	0xe	/* start of NVRAM: offset 14 */
#define	MC_NVRAM_SIZE	50	/* 50 bytes of NVRAM */

/* NVRAM bytes 7 & 8: base memory size */
#define NVRAM_BASELO	(MC_NVRAM_START + 7)	/* low byte; RTC off. 0x15 */
#define NVRAM_BASEHI	(MC_NVRAM_START + 8)	/* high byte; RTC off. 0x16 */

/* NVRAM bytes 9 & 10: extended memory size */
#define NVRAM_EXTLO	(MC_NVRAM_START + 9)	/* low byte; RTC off. 0x17 */
#define NVRAM_EXTHI	(MC_NVRAM_START + 10)	/* high byte; RTC off. 0x18 */

/* NVRAM bytes 34 and 35: extended memory POSTed size */
#define NVRAM_PEXTLO	(MC_NVRAM_START + 38)	/* low byte; RTC off. 0x34 */
#define NVRAM_PEXTHI	(MC_NVRAM_START + 39)	/* high byte; RTC off. 0x35 */

/* NVRAM byte 36: current century.  (please increment in Dec99!) */
#define NVRAM_CENTURY	(MC_NVRAM_START + 36)	/* RTC offset 0x32 */

unsigned mc146818_read(unsigned reg);
void mc146818_write(unsigned reg, unsigned datum);

#endif	// !JOS_KERN_KCLOCK_H
