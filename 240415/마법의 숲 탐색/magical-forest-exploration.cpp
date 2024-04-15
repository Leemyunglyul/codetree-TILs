#include <iostream>
#include <queue>
#include <cmath>

using namespace std;

int r, c, k;
int row, col, dir;
int arr[80][80];
bool exitt[80][80];
int score;

//0상 1우 2하 3좌
void rot(int clock){
    if(clock==0){
        if(dir>0) dir--;
        else dir=3;
    }
    else{
        if(dir<3) dir++;
        else dir=0;
    }
}

void gravity();
void rot_left();

void rot_right(){
    int tr=row;
    int tc=col+1;
    if(row>=r || col>=c-1) return;
    else if(tc>=1 && tr+1<=r && arr[tr+1][tc]>0) return;
    else if(tc>=1 && tr-2>=1 && arr[tr-2][tc]>0) return;
    else if(tr>=1 && tc+1<=c && arr[tr][tc+1]>0) return;
    else if(tr>=2 && tc+1<=c && arr[tr-1][tc+1]>0) return;
    else{
        col++;row++;
        rot(1);
     //   cout<<"우회전\n";
        gravity();
    }
}

void rot_left(){
    int tr=row;
    int tc=col-1;
    if(row>=r || col<=2) rot_right();
    else if(tc>=1 && tr+1<=r && arr[tr+1][tc]>0) rot_right();
    else if(tc>=1 && tr-2>=1 && arr[tr-2][tc]>0) rot_right();
    else if(tr>=1 && tc-1>=1 && arr[tr][tc-1]>0) rot_right();
    else if(tr>=2 && tc-1>=1 && arr[tr-1][tc-1]>0) rot_right();
    else{
        col--;row++;
        rot(0);
       // cout<<"좌회전\n";
        gravity();
    }
}

void gravity(){
    if(row>=r) rot_left();
    else if(row+1<=r && arr[row+1][col]>0) rot_left(); 
    else if(col-1>=1 && arr[row][col-1]>0) rot_left();
    else if(col+1<=c && arr[row][col+1]>0) rot_left();
    else{
        row++;
        gravity();
    }
}

void fill_(int idx){
    arr[row][col]=idx;
    arr[row-1][col]=idx;
    arr[row-2][col]=idx;
    arr[row-1][col-1]=idx;
    arr[row-1][col+1]=idx;

    if(dir==0){
        exitt[row-2][col]=true;
    }
    else if(dir==1){
        exitt[row-1][col+1]=true;
    }
    else if(dir==2){
        exitt[row][col]=true;
    }
    else{
        exitt[row-1][col-1]=true;
    }
}

void bfs(){
    bool visited[80][80];
    fill_n(&visited[0][0], 80*80, false);
    queue<pair<int, int>> q;
    q.push({row-1, col});
    visited[row-1][col]=true;
    int big=-1;

    while(!q.empty()){
        int tr=q.front().first;
        int tc=q.front().second;
        q.pop();

        int temp=arr[tr][tc];

        big=max(big, tr);
        if(exitt[tr][tc]){
            if(tr>=2 && !visited[tr-1][tc] && arr[tr-1][tc]>0){
                visited[tr-1][tc]=true;
                q.push({tr-1, tc});
            }
            if(tc>=2 && !visited[tr][tc-1] && arr[tr][tc-1]>0){
                visited[tr][tc-1]=true;
                q.push({tr, tc-1});
            }
             if(tr+1<=r && !visited[tr+1][tc] && arr[tr+1][tc]>0){
                visited[tr+1][tc]=true;
                q.push({tr+1, tc});
            }
            if(tc+1<=c && !visited[tr][tc+1] && arr[tr][tc+1]>0){
                visited[tr][tc+1]=true;
                q.push({tr, tc+1});
            }
        }
        else{
            if(tr>=2 && !visited[tr-1][tc] && arr[tr-1][tc]==temp){
                visited[tr-1][tc]=true;
                q.push({tr-1, tc});
            }
            if(tc>=2 && !visited[tr][tc-1] && arr[tr][tc-1]==temp){
                visited[tr][tc-1]=true;
                q.push({tr, tc-1});
            }
             if(tr+1<=r && !visited[tr+1][tc] && arr[tr+1][tc]==temp){
                visited[tr+1][tc]=true;
                q.push({tr+1, tc});
            }
            if(tc+1<=c && !visited[tr][tc+1] && arr[tr][tc+1]==temp){
                visited[tr][tc+1]=true;
                q.push({tr, tc+1});
            }
        }
    }

    score+=big;
}

void print(){
    int i, j;
    for(i=0;i<r;i++){
        for(j=0;j<c;j++){
            cout<<arr[i][j]<<" ";
        }cout<<endl;
    }
}

int main() {
    cin>>r>>c>>k;
    int i, j;
    fill_n(&arr[0][0], 80*80, 0);
    fill_n(&exitt[0][0], 80*80, false);
    for(i=1, score=0;i<=k;i++){
        cin>>col>>dir;
        row=0;
        gravity();
        if(row<=2){
            fill_n(&arr[0][0], 80*80, 0);
            fill_n(&exitt[0][0], 80*80, false);
        }
        else{
            fill_(i);
            bfs();
        }
       // cout<<i<<"%%%%%%"<<endl;
       // print();
        
    }
    cout<<score;

    return 0;
}