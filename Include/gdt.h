#ifndef GDT_H
#define GDT_H


 typedef struct
{
	uint_16		limit;             //! bits 0-15 of segment limit
    uint_16		baseLo;            //! bits 0-23 of base address
	uint_8			baseMid;
 	uint_8			flags;             //! descriptor access flags
 	uint_8			grand;
    uint_8			baseHi;            //! bits 24-32 of base address
}__attribute__((packed)) gdt_descriptor;
 
typedef struct{
     uint_16		m_limit;
     uint_32		m_base;
}__attribute__((packed)) gdtr;

gdt_descriptor	    _gdt[6];
gdtr				_gdtr;

 
void gdt_set_descriptor(uint_32 i, unsigned long base, unsigned long limit, uint_8 access, uint_8 grand)
{
	if (i > 6)
		return;
 
	_gdt[i].baseLo	= (uint_16)(base & 0xFFFF);
	_gdt[i].baseMid	= (uint_8)((base >> 16) & 0xFF);
	_gdt[i].baseHi	= (uint_8)((base >> 24) & 0xFF);
	
	_gdt[i].limit	= (uint_16)(limit & 0xFFFF);
	_gdt[i].grand = (uint_8)((limit >> 16) & 0x0F);
	
	_gdt[i].grand |= (grand & 0xF0);
	_gdt[i].flags = access;
}


 void  gdt_initialize () 
{
     _gdtr.m_limit = (sizeof (gdt_descriptor) * 6)-1;
	 _gdtr.m_base = (uint_32)&_gdt[0];

	 gdt_set_descriptor(0, 0, 0, 0, 0);
     gdt_set_descriptor (1,0,0xFFFFFFFF,0x9A,0xCF);
     gdt_set_descriptor (2,0,0xFFFFFFFF,0x92,0xCF);
	 gdt_set_descriptor(3, 0, 0xFFFFFFFF, 0xFA, 0xCF); // User mode code segment
     gdt_set_descriptor(4, 0, 0xFFFFFFFF, 0xF2, 0xCF); // User mode data segment
	 
  	 gdt_install ();
	 
}
 
#endif
