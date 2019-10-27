/* See COPYRIGHT for copyright information. */

#include <inc/x86.h>
#include <kern/kclock.h>

void
rtc_init(void)
{
    /* This is because if an interrupt happens,
     * the RTC may be left in an "undefined" (non functional) state.
     */
	nmi_disable();
	// LAB 4: your code here
    uint8_t B;
    outb(IO_RTC_CMND, RTC_BREG);
    B = inb(IO_RTC_DATA);
    outb(IO_RTC_DATA, B | RTC_PIE);

    outb(IO_RTC_CMND, RTC_AREG);
    uint8_t A = inb(IO_RTC_DATA);
    outb(IO_RTC_DATA, A | 0xF);

	nmi_enable();
}

uint8_t
rtc_check_status(void)
{
	uint8_t status = 0;
	// LAB 4: your code here
    outb(IO_RTC_CMND, RTC_CREG);
    status = inb(IO_RTC_DATA);
	return status;
}

unsigned
mc146818_read(unsigned reg)
{
	outb(IO_RTC_CMND, reg);
	return inb(IO_RTC_DATA);
}

void
mc146818_write(unsigned reg, unsigned datum)
{
	outb(IO_RTC_CMND, reg);
	outb(IO_RTC_DATA, datum);
}

