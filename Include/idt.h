#ifndef IDT_H
#define IDT_H

 
 
typedef struct {

    uint_16 low_offset;
    uint_16 sel; 
    uint_8 always0;
    uint_8 flags; 
    uint_16 high_offset;
	
} __attribute__((packed)) idt_descriptor ;

typedef struct {

    uint_16 limit;
    uint_32 base;
	
} __attribute__((packed)) idtr;

#define IDT_ENTRIES 256

idt_descriptor  _idt[IDT_ENTRIES];
idtr            _idtr;


 
 
int set_idt_gate(uint_32 n,uint_32 irq) 
{
    if (n>IDT_ENTRIES)
		return 0;
  
    _idt[n].low_offset =  (uint_16)((irq) & 0xffff);
    _idt[n].sel =  0x08;
    _idt[n].always0 = 0;
    _idt[n].flags =  0x8E  ;
    _idt[n].high_offset = (uint_16)(((irq) >> 16) & 0xffff);

	return 0;
}
void idt_install ()
{
     _idtr.base = (uint_32) &_idt[0];
     _idtr.limit = IDT_ENTRIES * sizeof(idt_descriptor) - 1;
	 
	 _memset(&_idt[0], 0, sizeof (idt_descriptor) * IDT_ENTRIES-1);
	 
    
			
    idt_load();
}

#endif
