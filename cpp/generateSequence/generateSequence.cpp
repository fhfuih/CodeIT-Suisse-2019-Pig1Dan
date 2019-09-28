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

void input(const char *path)
{
    ifstream file(path);
    string str((std::istreambuf_iterator<char>(file)),
               std::istreambuf_iterator<char>());
    const char *json = str.c_str();

    Document document;
    document.Parse(json);

    const Value& array = document["modules"];
    n = array.Size();
    for (int i = 0; i < n; i++) {
        string x;
        x = array[i].GetString();
        mod.push_back(x);
        id[x] = i;
    }

    const Value& dep = document["dependencyPairs"];
    m = dep.Size();
    for (int i = 0; i < m; i++) {
        string x, y;
        x = dep[i].GetObject()["dependee"].GetString();
        y = dep[i].GetObject()["dependentOn"].GetString();
        if (!id.count(x) || !id.count(y)) continue;
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

int main(int argc, char **argv)
{
    input(argv[1]);
    solve();
    output();
    return 0;
}
