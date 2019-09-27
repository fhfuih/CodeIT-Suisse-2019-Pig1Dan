#include <bits/stdc++.h>
#include "../rapidjson/document.h"
#include "../rapidjson/prettywriter.h"

using namespace rapidjson;
using namespace std;

void input(const char *json)
{
    Document document;
    document.Parse(json);
}

void solve()
{
}

void output()
{
    StringBuffer strBuf;
    Writer<StringBuffer> writer(strBuf);

    cout << strBuf.GetString();
}

int main(int argc, char **argv)
{
    input(argv[1]);
    solve();
    output();
    return 0;
}
