#ifndef ISR_H
#define ISR_H

char* exception_messages[] = {
    "Exception ! Division By Zero",
    "Exception ! Debug",
    "Exception ! Non Maskable Interrupt",
    "Exception ! Breakpoint",
    "Exception ! Into Detected Overflow",
    "Exception ! Out of Bounds",
    "Exception ! Invalid Opcode",
    "Exception ! No Coprocessor",

    "Exception ! Double Fault",
    "Exception ! Coprocessor Segment Overrun",
    "Exception ! Bad TSS",
    "Exception ! Segment Not Present",
    "Exception ! Stack Fault",
    "Exception ! General Protection Fault",
    "Exception ! Page Fault",
    "Exception ! Unknown Interrupt",

    "Exception ! Coprocessor Fault",
    "Exception ! Alignment Check",
    "Exception ! Machine Check",
    "Exception ! Reserved",
    "Exception ! Reserved",
    "Exception ! Reserved",
    "Exception ! Reserved",
    "Exception ! Reserved",

    "Exception ! Reserved",
    "Exception ! Reserved",
    "Exception ! Reserved",
    "Exception ! Reserved",
    "Exception ! Reserved",
    "Exception ! Reserved",
    "Exception ! Reserved",
    "Exception ! Reserved"
};
 
 void *isr_routines[32] =
{
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0 ,  0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0
};

 void isr_install_handler(int isr, void (*handler)(struct regs *r))
{
    isr_routines[isr] = handler;
}
 
extern void isr0(void);
extern void isr1(void);
extern void isr2(void);
extern void isr3(void);
extern void isr4(void);
extern void isr5(void);
extern void isr6(void);
extern void isr7(void);
extern void isr8(void);
extern void isr9(void);
extern void isr10(void);
extern void isr11(void);
extern void isr12(void);
extern void isr13(void);
extern void isr14(void);
extern void isr15(void);
extern void isr16(void);
extern void isr17(void);
extern void isr18(void);
extern void isr19(void);
extern void isr20(void);
extern void isr21(void);
extern void isr22(void);
extern void isr23(void);
extern void isr24(void);
extern void isr25(void);
extern void isr26(void);
extern void isr27(void);
extern void isr28(void);
extern void isr29(void);
extern void isr30(void);
extern void isr31(void);


void isr_install()
 {
       
    set_idt_gate(0, (uint_32)isr0);
    set_idt_gate(1,(uint_32)isr1);
    set_idt_gate(2, (uint_32)isr2);
    set_idt_gate(3,(uint_32)isr3);
    set_idt_gate(4,(uint_32)isr4);
    set_idt_gate(5,(uint_32)isr5);
    set_idt_gate(6,(uint_32)isr6);
    set_idt_gate(7,(uint_32)isr7);
    set_idt_gate(8,(uint_32)isr8);
    set_idt_gate(9,(uint_32)isr9);
    set_idt_gate(10, (uint_32)isr10);
    set_idt_gate(11, (uint_32)isr11);
    set_idt_gate(12,(uint_32)isr12);
    set_idt_gate(13,(uint_32)isr13);
    set_idt_gate(14,(uint_32)isr14);
    set_idt_gate(15,(uint_32)isr15);
    set_idt_gate(16, (uint_32)isr16);
    set_idt_gate(17, (uint_32)isr17);
    set_idt_gate(18, (uint_32)isr18);
    set_idt_gate(19, (uint_32)isr19);
    set_idt_gate(20, (uint_32)isr20);
    set_idt_gate(21,(uint_32)isr21);
    set_idt_gate(22, (uint_32)isr22);
    set_idt_gate(23,(uint_32)isr23);
    set_idt_gate(24,(uint_32)isr24);
    set_idt_gate(25,(uint_32)isr25);
    set_idt_gate(26,(uint_32)isr26);
    set_idt_gate(27,(uint_32)isr27);
    set_idt_gate(28,(uint_32)isr28);
    set_idt_gate(29,(uint_32)isr29);
    set_idt_gate(30,(uint_32)isr30);
    set_idt_gate(31, (uint_32)isr31);
   
   
}

void fault_handler(struct regs *r)
{
    
       if (r->int_no < 32)
       {
        Puts(exception_messages[r->int_no]);
        Puts(" Exception. System Halted!\n");
        Printf("Regs dump:\n eax=0x%x\n ebx=0x%x\n ecx=0x%x\n edx=0x%x\n esp=0x%x\n ebp=0x%x\n esi=0x%x\n edi=0x%x\n",\
                r->eax, r->ebx, r->ecx, r->edx, r->esp, r->ebp, r->esi, r->edi);
        Printf(" gs=0x%x\n fs=0x%x\n es=0x%x\n ds=0x%x\n err_code=0x%x\n eip=0x%x\n cs=0x%x\n eflags=0x%x\n useresp=0x%x\n ss=0x%x\n",\
                r->gs, r->fs, r->es, r->ds, r->err_code, r->eip, r->cs, r->eflags, r->useresp, r->ss); 
        for (;;);
       }
	 
}


#endif
