#include <bits/stdc++.h>
#include "../rapidjson/document.h"
#include "../rapidjson/prettywriter.h"

using namespace rapidjson;
using namespace std;

const int maxn = 1000005;
const int inf = 0x3f3f3f3f;

bool banned[28][28];

int dp[maxn];
int opt[28];

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

    string id = document["setId"].GetString();
    string str_ = document["composition"].GetString();
    
    const Value& arr = document["patterns"].GetArray();

    int z = arr.Size();
    int n = str_.size();

    for (int i = 0; i < z; i++) {
        string ss = arr[i].GetString();
        int x = ss[0] - 'a';
        int y = ss[1] - 'a';
        banned[x][y] = true;
        banned[y][x] = true;
    }

    memset(opt, inf, sizeof(opt));
    memset(dp, inf, sizeof(dp));

    dp[0] = 0;
    opt[str_[0] - 'a'] = 0;

    for (int i = 1; i < n; i++) {
        int x = str_[i] - 'a';
        dp[i] = i;
        for (int j = 0; j < 26; j++) {
            if (!banned[j][x]) {
                dp[i] = min(dp[i], opt[j] + i - 1);
            }
        }
        opt[x] = min(opt[x], dp[i] - i);
    }

    int ans = inf;

    for (int i = 0; i < n; i++) {
        ans = min(ans, dp[i] + n - i - 1);
    }

    writer.StartObject();
    writer.Key("testId");
    writer.String(id.c_str());
    writer.Key("result");
    writer.Int(ans);
    writer.EndObject();

    cout << strBuf.GetString();
}

void output()
{

}

int main(int argc, char **argv)
{
    input(argv[1]);
    return 0;
}
