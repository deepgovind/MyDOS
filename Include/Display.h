 #ifndef DISPLAT_H
 #define DISPLAY_H
 
#include "types.h"
#include "string.h"
#include "system.h"


#define Row 80
#define Col 25

 
//! video memory

static uint_16 *video_memory = (uint_16 *)0xB8000;
 
//! current position
static uint_8 cursor_x = 0;
static uint_8 cursor_y = 0;

 
//! current color
static uint_8	_color=0;


void updateCursor()
{
    unsigned temp;

    temp = cursor_y * Row + cursor_x;                                                      // Position = (y * width) +  x

    outportb(0x3D4, 14);                                                                // CRT Control Register: Select Cursor Location
    outportb(0x3D5, temp >> 8);                                                         // Send the high byte across the bus
    outportb(0x3D4, 15);                                                                // CRT Control Register: Select Send Low byte
    outportb(0x3D5, temp);                                                              // Send the Low byte of the cursor location
}

void scroll() 
{

	if (cursor_y >= Col) {

		uint_16 attribute = _color << 8;

		//! move current display up one line
		int i;
		for ( i=0*Row; i < (Col-1)*Row; i++)
			video_memory [i] = video_memory [i+Row];

		//! clear the bottom line
		for (i=(Col-1)*Row; i<Col*Row; i++)
			video_memory [i] = attribute | ' ';

		cursor_y = Col-1;
		
		updateCursor(); 
	}
}

//! Displays a character
void Putc (uint_8 c) {

    uint_16 attribute = _color << 8;

    //! backspace character
    if (c == 0x08 && cursor_x)
        cursor_x--;

    //! tab character
    else if (c == 0x09)
        cursor_x = (cursor_x+8) & ~(8-1);

    //! carriage return
    else if (c == '\r')
        cursor_x = 0;

    //! new line
	else if (c == '\n') {
        cursor_x = 0;
        cursor_y++;
	}

    //! printable characters
    else if(c >= ' ') {

		//! display character on screen
        uint_16* location = video_memory + (cursor_y*Row + cursor_x);
        *location = c | attribute;
        cursor_x++;
    }

    //! if we are at edge of row, go to new line
    if (cursor_x >= Row) {

        cursor_x = 0;
        cursor_y++;
    }

	//! if we are at the last line, scroll up
	if (cursor_y >= Col)
		scroll ();

	
}

  
//! Sets new position
void GotoXY (uint_32 x, uint_32 y) {

	if (cursor_x <= Row)
	    cursor_x = x;

	if (cursor_y <= Col)
	    cursor_y = y;
 
  updateCursor();
}

//! Clear screen
void ClrScr () {
    
	int i;
	//! clear video memory by writing space characters to it
	for (i = 0; i < Row*Col; i++)
        video_memory[i] = ' ' | _color << 8;

    //! move position back to start
    GotoXY (0,0);
}

//! Displays a string
void Puts(char* str) {

	if (!str)
		return;
		
      unsigned int i;
	//! err... displays a string
    for (i=0; i<strLen(str); i++)
        Putc (str[i]);
		
   updateCursor(); 
}
unsigned SetColor(const unsigned c)
{
    unsigned t=_color;
	_color=c;
	return t;
}

char tbuf[32];
char bchars[] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};

void itoa(unsigned i,unsigned base,char* buf) {
   int pos = 0;
   int opos = 0;
   int top = 0;

   if (i == 0 || base > 16) {
      buf[0] = '0';
      buf[1] = '\0';
      return;
   }

   while (i != 0) {
      tbuf[pos] = bchars[i % base];
      pos++;
      i /= base;
   }
   top=pos--;
   for (opos=0; opos<top; pos--,opos++) {
      buf[opos] = tbuf[pos];
   }
   buf[opos] = 0;
}

void itoa_s(int i,unsigned base,char* buf) {
   if (base > 16) return;
   if (i < 0) {
      *buf++ = '-';
      i *= -1;
   }
   itoa(i,base,buf);
}
int Printf(const char* str ,...)
{

	if(!str)
		return 0;

	va_list		args;
	va_start (args, str);
	size_t i;
	for (i=0; i<strlen(str);i++) {

		switch (str[i]) {

			case '%':

				switch (str[i+1]) {

					/*** characters ***/
					case 'c': {
						char c = va_arg (args, char);
						Putc (c);
						i++;		// go to next character
						break;
					}

					/*** address of ***/
					case 's': {
						int c = (int)va_arg (args, char);//(int&)va_arg (args, char);
						char str[64];
						strcpy (str,(const char*)c);
						Puts (str);
						i++;		// go to next character
						break;
					}

					/*** integers ***/
					case 'd':
					case 'i': {
						int c = va_arg (args, int);
						char str[32]={0};
						itoa_s (c, 10, str);
						Puts (str);
						i++;		// go to next character
						break;
					}

					/*** display in hex ***/
					case 'X':
					case 'x': {
						int c = va_arg (args, int);
						char str[32]={0};
						itoa_s (c,16,str);
						Puts (str);
						i++;		// go to next character
						break;
					}

					default:
						va_end (args);
						return 1;
				}

				break;

			default:
				Putc (str[i]);
				break;
		}

	}
    updateCursor();
	va_end (args);
	return i;
}

#endif