#include <stdint.h>

void main() {

    uint64_t r15;


    asm volatile (
        "movq %0, %%rip      \n"
        :            // input
        : "r" (r15)  // output
        :            // clobber
    );

}


