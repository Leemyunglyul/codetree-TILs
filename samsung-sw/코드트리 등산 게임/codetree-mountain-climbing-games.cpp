#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

using pi = pair<int, int>;

pi tree[4000010];

int best[4000010];

struct mt{
    int h;
    int dp;
    int prev;
};

vector<mt> arr(1);

void update(int n, int l, int r, int idx, int val){
    if(l==r){
        if(val == 0) tree[n] = {0, 0};
        else tree[n] = {val, idx};
        return;
    }

    int mid = (l+r)/2;

    if(idx <= mid){
        update(n*2, l, mid, idx, val);
    } else{
        update(n*2+1, mid+1, r, idx, val);
    }

    tree[n] = max(tree[n*2], tree[n*2+1]);
}

int query(int n, int l, int r, int a, int b){
    if(b < l || r < a) return 0;

    if(a <= l && r <= b){
        return tree[n].first;
    }

    int mid = (l+r)/2;

    return max(query(n*2, l, mid, a, b), query(n*2+1, mid+1, r, a, b));
}

void add(int h){
    int d = query(1, 1, 1000000, 1, h-1) + 1;

    arr.push_back({h, d, best[h]});

    best[h] = d;
    update(1, 1, 1000000, h, d);
}

void del(){
    mt x = arr.back();
    arr.pop_back();

    best[x.h] = x.prev;
    update(1, 1, 1000000, x.h, x.prev);
}


int main() {
    // Please write your code here.
    ios::sync_with_stdio(0);
    cin.tie(0);

    int testn, k, n, i, h, x;

    cin>>testn;

    while(testn--){
        cin>>k;

        if(k==100){
            cin>>n;

            for(i=1;i<=n;i++){
                cin>>h;
                add(h);
            }

        } else if(k==200){
            cin>>h;
            add(h);

        } else if(k==300){
            del();

        } else if(k==400){
            cin>>x;

            int before = arr[x].dp;
            int after = tree[1].first;
            int last_height = tree[1].second;

            long long ans =
                (long long)(before + after - 1) * 1000000
                + last_height;

            cout<<ans<<"\n";
        }
    }


    return 0;
}