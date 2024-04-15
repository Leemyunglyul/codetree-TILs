#include <iostream>
#include <queue>
#include <cmath>
#include <queue>
#include <tuple>

using namespace std;

int n,m, k, nn;
int arr[13][13];
int ord[13][13]={0};
bool rel[13][13];
int s1, s2, w1, w2, turn;


bool lazer(){
    bool visited[12][12];
    pair<int, int> prev[12][12];
    fill_n(&visited[0][0], 12*12, false);
    int i, j, r, c;
    for(i=1;i<=n;i++){
        for(j=1;j<=m;j++){
            if(arr[i][j]==0) visited[i][j]=true;
        }
    }

    queue<pair<int, int>> q;
    q.push({s1, s2});
    visited[s1][s2]=true;
    //0우1하2좌3상
    while(!q.empty()){
        r=q.front().first;
        c=q.front().second;
        q.pop();

        if(r==w1 && c==w2) break;

        //오른쪽
        if(c==m && !visited[r][1]){
            prev[r][1]={r, c};
            visited[r][1]=true;
            q.push({r, 1});
        }
        else if(c<m && !visited[r][c+1]){
            prev[r][c+1]={r, c};
            visited[r][c+1]=true;
            q.push({r, c+1});
        }

        //아래
        if(r==n && !visited[1][c]){
            prev[1][c]={r, c};
            visited[1][c]=true;
            q.push({1, c});
        }
        else if(r<n && !visited[r+1][c]){
            prev[r+1][c]={r, c};
            visited[r+1][c]=true;
            q.push({r+1, c});
        }

        //왼쪽
        if(c==1 && !visited[r][m]){
            prev[r][m]={r, c};
            visited[r][m]=true;
            q.push({r, m});
        }
        else if(c>1 && !visited[r][c-1]){
            prev[r][c-1]={r, c};
            visited[r][c-1]=true;
            q.push({r, c-1});
        }
        //위
        if(r==1 && !visited[n][c]){
            prev[n][c]={r, c};
            visited[n][c]=true;
            q.push({n, c});
        }
        else if(r>1 && !visited[r-1][c]){
            prev[r-1][c]={r, c};
            visited[r-1][c]=true;
            q.push({r-1, c});
        }
    }
    if(r!= w1 || c!=w2) return false;

    arr[w1][w2]-=arr[s1][s2];
    if(arr[w1][w2]<=0){
        arr[w1][w2]=0;
        nn--;
    }
    r=prev[w1][w2].first;
    c=prev[w1][w2].second;
    while(r!=s1 || c!=s2){
        arr[r][c]-=(arr[s1][s2]/2);
        rel[r][c]=true;
        if(arr[r][c]<=0){ 
            arr[r][c]=0;
            nn--;
        }
        int r1, r2;
        r1=prev[r][c].first;
        r2=prev[r][c].second;
        r=r1;
        c=r2;
    }
    return true;
}

pair<int, int> find(int r, int c){
    int x, y;
    if(r>=1 && r<=n){
        x=r;
    }
    else if(r==0){
        x=n;
    }
    else if(r==n+1){
        x=1;
    }

    if(c>=1 && c<=m){
        y=c;
    }
    else if(c==0){
        y=m;
    }
    else if(c==m+1){
        y=1;
    }
    return {x, y};
}

void bomb(){
    int i, j, r, c;
    arr[w1][w2]-=arr[s1][s2];
    int x=arr[s1][s2]/2;
    r=w1;c=w2;
    if(arr[w1][w2]<=0){
        arr[w1][w2]=0;
        nn--;
    }
    pair<int, int> z;

    for(i=r-1;i<=r+1;i++){
        for(j=c-1;j<=c+1;j++){
            if(i==r && j==c) continue;
            z=find(i, j);
            
            rel[z.first][z.second]=true;
            if(z.first==s1 && z.second==s2);
            else if(arr[z.first][z.second]==0);
            else{
                arr[z.first][z.second]-=x;
                if(arr[z.first][z.second]<=0){
                    arr[z.first][z.second]=0;
                    nn--;
                }
            }
        }
    }
    

}

int main() {
    // 여기에 코드를 작성해주세요.
    cin>>n>>m>>k;
    int i, j;
    for(i=1, nn=0;i<=n;i++){
        for(j=1;j<=m;j++){
            cin>>arr[i][j];
            if(arr[i][j]>0) nn++;
        }
    }
    for(turn=1;turn<=k;turn++){
        if(nn==1) break;
        fill_n(&rel[0][0], 13*13, false);
        priority_queue<tuple<int, int, int, int>> q1;
        priority_queue<tuple<int, int, int, int>> q2;
        for(i=1;i<=n;i++){
            for(j=1;j<=m;j++){
                if(arr[i][j]==0) rel[i][j]=true;
                else{
                    q1.push({-arr[i][j], ord[i][j], i+j, j});
                    q2.push({arr[i][j], -ord[i][j], -i-j, -j});
                }
            }
        }
        s1=get<2>(q1.top())-get<3>(q1.top());
        s2=get<3>(q1.top());
        arr[s1][s2]+=n+m;
        ord[s1][s2]=turn;
        rel[s1][s2]=true;
        w1=-get<2>(q2.top())+get<3>(q2.top());
        w2=-get<3>(q2.top());
        rel[w1][w2]=true;
        if(!lazer()){
            bomb();
        }
        //cout<<turn<<"///\n";
        for(i=1;i<=n;i++){
            for(j=1;j<=m;j++){
                //cout<<arr[i][j]<<" ";
                if(!rel[i][j]) arr[i][j]++;
            }//cout<<endl;
        }
    }
    int s=0;
    for(i=1;i<=n;i++){
            for(j=1;j<=m;j++){
                s=max(s, arr[i][j]);
            }
        }
    cout<<s;
    return 0;
}