#include <bits/stdc++.h>
#include "../rapidjson/document.h"
#include "../rapidjson/prettywriter.h"

using namespace rapidjson;
using namespace std;

enum DIRECTION { LEFT = 'L', RIGHT = 'R', BACKWARD = 'B', FORWARD = 'F', UP = 'U', DOWN = 'D' };

class Matrix {
public:
    virtual Matrix* clone() = 0;
    virtual bool shift(char dir) = 0;
    virtual bool shift(DIRECTION direction) = 0;
    virtual void print() = 0;
    virtual int diff(Matrix* another) = 0;
    virtual string hash() = 0;
};

class OneDimMatrix: public Matrix {
public:
    OneDimMatrix() = default;
    Matrix* clone() {
        OneDimMatrix* ret = new OneDimMatrix();
        ret->arr = this->arr;
        ret->length = this->length;
        ret->dimensions[0] = this->dimensions[0];
        ret->zero = this->zero;
        Matrix* res = dynamic_cast<Matrix*>(ret);
        return res;
    }
    OneDimMatrix(const Value& rootArray);
    virtual void print() {
        for (int x : arr) {
            cout << x << " ";
        }
        cout << endl;
    }
    virtual int diff(Matrix* another) {
        static int pos[1005];
        OneDimMatrix* ret = dynamic_cast<OneDimMatrix*>(another);
        const vector<int>& vec_ = ret->arr;
        int res = 0;
        for (int i = 0; i < vec_.size(); i++) {
            pos[vec_[i]] = i;
        }
        for (int i = 0; i < arr.size(); i++) {
            if (arr[i] == 0) continue;
            res += abs(pos[arr[i]] - i);
        }
        return res;
    }
    virtual bool shift(char dir) {
        this->shift(DIRECTION(dir));
    }
    virtual bool shift(DIRECTION direction);
    virtual string hash();
    vector<int> arr;
    int length;
    int dimensions[1];
    int zero;
};

class TwoDimMatrix: public Matrix {
public:
    TwoDimMatrix() = default;
    TwoDimMatrix(const Value& rootArray);
    Matrix* clone() {
        TwoDimMatrix* ret = new TwoDimMatrix();
        ret->arr = this->arr;
        ret->width = this->width;
        ret->height = this->height;
        ret->dimensions[0] = this->dimensions[0];
        ret->dimensions[1] = this->dimensions[1];
        ret->zero[0] = this->zero[0];
        ret->zero[1] = this->zero[1];
        Matrix* res = dynamic_cast<Matrix*>(ret);
        return res;
    }    
    virtual void print() {
        for (vector<int> x : arr) {
            for (int y : x) {
                cout << y << " ";
            }
            cout << endl;
        }
        cout << endl;
    }    
    virtual int diff(Matrix* another) {
        static int pos[1005][2];
        TwoDimMatrix* ret = dynamic_cast<TwoDimMatrix*>(another);
        const vector<vector<int>>& vec_ = ret->arr;
        int res = 0;
        for (int i = 0; i < vec_.size(); i++) {
            for (int j = 0; j < vec_[i].size(); j++) {
                pos[vec_[i][j]][0] = i;
                pos[vec_[i][j]][1] = j;
            }
        }
        for (int i = 0; i < arr.size(); i++) {
            for (int j = 0; j < arr[i].size(); j++) {
                if (arr[i][j] == 0) continue;
                res += abs(pos[arr[i][j]][0] - i) + abs(pos[arr[i][j]][1] - j);
            }
        }
        return res;
    }
    virtual bool shift(char dir) {
        this->shift(DIRECTION(dir));
    }
    virtual bool shift(DIRECTION direction);    
    virtual string hash();
    vector<vector<int>> arr;
    int width;
    int height;
    int dimensions[2];
    int zero[2];
};

class ThreeDimMatrix: public Matrix {
public:
    ThreeDimMatrix() = default;
    Matrix* clone() {
        ThreeDimMatrix* ret = new ThreeDimMatrix();
        ret->arr = this->arr;
        ret->width = this->width;
        ret->height = this->height;
        ret->depth = this->depth;
        ret->dimensions[0] = this->dimensions[0];
        ret->dimensions[1] = this->dimensions[1];
        ret->dimensions[2] = this->dimensions[2];
        ret->zero[0] = this->zero[0];
        ret->zero[1] = this->zero[1];
        ret->zero[2] = this->zero[2];
        Matrix* res = dynamic_cast<Matrix*>(ret);
        return res;
    }
    ThreeDimMatrix(const Value& rootArray);
    virtual bool shift(char dir) {
        this->shift(DIRECTION(dir));
    }
    virtual bool shift(DIRECTION direction);
    virtual string hash();
    virtual void print() {
        for (vector<vector<int>> x : arr) {
            for (vector<int> y : x) {
                for (int z : y) {
                    cout << z << " ";
                }
                cout << endl;
            }
            cout << endl;
        }
        cout << endl;
    }
    virtual int diff(Matrix* another) {
        static int pos[1005][3];
        ThreeDimMatrix* ret = dynamic_cast<ThreeDimMatrix*>(another);
        const vector<vector<vector<int>>>& vec_ = ret->arr;
        int res = 0;
        for (int i = 0; i < vec_.size(); i++) {
            for (int j = 0; j < vec_[i].size(); j++) {
                for (int k = 0; k < vec_[i][j].size(); k++) {
                    pos[vec_[i][j][k]][0] = i;
                    pos[vec_[i][j][k]][1] = j;
                    pos[vec_[i][j][k]][2] = k;
                }
            }
        }
        for (int i = 0; i < arr.size(); i++) {
            for (int j = 0; j < arr[i].size(); j++) {
                for (int k = 0; k < arr[i][j].size(); k++) {
                    if (arr[i][j][k] == 0) continue;
                    res += abs(pos[arr[i][j][k]][0] - i) 
                           + abs(pos[arr[i][j][k]][1] - j)
                           + abs(pos[arr[i][j][k]][2] - k);
                }
            }
        }
        return res;
    }
    vector<vector<vector<int>>> arr;
    int width;
    int height;
    int depth;
    int dimensions[3];
    int zero[3];
};
