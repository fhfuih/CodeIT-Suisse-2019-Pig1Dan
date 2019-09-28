#include <bits/stdc++.h>
#include "../rapidjson/document.h"
#include "../rapidjson/prettywriter.h"

using namespace rapidjson;
using namespace std;

const int maxn = 1005;

int n;
vector<string> target;
int len;

int fa[maxn];

int findfa(int x)
{
    if (fa[x] == x) return x;
    else return fa[x] = findfa(fa[x]);
}

void merge(int x, int y)
{
    if (findfa(x) != findfa(y)) {
        fa[findfa(x)] = findfa(y);
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

    const Value& array = document.GetArray();
    n = array.Size();

    for (int i = 0; i < n; i++) {
        string x = array[i].GetString();
        target.push_back(x);
    }

    len = target[0].size();

    for (int i = 0; i < n; i++) {
        fa[i] = i;
    }
}


vector<string> op;
vector<string> val;
int costall = 0;

int dist[maxn][maxn];

int calcDist(const string& x, const string& y)
{
    int ret = 0;
    for (int i = 0; i < x.size(); i++) {
        ret += (x[i] != y[i]);
    }
    return ret;
}

vector<pair<int, pair<int, int> > > edges;
vector<int> go[maxn];
int curDist[maxn];
bool vis[maxn];

void dfs(int cur, int pre)
{
    vis[cur] = true;
    
    if (pre != -1) {
        op.push_back("COPY");
        val.push_back(target[pre]);
        op.push_back("TRANSFORM");
        val.push_back(target[cur]);
        costall += dist[cur][pre] + 1;
    }
    
    for (int v : go[cur]) {
        if (v != pre) {
            dfs(v, cur);
        }
    }
}

void solve()
{
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            dist[i][j] = dist[j][i] = calcDist(target[i], target[j]);
            if (dist[i][j] < len) {
                edges.push_back(make_pair(dist[i][j], make_pair(i, j)));
            }
        }
    }
    sort(edges.begin(), edges.end());
    for (int i = 0; i < edges.size(); i++) {
        int x = edges[i].second.first;
        int y = edges[i].second.second;
        if (findfa(x) != findfa(y)) {
            merge(x, y);
            go[x].push_back(y);
            go[y].push_back(x);
        }
    }
    for (int i = 0; i < n; i++) {
        if (!vis[i]) {
            costall += len;
            op.push_back("INPUT");
            val.push_back(target[i]);
            dfs(i, -1);
        }
    }
}

void output()
{
    StringBuffer strBuf;
    Writer<StringBuffer> writer(strBuf);

    writer.StartObject();
    
    writer.Key("cost");
    writer.Int(costall);
    
    writer.Key("steps");
    writer.StartArray();
    
    for (int i = 0; i < op.size(); i++) {
        writer.StartObject();
        writer.Key("type");
        writer.String(op[i].c_str());    
        writer.Key("value");
        writer.String(val[i].c_str());   
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
