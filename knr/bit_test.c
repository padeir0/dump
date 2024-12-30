#include <stdint.h>
#include <stdio.h>

#define BYTE_TO_BINARY_PATTERN "%c%c%c%c%c%c%c%c"
#define BYTE_TO_BINARY(byte)  \
  ((byte) & 0x80 ? '1' : '0'), \
  ((byte) & 0x40 ? '1' : '0'), \
  ((byte) & 0x20 ? '1' : '0'), \
  ((byte) & 0x10 ? '1' : '0'), \
  ((byte) & 0x08 ? '1' : '0'), \
  ((byte) & 0x04 ? '1' : '0'), \
  ((byte) & 0x02 ? '1' : '0'), \
  ((byte) & 0x01 ? '1' : '0') 

#define LOWEST_BITS(n) (uint8_t)((1<<n)-1)
#define TOP_BITS(n) (uint8_t)(~((1<<(8-n))-1))

int main()
{
  int i = 0;
  char b = 0;
  while (i <= 8) {
    b = LOWEST_BITS(i);
    printf(BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY(b));
    printf(" ");
    b = TOP_BITS(i);
    printf(BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY(b));
    printf("\n");
    i+=1;
  }
  return 0;
}
