#include <iostream>
#include <vector>
#include <queue>
#include <map>


using namespace std;

vector<pair<int, int>> edge[2010];

struct trip{
    int id;
    int rev;
    int dest;
};

trip arr[30010];
bool valid[30010];
int dp[2010];

map<int, int> mp;

int src;
const int inf =987654321;

int tn;

priority_queue<pair<int, int>> sale;

void calc(){

    fill_n(&dp[0], 2010, inf);
    dp[src] = 0;

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    pq.push({0, src});

    while(!pq.empty()){
        int p = pq.top().second;
        int d = pq.top().first;

        pq.pop();

        for(int i = 0;i<edge[p].size();i++){
            int pre = edge[p][i].first;
            int dd = edge[p][i].second;

            if(dp[pre] > dd+d){
                dp[pre] = dd+d;
                pq.push({dp[pre], pre});
            }
        }
    }
}

void sett(){

    int i, j, x, a, b;

    for(i=1;i<=tn;i++){
        if(!valid[i]) continue;

        x=arr[i].dest;

        if(dp[x] == inf) continue;
        int d = arr[i].rev - dp[x];

        if(d<0) continue; 
        sale.push({d, -arr[i].id});
    }
}

int main() {
    // Please write your code here.

    int testn, i, j, x, k, a, b, c, d, n, m;

    cin>>testn;

    cin>>k;

    cin>>n>>m;

    fill_n(&valid[0], 30010, true);

    tn = 0;

    for(i=1, src = 0;i<=m;i++){
        cin>>a>>b>>d;


        edge[a].push_back({b, d});
        edge[b].push_back({a, d});
    }
    calc();
    sett();

    testn--;

    

    while(testn--){
        cin>>k;
        
        if(k==200){
            cin>> a>>b>>d;
            arr[++tn] = {a, b, d};
            mp[a] = tn;


            if(dp[d] == inf) continue;
            int ddd = b - dp[d];

            if(ddd<0) continue; 
            sale.push({ddd, -a});

        } else if(k==300){
            cin>>x;
            valid[mp[x]]=false;

        } else if(k==400){
            while(!sale.empty() && !valid[mp[-sale.top().second]]) sale.pop();

            if(sale.empty()) cout<<"-1\n";
            else{
                cout<<-sale.top().second<<"\n";
                valid[mp[-sale.top().second]] =false;
                sale.pop();

            }
        }else{
            cin>>src;

            calc();
            while(!sale.empty()) sale.pop();
            sett();
        }
    }



    return 0;
}