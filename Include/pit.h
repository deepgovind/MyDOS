#ifndef PIT_H
#define PIT_H
 
#include "system.h"
#include "idt.h"
#include "pic.h"
 


struct date time_run;

void timer_phase(int hz)
{
  int divisor = 1193180 / hz;       /* Calculate our divisor */
  outportb(0x43, 0x36);             /* Set our command byte 0x36 */
  outportb(0x40, divisor & 0xFF);   /* Set low byte of divisor */
  outportb(0x40, divisor >> 8);     /* Set high byte of divisor */
  timer_ticks = 0;
}
/* Sets up the system clock by installing the timer handler
*  into IRQ0 */
void timer_handler(struct regs *r)
{
  /* Increment our 'tick count' */
  timer_ticks++;

  
  /* Every 18 clocks (approximately 1 second), we will
  *  display a message on the screen */
  if (timer_ticks % (3*18) == 0)  //approximately 1 secound
  {
        if(++time_run.sec >= 60)
		{
           if(++time_run.min >= 60)
		   {
             if(++time_run.hrs >= 24)
		     {
               time_run.days++;
               time_run.hrs = 0;
              }
          time_run.min = 0;
        }
        time_run.sec = 0;
		
      }
	   GotoXY(20,5);
	   Printf("Time: %d:%d:%d", time_run.hrs, time_run.min, time_run.sec ); 
	   GotoXY(37,21);
  } 
}
void timer_install()
{
  /* Installs 'timer_handler' to IRQ0 */
  irq_install_handler(0, timer_handler);
  
	
}

#endif