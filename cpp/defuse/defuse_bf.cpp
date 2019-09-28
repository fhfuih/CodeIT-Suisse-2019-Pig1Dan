#include <bits/stdc++.h>
#include "../rapidjson/document.h"
#include "../rapidjson/prettywriter.h"

using namespace rapidjson;
using namespace std;

const int modulo = 998244353;
const int maxn = 10005;

int n;
int k;

vector<int> arr;

int ans;


bool check()
{
    for (int i = 1; i < n - 1; i++) {
        if (arr[i - 1] == arr[i + 1]) {
            return true;
        }
    }
    return false;
}

void dfs(int cur)
{
    if (cur == n) {
        if (check()) {
            ans ++;
        }
        return;
    }
    if (arr[cur] != -1) {
        dfs(cur + 1);
    } else {
        for (int i = 1; i <= k; i++) {
            arr[cur] = i;
            dfs(cur + 1);
            arr[cur] = -1;
        }
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
        for (int j = 0; j < n; j++) {
            arr[j] = document[i]["password"][j].GetInt();
        }
        dfs(0);
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