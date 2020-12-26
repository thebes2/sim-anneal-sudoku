#include <bits/stdc++.h>
using namespace std;

typedef vector<int> vi;

const int MN = 100, LIM = 9;
const long double GAMMA = 0.99999, ALPHA = 10, BETA = 1e-1;

int N=81, col[MN], sol[MN], mod[MN], deg[MN], i, j, x, y, best, ans, cur;
vi adj[MN]; mt19937 mt(time(0));
inline int rng(int l,int r){return mt()%(r-l+1)+l;}

inline void read(){
    N = 81;
    freopen("sudoku.txt","r",stdin);
    for(i=1;i<=N;i++) adj[i].clear();
    memset(col,0,sizeof(col));
    memset(mod,0,sizeof(mod));
    for(i=0;i<9;i++){
        for(j=0;j<9;j++){
            char x;
            scanf("%c",&x);
            int idx = i*9+j+1;
            if(x>='1'&&x<='9') col[idx]=x-'0', mod[idx]=1;
            else col[idx]=rng(1,LIM);
            int bx = (i/3)*3, by = (j/3)*3;
            for(int k=0;k<3;k++){
                for(int l=0;l<3;l++){
                    if(bx+k!=i||by+l!=j){
                        int ot = (bx+k)*9+by+l+1;
                        adj[idx].push_back(ot);
                    }
                }
            }
            for(int k=0;k<9;k++){
                if(k<bx||k>=bx+3){
                    int ot = k*9+j+1;
                    adj[idx].push_back(ot);
                }
                if(k<by||k>=by+3){
                    int ot = i*9+k+1;
                    adj[idx].push_back(ot);
                }
            }
        }
        getchar();
    }
}

inline int F(){
    int res = 0;
    for(int i=1;i<=N;i++){
        for(auto v : adj[i]){
            if(col[v]==col[i]) res++;
        }
    }
    return res;
}

inline int kth(int k){
    for(int i=1;i<=N;i++){
        if(k<=deg[i]+1) return i;
        else k -= deg[i]+1;
    }
}

inline void solve(){
    best = cur = ans = F()/2;
    for(i=1;i<=N;i++) sol[i]=col[i];
    long double temp = ALPHA;
    int cnt = 0;
    for(i=1;i<=N;i++){
        deg[i] = 0;
        for(auto v : adj[i]){
            if(col[v]==col[i]) deg[i]++;
        }
    }
    while(temp>BETA&&best>0){
        x = kth(rng(1, 2*ans+N));
        while(mod[x]) x = kth(rng(1, ans+N));
        int nc = rng(1, LIM);
        while(nc==col[x]) nc = rng(1, LIM);
        int orig = col[x];
        col[x] = nc;
        cur = ans;
        for(auto v : adj[x]){
            if(orig==col[v]) cur--;
            if(nc==col[v]) cur++;
        }
        if(cur<=ans||rng(1,1000000)/1000000.0<=exp((ans-cur)/temp)){
            ans = cur;
            deg[x] = 0;
            for(auto v : adj[x]){
                if(orig==col[v]) deg[v]--;
                if(nc==col[v]) deg[v]++, deg[x]++;
            }
        }
        else col[x] = orig;
        if(ans<best){
            best = ans;
            for(i=1;i<=N;i++) sol[i]=col[i];
        }
        temp *= GAMMA;
        cnt ++;
        if(cnt%10000==0){
            cerr << temp << " " << best << " " << ans << endl;
        }
        if(temp<=BETA&&best>0) temp = 1;
    }
    cerr << "TOTAL ITERATIONS: " << cnt << endl;
}

inline void print(){
    for(i=0;i<9;i++){
        for(j=0;j<9;j++){
            int idx = 9*i+j+1;
            printf("%d",sol[idx]);
        }
        printf("\n");
    }
}

int main(){
    read();
    solve();
    print();
}
