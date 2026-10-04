#include <iostream>
#include <set>
using namespace std;

using pi = pair<int, int>;

int n;

pi arr[1200];
bool valid[1200];
int dp[3010];
set<pi> s;

int main() {
    // Please write your code here.

    int testn, i,j, w, v, k, a, b, c, x, tgt, s1, s2;

    cin>>testn;

    cin>>k >>n;

    fill_n(&valid[0], 1200, true);

    for(i=1;i<=n;i++){
        cin>>w>>v;

        arr[i]={w, v};
        s.insert({w, i});
    }

    testn--;

    while(testn--){
        cin>>k;

        if(k==2){
            cin>>w>>v;

            arr[++n] ={w, v};
            s.insert({w, n});
        } else if(k==3){
            cin>>x;

            if(!valid[x] || x > n) cout<<"-1\n";
            else{
                cout<<arr[x].second<<"\n";
                valid[x]=false;
                s.erase({arr[x].first, x});
            } 

            
        } else if(k==4){
            cin>>tgt;
            fill_n(&dp[0], 3010, -1);

            dp[0] = 0;

            int anw = 0;

            for(i=1;i<=n;i++){
                if(!valid[i]) continue;
                
                w = arr[i].first;
                v=arr[i].second;
                if(w>tgt) continue;

                for(j=tgt-1;j>=0;j--){
                    if(dp[j] ==-1 || j+w > tgt) continue;

                    dp[j+w] = max(dp[j+w], dp[j] + v);
                    anw = max(dp[j+w], anw);
                }
            }
            cout<<anw<<"\n";
        } else{
            cin>>tgt;

            if(s.size()<2){
                cout<<"0\n";
                continue;
            }

            auto i1 = s.begin();
            auto i2 = s.begin(); i2++;
            int s1 = 1;
            int s2 = 2;

            int anw = 0;
            while(1){
                if(i2 == s.end()) break;

                while(i2 != s.end() && i2->first - i1->first <= tgt){
                    
                    //cout<< i1 -> second <<" hhhh "<<i2->second<<endl;
                    anw+=(s2-s1);
                    i2++;
                    s2++;
                }

                if(i2 == s.end()) break;

                while(i1 != i2 && i2->first - i1->first > tgt){
                    //cout<< i1 -> second <<" xxxxx "<<i2->second<<endl;
                    i1++;
                    s1++;
                       
                }

                if(i1 ==  i2){
                    i2++;
                    s2++;
                }

            }
            cout<<anw<<"\n";
        }
    }

    return 0;
}