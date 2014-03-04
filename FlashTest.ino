/*-----------------------------------------------------------------------------
 
 Flash Test for strings and arrays of strings
 By Allen C. Huffman
 www.subethasoftware.com
 
 This is just a test showing how you can handle arrays of strings and have
 them stored in RAM or in flash based on using some macros/defines from the
 FlashMem.h header file.

 Compile this with #define USE_FLASH commented out and see how much RAM it
 uses, then compile and run it using USE_FLASH and see the difference. By
 using the FLASHMEM define and the FLASHSTR()/FLASHPTR() macros, your code
 can work with either way. If you do it manually, you have to go in and
 change all your code to make things work in flash.
 
 NOTE: This does not work with everything. Creating an array in memory or
 in PROGMEM can not be done easily since you have to use functions like
 memcpy_P() or pgm_read_byte_near() to access the data, so a simple macro
 trick won't work. However, in time, I will expand the header file to include
 a few more things to make this easier.
 
 2014-03-04 1.00 allenh - Posted to GitHub.
 -----------------------------------------------------------------------------*/

//#include <avr/pgmspace.h>

//#define USE_FLASH
#include "FlashMem.h"

// USE_FLASH - 1835 bytes free
// without   - 1797 bytes free (38 bytes less RAM)

// (Earlier tests showed 36 bytes different, which was what I expected - 30
// for the strings, and 6 for the three 16-bit pointers. I'll have to see
// where the other two bytes are going.)

/*---------------------------------------------------------------------------*/

// This creates three 10 byte strings.
// 10 bytes for each string. 30 bytes total here.
char string1[] FLASHMEM = "String #1"; // 9+NULL = 10 bytes
char string2[] FLASHMEM = "String #2"; // 
char string3[] FLASHMEM = "String #3"; // 30 bytes total here.

// This creates an array of three pointers to the three strings.
// 2 bytes for each pointer to string. 6 bytes total here.
const char *flashArray[] FLASHMEM = { string1, string2, string3 };

// This was just a test.
//const char * FLASHMEM flashArray[] = { string1, string2, string3 };

/*---------------------------------------------------------------------------*/

void setup()
{
  int i;
  
  Serial.begin(9600);
  while(!Serial);

#if defined(USE_FLASH)
  Serial.println(F("Using Flash"));
#else
  Serial.println(F("Using RAM  "));
#endif

  // Print a string.
  Serial.print(F("X. "));
  Serial.println(FLASHSTR(string1));

  // Print the strings inside the array.
  for (i=0; i<3; i++) {
    Serial.print(i);
    Serial.print(F(". "));
    Serial.println(FLASHPTR(flashArray[i]));
  }
  
  showFreeRam();
}

void loop()
{
}

/*---------------------------------------------------------------------------*/
// Some functions to display free memory, used for testing.

unsigned int freeRam()
{
  extern int __heap_start, *__brkval; 
  int v; 
  return (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval); 
}

void showFreeRam()
{
  Serial.print(F("Free RAM: "));
  Serial.println(freeRam());
}

// End of FlashTest
