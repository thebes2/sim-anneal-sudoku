#include <bits/stdc++.h>
using namespace std;

typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<pii> vpii;
typedef long double ld;
#define F first
#define S second
#define pb push_back

mt19937 mt(time(0));
inline int rng(int l,int r){return mt()%(r-l+1)+l;}

const ld ALPHA = 0.999999;
const ld BETA = 0.05;
const ld GAMMA = 5;
const ld DELTA = 0.9;

const int N = 9;
int i, j, k, cur, tmp, best;
vvi arr, sol; vpii fr;

inline int upd(int x,int y,int ov,int nv){
    int res = 0;
    for(int i=0;i<N;i++){
        if(i!=x){
            if(ov==arr[i][y]) res--;
            if(nv==arr[i][y]) res++;
        }
        if(i!=y){
            if(ov==arr[x][i]) res--;
            if(nv==arr[x][i]) res++;
        }
    }
    int bx = 3*(x/3), by = 3*(y/3);
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            if(i+bx!=x||j+by!=y){
                if(ov==arr[i+bx][j+by]) res--;
                if(nv==arr[i+bx][j+by]) res++;
            }
        }
    }
    return res;
}

int main(){
    freopen("sudoku.txt","r",stdin);
    vi num(N+1, 0);
    arr = vvi(N, vi(N, 0));
    vvi orig(N, vi(N, 0));
    for(i=0;i<N;i++){
        for(j=0;j<N;j++){
            char ch; scanf("%c",&ch);
            if(ch>='1'&&ch<='9'){
                orig[i][j] = ch-'0';
                num[ch-'0']++;
            }
            else fr.pb({i,j});
        }
        getchar();
    }
    for(auto v : fr){
        for(k=1;k<=N;k++){
            if(num[k]<N){
                num[k]++;
                orig[v.F][v.S] = k;
                break;
            }
        }
    }
    for(i=0;i<N;i++){
        for(j=0;j<N;j++){
            cur += upd(i, j, -1, orig[i][j]);
            arr[i][j] = orig[i][j];
        }
    }
    best = cur; sol = arr;
    ld temp = GAMMA;
    int cnt = 0, cyc = 0;
    while(best>0){
        int idx = rng(0, (int)fr.size()-1);
        int idx2 = rng(0, (int)fr.size()-1);
        int ccnt = 0;
        while((idx==idx2||arr[fr[idx].F][fr[idx].S]==arr[fr[idx2].F][fr[idx2].S])&&ccnt<400)
            idx2 = rng(0, (int)fr.size()-1), ccnt++;
        int x = fr[idx].F, y = fr[idx].S, nx = fr[idx2].F, ny = fr[idx2].S;
        int ov = arr[x][y], nv = arr[nx][ny];
        tmp = cur;
        tmp += upd(x, y, ov, nv);
        arr[x][y] = nv;
        tmp += upd(nx, ny, nv, ov);
        arr[nx][ny] = ov;
        if(tmp<cur) cur = tmp;
        else if(rng(1,1000000)/(ld)1000000<exp((cur-tmp)/temp)) cur = tmp;
        else swap(arr[x][y], arr[nx][ny]);
        if(cur<best){
            best = cur;
            sol = arr;
        }
        cnt = (cnt+1)%100;
        if(!cnt) printf("Temp: %.6Lf Cur: %d Best: %d\n",temp,cur,best);
        temp *= ALPHA;
        if(temp<=BETA) temp = DELTA;
    }
    if(best>0) printf("No solution found.\n");
    else{
        printf("Solution found.\n");
        for(i=0;i<N;i++){
            for(j=0;j<N;j++){
                printf("%d",sol[i][j]);
            }
            printf("\n");
        }
    }
    return 0;
}
