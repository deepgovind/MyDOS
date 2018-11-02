#ifndef STRING_H
#define STRING_H


typedef unsigned char *va_list;

typedef unsigned size_t;

#ifdef __cplusplus
extern "C"
{
#endif
 
#define	STACKITEM	int

#define	VA_SIZE(TYPE)					\
	((sizeof(TYPE) + sizeof(STACKITEM) - 1)	\
		& ~(sizeof(STACKITEM) - 1))
		
#define	va_start(AP, LASTARG)	\
	(AP=((va_list)&(LASTARG) + VA_SIZE(LASTARG)))

#define va_end(AP)

#define va_arg(AP, TYPE)	\
	(AP += VA_SIZE(TYPE), *((TYPE *)(AP - VA_SIZE(TYPE))))

#ifdef __cplusplus
}
#endif

uint_16 strLen(char* ch)
{
        uint_16 i = 0;         
        while(ch[i++]);  
        return i;     
}
 
uint_8 strCmp(char* ch1,char* ch2)                     
{
        uint_8 result = 1;
        uint_8 size = strLen(ch1);
        if(size != strLen(ch2)) result =0;
        else 
        {
        uint_8 i = 0;
        for(i;i<=size;i++)
        {
                if(ch1[i] != ch2[i]) result = 0;
        }
        }
        return result;
}
 void *_memset(void *dest, uint_8 val, uint_32 len)
{
    uint_8 *temp = (uint_8 *)dest;
    for ( ; len != 0; len--) *temp++ = val;

  return dest;
}
char *strcpy(char *s1, const char *s2)
{
    char *s1_p = s1;
    while (*s1++ = *s2++);
    return s1_p;
}

//! returns length of string
int strlen ( const char* str ) {

	int	len=0;
	while (str[len++]);
	return len;
}

#endif