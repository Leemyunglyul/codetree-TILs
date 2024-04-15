#include <iostream>
#include <queue>
#include <tuple>
#include <vector>

using namespace std;

struct list {
    int row, col, ht, wt, hl;
    int dam;
};

int n, kn, q;
int board[50][50];
int zone[50][50];
list k[50];

//상0 우1 하2 좌3
void move(int idx, int dir) {
    bool visited[50];
    fill_n(&visited[0], 50, false);
    int dam[50] = { 0 };//데미지 누적
    int temp[50][50] = { 0 };//임시
    int i, j, r, c, l, ex, id, x, y, h, w;
    //idx, row, col
    queue<tuple<int, int, int>> q;
    r = k[idx].row;
    c = k[idx].col;
    q.push({ idx, r, c });

    //상0 우1 하2 좌3
    while (!q.empty()) {
        id = get<0>(q.front());
        r = get<1>(q.front());
        c = get<2>(q.front());
        q.pop();
        if (!visited[id]) {
            visited[id] = true;
            x = k[id].row;
            y = k[id].col;
            h = k[id].ht;//세로 row
            w = k[id].wt;//가로
            for (j = x; j < x + h; j++) {
                for (l = y; l < y + w; l++) {
                    q.push({ id, j, l });
                }
            }
        }
        if (dir == 0) {
            if (r == 1 || board[r - 1][c] == 2) {
                return;
            }
            temp[r - 1][c] = id;
            if (zone[r - 1][c] > 0) {
                q.push({ zone[r - 1][c], r - 1, c });
            }
        }
        else if (dir == 1) {
            if (c == n || board[r][c + 1] == 2) {
                return;
            }
            temp[r][c + 1] = id;
            if (zone[r][c + 1] > 0) {
                q.push({ zone[r][c + 1], r, c + 1 });
            }
        }
        else if (dir == 2) {
            if (r == n || board[r + 1][c] == 2) {
                return;
            }
            temp[r + 1][c] = id;
            if (zone[r + 1][c] > 0) {
                q.push({ zone[r + 1][c], r + 1, c });
            }
        }
        else if (dir == 3) {
            if (c == 1 || board[r][c - 1] == 2) {
                return;
            }
            temp[r][c - 1] = id;
            if (zone[r][c - 1] > 0) {
                q.push({ zone[r][c - 1], r, c - 1 });
            }
        }
    }
    for (i = 1; i <= n; i++) {
        for (j = 1; j <= n; j++) {

            if (temp[i][j] > 0 && board[i][j] == 1) {
                dam[temp[i][j]]++;
                //cout << temp[i][j] << "--" << dam[temp[i][j]] << endl;
            }
        }
        // cout<<endl;
    }
    //피가 닳은 친구.
    int del[50] = { 0 };
    for (i = 1; i <= kn; i++) {
        if (visited[i]) {
            //cout<<i<<"피가 닳음\n";
            if (i != idx) {
                k[i].hl -= dam[i];
                k[i].dam += dam[i];
            }
            if (k[i].hl <= 0) del[i] = 1;
            //상0 우1 하2 좌3
            if (dir == 0) {
                k[i].row--;
            }
            else if (dir == 1) {
                k[i].col++;
            }
            else if (dir == 2) {
                k[i].row++;
            }
            else {
                k[i].col--;
            }
        }
        //cout<<i<<"번째"<<k[i].hl<<endl;
    }
    for (i = 1; i <= n; i++) {
        for (j = 1; j <= n; j++) {
            if (del[temp[i][j]] == 1) {
                temp[i][j] = 0;
            }
        }
    }
    //이동하면 바꾸고
    for (i = 1; i <= n; i++) {
        for (j = 1; j <= n; j++) {
            if (!visited[zone[i][j]] && zone[i][j] > 0) continue;
            zone[i][j] = temp[i][j];
        }
    }

}

int main() {
    // 여기에 코드를 작성해주세요.
    int i, j, r, c, h, w, kt, x, d, l;
    cin >> n >> kn >> q;
    for (i = 1; i <= n; i++) {
        for (j = 1; j <= n; j++) {
            cin >> board[i][j];
        }
    }
    for (i = 1; i <= kn; i++) {
        cin >> r >> c >> h >> w >> kt;
        k[i].dam = 0;
        k[i].row = r;
        k[i].col = c;
        k[i].ht = h;
        k[i].wt = w;
        k[i].hl = kt;
    }
    for (i = 1; i <= kn; i++) {
        r = k[i].row;
        c = k[i].col;
        h = k[i].ht;//세로 row
        w = k[i].wt;//가로
        for (j = r; j < r + h; j++) {
            for (l = c; l < c + w; l++) {
                zone[j][l] = i;
                //cout << j << "//" << l << "\n";
            }
        }
    }
    //cout << "번째\n";
    for (j = 1; j <= n; j++) {
        for (l = 1; l <= n; l++) {
            //cout << zone[j][l] << " ";
        }//cout << endl;
    }
    for (i = 1; i <= q; i++) {
        cin >> x >> d;
        if (k[x].hl > 0)move(x, d);
       // cout << i << "번째\n";
        for (j = 1; j <= n; j++) {
            for (l = 1; l <= n; l++) {
               // cout<<zone[j][l]<<" ";
            }//cout<<endl;
        }
    }
    int sum = 0;
    for (i = 1; i <= kn; i++) {
        if (k[i].hl > 0) {
            sum += k[i].dam;
        }
    }
    cout << sum;
    return 0;
}