#include <iostream>
#include <set>
#include <vector>
#include <algorithm>
using namespace std;

bool valid[2000];
int arr[2000];
int dp[3010];
set<int> s;

int n, idx;

const int inf = 987654321;


int main() {
    // Please write your code here.
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int testn;

    cin>>testn;

    int x, n, i, k, j, a, b, c;

    cin>>x;

    cin>>n;

    fill_n(&valid[0], 2000, true);
    for(i=1, idx = 1;i<=n;i++){
        cin>>arr[idx++];
    }

    testn--;

    while(testn--){
        cin>>k;

        if(k==2){
            cin>>arr[idx++];
        } else if(k==3){
            cin>>x;
            if(x < idx && valid[x])cout<<arr[x]<<"\n";
            else cout<<"-1\n";
            valid[x]=false;
            
        } else if(k==4){
            cin>>x;

            for(i = 1, dp[0]=0;i<=x;i++) dp[i]=inf;

            s.clear();

            for(i=1;i<idx;i++){
                if(valid[i]) s.insert(arr[i]);

            }

            for(auto it = s.begin();it!=s.end();it++){
                int tgt = *it;

                for(i=0;i<x;i++){
                    if(i+tgt>x) break;
                    if(dp[i] == inf) continue;
                    
                     //cout<<i+tgt<<": "<<dp[i+tgt]<<"\n";
                    dp[i+tgt] = min(dp[i+tgt], dp[i] + 1);

                    //cout<<i+tgt<<": "<<dp[i+tgt]<<"\n";
                }
            }

            if(dp[x]==inf) cout<<"-1\n";
            else cout << dp[x]<<"\n";
        } else{

            cin>>x;
            
            vector<int> v;
            for(i=1;i<idx;i++){
                if(valid[i]) v.push_back(arr[i]);
            }

            int siz = v.size();

            sort(v.begin(), v.end());

            int dd;

            long long anw = 0;
            for(i=0;i<siz;i++){
                for(j=0;j<siz;j++){
                    int sum = v[i]+v[j];
                    dd = lower_bound(v.begin(), v.end(), x - sum) - v.begin();

                    
                    anw+= siz-dd;
                }
            }

            cout<<anw<<"\n";

        }
    }

    return 0;
}