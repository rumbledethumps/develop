#include <rp6502.h>
#include <stdio.h>
#include <stdarg.h>

volatile uint8_t foo_a;
volatile uint8_t foo_x;
volatile uint8_t foo_y;

volatile int foo_z;

// extern void __cdecl__ foo(unsigned char dev_chan, ...);

extern void __cdecl__ foo(unsigned char dev_chan, char x, ...);

void fooxxxx(unsigned dev_chan, ...)
{
    va_list args;
    va_start(args, dev_chan);
    foo_z = va_arg(args, int);
    foo_z = va_arg(args, int);
    // foo_a = 0;
    va_end(args);
}

void main()
{
    puts("Hello, world!");
    foo(0x66,0x1111,0x2222,0x3333);
    // RIA_BLOCK();
    foo(0x66, 9,8,7,6,5,4,3,2,1,0);
    // RIA_BLOCK();
    foo(0x66, 0x42);
    // RIA_BLOCK();
}
