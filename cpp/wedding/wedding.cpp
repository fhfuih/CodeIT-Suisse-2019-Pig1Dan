#include <bits/stdc++.h>
#include "../rapidjson/document.h"
#include "../rapidjson/prettywriter.h"

using namespace rapidjson;
using namespace std;

const int maxn = 100;

int fa[maxn];
int n;
int m;

vector<pair<int, int> > yes;
vector<pair<int, int> > no;

int find(int x)
{
    if (fa[x] == x) return x;
    else return fa[x] = find(fa[x]);
}

void merge(int x, int y)
{
    if (find(x) != find(y)) {
        fa[find(x)] = find(y);
    }
}

bool ok = true;
vector<int> tables[maxn];

bool hate[maxn][maxn];

void init()
{
    for (int i = 1; i <= n; i++) {
        fa[i] = i;
    }
    yes.clear();
    no.clear();
    ok = true;
    for (int i = 0; i < maxn; i++) {
        tables[i].clear();
    }
    for (int i = 0; i < maxn; i++) {
        for (int j = 0; j < maxn; j++) {
            hate[i][j] = false;
        }
    }
}

void solve()
{
    for (pair<int, int> ele : yes) {
        int x = ele.first;
        int y = ele.second;
        merge(x, y);
    }
    for (int i = 1; i <= n; i++) {
        find(i);
    }
    for (pair<int, int> ele : no) {
        int x = ele.first;
        int y = ele.second;
        if (find(x) == find(y)) {
            ok = false;
            return;
        }
        hate[find(x)][find(y)] = hate[find(y)][find(x)] = true;
    }
    vector<pair<int, int> > merges;
    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            int x = find(i);
            int y = find(j);
            if (x != y && !hate[x][y]) {
                merges.push_back(make_pair(x, y));
            }
        }
    }
    for (pair<int, int> ele : merges) {
        int x = ele.first;
        int y = ele.second;
        merge(x, y);
    }

    int counter = 0;
    vector<int> id;
    id.resize(n + 1, -1);
    
    for (int i = 1; i <= n; i++) {
        int fa = find(i);
        if (id[fa] == -1) {
            id[fa] = counter++;
        }
        tables[id[fa]].push_back(i);
    }

    if (counter > m) {
        ok = false;
        return;
    }
}

void input(const char *path)
{
    ifstream file(path);
    string str((std::istreambuf_iterator<char>(file)),
               std::istreambuf_iterator<char>());
    const char *json = str.c_str();

    Document document;
    document.Parse(json);

    StringBuffer strBuf;
    Writer<StringBuffer> writer(strBuf);
    
    writer.StartArray();

    const Value& cases = document.GetArray();
    int T = cases.Size();

    for (int i = 1; i <= T; i++) {
        const Value& obj = cases[i - 1];
        init();
        n = obj["guests"].GetInt();
        m = obj["tables"].GetInt();
        const Value& fri = obj["friends"];
        int t = fri.Size();
        for (int j = 0; j < t; j++) {
            const Value& pair = fri[j];
            int x = pair[0].GetInt();
            int y = pair[1].GetInt();
            if (x > y) swap(x, y);
            yes.push_back(make_pair(x, y));
        }
        const Value& fri2 = obj["families"];
        t = fri2.Size();
        for (int j = 0; j < t; j++) {
            const Value& pair = fri2[j];
            int x = pair[0].GetInt();
            int y = pair[1].GetInt();
            if (x > y) swap(x, y);
            yes.push_back(make_pair(x, y));
        }
        const Value& ene = obj["enemies"];
        t = ene.Size();
        for (int j = 0; j < t; j++) {
            const Value& pair = ene[j];
            int x = pair[0].GetInt();
            int y = pair[1].GetInt();
            if (x > y) swap(x, y);
            no.push_back(make_pair(x, y));
        }
        
        solve();
        
        writer.StartObject();
        writer.Key("test_case");
        writer.Int(i);
        writer.Key("satisfiable");
        writer.Int(ok);
        writer.Key("allocation");
        writer.StartArray();
        if (ok) {
            for (int v = 0; v < m; v++) {
                for (int j = 0; j < tables[v].size(); j++) {
                    writer.StartArray();
                    writer.Int(tables[v][j]);
                    writer.Int(v + 1);
                    writer.EndArray();
                }
            }
        }
        writer.EndArray();
    
        writer.EndObject();
    }

    writer.EndArray();

    cout << strBuf.GetString();
}

int main(int argc, char **argv)
{
    input(argv[1]);
    return 0;
}
