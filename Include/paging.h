#ifndef PAGING_H
#define PAGINH_H

// Macros used in the bitset algorithms.
#define INDEX_FROM_BIT(a) (a/(8*4))
#define OFFSET_FROM_BIT(a) (a%(8*4))
 
typedef struct page
{
    uint_32 present    : 1;   // Page present in memory
    uint_32 rw         : 1;   // Read-only if clear, readwrite if set
    uint_32 user       : 1;   // Supervisor level only if clear
    uint_32 accessed   : 1;   // Has the page been accessed since last refresh?
    uint_32 dirty      : 1;   // Has the page been written to since last refresh?
    uint_32 unused     : 7;   // Amalgamation of unused and reserved bits
    uint_32 frame      : 20;  // Frame address (shifted right 12 bits)
} page_t;

typedef struct page_table
{
    page_t pages[1024];
} page_table_t;

typedef struct page_directory
{
    page_table_t *tables[1024];
    uint_32 tablesPhysical[1024];
    uint_32 physicalAddr;
} page_directory_t;

void initialise_paging();
void switch_page_directory(page_directory_t *new);
page_t *get_page(uint_32 address, int make, page_directory_t *dir);
void page_fault(struct regs regs);
uint_32 kmalloc_int(uint_32 sz, int align, uint_32 *phys);
uint_32 kmalloc_a(uint_32 sz);
uint_32 kmalloc_p(uint_32 sz, uint_32 *phys);
uint_32 kmalloc_ap(uint_32 sz, uint_32 *phys);
uint_32 kmalloc(uint_32 sz);

page_directory_t *kernel_directory=0;
page_directory_t *current_directory=0;

// A bitset of frames - used or free.
uint_32 *frames;
uint_32 nframes;

extern uint_32 placement_address;
extern uint_32 end;
uint_32 placement_address = (uint_32)&end;

uint_32 kmalloc_int(uint_32 sz, int align, uint_32 *phys)
{
 
    if (align == 1 && (placement_address & 0xFFFFF000) )
    {
        // Align the placement address;
        placement_address &= 0xFFFFF000;
        placement_address += 0x1000;
    }
    if (phys)
    {
        *phys = placement_address;
    }
    uint_32 tmp = placement_address;
    placement_address += sz;
    return tmp;
}

uint_32 kmalloc_a(uint_32 sz)
{
    return kmalloc_int(sz, 1, 0);
}

uint_32 kmalloc_p(uint_32 sz, uint_32 *phys)
{
    return kmalloc_int(sz, 0, phys);
}

uint_32 kmalloc_ap(uint_32 sz, uint_32 *phys)
{
    return kmalloc_int(sz, 1, phys);
}

uint_32 kmalloc(uint_32 sz)
{
    return kmalloc_int(sz, 0, 0);
}

// Static function to set a bit in the frames bitset
static void set_frame(uint_32 frame_addr)
{
    uint_32 frame = frame_addr/0x1000;
    uint_32 idx = INDEX_FROM_BIT(frame);
    uint_32 off = OFFSET_FROM_BIT(frame);
    frames[idx] |= (0x1 << off);
}

// Static function to clear a bit in the frames bitset
static void clear_frame(uint_32 frame_addr)
{
    uint_32 frame = frame_addr/0x1000;
    uint_32 idx = INDEX_FROM_BIT(frame);
    uint_32 off = OFFSET_FROM_BIT(frame);
    frames[idx] &= ~(0x1 << off);
}

// Static function to test if a bit is set.
static uint_32 test_frame(uint_32 frame_addr)
{
    uint_32 frame = frame_addr/0x1000;
    uint_32 idx = INDEX_FROM_BIT(frame);
    uint_32 off = OFFSET_FROM_BIT(frame);
    return (frames[idx] & (0x1 << off));
}

// Static function to find the first free frame.
static uint_32 first_frame()
{
    uint_32 i, j;
    for (i = 0; i < INDEX_FROM_BIT(nframes); i++)
    {
        if (frames[i] != 0xFFFFFFFF) // nothing free, exit early.
        {
            // at least one bit is free here.
            for (j = 0; j < 32; j++)
            {
                uint_32 toTest = 0x1 << j;
                if ( !(frames[i]&toTest) )
                {
                    return i*4*8+j;
                }
            }
        }
    }
}

