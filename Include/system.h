#ifndef SYSTEM_H
#define SYSTEM_H
 
uint_8 inportb (uint_16 port)
{
    	uint_8 rv;
    	__asm__ __volatile__ ("inb %1, %0" : "=a" (rv) : "dN" (port));
    	return rv;
}

void outportb (uint_16 port, uint_8 data)
{
	__asm__ __volatile__ ("outb %1, %0" : : "dN" (port), "a" (data));
}

struct regs
{
    uint_32 gs, fs, es, ds;
    uint_32 edi, esi, ebp, esp, ebx, edx, ecx, eax;
    uint_32 int_no, err_code;
    uint_32 eip, cs, eflags, useresp, ss;    
};

//Timer Tics 
uint_32 timer_ticks = 0;

 
//time 
 struct date
{
  uint_32 sec;
  uint_32 min;
  uint_32 hrs;
  uint_32 days;
};

// Display

extern void updateCursor();
extern void Putc (uint_8 c);
extern void GotoXY (uint_32 x, uint_32 y) ;
extern void ClrScr ();
extern void Puts(char* str) ;
extern unsigned SetColor(const unsigned c);
extern int Printf(const char* str ,...);

// PIT  
extern void timer_install();
extern void timer_handler(struct regs *r);
extern void timer_phase(int hz);

// GDT 
extern void gdt_set_gate(uint_32 num, unsigned long base, unsigned long limit, uint_8 access, uint_8 gran);
extern void gdt_install(void);
extern void gdt_install ();

//IDT 

extern void idt_load();
extern void idt_install();

//PIC 

extern void irq_install_handler(int irq, void (*handler)(struct regs *r));
extern void irq_uninstall_handler(int irq);
extern void irq_install();
extern void irq_handler(struct regs *r);
extern void pic_irq_map();

// String

extern uint_16 strLen(char* ch);
extern uint_8 strCmp(char* ch1,char* ch2);
extern void *_memset(void *dest, uint_8 val, uint_32 len);
extern char *strcpy(char *s1, const char *s2);
extern int strlen ( const char* str );



#endif
