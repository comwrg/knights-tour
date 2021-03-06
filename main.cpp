#include <iostream>
#include <queue>
#include <stack>
using namespace std;

const int H = 8;
const int W = 8;
const int DIR[8][2] = {
        { -2,  1 }, { -1,  2 }, {  1,  2 }, {  2,  1 },
        {  2, -1 }, {  1, -2 }, { -1, -2 }, { -2, -1 }
};
int arrived[H][W];

struct point {
    int x, y;
    point(int x = 0, int y = 0) : x(x), y(y) {}
};

stack<point> path;
point start, dst;
bool closed;

bool valid(const point &p) {
    return p.x >= 0 and p.x < H
       and p.y >= 0 and p.y < W
       and !arrived[p.x][p.y];
}

queue<point> get_next(const point &p) {
    vector<pair<point, int>> vp;
    for (int i = 0; i < 8; i++) {
        point next(p.x+DIR[i][0], p.y+DIR[i][1]);
        if (!valid(next))
            continue;
        int step = 0;
        for (int i = 0; i < 8; i++) {
            point next2(next.x+DIR[i][0], next.y+DIR[i][1]);
            if (!valid(next2))
                continue;
            step++;
        }
        vp.emplace_back(next, step);
    }
    sort(vp.begin(), vp.end(),
         [](const pair<point, int>& lhs, const pair<point, int>& rhs) {
            return lhs.second < rhs.second;
         }
    );
    queue<point> que;
    for (auto item : vp) {
        que.push(item.first);
    }
    return que;
}

void show() {
    int chessboard[H][W];
    memset(chessboard, 0 , sizeof(chessboard));
    int i = H*W;
    stack<point> cp(path);
    while (!cp.empty()) {
        auto p = cp.top();
        cp.pop();
        chessboard[p.x][p.y] = i--;
    }
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            printf("%4d", chessboard[i][j]);
        }
        cout << endl;
    }
    cout << endl;
}

bool knight_tour(const point &p) {
    if (path.size() >= H*W) {
        if (closed) {
            for (int i = 0; i < 8; i++) {
                if (p.x+DIR[i][0] == start.x and p.y+DIR[i][1] == start.y) {
                    show();
                    return true;
                }
            }
            return false;
        } else {
            bool r = p.x == dst.x and p.y == dst.y;
            if (r) {
                show();
            }
            return r;
        }
    }

    auto que = get_next(p);
    while (!que.empty()) {
        auto next = que.front();
        que.pop();
        arrived[next.x][next.y] = true;
        path.push(next);
        bool r = knight_tour(next);
        if (r and !closed)
            return true;
        path.pop();
        arrived[next.x][next.y] = false;
    }

    return false;
}

int main() {
    cout << "start:";
    cin >> start.x >> start.y;
    cout << "dst  :";
    cin >> dst.x   >> dst.y;
    while (!path.empty())
        path.pop();
    path.push(start);
    closed = (start.x == dst.x and start.y == dst.y);
    memset(arrived, 0, sizeof(arrived));
    arrived[start.x][start.y] = true;
    knight_tour(start);
    main();
    return 0;
}