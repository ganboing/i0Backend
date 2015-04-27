class PP<dag para1>
{
dag Para1 = para1;
}

class KK<int _a>
{
int a = _a;
}

def k1 : KK<1>;
def k2 : KK<2>;

def p1 : PP<(k1 k1:$t1, k2:$t2)>;

