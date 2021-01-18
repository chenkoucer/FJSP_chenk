#pragma once
#ifndef GRAPH_COLORING_H
#define GRAPH_COLORING_H


#include <vector>
#include <random>
#include <string>
#include <sstream>
#include <ctime>

namespace ck {

#define NONE -1
#define kINF INT32_MAX
#define MAX_BUF_LEN 1000
using namespace std;
template<typename T>
void split_generic(vector<T> &v, const T & str, const T & delimiters) {
    //vector<T> v;
    v.clear();	// clear v to be empty
    typename T::size_type start = 0;
    auto pos = str.find_first_of(delimiters, start);
    while (pos != T::npos) {
        if (pos != start) // ignore empty tokens
            v.emplace_back(str, start, pos - start);
        start = pos + 1;
        pos = str.find_first_of(delimiters, start);
    }
    if (start < str.length()) // ignore trailing delimiter
        v.emplace_back(str, start, str.length() - start); // add what's left of the string
}

class FJSP {
public:
    const clock_t kStartClock = clock();
    const time_t kStartTime = time(NULL);
    const std::string  kAlgorithm = "TabuSearch";
    std::string kInstanceName;
    const std::string OptimalSolName = "optima.txt";
    
    struct Configure {
        int perturb_range = kINF;
        int timeout_seconds = 300;
        int max_tabu_steps = kINF;
        char* inPathFile = nullptr, *outPathFile = nullptr;
        unsigned int random_seed = 99995011 / (time(NULL) % 255) + 1;
        std::string ToString() {
            std::ostringstream res;
            res << "(" << perturb_range << "/"
                << timeout_seconds << "/"
                << max_tabu_steps << "/"
                << random_seed << ")";
            return res.str();
        }
    };
    class Process{
    private:
        int m; //工序的候选机器
        int t;    //工序在该候选机器上耗费的时间
    public:
        Process(){}
        Process(int _m, int _t) :m(_m), t(_t) {}
    };
public:
    explicit FJSP() {}
    explicit FJSP(Configure &cfg) : cfg_(cfg){
        kInstanceName = cfg_.inPathFile;
        srand(cfg_.random_seed);
    }
    ~FJSP() {}
    void Solve();

protected:
    void loadInstance(const std::string path);
    const bool isTimeOut() const {return (clock() - kStartClock) / CLOCKS_PER_SEC > cfg_.timeout_seconds;
    }

private:
    int task_num_;   //任务数量
    int machine_num_; //机器数量
    int num_mach_per_oper; //每个任务至多能有的候选机器
    Configure cfg_;
    
    vector<vector<vector<Process*>>> task_times;  //每个任务的若干工序在候选机器上的完成时间

    
 };

}















#endif // !GRAPH_COLORING_H
