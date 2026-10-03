#include <iostream>
#include <set>
#include <vector>
#include <queue>
#include <cmath>
#include <map>
using namespace std;

struct light{
    int d;
    int l;
    int lp;
    int r;
    int rp;
};

struct cmp{
    bool operator()(const light& a, const light& b) const{
        if(a.d != b.d) return a.d < b.d;
        if(a.l != b.l) return a.l > b.l;
        return a.r > b.r;
    }
};


map<int, int> tf;

set<int> s;
priority_queue<light, vector<light>, cmp> pq;
bool valid[200100];
int arr[200100];

int n, m, idx;

int main() {

    ios_base::sync_with_stdio(0);

    // Please write your code here.

    int testn, k, x, i, j, a, b, c, prev, d, y;
    cin>>testn;

    cin>>k;
    cin>>n>>m;
    fill_n(&valid[0], 200100, true);
    for(i=1, idx = m+1;i<=m;i++){
        cin>>x;
        arr[i] = x;
        s.insert(x);
        tf.insert({x, i});

        if(i>1){
            light t = {x-prev, prev, i-1,x, i};
            pq.push(t);
        }

        prev = x;
    }


    testn--;

    while(testn--){
        cin>>k;

        if(k==200){

            while(1){
                a = pq.top().lp;
                b = pq.top().rp; 
                d = pq.top().d;

                if(!valid[a] || !valid[b]){
                    pq.pop();
                    continue;
                }

                auto it = s.find(arr[a]);
                it++;

                
            
                if(*it != arr[b]){
                    pq.pop();
                    continue;
                }

                break;
            }

            x = arr[a];
            y = arr[b];

            int pos = ((x+y)%2==0) ? (x+y)/2 : (x+y)/2 + 1;
            arr[idx] = pos;
            light lt = {pos-x, x, a, pos, idx};
            pq.push(lt);
            lt = {y-pos, pos, idx, y, b};
            pq.push(lt);
            s.insert(pos);
            tf.insert({pos, idx});

            //cout<<pos<<" /// "<<"\n";

            idx++;
            //cout<<"200 성공\n";

        } else if(k==300){
            cin>>x;
            // cout<<"300 성공\n";

            auto it1 = s.find(arr[x]);
            if(it1==s.begin()){
                s.erase(arr[x]);
            valid[x]=false;
            tf.erase(arr[x]);
            continue;
            }
            it1--;
                        
            
            auto it2 = s.find(arr[x]);
            it2++;
            if(it2==s.end()){
                s.erase(arr[x]);
                valid[x]=false;
                tf.erase(arr[x]);
                continue;
            }
            
            a = tf[*it1];

            b = tf[*it2];

            pq.push({arr[b]-arr[a], arr[a], a , arr[b], b});

            
            s.erase(arr[x]);
            valid[x]=false;
            tf.erase(arr[x]);
        } else{
            while(1){
                a = pq.top().lp;
                b = pq.top().rp; 
                d = pq.top().d;

                if(!valid[a] || !valid[b]){
                    pq.pop();
                    continue;
                }

                auto it = s.find(arr[a]);
                it++;
            
                if(*it != arr[b]){
                    pq.pop();
                    continue;
                }

                break;
            }

            auto it = s.begin();
            int d1 = *it - 1;
            
            it = s.end();
            it--;
            int d2 = n - *it;

            int anw = max(max(2*d1, 2*d2), d);
            cout<<anw<<"\n";
        }
    }

    

    return 0;
}