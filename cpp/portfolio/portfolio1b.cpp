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
        return rhs.profit * 1.0 / rhs.price > profit * 1.0 / price;
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
vector<int> count_;
vector<int> anslist;

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
            anslist = count_;
        }
        return;
    }
    for (int i = 0; ; i++) {
        if (remain >= stocks[cur].price * i) {
            count_[cur] += i;
            dfs(cur + 1, remain - stocks[cur].price * i, prof + stocks[cur].profit * i);
            count_[cur] -= i;
        } else {
            break;
        }
    }
}

void solve()
{
    anslist.resize(n + 1);
    count_.resize(n + 1);
    sort(stocks.begin(), stocks.end());
    for (int i = 0; i < n; i++) {
        if (capi < stocks[i].price) {
            ans = 0;
            for (int j = 0; j < n; j++) {
                anslist[j] = 0;
            }
            return;
        } else {
            ans += stocks[i].profit;
            capi -= stocks[i].price;
            count_[i] ++;
        }
    }
    st = clock();
    dfs(0, capi, ans);
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
    for (int i = 0; i < n; i++) {
        int x = anslist[i];
        while (x > 0) {
            writer.String(stocks[i].name.c_str());
            x --;
        }
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
