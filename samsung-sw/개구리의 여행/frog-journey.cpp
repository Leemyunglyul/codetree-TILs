#include <iostream>
#include <vector>
#include <cmath>
#include <queue>
#include <algorithm>
#include <functional>
#include <string>

using namespace std;

struct dd{
    int p;
    int d;
};

struct pr{
    int d;
    int p;
    int j;

    bool operator>(const pr& a) const{
        return d > a.d;
    }
};

const int inf = 987654321;

bool go[3010];
int n;
vector<dd> edge[3010];
int dist[3010][6]; // [위치][점프력]
string arr[3010];

inline int tf(int r, int c){
    return (r-1)*n+c;
}

inline pair<int, int> rev(int x){
    return {(x-1)/n+1, (x-1)%n+1};
}

int dijkstra(int x, int y){
    priority_queue<pr, vector<pr>, greater<pr>> pq;

    int i;

    for(i=1;i<=n*n;i++){
        fill_n(dist[i], 6, inf);
    }

    dist[x][1] = 0;
    pq.push({0, x, 1});

    while(!pq.empty()){
        int pos = pq.top().p;
        int d = pq.top().d;
        int j = pq.top().j;
        pq.pop();

        if(d != dist[pos][j]) continue;
        if(pos == y) return d;

        for(i=0;i<(int)edge[pos].size();i++){
            int ppos = edge[pos][i].p;
            int ddd = edge[pos][i].d;

            if(j != ddd) continue;

            int cost = d+1;

            if(cost < dist[ppos][j]){
                dist[ppos][j] = cost;
                pq.push({cost, ppos, j});
            }
        }

        // 점프력 증가
        if(j < 5){
            int cost = d+(j+1)*(j+1);

            if(cost < dist[pos][j+1]){
                dist[pos][j+1] = cost;
                pq.push({cost, pos, j+1});
            }
        }

        // 점프력 감소
        for(i=1;i<j;i++){
            int cost = d+1;

            if(cost < dist[pos][i]){
                dist[pos][i] = cost;
                pq.push({cost, pos, i});
            }
        }
    }

    return -1;
}

void solve(){
    cin>>n;

    fill_n(&go[0], 3010, false);

    int i, j, k, x, y, a, b;
    string s;

    for(i=1;i<=n;i++){
        cin>>s;
        arr[i] = s;

        for(j=0;j<n;j++){
            if(s[j] == '.'){
                go[tf(i, j+1)] = true;
            }
        }
    }

    for(i=1;i<=n;i++){
        for(j=1;j<=n;j++){
            a = tf(i, j);

            if(!go[a]) continue;

            for(k=1;k<=n;k++){
                if(k==i) continue;
                if(abs(k-i)>5) continue;
                if(!go[tf(k, j)]) continue;

                bool check = true;

                for(int t=min(i, k)+1;t<max(i, k);t++){
                    if(arr[t][j-1] == '#'){
                        check = false;
                        break;
                    }
                }

                if(!check) continue;

                edge[a].push_back({tf(k, j), abs(k-i)});
            }

            for(k=1;k<=n;k++){
                if(k==j) continue;
                if(abs(k-j)>5) continue;
                if(!go[tf(i, k)]) continue;

                bool check = true;

                for(int t=min(j, k)+1;t<max(j, k);t++){
                    if(arr[i][t-1] == '#'){
                        check = false;
                        break;
                    }
                }

                if(!check) continue;

                edge[a].push_back({tf(i, k), abs(k-j)});
            }
        }
    }

    int testn;

    cin>>testn;

    while(testn--){
        cin>>x>>y>>a>>b;

        cout<<dijkstra(tf(x, y), tf(a, b))<<"\n";
    }
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    solve();

    return 0;
}