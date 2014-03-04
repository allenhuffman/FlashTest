FlashTest
=========

Macros to simplify storing strings and arrays of strings in flash memory versus RAM.

These macros were created for my sesTelnetServer project when I needed to store a bunch of strings in an array. I originally was using normal C arrays in RAM, and when I ran out of memory I had to go convert them to use flash. This required a number of changes to the code, so I decided to make macros so I would never have to make those changes again. Now I always use these macros for strings and arrays of strings, and I can easily switch between them using RAM or flash just by altering a #define at the top of the file.

Maybe they will be of use to someone else.
