#include <stdio.h>

int main()
{
    unsigned char buffer[100];
    FILE *ptr;

    ptr = fopen("hello.obj","rb");  // r for read, b for binary

    fread(buffer,sizeof(buffer),1,ptr);
    
    for(int i = 0; i<10; i++)
    printf("%u ", buffer[i]);
}
