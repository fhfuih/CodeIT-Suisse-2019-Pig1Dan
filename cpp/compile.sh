docker run --rm -v `pwd`:/tmp frolvlad/alpine-gxx g++ /tmp/$1/$1.cpp -o /tmp/$1/$1 -std=c++11 -O2