#include <bits/stdc++.h>
#include "../rapidjson/document.h"
#include "../rapidjson/prettywriter.h"

using namespace rapidjson;
using namespace std;

const int maxn = 1005;

struct stock
{
    string name;
    int profit;
    int price;
    int risk;

    bool operator < (const stock& rhs) const
    {
        return rhs.profit * 1.0 / rhs.price > profit * 1.0 / price;
    }
};

int capi;
int risk;
int n;
vector<stock> stocks;

int st;

void input(const char *path)
{
    ifstream file(path);
    string str((std::istreambuf_iterator<char>(file)),
               std::istreambuf_iterator<char>());
    const char *json = str.c_str();

    Document document;
    document.Parse(json);

    capi = document["startingCapital"].GetInt();
    risk = document["risk"].GetInt();

    const Value& array = document["stocks"];

    n = array.Size();

    for (int i = 0; i < n; i++) {
        stock x;
        x.name = array[i][0].GetString();
        x.profit = array[i][1].GetInt();
        x.price = array[i][2].GetInt();
        x.risk = array[i][3].GetInt();
        stocks.push_back(x);
        cout << x.name << " " << x.profit << " " << x.price << endl;
    }
}

int ans = 0;
bool chosen[maxn];
vector<string> anslist;

bool stop = false;

void dfs(int cur, int remain, int prof)
{
    if (stop || (clock() - st) * 1.0 / CLOCKS_PER_SEC < 20) {
        stop = true;
        return;
    }
    if (cur == n) {
        if (prof > ans) {
            ans = prof;
            anslist.clear();
            for (int i = 0; i < n; i++) {
                if (chosen[i]) {
                    anslist.push_back(stocks[i].name);
                }
            }
            return;
        }
    }
    if (remain >= stocks[cur].price) {
        chosen[cur] = true;
        dfs(cur + 1, remain - stocks[cur].price, prof + stocks[cur].profit);
        chosen[cur] = false;
    }
    dfs(cur + 1, remain, prof);
}

void solve()
{
    st = clock();
    sort(stocks.begin(), stocks.end());
    dfs(0, capi, 0);
}

void output()
{
    StringBuffer strBuf;
    Writer<StringBuffer> writer(strBuf);

    writer.StartObject();
    writer.Key("profit");
    writer.Int(ans);
    writer.Key("portfolio");
    writer.StartArray();
    for (int i = 0; i < anslist.size(); i++) {
        writer.String(anslist[i].c_str());
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
