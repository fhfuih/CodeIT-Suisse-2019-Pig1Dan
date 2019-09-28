#include <bits/stdc++.h>
#include "../rapidjson/document.h"
#include "../rapidjson/prettywriter.h"

using namespace rapidjson;
using namespace std;

const int maxsz = (1 << 20) + 1;
const int inf = 0x3f3f3f3f;

int N;
int T;

int dp[maxsz][2];

void input(const char *path)
{
    ifstream file(path);
    string str((std::istreambuf_iterator<char>(file)),
               std::istreambuf_iterator<char>());
    const char *json = str.c_str();

    Document document;
    document.Parse(json);

    N = stoi(document["maxChoosableInteger"].GetString());
    T = stoi(document["desiredTotal"].GetString());
}

int ans;

void solve()
{
    int sz = 1 << N;
    
    for (int i = sz - 1; i >= 0; i--) {
        int sum = 0;
        for (int j = 0; j < N; j++) {
            if (i >> j & 1) {
                sum += j + 1;
            }
        }
        if (sum >= T) {
            dp[i][0] = -1;
            dp[i][1] = 0;
        } else {
            // A first
            dp[i][0] = -1;
            for (int j = 0; j < N; j++) {
                if (i >> j & 1) continue;
                int to = i | (1 << j);
                if (dp[to][1] != -1) {
                    dp[i][0] = max(dp[to][1] + 1, dp[i][0]);
                }
            }
            // B first
            dp[i][1] = -1;
            bool win = false;
            for (int j = 0; j < N; j++) {
                if (i >> j & 1) continue;
                int to = i | (1 << j);
                if (dp[to][0] == -1) {
                    win = true;
                } else {
                    dp[i][1] = max(dp[to][0] + 1, dp[i][1]);
                }
            }
            if (win) {
                dp[i][1] = -1;
            }
        }
    }

    ans = dp[0][0];
}

void output()
{
    StringBuffer strBuf;
    Writer<StringBuffer> writer(strBuf);

    writer.StartObject();
    writer.Key("res");
    writer.Int(ans);
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
