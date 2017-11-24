#include <cstdio>

void check(int sum){
    char a[1024*1024];
    a[sizeof(a)-1]=0;
    asm volatile (""::"g"(a):"memory");
    printf("%d MB pass\n", sum);
    check(sum+1);
}

int main (){
    check(1);
}
