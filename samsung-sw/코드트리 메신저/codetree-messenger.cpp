#include <iostream>
#include <algorithm>
using namespace std;

int parent[100100];
int force[100100];
int dp[100100][21];
bool onn[100100];

int n;

void update(int nod, int num, int x){
    if(num == 0 || !onn[nod] || x == 0) return;

    int p = parent[nod];
    if(p == 0) return;

    dp[p][num-1] += x;

    update(p, num-1, x);
}

void update2(int nod, int x){
    if(!onn[nod]) return;

    for(int i=1;i<=20;i++){
        update(nod, i, dp[nod][i] * x);
    }
}

void init(){
    int i;

    for(i=1;i<=n;i++){
        dp[i][force[i]]++;
    }

    for(i=1;i<=n;i++){
        update(i, force[i], 1);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int testn, k, i, a, b, x, p, y;

    cin>>n>>testn;

    cin>>k;

    fill_n(&onn[0], 100100, true);

    for(i=1;i<=n;i++){
        cin>>parent[i];
    }

    for(i=1;i<=n;i++){
        cin>>force[i];
        force[i] = min(force[i], 20);
    }

    init();

    testn--;

    while(testn--){
        cin>>k;

        if(k==200){
            cin>>x;

            if(onn[x]){
                update2(x, -1);
                onn[x] = false;
            } else{
                onn[x] = true;
                update2(x, 1);
            }

        } else if(k==300){
            cin>>x>>p;

            p = min(p, 20);

            update(x, force[x], -1);
            dp[x][force[x]]--;

            force[x] = p;

            dp[x][force[x]]++;
            update(x, force[x], 1);

        } else if(k==400){
            cin>>a>>b;

            update2(a, -1);
            update2(b, -1);

            x = parent[a];
            y = parent[b];

            parent[a] = y;
            parent[b] = x;

            update2(a, 1);
            update2(b, 1);

        } else if(k==500){
            cin>>x;

            int ans = 0;

            for(i=0;i<=20;i++){
                ans += dp[x][i];
            }

            cout<<ans-1<<"\n";
        }
    }

    return 0;
}