/* See COPYRIGHT for copyright information. */

#include <inc/x86.h>
#include <kern/kclock.h>
#include <inc/time.h>

static int
gettimestamp(void)
{
    struct tm t;

    t.tm_sec = BCD2BIN(mc146818_read(RTC_SEC));
    t.tm_min = BCD2BIN(mc146818_read(RTC_MIN));
    t.tm_hour = BCD2BIN(mc146818_read(RTC_HOUR));
    t.tm_mday = BCD2BIN(mc146818_read(RTC_DAY));
    t.tm_mon = BCD2BIN(mc146818_read(RTC_MON));
    t.tm_year = BCD2BIN(mc146818_read(RTC_YEAR));

    return timestamp(&t);
}


int gettime(void)
{
    int time;

	nmi_disable();
	// LAB 12: your code here
    while (mc146818_read(RTC_AREG) & RTC_UPDATE_IN_PROGRESS){}

    if ((time = gettimestamp()) != gettimestamp()) {
        time = gettimestamp();
    }
    nmi_enable();

    return time;
}

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
    outb(IO_RTC_DATA, A | 0xE);

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

