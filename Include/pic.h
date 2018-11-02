#ifndef PIC_H
#define PIC_H

#include "system.h"


extern void irq0(void);
extern void irq1(void);
extern void irq2(void);
extern void irq3(void);
extern void irq4(void);
extern void irq5(void);
extern void irq6(void);
extern void irq7(void);
extern void irq8(void);
extern void irq9(void);
extern void irq10(void);
extern void irq11(void);
extern void irq12(void);
extern void irq13(void);
extern void irq14(void);
extern void irq15(void);


  void *irq_routines[16] =
{
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0
};

 void irq_install_handler(int irq, void (*handler)(struct regs *r))
{
    irq_routines[irq] = handler;
}

void irq_uninstall_handler(int irq)
{
    irq_routines[irq] = 0;
}

void pic_irq_map()
{
   	/* send ICW1   enable initialization, and to send ICW 4*/
	outportb(0x20, 0x11); 
    outportb(0xA0, 0x11);
	/* send ICW2    This is the base addresses of the irq's */
	outportb(0x21, 0x20); //PIC1 +1 =  0x21  ,MASTER PIC DATA REGISTER
    outportb(0xA1, 0x28);//PIC1 +1 =  0xA1  ,SLEVE PIC DATA REGISTER
 
	/* send ICW3 */
	outportb(0x21, 0x4);	     // set PIC1 as MASTER 0x04         MASTER identifier
	outportb(0xA1, 0x2);         //set PIC2 as SLAVE  0x02         SLAVE identifier
 
	/* send ICW4 , This is the x86 mode code for both 8259 PIC chips*/
	outportb(0x21, 0x01);              //Set PIC1 mode
	outportb(0xA1, 0x01);              //Set PIC2 mode
 
	 /* enable all IRQs */
	outportb(0x21, 0x0);      
	outportb(0xA1, 0x0);
 
}  
void irq_init()
{
 
    pic_irq_map();
  
    set_idt_gate(32, (uint_32)irq0);
    set_idt_gate(33, (uint_32)irq1);
    set_idt_gate(34, (uint_32)irq2);
    set_idt_gate(35, (uint_32)irq3);
    set_idt_gate(36, (uint_32)irq4);
    set_idt_gate(37, (uint_32)irq5);
    set_idt_gate(38, (uint_32)irq6);
    set_idt_gate(39, (uint_32)irq7);
    set_idt_gate(40, (uint_32)irq8);
    set_idt_gate(41, (uint_32)irq9);
    set_idt_gate(42, (uint_32)irq10);
    set_idt_gate(43, (uint_32)irq11);
    set_idt_gate(44, (uint_32)irq12);
    set_idt_gate(45, (uint_32)irq13);
    set_idt_gate(46, (uint_32)irq14);
    set_idt_gate(47, (uint_32)irq15);
}

void irq_handler(struct regs *r)
{    
      void (*handler)(struct regs *r);
     handler = irq_routines[r->int_no - 32];
    if (handler)
    {
        handler(r);
			
    }
	
     if (r->int_no >= 40)
    {
        outportb(0xA0, 0x20);
    }
     outportb(0x20, 0x20);

}

#endif
