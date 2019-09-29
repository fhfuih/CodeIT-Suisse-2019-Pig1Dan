#include <bits/stdc++.h>
#include "../rapidjson/document.h"
#include "../rapidjson/prettywriter.h"

using namespace rapidjson;
using namespace std;

const int maxn = 4096;

struct point
{
    int x;
    int y;
};

struct bucket
{
    int id; // -1 -> not cnosider
    int x_left;
    int x_right;
    int y_low;
    int y_high;
    bool full;
};

struct line
{
    point high;
    point low;
};

int width;
int height;
int n; // bucket
int m; // line
int s;

bucket bck[maxn];
line pipe[maxn];
point source[maxn];

int8_t pixel[maxn][maxn]; // 1 for bucket, 2 for pipe
int val[maxn][maxn]; // corresponding id

void input(const char *path)
{
    ifstream file(path);
    string str((std::istreambuf_iterator<char>(file)),
               std::istreambuf_iterator<char>());
    const char *json = str.c_str();

    ofstream out("/root/CodeIT-Suisse-2019-Pig1Dan/cpp/bucket/json.txt");
    out << json << endl;
    out.close();

    Document document;
    document.Parse(json);

    width = height = 3000;

    const Value& bucketArr = document["bck"];
    n = document["bck"].Size();
    for (int i = 0; i < n; i++) {
        bck[i].x_left = bucketArr[i]["x_left"].GetInt();
        bck[i].x_right = bucketArr[i]["x_right"].GetInt();
        bck[i].y_low = bucketArr[i]["y_low"].GetInt();
        bck[i].y_high = bucketArr[i]["y_high"].GetInt();
        bck[i].id = i;
        bck[i].full = false;
        if (bck[i].x_left > bck[i].x_right) {
            swap(bck[i].x_left, bck[i].x_right);
        }
        if (bck[i].y_high > bck[i].y_low) {
            swap(bck[i].y_low, bck[i].y_high);
        }
    }

    const Value& pipeArr = document["pipe"];
    m = document["pipe"].Size();
    for (int i = 0; i < m; i++) {
        pipe[i].high.x = pipeArr[i]["high"]["x"].GetInt();
        pipe[i].high.y = pipeArr[i]["high"]["y"].GetInt();
        pipe[i].low.x = pipeArr[i]["low"]["x"].GetInt();
        pipe[i].low.y = pipeArr[i]["low"]["y"].GetInt();
        if (pipe[i].high.y > pipe[i].low.y) {
            swap(pipe[i].high, pipe[i].low);
        }
    }
    
    const Value& sourceArr = document["source"];
    s = document["source"].Size();
    for (int i = 0; i < s; i++) {
        source[i].x = sourceArr[i]["x"].GetInt();
        source[i].y = sourceArr[i]["y"].GetInt();
    }
}

bool memo[maxn][maxn];

vector<point> overflow(int id)
{
    vector<point> ret;
    
    if (bck[id].y_high > 0) {

        int hy = bck[id].y_high;

        if (bck[id].x_left > 0) {
            int lx = bck[id].x_left;
            if (!pixel[hy - 1][lx] && !pixel[hy - 1][lx - 1] && !pixel[hy - 1][lx + 1]) {
                ret.push_back({lx - 1, hy - 1});
            }
        }

        if (bck[id].x_right < width - 1) {
            int rx = bck[id].x_right;
            if (!pixel[hy - 1][rx] && !pixel[hy - 1][rx - 1] && !pixel[hy - 1][rx + 1]) {
                ret.push_back({rx + 1, hy - 1});
            }  
        }

    }
    
    return ret;
}

void go(int x, int y)
{
    if (memo[y][x]) return;
    while (y < height) {
        memo[y][x] = true;
        if (pixel[y][x] == 0) {
            y ++;
        } else if (pixel[y][x] == 1) {
            int id = val[y][x];
            bck[id].full = true;
            vector<point> newsource = overflow(id);
            for (int i = 0; i < newsource.size(); i++) {
                go(newsource[i].x, newsource[i].y);
            }
            break;
        } else {
            int id = val[y][x];
            point to = pipe[id].low;
            if (to.y < height - 1) {
                go(to.x, to.y + 1);
            }
            break;
        }
    }
}

int ans = 0;

void bck_fill(int id)
{
    for (int i = bck[id].y_high; i < bck[id].y_low; i++) {
        for (int j = bck[id].x_left; j < bck[id].x_right; j++) {
            if (!pixel[i][j]) {
                pixel[i][j] = 3;
                ans ++;
            }
        }
    }
}

void solve()
{
    for (int i = 0; i < n; i++) {
        int foo = bck[i].y_low;
        for (int k = bck[i].x_left; k <= bck[i].x_right; k++) {
            pixel[foo][k] = 1;
            val[foo][k] = i;
        }
        int bar = bck[i].x_right;
        foo = bck[i].x_left;
        for (int k = bck[i].y_high; k <= bck[i].y_low; k++) {
            pixel[k][foo] = pixel[k][bar] = 1;
            val[k][foo] = val[k][bar] = i;
        }
    }
    for (int i = 0; i < m; i++) {
        int dx = pipe[i].high.x > pipe[i].low.x ? -1 : 1;
        int dy = pipe[i].high.y > pipe[i].low.y ? -1 : 1;
        int cx = pipe[i].high.x;
        int cy = pipe[i].high.y;
        while (cx != pipe[i].low.x || cy != pipe[i].low.y) {
            pixel[cy][cx] = 2;
            val[cy][cx] = i;
            cx += dx;
            cy += dy;
        }
    }
    for (int i = 0; i < s; i++) {
        go(source[i].x, source[i].y);
    }
    for (int i = 0; i < n; i++) {
        if (bck[i].full) {
            bck_fill(i);
        }
    }
}

void output()
{
    StringBuffer strBuf;
    Writer<StringBuffer> writer(strBuf);

    writer.StartObject();
    writer.Key("result");
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
