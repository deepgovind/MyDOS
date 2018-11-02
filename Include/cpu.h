#ifndef CPU_H
#define CPU_H

#include "system.h"
#include "gdt.h"
#include "idt.h"
#include "isr.h"
#include "pic.h"
#include "pit.h"
#include "Keyboard.h"
#include "ico.h"


void cpu_init()
{
     __asm__ __volatile__("cli");
	 
     GotoXY (0,0);
	 SetColor (0x04);
     ClrScr();
     Printf("CPU is Initializing....................\n");
     gdt_initialize();
	 SetColor (0x02);
     Printf("    GDT [Global Descriptor Table ] is Initialized Successfull !..... \n");
	 idt_install ();
	 Printf("    IDT [Interrupt Descriptor Table ] is Initialized Successfull !.... \n");
     isr_install();
	 Printf("    ISRs [ Interrupt Service Routines ] is Initialized Successfull !.... \n");
	 irq_init();
	 Printf("    ISRs [ interrupt requests ] is Initialized Successfull !.... \n");
     timer_install();
	 timer_phase(100);
	 Printf("    PIT [  Timer IC             ] is Initialized Successfull !.... \n");
	  SetColor (0x01);
	 Printf("CPU is Initialized Successfull....................\n"); 
	 SetColor (0x03);
	 Puts(ico);
	 SetColor (0x0a);
	 Printf("\nWelcome To D_OS......");
	 SetColor (0x07);
	 Printf("\nPress Any Key For Continue...........");
	  
	  __asm__ __volatile__("sti");
	 
     char* ch = ReadKey();
	 GotoXY (0,0);
	 SetColor (0x0e);
     ClrScr();

}

#endif
