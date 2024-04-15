#include <iostream>
#include <vector>
#include <queue>
#include <tuple>

using namespace std;

class part{
    public:
    int r, c;
    bool ex=false;
};

int turn=0;
int partn;
int dis=0;
part p[13];
int arr[13][13];
vector<int> list[25][25];
int n,m,k, e1, e2;

void p_move(){
    int i, j, r, c;
   // cout<<e1<<" "<<e2<<endl;
    for(i=1;i<=m;i++){
        if(p[i].ex) continue;
        r=p[i].r;
        c=p[i].c;
        //상 하로 움직이기.
        
        if(c==e2){
            if(r>e1 && arr[r-1][c]==0){
                r--;
                dis++;
            }
            else if(r<e1 && arr[r+1][c]==0){
                r++;
                dis++;
            }
            p[i].r=r;
        }
        else if(r==e1){
            if(c>e2 && arr[r][c-1]==0){
                c--;
                dis++;
            }
            else if(c<e2 && arr[r][c+1]==0){
                c++;
                dis++;
            }
            p[i].c=c;
        }
        
        else{
            if(r>e1 && c>e2){
                if(arr[r-1][c]==0){
                    r--;
                    dis++;
                }
                else if(arr[r][c-1]==0){
                    c--;
                    dis++;
                }
            }
            else if(r>e1 && c<e2){
                 if(arr[r-1][c]==0){
                    r--;
                    dis++;
                }
                else if(arr[r][c+1]==0){
                    c++;
                    dis++;
                }
            }
            else if(r<e1 && c<e2){
                 if(arr[r+1][c]==0){
                    r++;
                    dis++;
                }
                else if(arr[r][c+1]==0){
                    c++;
                    dis++;
                }
            }
            else if(r<e1 && c>e2){
                 if(arr[r+1][c]==0){
                    r++;
                    dis++;
                }
                else if(arr[r][c-1]==0){
                    c--;
                    dis++;
                }
            }
            p[i].r=r;
            p[i].c=c;
        }
        if(r==e1 && c==e2){
            p[i].ex=true;
            partn--;
        }
       // if(!p[i].ex)cout<<i<<"번"<<r<<" "<<c<<endl;
    }
}

void rot(int rr, int cc, int len);

void bfs(){
    bool visited[20][20];
    fill_n(&visited[0][0], 20*20, false);

    int i, j, r, c, num;
    bool person[20][20];
    fill_n(&person[0][0], 20*20, false);
    for(i=1;i<=m;i++){
        if(p[i].ex) continue;
        person[p[i].r][p[i].c]=true;
    }
    int p1, p2;
    int b1, b2, b;
    queue<tuple<int, int, int>> q;
    q.push({e1, e2, 0});
    visited[e1][e2]=true;
    bool ad=true;
    b1=10000;b2=10000;b=10000;
    while(!q.empty()){
        r=get<0>(q.front());
        c=get<1>(q.front());
        num=get<2>(q.front());
        q.pop();
        if(person[r][c]&&b>=num){
            ad=false;
            int m1=max(r, e1);
            int m2=max(c, e2);
            if(m1-num<1) p1=1;
            else p1=m1-num;
            if(m2-num<1) p2=1;
            else p2=m2-num;
            if(b1>p1){
                b1=p1;
                b2=p2;
                b=num;
            }
            else if(b1==p1){
                if(b2>p2){
                b1=p1;
                b2=p2;
                b=num;
                }
            }
        }
        if(!ad) continue;

        if(r>1 && c>1 && !visited[r-1][c-1]){
            q.push({r-1, c-1, num+1});
            visited[r-1][c-1]=true;
        }
        if(r>1 && !visited[r-1][c]){
            q.push({r-1, c, num+1});
            visited[r-1][c]=true;
        }
        if(r>1 && c<n && !visited[r-1][c+1]){
            q.push({r-1, c+1, num+1});
            visited[r-1][c+1]=true;
        }
        if(c>1 && !visited[r][c-1]){
          q.push({r, c-1, num+1});
            visited[r][c-1]=true;
        }
        if(c<n && !visited[r][c+1]){
           q.push({r, c+1, num+1});
            visited[r][c+1]=true;
        }
        if(r<n && c>1 && !visited[r+1][c-1]){
           q.push({r+1, c-1, num+1});
            visited[r+1][c-1]=true;
        }
        if(r<n && !visited[r+1][c]){
            q.push({r+1, c, num+1});
            visited[r+1][c]=true;
        }
        if(r<n && c<n && !visited[r+1][c+1]){
            q.push({r+1, c+1, num+1});
            visited[r+1][c+1]=true;
        }
    }
   // cout<<b1<<" "<<b2<<" "<<b<<endl;
    if(b==10000){ 
        //cout<<"hmm";
        return;

    }
    rot(b1, b2, b);
}

void rot(int rr, int cc, int len){
  // cout<<"회전 회오리\n";
   // cout<<rr<<" "<<cc<<" "<<len<<endl;
    vector<int> temp[20][20];
    vector<int> rot[20][20];
    int i, j, k, a1, a2;
    for(i=rr;i<=rr+len;i++){
        for(j=cc;j<=cc+len;j++){
            if(i==e1 && j==e2){
                temp[i][j].push_back(10000);
            }
            else temp[i][j].push_back(arr[i][j]);
        }
    }
    
    for(i=1;i<=m;i++){
        if(p[i].ex) continue;
        temp[p[i].r][p[i].c].push_back(i);
    }
    for(i=cc,a1=rr;i<=cc+len;i++, a1++){
        for(j=rr+len, a2=cc;j>=rr;j--, a2++){
            for(k=0;k<temp[j][i].size();k++){
                rot[a1][a2].push_back(temp[j][i][k]);
            }
        }
    }
    for(i=rr;i<=rr+len;i++){
        for(j=cc;j<=cc+len;j++){
            if(rot[i][j][0]==10000){
                e1=i;
                e2=j;
                arr[i][j]=0;
            }
            else{
                arr[i][j]=max(0, rot[i][j][0]-1);
            }
            for(k=1;k<rot[i][j].size();k++){
                a1=rot[i][j][k];
                p[a1].r=i;
                p[a1].c=j;
            }
        }
    }
    /*if(turn==4){
    for(i=1;i<=n;i++){
        for(j=1;j<=n;j++){
            cout<<arr[i][j]<<" ";
        }cout<<endl;
    }
    }*/
}

int main() {
    // 여기에 코드를 작성해주세요.
    //미로, 참가자, 게임시간
    cin>>n>>m>>k;
    partn=m;
    int i, j, r, c;
    for(i=1;i<=n;i++){
        for(j=1;j<=n;j++){
            cin>>arr[i][j];
        }
    }
    for(i=1;i<=m;i++){
        cin>>r>>c;
        p[i].r=r;
        p[i].c=c;
    }
    cin>>e1>>e2;
    for(i=1;i<=k;i++){
      //  cout<<i<<"번째**********\n";
        if(partn==0) break;
        p_move();
        bfs();
        //cout<<partn<<"남은사람명"<<endl;
       // cout<<"움직인거 ";
       // cout<<dis<<endl<<e1<<" "<<e2<<endl;
    }

    cout<<dis<<endl<<e1<<" "<<e2;
    return 0;
}