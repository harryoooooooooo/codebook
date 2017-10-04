#include<cstdio>

int main (){
    // t = x * y
    // they are all n*n matrix
    const int n = 3;
    for (int i=0;i<n;i++){
        for (int j=0;j<n;j++){
            printf("t[%d][%d]=(", i, j);
            for (int k=0;k<n;k++){
                if (k) printf("+");
                printf("(x[%d][%d]*y[%d][%d])%%prime", i, k, k, j);
            }
            printf(")%%prime;\n");
        }
    }
    printf(" = {{");
    for (int i=0;i<n;i++){
        if (i) printf(",");
        printf("{");
        for (int j=0;j<n;j++){
            if (j) printf(",");
            printf("%d", i==j?1:0);
        }
        printf("}");
    }
    printf("}};\n");
}
