void test()
{
for(long i=0, j = *(long*)0x80;i<j;++i)
{
*(long*)0x40 *= i;
}

}
