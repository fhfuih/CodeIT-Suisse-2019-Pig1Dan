#include <bits/stdc++.h>
#include "../rapidjson/document.h"
#include "../rapidjson/prettywriter.h"
#include "matrix.h"

using namespace rapidjson;
using namespace std;

int dimension;
Matrix *goal;
Matrix *start;

void input(const char *path)
{
    ifstream file(path);
    string str((std::istreambuf_iterator<char>(file)),
               std::istreambuf_iterator<char>());
    const char *json = str.c_str();

    Document document;
    document.Parse(json);

    int arrayOneSize = 0, arrayTwoSize = 0, arrayThreeSize = 0;
    const Value& arrayOne = document["initial"];
    const Value& goalOne = document["goal"];

    // detect dimension
    arrayOneSize = arrayOne.Size();
    if (arrayOne[0].IsArray()) {
        const Value& arrayTwo = arrayOne[0];
        arrayTwoSize = arrayTwo.Size();
        if (arrayTwo[0].IsArray()) {
            const Value& arrayThree = arrayTwo[0];
            arrayThreeSize = arrayThree.Size();
            dimension = 3;
        } else {
            dimension = 2;
        }
    } else {
        dimension = 1;
    }

    // loading data
    if (dimension == 1) {
        start = new OneDimMatrix(arrayOne);
        goal = new OneDimMatrix(goalOne);
    } else if (dimension == 2) {
        start = new TwoDimMatrix(arrayOne);
        goal = new TwoDimMatrix(goalOne);
    } else if (dimension == 3) {
        start = new ThreeDimMatrix(arrayOne);
        goal = new ThreeDimMatrix(goalOne);
    }
}

vector<string> ans;
vector<char> steps;

int limit;
int st;

bool stop;

char rev[257];

char dir[] = {'R', 'L', 'B', 'F', 'D', 'U'};
char ops[] = {'L', 'R', 'F', 'B', 'U', 'D'}; 

bool dfs(int used, char last)
{
    int dist = start->diff(goal);
    if (dist == 0) {
        stop = true;
        return true;
    }
    if (limit == used) return false;
    for (int i = 0; i < 6; i++) {
        if (stop) break;
        if (rev[dir[i]] == last) continue;
        if (start->shift(dir[i])) {
            steps.push_back(dir[i]);
            if (used + start->diff(goal) + 1 <= limit) {
                if (dfs(used + 1, dir[i])) {
                    return true;
                }
            }
            steps.pop_back();
            start->shift(ops[i]);
        }
    }
    return false;
}

void getans()
{
    for (int i = 0; i < steps.size(); i++) {
        ans.push_back(string(1, steps[i]));
    }
}

void solve()
{
    rev['L'] = 'R';
    rev['R'] = 'L';
    rev['F'] = 'B';
    rev['B'] = 'F';
    rev['U'] = 'D';
    rev['D'] = 'U';
    limit = 0;
    while (true) {
        stop = false;
        if (dfs(0, 'X')) {
            getans();
            return;
        }
        limit ++;
    }
}

void output()
{
    StringBuffer strBuf;
    Writer<StringBuffer> writer(strBuf);

    writer.StartObject();
    writer.Key("moves");
    writer.StartArray();
    for (int i = 0; i < ans.size(); i++) {
        writer.String(ans[i].c_str());
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
