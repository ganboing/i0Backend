void add()
{
long* pa = (long*)0x500;
long* pb = (long*)0x400;
long a = *pa;
long b = *pb;
long* c = (long*)0x800;
*c = a+b;
}