// Function to allocate a frame.
void alloc_frame(page_t *page, int is_kernel, int is_writeable)
{
    if (page->frame != 0)
    {
        return;
    }
    else
    {
        uint_32 idx = first_frame();
        if (idx == (uint_32)-1)
        {
            // PANIC! no free frames!!
        }
        set_frame(idx*0x1000);
        page->present = 1;
        page->rw = (is_writeable)?1:0;
        page->user = (is_kernel)?0:1;
        page->frame = idx;
    }
}

// Function to deallocate a frame.
void free_frame(page_t *page)
{
    uint_32 frame;
    if (!(frame=page->frame))
    {
        return;
    }
    else
    {
        clear_frame(frame);
        page->frame = 0x0;
    }
}

void switch_page_directory(page_directory_t *dir)
{
    current_directory = dir;
    asm volatile("mov %0, %%cr3":: "r"(&dir->tablesPhysical));
    uint_32 cr0;
    asm volatile("mov %%cr0, %0": "=r"(cr0));
    cr0 |= 0x80000000; // Enable paging!
    asm volatile("mov %0, %%cr0":: "r"(cr0));
}

page_t *get_page(uint_32 address, int make, page_directory_t *dir)
{
    // Turn the address into an index.
    address /= 0x1000;
    // Find the page table containing this address.
    uint_32 table_idx = address / 1024;
    if (dir->tables[table_idx]) // If this table is already assigned
    {
        return &dir->tables[table_idx]->pages[address%1024];
    }
    else if(make)
    {
        uint_32 tmp;
        dir->tables[table_idx] = (page_table_t*)kmalloc_ap(sizeof(page_table_t), &tmp);
        dir->tablesPhysical[table_idx] = tmp | 0x7; // PRESENT, RW, US.
        return &dir->tables[table_idx]->pages[address%1024];
    }
    else
    {
        return 0;
    }
}


void page_fault(struct regs regs)
{
     GotoXY(0,0);
    // A page fault has occurred.
    // The faulting address is stored in the CR2 register.
    uint_32 faulting_address;
    asm volatile("mov %%cr2, %0" : "=r" (faulting_address));
    
    // The error code gives us details of what happened.
    int present   = !(regs.err_code & 0x1); // Page not present
    int rw = regs.err_code & 0x2;           // Write operation?
    int us = regs.err_code & 0x4;           // Processor was in user-mode?
    int reserved = regs.err_code & 0x8;     // Overwritten CPU-reserved bits of page entry?
    int id = regs.err_code & 0x10;          // Caused by an instruction fetch?

    // Output an error message.
    Printf("Page fault!  deep( ");
    if (present) {Printf("present ");}
    if (rw) {Printf("read-only ");}
    if (us) {Printf("user-mode ");}
    if (reserved) {Printf("reserved ");}
    Printf(") at 0x%x\n",faulting_address);
	
    for(;;){}
   
}

void initialise_paging()
{
    // The size of physical memory. For the moment we 
    // assume it is 16MB big.
    uint_32 mem_end_page = 0x1000000;
    
    nframes = mem_end_page / 0x1000;
    frames = (uint_32*)kmalloc(INDEX_FROM_BIT(nframes));
    _memset(frames, 0, INDEX_FROM_BIT(nframes));
    
    // Let's make a page directory.
    kernel_directory = (page_directory_t*)kmalloc_a(sizeof(page_directory_t));
    current_directory = kernel_directory;

    // We need to identity map (phys addr = virt addr) from
    int i = 0;
    while (i < placement_address)
    {
        // Kernel code is readable but not writeable from userspace.
        alloc_frame( get_page(i, 1, kernel_directory), 0, 0);
        i += 0x1000;
    }
   set_idt_gate(14,(uint_32)page_fault);
    switch_page_directory(kernel_directory);
}


#endif
