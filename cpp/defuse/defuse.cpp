#include <bits/stdc++.h>
#include "../rapidjson/document.h"
#include "../rapidjson/prettywriter.h"

using namespace rapidjson;
using namespace std;

const int modulo = 998244353;
const int maxn = 10005;

int n;
int k;

int memo[15];

int fix;
int total;
map<int, int> fix_mapping;

vector<int> arr;
vector<int> tar;

int ans;


bool check()
{
    for (int i = 1; i < n - 1; i++) {
        if (tar[i - 1] == tar[i + 1]) {
            return true;
        }
    }
    return false;
}

int calc(int x)
{
    if (memo[x] != -1) return memo[x];
    int cur = k - fix;
    int &res = memo[x];
    res = 1;
    while (x > 0) {
        res = 1ll * res * cur % modulo;
        cur --;
        x --;
    }
    return res;
}

int vis[15];
int counter = 0;

void dfs(int cur, int max_avail)
{
    if (cur == n) {
        if (check()) {
            int diff_count = 0;
            counter ++;
            for (int i = 0; i < n; i++) {
                int y = tar[i];
                if (y >= fix && vis[y] != counter) {
                    diff_count ++;
                    vis[y] = counter;
                }
            }
            ans = ans + calc(diff_count);
            if (ans > modulo) {
                ans -= modulo;
            }
        }
        return;
    }
    if (tar[cur] != -1) {
        dfs(cur + 1, max_avail);
    } else {
        for (int i = 0; i < max_avail; i++) {
            tar[cur] = i;
            dfs(cur + 1, max_avail);
        }
        if (max_avail < total) {
            tar[cur] = max_avail;
            dfs(cur + 1, max_avail + 1);
            tar[cur] = -1;
        }
        tar[cur] = -1;
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

    int T = document.Size();

    writer.StartArray();

    for (int i = 0; i < T; i++) {
        n = document[i]["n"].GetInt();
        k = document[i]["k"].GetInt();
        arr.resize(n);
        tar.resize(n);
        fix = 0;
        ans = 0;
        total = n;
        memset(memo, -1, sizeof(memo));
        fix_mapping.clear();
        for (int j = 0; j < n; j++) {
            arr[j] = document[i]["password"][j].GetInt();
            tar[j] = arr[j];
        } 
        for (int j = 0; j < n; j++) {
            if (arr[j] != -1) {
                if (!fix_mapping.count(arr[j])) {
                    fix_mapping[arr[j]] = fix ++;
                }
                tar[j] = fix_mapping[arr[j]];
                total --;
            }
        }
        total += fix;
        total = min(total, k);
        dfs(0, fix);
        writer.Int(ans);
    }
    

    writer.EndArray();

    cout << strBuf.GetString();
}


int main(int argc, char **argv)
{
    input(argv[1]);
    return 0;
}

/*

[ { "n": 2, "k": 3, "password": [ -1, -1 ] },
  { "n": 5, "k": 2, "password": [ 1, -1, -1, 1, 2 ] },
  { "n": 5, "k": 3, "password": [ 1, -1, -1, 1, 2 ] },
  { "n": 4, "k": 200000, "password": [ -1, -1, 12345, -1 ] },
  { "n": 10,
    "k": 5,
    "password": [ 4, -1, -1, 1, -1, -1, -1, 2, -1, -1 ] },
  { "n": 10, "k": 8, "password": [ 4, 8, -1, -1, -1, 2, -1, 4, -1, -1 ] } ]

*/