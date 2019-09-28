#include <bits/stdc++.h>
#include "../rapidjson/document.h"
#include "../rapidjson/prettywriter.h"

using namespace rapidjson;
using namespace std;

const int maxn = 31;

int n;
int k;
string s;

double ans;

unordered_map<string, double> memo[maxn];

void input(const char *path)
{
    ifstream file(path);
    string str((std::istreambuf_iterator<char>(file)),
               std::istreambuf_iterator<char>());
    const char *json = str.c_str();

    Document document;
    document.Parse(json);

    n = document["number_of_elements"].GetInt();
    k = document["number_of_operations"].GetInt();
    s = document["elements"].GetString();
}

double dfs(string now, int taken)
{
    if (memo[taken].count(now)) {
        return memo[taken][now];
    }
    double &res = memo[taken][now];
    if (taken == k) {
        return res = 0.0;
    }
    res = 0;
    double coef = 1.0 / now.size();
    int sz = now.size();
    for (int i = 0, j = sz - 1; i <= j; i ++, j --) {
        string left = now.substr(0, i) + now.substr(i + 1, sz - i - 1);
        string right = now.substr(0, j) + now.substr(j + 1, sz - j - 1);
        double lf = dfs(left, taken + 1) + (now[i] == 'Y');
        double rg = dfs(right, taken + 1) + (now[j] == 'Y');
        if (i != j) {
            res += 2.0 * coef * max(lf, rg);
        } else {
            res += coef * max(lf, rg);
        }
    }
    return res;
}

void solve()
{
    ans = dfs(s, 0);
}

void output()
{
    StringBuffer strBuf;
    Writer<StringBuffer> writer(strBuf);

    writer.StartObject();
    writer.Key("result");
    writer.Double(ans);
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
