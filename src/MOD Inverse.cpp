const int prime = 1e9+7;

long long rmod(long long x,long long y = prime,long long ax = 1,long long ay=0){
    if(y==0){
        long long tmp=ax%prime;
        if(tmp<0)tmp+=prime;
        return tmp;
    }
    long long k=x/y;
    return rmod(y,x%y,ay,ax-k*ay);
}
