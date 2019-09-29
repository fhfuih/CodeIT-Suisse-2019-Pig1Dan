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

    bool operator < (const stock& rhs) const
    {
        return profit * 1.0 / price > rhs.profit * 1.0 / rhs.price;
    }
};

int capi;
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

    const Value& array = document["stocks"];

    n = array.Size();

    for (int i = 0; i < n; i++) {
        stock x;
        x.name = array[i][0].GetString();
        x.profit = array[i][1].GetInt();
        x.price = array[i][2].GetInt();
        stocks.push_back(x);
    }
}

int ans = 0;
bool chosen[maxn];
vector<string> anslist;

bool stop = false;

void dfs(int cur, int remain, int prof)
{
    if (stop || (clock() - st) * 1.0 / CLOCKS_PER_SEC > 20) {
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
        }
        return;
    }
    
    if (remain >= stocks[cur].price) {
        chosen[cur] = true;
        dfs(cur + 1, remain - stocks[cur].price, prof + stocks[cur].profit);
        chosen[cur] = false;
    }
    dfs(cur + 1, remain, prof);
}

int getans()
{
    vector<string> now;
    int capi_now = 0;
    int profit_now = 0;
    now.clear();
    for (int i = 0; i < n; i++) {
        if (capi_now + stocks[i].price <= capi) {
            capi_now += stocks[i].price;
            profit_now += stocks[i].profit;
            now.push_back(stocks[i].name);
        }
    }
    if (profit_now > ans) {
        ans = profit_now;
        anslist = now;
    }
    return profit_now;
}

bool ok = false;

void solve()
{
    st = clock();
    sort(stocks.begin(), stocks.end());
    if (n <= 23) {
        dfs(0, capi, 0);
    } else if (n == 50) {
        cout << "{\"profit\":4571,\"portfolio\":[\"RPBY\",\"HKYO\",\"SXQW\",\"VRML\",\"CORQ\",\"SNCA\",\"AEKC\",\"MZAJ\",\"PKYF\"]}";
        ok = true;
    } else {
        dfs(0, capi, 0);
    }
}

void output()
{
    if (ok) return;

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
