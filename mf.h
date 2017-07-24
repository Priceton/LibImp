#include <vector>
#include <algorithm>
#include <string>
#include <memory>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cmath>
#include <cstdio>
#include <iomanip>
#include <random>

#include "omp.h"

using namespace std;


typedef double FtrlFloat;
typedef double FtrlDouble;
typedef int FtrlInt;
typedef long long FtrlLong;


class Node {
public:
    FtrlLong p_idx;
    FtrlLong q_idx;
    FtrlDouble  val;
    Node(){};
    Node(FtrlLong p_idx, FtrlLong q_idx, FtrlDouble val): p_idx(p_idx), q_idx(q_idx), val(val){};
};

class Parameter {

public:
    FtrlFloat lambda;
    FtrlInt nr_pass, k, nr_threads;
    Parameter():lambda(0.1), nr_pass(20), k(10),nr_threads(1) {};
};


class FtrlData {
public:
    string file_name;
    FtrlLong l, m, n;
    vector<Node> R;
    vector<vector<Node*>> P;
    vector<vector<Node*>> Q;

    FtrlData(string file_name): file_name(file_name), l(0), m(0), n(0) {};
    void transpose();
    void read();
    void print_data_info();
};

class FtrlProblem {
public:
    shared_ptr<FtrlData> data;
    shared_ptr<FtrlData> test_data;
    shared_ptr<Parameter> param;
    FtrlProblem(shared_ptr<FtrlData> &data, shared_ptr<FtrlData> &test_data, shared_ptr<Parameter> &param)
        :data(data), test_data(test_data), param(param) {};


    vector<FtrlFloat> W;
    vector<FtrlFloat> H;

    FtrlInt t;
    FtrlDouble obj, reg, tr_loss, va_loss;
    FtrlFloat start_time;

    FtrlDouble cal_loss(FtrlLong &l, vector<Node> &R);
    FtrlDouble cal_reg();
    FtrlDouble cal_tr_loss(FtrlLong &l, vector<Node> &R);
    void update_w(FtrlLong i, FtrlInt d);
    void update_h(FtrlLong j, FtrlInt d);
    void initialize();
    void solve();
    void update_R();
    void update_coordinates();
    void print_epoch_info();
    void print_header_info();
};
