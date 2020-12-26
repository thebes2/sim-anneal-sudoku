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
const ld GAMMA = 1.5;
const ld DELTA = 0.9;

const int N = 9;
const int M = sqrt(N);
int i, j, k, cur, tmp, best, bit[N*N+1];
vvi arr, sol;

inline void print(vvi x){
    for(auto r : x){
        for(auto v : r){
            printf("%d",v);
        }
        printf("\n");
    }
}

inline int kth(int k){
    int cur = 0;
    for(int i=10;i>=0;i--){
        if(cur+(1<<i)<=(N*N)&&bit[cur+(1<<i)]<k){
            cur += (1<<i);
            k -= bit[cur];
        }
    }
    return cur+1;
}

inline void upd(int p,int v){for(;p<=N*N;p+=p&-p)bit[p]+=v;}
inline int qu(int p){int sm=0;for(;p;p-=p&-p)sm+=bit[p];return sm;}

int main(){
    freopen("sudoku.txt","r",stdin);
    arr = vvi(N, vi(N, 0));
    vvi can(N, vi(N, 1));
    for(i=0;i<N;i++){
        for(j=0;j<N;j++){
            char ch; scanf("%c",&ch);
            if(ch>='1'&&ch<='9'){
                arr[i][j] = ch-'0';
                can[i][j] = 0;
                cur ++;
            }
            else{upd(i*N+j+1,1);}
        }
        getchar();
    }
    best = cur; sol = arr;
    ld temp = GAMMA;
    int cnt = 0, cyc = 0;
    while(best<N*N&&temp>BETA){
        int idx = kth(rng(1, N*N-cur));
        int x = (idx-1)/N, y = (idx-1)%N;
        int ccnt = 0, nv = rng(1, N), ok = 0;
        while(ccnt<50){
            int flg = 0;
            for(int i=0;i<N;i++){
                if(arr[i][y]==nv&&!can[i][y]){flg=1; break;}
                if(arr[x][i]==nv&&!can[x][i]){flg=1; break;}
            }
            int bx = M*(x/M), by = M*(y/M);
            if(!flg){
                for(int i=0;i<M;i++){
                    for(int j=0;j<M;j++){
                        if(nv==arr[i+bx][j+by]&&!can[i+bx][j+by]){flg=1; break;}
                    }
                    if(flg) break;
                }
            }
            if(!flg){ok = 1; break;}
            else nv = rng(1, N), ccnt++;
        }
        if(ok){
            tmp = cur+1;
            for(int i=0;i<N;i++){
                if(arr[i][y]==nv) tmp--;
                if(arr[x][i]==nv) tmp--;
            }
            int bx = M*(x/M), by = M*(y/M);
            for(int i=0;i<M;i++){
                for(int j=0;j<M;j++){
                    if(nv==arr[i+bx][j+by]&&i+bx!=x&&j+by!=y) tmp--;
                }
            }
            if(tmp>=cur||rng(1,1000000)/(ld)1000000<exp((tmp-cur)/temp)){
                cur = tmp;
                for(int i=0;i<N;i++){
                    if(arr[i][y]==nv) arr[i][y]=0, upd(i*N+y+1,1);
                    if(arr[x][i]==nv) arr[x][i]=0, upd(x*N+i+1,1);
                }
                for(int i=0;i<M;i++){
                    for(int j=0;j<M;j++){
                        if(nv==arr[i+bx][j+by]) arr[i+bx][j+by]=0, upd((i+bx)*N+j+by+1,1);
                    }
                }
                arr[x][y] = nv; upd(x*N+y+1, -1);
            }
            if(cur>best){
                best = cur;
                sol = arr;
            }
            temp *= ALPHA;
            // if(temp<=BETA) temp = DELTA;
        }
        //cnt = (cnt+1)%5000;
        //if(!cnt) printf("Temp: %.6Lf Cur: %d Best: %d\n",temp,cur,best);
    }
    if(best<N*N) printf("No solution found.\n");
    else printf("Solution found.\n"), print(sol);
    return 0;
}
