#include <bits/stdc++.h>
#include "../rapidjson/document.h"
#include "../rapidjson/prettywriter.h"

using namespace rapidjson;
using namespace std;

vector<int> arr;
vector<int> sorted;

void input(const char *json)
{
    Document document;
    document.Parse(json);
    const Value array = document.GetArray();

    for (int i = 0; i < array.Size(); i++) {
        arr.push_back(array[i].GetInt());
    }
}

void solve()
{
    int count_[20050] = {0};

    for (const int &x : arr) {
        count_[x + 10000] ++;
    }

    for (int i = -10000; i <= 10000; i++) {
        while (count_[i + 10000] > 0) {
            sorted.push_back(i);
            count_[i + 10000] --;
        }
    }
}

void output()
{
    StringBuffer strBuf;
    Writer<StringBuffer> writer(strBuf);

    writer.StartArray();
    for (const auto &x : sorted) {
        writer.Int(x);
    }
    writer.EndArray();

    cout << strBuf.GetString();
}

int main(int argc, char **argv)
{
    input(argv[1]);
    solve();
    output();
    return 0;
}
