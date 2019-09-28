#include "matrix.h"

const int modulo = 998244353;
const int a1 = 107;
const unsigned int a2 = 91;

OneDimMatrix::OneDimMatrix(const Value& rootArray) {
    length = dimensions[0] = rootArray.Size();
    arr.resize(length);
    for (int i = 0; i < length; i++) {
        arr[i] = rootArray[i].GetInt();
        if (arr[i] == 0) {
            zero = i;
        }
    }
}

bool OneDimMatrix::shift(DIRECTION direction) {
    int t;
    switch(direction) {
    case DIRECTION::LEFT:
        if (zero == 0) {
            return false;
        }
        swap(arr[zero], arr[zero - 1]);
        zero--;
        return true;
    case DIRECTION::RIGHT:
        if (zero == length - 1) {
            return false;
        }
        swap(arr[zero], arr[zero + 1]);
        zero++;
        return true;
    default:
        return false;
    }
}

string OneDimMatrix::hash()
{
    int hash1 = 0;
    unsigned int hash2 = 0;
    for (const int &x : arr) {
        hash1 = (1ll * hash1 * a1 + x) % modulo;
        hash2 = hash2 * a2 + (unsigned int)x;
    }
    return to_string(hash1) + '#' + to_string(hash2);
}

TwoDimMatrix::TwoDimMatrix(const Value& rootArray) {
    height = dimensions[0] = rootArray.Size();
    width = dimensions[1] = rootArray[0].Size();
    arr.resize(height);
    for (int i = 0; i < height; i++) {
        arr[i].resize(width);
        for (int j = 0; j < width; j++) {
            arr[i][j] = rootArray[i][j].GetInt();
            if (arr[i][j] == 0) {
                zero[0] = i;
                zero[1] = j;
            }
        }
    }
}

bool TwoDimMatrix::shift(DIRECTION direction) {
    int t;
    switch(direction) {
    case DIRECTION::LEFT:
        if (zero[1] == 0) {
            return false;
        }
        t = arr[zero[0]][zero[1]];
        arr[zero[0]][zero[1]] = arr[zero[0]][zero[1] - 1];
        arr[zero[0]][zero[1] - 1] = t;
        zero[1]--;
        return true;
    case DIRECTION::RIGHT:
        if (zero[1] == width - 1) {
            return false;
        }
        t = arr[zero[0]][zero[1]];
        arr[zero[0]][zero[1]] = arr[zero[0]][zero[1] + 1];
        arr[zero[0]][zero[1] + 1] = t;
        zero[1]++;
        return true;
    case DIRECTION::BACKWARD:
        if (zero[0] == 0) {
            return false;
        }
        t = arr[zero[0]][zero[1]];
        arr[zero[0]][zero[1]] = arr[zero[0] - 1][zero[1]];
        arr[zero[0] - 1][zero[1]] = t;
        zero[0]--;
        return true;
    case DIRECTION::FORWARD:
        if (zero[0] == height - 1) {
            return false;
        }
        t = arr[zero[0]][zero[1]];
        arr[zero[0]][zero[1]] = arr[zero[0] + 1][zero[1]];
        arr[zero[0] + 1][zero[1]] = t;
        zero[0]++;
        return true;
    default:
        return false;
    }
}

string TwoDimMatrix::hash()
{
    int hash1 = 0;
    unsigned int hash2 = 0;
    for (const vector<int> &x : arr) {
        for (const int &y : x) {
            hash1 = (1ll * hash1 * a1 + y) % modulo;
            hash2 = hash2 * a2 + (unsigned int)y;
        }
    }
    return to_string(hash1) + '#' + to_string(hash2);
}

ThreeDimMatrix::ThreeDimMatrix(const Value& rootArray) {
    height = dimensions[0] = rootArray.Size();
    width = dimensions[1] = rootArray[0].Size();
    depth = dimensions[2] = rootArray[0][0].Size();
    arr.resize(depth);
    for (int i = 0; i < depth; i++) {
        arr[i].resize(height);
        for (int j = 0; j < height; j++) {
            arr[i][j].resize(width);
            for (int k = 0; k < width; k++) {
                arr[i][j][k] = rootArray[i][j][k].GetInt();
                if (arr[i][j][k] == 0) {
                    zero[0] = i;
                    zero[1] = j;
                    zero[2] = k;
                }
            }
        }
    }
}

bool ThreeDimMatrix::shift(DIRECTION direction) {
    int t;
    switch(direction) {
    case DIRECTION::LEFT:
        if (zero[2] == 0) {
            return false;
        }
        swap(arr[zero[0]][zero[1]][zero[2]], arr[zero[0]][zero[1]][zero[2] - 1]);
        zero[2]--;
        return true;
    case DIRECTION::RIGHT:
        if (zero[2] == width - 1) {
            return false;
        }
        swap(arr[zero[0]][zero[1]][zero[2]], arr[zero[0]][zero[1]][zero[2] + 1]);
        zero[2]++;
        return true;
    case DIRECTION::BACKWARD:
        if (zero[1] == 0) {
            return false;
        }
        swap(arr[zero[0]][zero[1]][zero[2]], arr[zero[0]][zero[1] - 1][zero[2]]);
        zero[1]--;
        return true;
    case DIRECTION::FORWARD:
        if (zero[1] == height - 1) {
            return false;
        }
        swap(arr[zero[0]][zero[1]][zero[2]], arr[zero[0]][zero[1] + 1][zero[2]]);
        zero[1]++;
        return true;
    case DIRECTION::DOWN:
        if (zero[0] == 0) {
            return false;
        }
        swap(arr[zero[0]][zero[1]][zero[2]], arr[zero[0] - 1][zero[1]][zero[2]]);
        zero[0]--;
        return true;
    case DIRECTION::UP:
        if (zero[0] == depth - 1) {
            return false;
        }
        swap(arr[zero[0] + 1][zero[1]][zero[2]], arr[zero[0]][zero[1]][zero[2]]);
        zero[0]++;
        return true;
    default:
        return false;
    }
}

string ThreeDimMatrix::hash()
{
    int hash1 = 0;
    unsigned int hash2 = 0;
    for (const vector<vector<int>> &x : arr) {
        for (const vector<int> &y : x) {
            for (const int &z : y) {
                hash1 = (1ll * hash1 * a1 + z) % modulo;
                hash2 = hash2 * a2 + (unsigned int)z;
            }
        }
    }
    return to_string(hash1) + '#' + to_string(hash2);
}
