bool miller_rabin(int n)
{
    if (n < 2) return false; 
//  srand(time(0));
    int a = rand() % (n-2) + 2;
    int u = n-1, t = 0;
    while (u % 2 == 0) u >>= 1, t++;
    int x = pow(a, u, n);   // x = a ^ u % n;
    if (x == 1 || x == n-1) return true;
    for (int i=0; i<t-1; i++)
    {
        x = mul(x, x, n);   // x = x * x % n;
        if (x == 1) return false;
        if (x == n-1) return true;
    }
    return false;
}

