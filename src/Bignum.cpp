#include<iostream>
#include<iomanip>
#include<array>
using namespace std;

template<int N>
class bignum{
    array<long long,N+2> a;
    static const long long m = 1e8;
    void shift(int x){
        for (int i=N;i>=x;i--)
            a[i] = a[i-x];
        for (int i=0;i<x;i++)
            a[i] = 0;
    }
public:
    bignum():a(){}
    bignum(long long x):a(){
        if (x<0) *this -= (-x);
        else {
            a[0] = x%m;
            a[1] = (x/m)%m;
            a[2] = x/m/m;
        }
    }
    bignum(const bignum<N> &) = default;
    bignum(bignum<N> &&) = default;
    bignum& operator=(const bignum<N> &) = default;
    bignum& operator=(bignum<N> &&) = default;
    bignum<N>& operator+=(const bignum<N>& r){
        for (int i=0;i<N+1;i++){
            a[i]+=r.a[i];
            if (a[i]>=m){
                a[i]-=m;
                a[i+1]+=1;
            }
        }
        return *this;
    }
    bignum<N>& operator-=(const bignum<N>& r){
        for (int i=0;i<N+1;i++){
            a[i]-=r.a[i];
            if (a[i]<0){
                a[i]+=m;
                a[i+1]-=1;
            }
        }
        return *this;
    }
    bignum<N> operator-()const{
        bignum<N> res;
        res -= *this;
        return res;
    }
    bignum<N> operator+(const bignum<N>& r)const{
        bignum<N> res = *this;
        res += r;
        return res;
    }
    bignum<N> operator-(const bignum<N>& r)const{
        bignum<N> res = *this;
        res -= r;
        return res;
    }
    bignum<N> operator*(const bignum<N>& r)const{
        bignum<N> res;
        for (int i=0;i<N+1;i++){
            bignum<N> tmp = r;
            auto& b = tmp.a;
            for (int j=0;j<N+1;j++)
                b[j] *= a[i];
            for (int j=0;j<N+1;j++){
                b[j+1] += b[j]/m;
                b[j] %= m;
            }
            tmp.shift(i);
            res += tmp;
        }
        return res;
    }
    bignum<N>& operator*=(const bignum<N>& r){
        *this = (*this) * r;
        return *this;
    }
    bool operator<(const bignum<N>& r)const{
        auto& b = r.a;
        if ((a[N]%2)^(b[N]%2)) return a[N]%2;
        if (a[N]%2){
            for (int i=N-1;i>=0;i--)
                if (a[i]!=b[i]) return a[i]>b[i];
        }
        else {
            for (int i=N-1;i>=0;i--)
                if (a[i]!=b[i]) return a[i]<b[i];
        }
        return false;
    }
    bool operator>(const bignum<N>& r)const{
        auto& b = r.a;
        if ((a[N]%2)^(b[N]%2)) return b[N]%2;
        if (a[N]%2){
            for (int i=N-1;i>=0;i--)
                if (a[i]!=b[i]) return a[i]<b[i];
        }
        else {
            for (int i=N-1;i>=0;i--)
                if (a[i]!=b[i]) return a[i]>b[i];
        }
        return false;
    }
    bool operator<=(const bignum<N>& r)const{
        return !(*this>r);
    }
    bool operator>=(const bignum<N>& r)const{
        return !(*this<r);
    }
    bool operator==(const bignum<N>& r)const{
        auto& b = r.a;
        if ((a[N]%2)^(b[N]%2)) return false;
        for (int i=0;i<N;i++)
            if (a[i]!=b[i]) return false;
        return true;
    }
    bool operator!=(const bignum<N>& r)const{
        return !(*this==r);
    }
    friend ostream& operator<<(ostream& o, const bignum<N>& r){
        bignum<N> tmp;
        if (r.a[N]%2){
            o << '-';
            tmp = -r;
        }
        else tmp = r;
        bool first = true;
        for (int i=N-1;i>=0;i--){
            if (first && !tmp.a[i]) continue;
            if (first) o << tmp.a[i];
            else o << setfill('0') << setw(8) << tmp.a[i];
            first = false;
        }
        if (first) o << '0';
        return o;
    }
};

int main (){
    // template 5 means that its maximum is 10^(5*8)
    bignum<5> a = -100;
    for (int i=0;i<20;i++){
        a*=-100;
        cout << a << endl;
    }
}
