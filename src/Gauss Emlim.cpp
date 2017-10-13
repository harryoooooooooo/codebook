#include <vector>
#include <cstdio>
using namespace std;


vector<vector<double>> mat;

// n for how many vars, expect the inside length > n
void guass(size_t n){
    auto len = mat[0].size();
    auto m = mat.size();
    for(size_t x = 0 ; x < n ; x ++){
        for(size_t i = x ; i < m ; i ++){
            if(mat[i][x]!=0){
                if(i!=x){
                    swap(mat[i],mat[x]);
                }
                break;
            }
        }
        // Give up current var
        if(mat[x][x]==0)continue;
        {
            auto r = mat[x][x];
            for(size_t i = 0 ; i < len ; i ++){
                mat[x][i]/=r;
            }
        }
        for(size_t i = 0 ; i < m ; i ++){
            if(i==x)continue;
            auto r=mat[i][x];
            for(size_t j = 0 ; j < len ; j ++){
                mat[i][j]-=r*mat[x][j];
            }
        }
    }
}
