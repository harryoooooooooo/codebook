vector<pair<long long,long long>> ns;
long long res;
long long lcm;
vector<long long> prime;
bool isprime[10000010];
void init(){
    fill(isprime,isprime+10000010,true);
    for(int i = 2 ; i < 10000010 ; i ++){
        if(!isprime[i])continue;
        prime.push_back(i);
        for(int j = 2 ; i*j < 10000010 ; j ++){
            isprime[i*j]=false;
        }
    }
}

long long rm_prime;
long long rmod(long long x,long long y=rm_prime,long long ax = 1,long long ay=0){
    if(y==0){
        long long tmp=ax%rm_prime;
        if(tmp<0)tmp+=rm_prime;
        return tmp;
    }
    long long k=x/y;
    return rmod(y,x%y,ay,ax-k*ay);
}

bool crt(){
    struct r{
        long long pow;
        long long rem;
    };
    unordered_map<long long,r> prs;
    for(auto m:ns){
        for(auto p:prime){
            if(p>m.first)break;
            if(m.first%p==0){
                long long pow=1;
                while(m.first%p==0){
                    m.first/=p;
                    pow*=p;
                }
                long long rem = m.second%pow;
                if(prs.count(p)){
                    auto old=prs[p];
                    if(old.pow>=pow){
                        if(old.rem%pow!=rem)return false;
                    }
                    else{
                        if(rem%old.pow!=old.rem)return false;
                        prs[p]={pow,rem};
                    }
                }
                else{
                    prs[p]={pow,rem};
                }
            }
        }
    }
    //need mul sum is in long long
    lcm=1;
    for(auto m:prs){
        lcm*=m.second.pow;
    }
    res=0;
    for(auto m:prs){
        long long tmp=m.second.rem;
        tmp*=lcm/m.second.pow;
        rm_prime=m.second.pow;
        tmp*=rmod(lcm/m.second.pow);
        tmp%=lcm;
        res+=tmp;
        res%=lcm;
    }
    return true;
}
int main (){
    init();
    ns.push_back({84,23});
    ns.push_back({160,7});
    ns.push_back({63,2});
    crt();
    printf("%lld\n",res);
}
