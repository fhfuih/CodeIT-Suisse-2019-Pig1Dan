#include <bits/stdc++.h>
#include "../rapidjson/document.h"
#include "../rapidjson/prettywriter.h"

using namespace rapidjson;
using namespace std;

int n;
int m;
int fuel;

bool marked[105][105] = {};
const int direction[4][2] = { {0,1}, {0,-1}, {1,0}, {-1,0} };

vector<string> grid;

struct Coord {
    int x;
    int y;
    int dis;
    Coord(int x, int y, int dis):x(x),y(y),dis(dis) {}
};

vector<Coord> deadEnds;
vector<int>   deadEndDists;
vector<int>   plan;

void input(const char *path)
{
    ifstream file(path);
    string str((std::istreambuf_iterator<char>(file)),
               std::istreambuf_iterator<char>());
    const char *json = str.c_str();

    Document document;
    document.Parse(json);

    const Value& array = document["grid"].GetArray();
    n = array.Size();
    grid.resize(n);
    for (int i = 0; i < n; i++) {
        grid[i] = array[i].GetString();
        m = grid[i].size();
    }
    fuel = document["fuel"].GetInt();
}

void solve()
{
    queue<Coord> q;
    q.push(Coord(0,0,1));
    marked[0][0] = true;
    while (!q.empty()) {
        const Coord & head = q.front();
        bool isDead = true;
        for (int d = 0; d < 4; d++) {
            const int xx = head.x + direction[d][0];
            const int yy = head.y + direction[d][1];
            if (xx < 0 || xx >= n || yy < 0 || yy >= m || grid[xx][yy] == 'X' || marked[xx][yy])
                continue;
            isDead = false;
            marked[xx][yy] = true;
            q.push(Coord(xx, yy, head.dis + 1));
        }
        if (isDead) {
            // cout << head.x << ' ' << head.y << " is a dead end with " << head.dis << endl;
            deadEnds.push_back(head);
            deadEndDists.push_back(head.dis);
        }
        q.pop();
    }
    int p = deadEndDists.size();
    int sum = 0;
    for (int x : deadEndDists) {
        sum += x;
    }
    vector<bool> dp(sum + 1);
    vector<int> pre(sum + 1);
    dp[0] = true;
    for (int k = 0; k < p; k++) {
        int x = deadEndDists[k];
        for (int i = sum; i >= x; i--) {
            if (dp[i - x]) {
                dp[i] = true;
                pre[i] = k;
            }
        }
    }
    int ans = 0;
    for (int i = 0; i <= fuel; i++) {
        if (dp[i]) {
            ans = i;
        }
    }
    int cur = ans;
    while (cur > 0) {
        plan.push_back(pre[cur]);
        cur -= deadEndDists[pre[cur]];
    }
}

void output()
{
    // for (const int i : plan) {
    //     cout << deadEnds[i].x << ' ' << deadEnds[i].y << ' ' << deadEnds[i].dis << endl;
    // }
    StringBuffer strBuf;
    Writer<StringBuffer> writer(strBuf);

    writer.StartObject();

    writer.Key("hits");
    writer.StartArray();
    // cout << "start main array" << endl;

    for (int i = 0; i < plan.size(); i++) {
        const int ind = plan[i];
        writer.StartObject();

        writer.Key("cell");
        writer.StartObject();
        writer.Key("x");
        writer.Int(deadEnds[ind].y + 1);
        writer.Key("y");
        writer.Int(deadEnds[ind].x + 1);
        writer.EndObject();

        writer.Key("guns");
        writer.Int(deadEnds[ind].dis);

        writer.EndObject();
    }

    writer.EndArray();
    writer.EndObject();

    cout << strBuf.GetString();
}

int main(int argc, char **argv)
{
    input(argv[1]);
    solve();
    output();
    return 0;
}
