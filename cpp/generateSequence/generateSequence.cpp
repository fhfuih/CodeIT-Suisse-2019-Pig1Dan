#include <bits/stdc++.h>
#include "../rapidjson/document.h"
#include "../rapidjson/prettywriter.h"

using namespace rapidjson;
using namespace std;

const int maxn = 105;

vector<string> mod;
map<string, int> id;

vector<int> go[maxn];
int indeg[maxn];

int n;
int m;

void input()
{
    cin >> n;
    for (int i = 0; i < n; i++) {
        string x;
        cin >> x;
        mod.push_back(x);
        id[x] = i;
    }
    cin >> m;
    for (int i = 0; i < m; i++) {
        string x, y;
        cin >> x >> y;
        int idx = id[x];
        int idy = id[y];
        go[idy].push_back(idx);
        indeg[idx] ++;
    }
}

void solve()
{
    queue<int> q;
    vector<string> ans;

    for (int i = 0; i < n; i++) {
        if (indeg[i] == 0) {
            q.push(i);
        }
    }

    while (q.size()) {
        int id = q.front();
        q.pop();
        ans.push_back(mod[id]);
        for (int to : go[id]) {
            indeg[to] --;
            if (indeg[to] == 0) {
                q.push(to);
            }
        }
    }

    cout << "[";
    for (int i = 0; i < ans.size(); i++) {
        cout << "\"" << ans[i] << "\"";
        if (i != ans.size() - 1) {
            cout << ",";
        }
    }
    cout << "]";
}

void output()
{
}

int main()
{
    input();
    solve();
    output();
    return 0;
}
