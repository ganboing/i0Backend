int external1(int x);
int external2(int x);

int proc(int x){
if(x<0)
return external1(x);
else
return external2(x);
}
