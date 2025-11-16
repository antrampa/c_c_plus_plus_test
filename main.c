#include <stdio.h>

extern const char* hello_asm();

int main(){
    const char* msg = hello_asm();
    printf("%s\n", msg);
    return 0;
}