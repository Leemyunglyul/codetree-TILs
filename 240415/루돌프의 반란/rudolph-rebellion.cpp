#include <iostream>
#include <queue>
#include <tuple>
#include <cmath>

using namespace std;

class san{
    public:
    int r, c;
    int score=0;
    bool hp=true;
    int stun=0;
};

//크기, 턴, 산타 수, 루돌프 힘, 산타 힘.
int n, m, p, c, d;
int dr, dc, nn;
san ss[33];
int arr[53][53];

int dd(int x, int y){
    return (x-dr)*(x-dr)+(y-dc)*(y-dc);
}


void collide(int idx, int s1, int s2, int d1, int d2){
    //cout<<idx<<" "<<s1<<" "<<s2<<" "<<d1<<" "<<d2<<" "<<num<<endl;
    int temp, n1, n2;
    if(s1+d1<1 || s1+d1>n || s2+d2<1 || s2+d2>n){
        ss[idx].hp=false;
        nn--;
        return;

    }
    ss[idx].r=s1+d1;
    ss[idx].c=s2+d2;
    if(arr[s1+d1][s2+d2]==0){
        arr[s1+d1][s2+d2]=idx;
    }
    else{
        temp=arr[s1+d1][s2+d2];
        arr[s1+d1][s2+d2]=idx;
        // cout<<arr[s1+d1][s2+d2]<<endl;
         n1=s1+d1;n2=s2+d2;
        if(d1!=0) d1=d1/abs(d1);
        if(d2!=0) d2=d2/abs(d2);
       
        collide(temp, n1, n2, d1, d2);
    }
}

void deer_move(){
    priority_queue<tuple<int, int, int>> pq;
    int i, j, x, y, d1, d2;
    for(i=1;i<=p;i++){
        if(!ss[i].hp) continue;
        pq.push({-dd(ss[i].r, ss[i].c), ss[i].r, ss[i].c});
        //cout<<ss[i].r<<" "<<ss[i].c<<"//";
    }
    if(pq.empty()) return;
    x=get<1>(pq.top());
    y=get<2>(pq.top());
    

    d1=0;d2=0;
    if(dr>x){
        dr--;
        d1--;
    }
    else if(dr<x){
        dr++;
        d1++;
    }
    if(dc>y){
        dc--;
        d2--;
    }
    else if(dc<y){
        dc++;
        d2++;
    }
    if(dr==x && dc==y){
        ss[arr[x][y]].score+=c;
        ss[arr[x][y]].stun=2;
        int temp=arr[x][y];
        arr[x][y]=0;
        collide(temp, x, y, d1*c, d2*c);
    }
}


//상우하좌
void santa_move(){
    int i, j, x, y, d1, d2;
    for(i=1;i<=p;i++){
        if(!ss[i].hp) continue;
        if(ss[i].stun>0){
            //cout<<i<<"스턴\n";
            continue;
        }
        x=ss[i].r;
        y=ss[i].c;
        priority_queue<pair<int, int>> pq;
        if(dr<x && arr[x-1][y]==0){
            pq.push({-dd(x-1, y), 0});
        }
        if(dc>y&& arr[x][y+1]==0){
           pq.push({-dd(x, y+1), -1});
        }
        if(dr>x&& arr[x+1][y]==0){
            pq.push({-dd(x+1, y), -2});
        }
        if(dc<y&& arr[x][y-1]==0){
            pq.push({-dd(x, y-1), -3});
        }
        if(pq.empty()) continue;
        int dir=-pq.top().second;
        d1=0;d2=0;
        arr[x][y]=0;
        if(dir==0){ 
            d1=1;
            
            arr[x-1][y]=i;
            ss[i].r--;
        }
        else if(dir==1){ 
            d2=-1;
            arr[x][y+1]=i;
            ss[i].c++;
        }
        else if(dir==2){
             d1=-1;
            arr[x+1][y]=i;
            ss[i].r++;
        }
        else{ 
            d2=1;
            arr[x][y-1]=i;
            ss[i].c--;
        }


        if(ss[i].r==dr && ss[i].c==dc){
            //cout<<i<<"^^^^^"<<endl;
            ss[i].score+=d;
            ss[i].stun=2;
            arr[ss[i].r][ss[i].c]=0;
            collide(i, ss[i].r, ss[i].c, d1*d, d2*d);
        }
        //cout<<i<<"산타"<<ss[i].r<<" "<<ss[i].c<<endl;
    }
}

int main() {
    // 여기에 코드를 작성해주세요.

    cin>>n>>m>>p>>c>>d;
    cin>>dr>>dc;
    int i, j, x, y, z, k;
    for(i=1, nn=p;i<=p;i++){
        cin>>x>>y>>z;
        arr[y][z]=x;
        ss[x].r=y;
        ss[x].c=z;
    }
    for(i=1;i<=m;i++){
        if(nn==0) break;
      // cout<<"******"<<i<<endl;
        deer_move();
        if(i>=4){
     /*  for(j=1;j<=n;j++){
            for(k=1;k<=n;k++){
                cout<<arr[j][k]<<" ";
                
            }cout<<endl;
        }*/
        }
        santa_move();
    // cout<<dr<<" "<<dc<<endl;
     //   cout<<"남은산타"<<nn<<endl;
       if(i>=4){
       /*for(j=1;j<=n;j++){
            for(k=1;k<=n;k++){
                cout<<arr[j][k]<<" ";
                
            }cout<<endl;
        }*/
        }
        //cout<<">>";
        for(j=1;j<=p;j++){
            if(ss[j].hp){
                ss[j].score++;
            }
            if(ss[j].stun>0) ss[j].stun--;
          //  cout<<ss[j].score<<" ";
        }//cout<<endl;
    }
    for(i=1;i<=p;i++){
        cout<<ss[i].score<<" ";
    }
    return 0;
}