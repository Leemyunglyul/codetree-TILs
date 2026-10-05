#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

using ll = long long;

int N;
ll B;
vector<int> a;

int main() {
    cin >> N >> B;

    a.resize(N);
    ll minn = 987654321;
    for (int i = 0; i < N; i++) {
        cin >> a[i];
        minn = min((ll)a[i], minn);
    }

    // Please write your code here.

    ll s = minn;
    ll e = 2987654321;
    ll mid, bug;

    while(s<e){
        
        mid = (s+e)/2;

        bug = B;

        for (int i = 0; i < N; i++) {
            if(mid > a[i]) bug -= (a[i]-mid)*(a[i]-mid);
            if(bug < 0) break;
        }

        if(bug < 0){
            e = mid;
        } else if(bug == 0) break;
        else{
            s = mid + 1;
        }
    }

    if(bug >= 0) cout<<mid;
    else cout<<mid-1;

    return 0;
}
