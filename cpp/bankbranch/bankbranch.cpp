#include <bits/stdc++.h>
#include "../rapidjson/document.h"
#include "../rapidjson/prettywriter.h"

using namespace rapidjson;
using namespace std;

const int maxb = 1005;

int N;
int B;
int T[maxb];

int max_time;

void input(const char *path)
{
    ifstream file(path);
    string str((std::istreambuf_iterator<char>(file)),
               std::istreambuf_iterator<char>());
    const char *json = str.c_str();

    Document document;
    document.Parse(json);

    N = document["N"].GetInt();

    B = document["branch_officers_timings"].Size();
    for (int i = 0; i < B; i++) {
        T[i] = document["branch_officers_timings"][i].GetInt();
        max_time = max(max_time, T[i]);
    }
}

long long check(long long tm)
{
    long long ret = 0;
    for (int i = 0; i < B; i++) {
        ret += tm / T[i];
    }
    return ret;
}

int ans;

void specialSolve()
{
    vector<pair<int, int> > pool;
    for (int i = 0; i < B; i++) {
        for (int j = 0; j < N; j++) {
            pool.push_back(make_pair(T[i] * j, i));
        }
    }
    sort(pool.begin(), pool.end());
    ans = pool[N - 1].second + 1;
}

void solve()
{
    if (N * B <= 100000) {
        specialSolve();
        return;   
    }
    long long l = 0;
    long long r = 1ll * N * max_time;
    long long ret = -1;
    while (l < r) {
        long long mid = (l + r) >> 1;
        long long x = check(mid);
        if (x >= N) {
            r = mid - 1;
        } else {
            l = mid + 1;
            ret = mid;
        }
    }
    long long remain = N - check(ret);
    vector<pair<int, int> > wait;
    for (int i = 0; i < B; i++) {
        wait.push_back(make_pair((T[i] - ret % T[i]) % T[i], i));
    }
    sort(wait.begin(), wait.end());
    ans = wait[remain - 1].second + 1;
}

void output()
{
    StringBuffer strBuf;
    Writer<StringBuffer> writer(strBuf);

    writer.StartObject();
    writer.Key("answer");
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
