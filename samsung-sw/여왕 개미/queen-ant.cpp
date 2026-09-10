#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int arr[30010];
vector<int> ant; 

int main() {
    // Please write your code here.
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int k, q, i, j, n, m,x;

    cin>>q;

    q--;

    cin>>k>>n;

    for(i=1;i<=n;i++){
        cin>>arr[i];
    }

    while(q--){
        cin>>k;

        if(k==200){
            cin>>arr[++n];
        } else if(k==300){
            cin>>x;
            arr[x] = -1;
        } else{
            cin>>x;

            for(i=1, ant.clear();i<=n;i++){
                if(arr[i]>0) ant.push_back(arr[i]);
            }

            if(ant.empty()){
                cout<<"0\n";
                continue;
            }

            int s= 0;
            int e = ant[ant.size()-1] - ant[0];
            int mid;
            int idx;
            int dd;
            int anw =(s+e)/2;

            while(s<=e){

                mid = (s+e)/2;
                
                bool boo = false;
                //cout<<"haha: "<<mid<<"\n";
                for(i=2, idx = 0;i<=x;i++){
                    idx = upper_bound(ant.begin(), ant.end(), mid+ant[idx]) - ant.begin();
                    if(idx>=ant.size()) break;

                    //cout<<"////"<<idx<<"\n";
                } 
                if(idx>=ant.size() || ant[idx] + mid >= ant[ant.size()-1]) boo = true;
                else boo= false;

                if(boo){
                    anw = mid;
                    e = mid - 1;
                } else{
                    s = mid+1;
                }
                
            }

            cout<< anw<<"\n";
        }
    }

    return 0;
}