#include <stdio.h>

int func4(int x, int y, int z, int val, int r_val)
{
    val;//rcx
    r_val = x;//rax
    r_val -= y;
    val = r_val;
    val = val >> 0x1f;
    val += r_val;
    val = val >> 1;
    if(val > z)
    {
        x = val - 1;
        func4(x, y, z, val, r_val);
    }
    r_val = 0;
    if(val < 2)
    {
        y += val + 1;
        z = z+z+1;
    }
    return 0;
}

int main()
{
    static int x = 14;
    static int y = 0;
    static int z=0;//입력 한 수
    static int val = 0;
    static int r_val = 0;
    for(int i = 0; i < 15; ++i)
    {
        x = 14;
        y = 0;
        val = 0;
        r_val = 0;
        z = i;
        func4(x, y, z, val, r_val);
        printf("%d\n", r_val);
    }
    
}