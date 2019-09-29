#include <bits/stdc++.h>
#include "../rapidjson/document.h"
#include "../rapidjson/prettywriter.h"

using namespace rapidjson;
using namespace std;

const int maxn = 105;
const int maxk = 5;

const double pi = acos(-1.0);

int K;
int N;

vector<int> arr[maxk];

void input(const char *path)
{
    ifstream file(path);
    string str((std::istreambuf_iterator<char>(file)),
               std::istreambuf_iterator<char>());
    const char *json = str.c_str();

    Document document;
    document.Parse(json);

    K = document.Size();
    for (int i = 0; i < K; i++) {
        N = document[i].Size();
        for (int j = 0; j < N; j++) {
            arr[i].push_back(document[i][j].GetInt());
        }
    }
}

vector<double> randList(double low, double high, int n)
{
    vector<double> res(n);
    for (int i = 0; i < n; i++) {
        res[i] = low + (high - low) * (rand() * 1.0 / RAND_MAX);   
    }
    return res;
}

int sine;

vector<int> out[5];

vector<double> calc(double base, double trend, const vector<double> &scales, const vector<double> &pcounts, int st, int ed)
{
    vector<double> ret;
    ret.resize(ed - st, 0);
    for (int i = 0; i < ed - st; i++) {
        int x = i + st;
        double addi = 0;
        ret[i] = base + trend * x;  
        for (int j = 0; j < sine; j++) {
            addi += scales[j] * sin(2 * pi * pcounts[j] * x);
        }     
        ret[i] += addi;
    }   
    return ret;
}

double param_score(double base, double trend, const vector<double> &scales, const vector<double> &pcounts)
{
    vector<double> y_pred = calc(base, trend, scales, pcounts, 0, 100);
    double ret = 0;
    for (int i = 0; i < N; i++) {
        ret += fabs(y_pred[i] - arr[sine - 1][i]);
    }
    return ret;
}

void solve()
{
    for (sine = 1; sine <= 4; sine++) {

        double base = 200 + 100 * (rand() * 1.0 / RAND_MAX);
        double trend = -100 + 200 * (rand() * 1.0 / RAND_MAX);
        vector<double> scales = randList(5, 15, sine);
        vector<double> pcounts = randList(10, 100, sine);

        // best set
        double base_ = base;
        double trend_ = trend;
        vector<double> scales_ = scales;
        vector<double> pcounts_ = pcounts;

        double best_score = param_score(base, trend, scales, pcounts);
        double now_score = best_score;

        double T = 1e4;
        double coef = 0.9999;
        double T_low = 1e-4;

        int st = clock();

        int counter = 0;

        while (T > T_low) {

            if ((clock() - st) * 1.0 / CLOCKS_PER_SEC > 6.5) {
                break;
            }

            double base__ = base;
            double trend__ = trend;
            vector<double> scales__ = scales;
            vector<double> pcounts__ = pcounts;

            double perc;
            if (T > 1e5) {
                perc = 0.4;
            } else if (T > 1) {
                perc = 0.05;
            } else {
                perc = T * 0.1;
            }

            base__ += (50 - 100 * (rand() * 1.0 / RAND_MAX)) * perc;
            base__ = min(max(base__, 200.0), 300.0);
            trend__ += (100 - 200 * (rand() * 1.0 / RAND_MAX)) * perc;
            trend__ = min(max(trend__, -100.0), 100.0);
            for (int i = 0; i < sine; i++) {
                scales__[i] += (5 - 10 * (rand() * 1.0 / RAND_MAX)) * perc;
                scales__[i] = min(max(scales__[i], 5.0), 15.0);
                pcounts__[i] += (45 - 90 * (rand() * 1.0 / RAND_MAX)) * perc;
                pcounts__[i] = min(max(pcounts__[i], 10.0), 100.0);
            }

            double new_score = param_score(base__, trend__, scales__, pcounts__);
            double delta = new_score - now_score;

/*
            if (counter % 1000000 == 0) {
                cout << "best_score = " << best_score 
                    << "  now_score = " << now_score << endl;
                if (delta > 0) {
                    cout << "T = " << T << "  exp = " << exp(-delta / T) << endl;
                } else {
                    cout << "T = " << T << endl;
                }
            }
*/

            if (delta < 0 || exp(-delta / T) > rand() * 1.0 / RAND_MAX) {
                now_score = new_score;
                base = base__;
                trend = trend__;
                scales = scales__;
                pcounts = pcounts__;
                if (new_score < best_score) {
                    best_score = new_score;
                    base_ = base__;
                    trend_ = trend__;
                    scales_ = scales__;
                    pcounts_ = pcounts__;
                }
            }

            T *= coef;
        }

        out[sine - 1].push_back(100);
        bool hold = true;

        vector<double> result = calc(base_, trend_, scales_, pcounts_, 100, 1100);

        for (int i = 1; i < 999; i++) {
            if (hold && result[i] >= result[i - 1] && result[i] > result[i + 1]) {
                out[sine - 1].push_back(100 + i);
                hold = false;
            }
            if (!hold && result[i] <= result[i - 1] && result[i] < result[i + 1]) {
                out[sine - 1].push_back(100 + i);
                hold = true;
            }
        }
    }

}

void output()
{
    StringBuffer strBuf;
    Writer<StringBuffer> writer(strBuf);

    writer.StartArray();

    for (int i = 0; i < 4; i++) {
        writer.StartArray();
        for (int j = 0; j < out[i].size(); j++) {
            writer.Int(out[i][j]);        
        }
        writer.EndArray();
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
