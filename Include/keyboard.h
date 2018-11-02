#ifndef KEYBOARD_H
#define KEYBOARD_H

char* ReadKey()
{
    char buff;
    char* buffstr;
    uint_8 i = 0;
    uint_8 reading = 1;
    while(reading)
    {
        if(inportb(0x64) & 0x1)                 
        {
            switch(inportb(0x60))
            { 
      /*case 1:
               Putc('(char)27);           Escape button
                buffstr[i] = (char)27;
                i++;
                break;*/
        case 2:
               Putc('1');
                buffstr[i] = '1';
                i++;
                break;
        case 3:
               Putc('2');
                buffstr[i] = '2';
                i++;
                break;
        case 4:
               Putc('3');
                buffstr[i] = '3';
                i++;
                break;
        case 5:
               Putc('4');
                buffstr[i] = '4';
                i++;
                break;
        case 6:
               Putc('5');
                buffstr[i] = '5';
                i++;
                break;
        case 7:
               Putc('6');
                buffstr[i] = '6';
                i++;
                break;
        case 8:
               Putc('7');
                buffstr[i] = '7';
                i++;
                break;
        case 9:
               Putc('8');
                buffstr[i] = '8';
                i++;
                break;
        case 10:
               Putc('9');
                buffstr[i] = '9';
                i++;
                break;
        case 11:
               Putc('0');
                buffstr[i] = '0';
                i++;
                break;
        case 12:
               Putc('-');
                buffstr[i] = '-';
                i++;
                break;
        case 13:
               Putc('=');
                buffstr[i] = '=';
                i++;
                break;
        case 14:
               Putc('\b');
                i--;
                buffstr[i] = 0;
                break;
       /* case 15:
               Putc('\t');          Tab button
                buffstr[i] = '\t';
                i++;
                break;*/
        case 16:
               Putc('q');
                buffstr[i] = 'q';
                i++;
                break;
        case 17:
               Putc('w');
                buffstr[i] = 'w';
                i++;
                break;
        case 18:
               Putc('e');
                buffstr[i] = 'e';
                i++;
                break;
        case 19:
               Putc('r');
                buffstr[i] = 'r';
                i++;
                break;
        case 20:
               Putc('t');
                buffstr[i] = 't';
                i++;
                break;
        case 21:
               Putc('y');
                buffstr[i] = 'y';
                i++;
                break;
        case 22:
               Putc('u');
                buffstr[i] = 'u';
                i++;
                break;
        case 23:
               Putc('i');
                buffstr[i] = 'i';
                i++;
                break;
        case 24:
               Putc('o');
                buffstr[i] = 'o';
                i++;
                break;
        case 25:
               Putc('p');
                buffstr[i] = 'p';
                i++;
                break;
        case 26:
               Putc('[');
                buffstr[i] = '[';
                i++;
                break;
        case 27:
               Putc(']');
                buffstr[i] = ']';
                i++;
                break;
        case 28:
               //Putc('\n');
               // buffstr[i] = '\n';
                  i++;
               reading = 0;
                break;
      /*  case 29:
               Putc('q');           Left Control
                buffstr[i] = 'q';
                i++;
                break;*/
        case 30:
               Putc('a');
                buffstr[i] = 'a';
                i++;
                break;
        case 31:
               Putc('s');
                buffstr[i] = 's';
                i++;
                break;
        case 32:
               Putc('d');
                buffstr[i] = 'd';
                i++;
                break;
        case 33:
               Putc('f');
                buffstr[i] = 'f';
                i++;
                break;
        case 34:
               Putc('g');
                buffstr[i] = 'g';
                i++;
                break;
        case 35:
               Putc('h');
                buffstr[i] = 'h';
                i++;
                break;
        case 36:
               Putc('j');
                buffstr[i] = 'j';
                i++;
                break;
        case 37:
               Putc('k');
                buffstr[i] = 'k';
                i++;
                break;
        case 38:
               Putc('l');
                buffstr[i] = 'l';
                i++;
                break;
        case 39:
               Putc(';');
                buffstr[i] = ';';
                i++;
                break;
        case 40:
               Putc((char)44);               //   Single quote (')
                buffstr[i] = (char)44;
                i++;
                break;
        case 41:
               Putc((char)44);               // Back tick (`)
                buffstr[i] = (char)44;
                i++;
                break;
     /* case 42:                                 Left shift 
               Putc('q');
                buffstr[i] = 'q';
                i++;
                break;
        case 43:                                 \ (< for somekeyboards)   
               Putc((char)92);
                buffstr[i] = 'q';
                i++;
                break;*/
        case 44:
               Putc('z');
                buffstr[i] = 'z';
                i++;
                break;
        case 45:
               Putc('x');
                buffstr[i] = 'x';
                i++;
                break;
        case 46:
               Putc('c');
                buffstr[i] = 'c';
                i++;
                break;
        case 47:
               Putc('v');
                buffstr[i] = 'v';
                i++;
                break;                
        case 48:
               Putc('b');
                buffstr[i] = 'b';
                i++;
                break;               
        case 49:
               Putc('n');
                buffstr[i] = 'n';
                i++;
                break;                
        case 50:
               Putc('m');
                buffstr[i] = 'm';
                i++;
                break;               
        case 51:
               Putc(',');
                buffstr[i] = ',';
                i++;
                break;                
        case 52:
               Putc('.');
                buffstr[i] = '.';
                i++;
                break;            
        case 53:
               Putc('/');
                buffstr[i] = '/';
                i++;
                break;            
        case 54:
               Putc('.');
                buffstr[i] = '.';
                i++;
                break;            
        case 55:
               Putc('/');
                buffstr[i] = '/';
                i++;
                break;            
      /*case 56:
               Putc(' ');           Right shift
                buffstr[i] = ' ';
                i++;
                break;*/           
        case 57:
               Putc(' ');
                buffstr[i] = ' ';
                i++;
                break;
            }
        }
    }
    buffstr[i] = 0;                
    return buffstr;
}
#endif