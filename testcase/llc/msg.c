//#include "libi0/stddef.h"

#define STDIN   (0x100000200ULL)
#define STDOUT  (0x100000208ULL)

void main(void){
char msg[] = "hello";
for(unsigned i=0;i<sizeof(msg)/sizeof(msg[0]);++i){
*(volatile long*)STDOUT = msg[i];
}
}

void test2(void){
char msg[] = "world";
for(unsigned i=0;i<sizeof(msg)/sizeof(msg[0]);++i){
*(volatile long*)STDOUT = msg[i];
}
}

