//#include "libi0/stddef.h"

#define STDIN   (0x100000200ULL)
#define STDOUT  (0x100000208ULL)

void main(void);

void main(void){

long c;
while((c=*(long*)STDIN) != -1){

if(c>=0x61 && c<=0x7a){
c-=0x20;
}

*(long*)STDOUT = c;

}
}

/*void test(void);
void test(void){
long msg[] = {'e', 'q'};
for(unsigned i=0;i<sizeof(msg);++i){
*(long*)STDOUT = msg[i];
}
}*/
