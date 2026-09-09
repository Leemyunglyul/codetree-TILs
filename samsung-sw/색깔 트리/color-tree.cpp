#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct node {
    int id;
    int dep;       // max_depth
    int color;
    int parent;
    int value;     // 서브트리 색상 비트마스크
    int t;         // 마지막 색 지정 시각
    int newc;      // 마지막으로 지정된 색
};

bool yes[100010];
node arr[100010];
vector<int> edge[100010];

void add(int id, int p, int c, int dep, int time) {
    // 새 노드는 부모 기준 깊이 2
    int cur = p;
    int depth = 2;

    while (cur != -1) {
        if (arr[cur].dep < depth)
            return;

        cur = arr[cur].parent;
        depth++;
    }

    yes[id] = true;

    arr[id] = {
        id,
        dep,
        c,
        p,
        1 << (c - 1),
        time,
        c
    };

    if (p != -1)
        edge[p].push_back(id);
}

// 현재 노드의 실제 색 조회
int getColor(int id) {
    int latestTime = -1;
    int result = arr[id].color;

    int cur = id;

    while (cur != -1) {
        if (arr[cur].t > latestTime) {
            latestTime = arr[cur].t;
            result = arr[cur].newc;
        }

        cur = arr[cur].parent;
    }

    return result;
}

// 서브트리 색상 비트마스크 반환
int dfs(int id, int parentTime, int parentColor, long long& score) {
    int currentTime = parentTime;
    int currentColor = parentColor;

    if (arr[id].t > currentTime) {
        currentTime = arr[id].t;
        currentColor = arr[id].newc;
    }

    int colorMask = 1 << (currentColor - 1);

    for (int child : edge[id]) {
        colorMask |= dfs(child, currentTime, currentColor, score);
    }

    arr[id].value = colorMask;

    long long colorCount = __builtin_popcount(colorMask);
    score += colorCount * colorCount;

    return colorMask;
}

void solve() {
    int q;
    cin >> q;

    fill_n(yes, 100010, false);

    for (int time = 1; time <= q; time++) {
        int command;
        cin >> command;

        if (command == 100) {
            int id, parent, color, maxDepth;
            cin >> id >> parent >> color >> maxDepth;

            add(id, parent, color, maxDepth, time);
        }
        else if (command == 200) {
            int id, color;
            cin >> id >> color;

            arr[id].t = time;
            arr[id].newc = color;
            arr[id].color = color;
        }
        else if (command == 300) {
            int id;
            cin >> id;

            cout << getColor(id) << '\n';
        }
        else if (command == 400) {
            long long score = 0;

            for (int id = 1; id <= 100000; id++) {
                if (yes[id] && arr[id].parent == -1) {
                    dfs(id, -1, 0, score);
                }
            }

            cout << score << '\n';
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();
    return 0;
}