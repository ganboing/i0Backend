void test(){

long a = *(long*)0x80;
long b = *(long*)0x60;
*(long*)0x100 = a*b;

}
