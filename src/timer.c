#include <system.h>

#define CHANNEL_CMD_REG 0x43
#define CHANNEL0_DATA_REG 0x40
#define CHANNEL1_DATA_REG 0x41
#define CHANNEL2_DATA_REG 0x42

/* System dida counter */
/* track how many ticks */
int timer_ticks = 0;

void timer_phase(int hz)
{
	int divisor = 1193180 / hz;	/* Calculate our divisor */
	outportb(CHANNEL_CMD_REG, 0x36);
	outportb(CHANNEL0_DATA_REG, divisor & 0xFF);
	outportb(CHANNEL0_DATA_REG, divisor >> 8);
}

/* Handles the timer. In this case, it's very simple: 
 * We increment the 'timer_ticks' variable every time the 
 * timer fires. By default, the timer fires 18.222 times
 * per second. */
void timer_handler(struct regs *r)
{
	/* inc the 'tick cnt' */
	timer_ticks++;

	/* Every 18 clocks (approximately 1 second), we will
 	*  display a message on the screen  */
	if(timer_ticks % 18 == 0)
		puts("One Sec(18 ticks)\n");
}


/* sets up the sys clock by installing the timer handler
 * into IRQ0 */
void timer_install()
{
	/* Installs timer_handler to IRQ0 */
	irq_install_handler(0, timer_handler);
}

/* Delay system lock to a given tick */
void timer_wait(int ticks)
{
	unsigned long eticks;
	eticks = timer_ticks + ticks;
	while(timer_ticks < eticks);
}
