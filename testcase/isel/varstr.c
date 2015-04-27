int external(char*);

int internal(long size)
{
char buf[size];
return external(buf);
}
