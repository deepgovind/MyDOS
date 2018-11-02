 
#include <Display.h>
#include <cpu.h>
#include <keyboard.h>
#include <paging.h>

int main() 
{ 

  // GotoXY (0,0);
  // SetColor (0x19);
     cpu_init();
	 
	
    initialise_paging();
   	//  int s = 8/0;
     Printf("MyD_OS >");
	 irq_uninstall_handler(0);  //Close Timer
	
	uint_32 *ptr = (uint_32*)0xA0000000;
    uint_32 do_page_fault = *ptr;
	 
	// while(1)
	//{  
	//   char* ch = ReadKey();
	//	Printf("%c",ch);
   //   }
	   for(;;){}
	 
}

  