#include "solver.h"
#include <string>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <cassert>

using namespace std;

namespace ck {

void FJSP::Solve() {
    //cout << "ËãÀý£º" << kInstanceName << endl;
    loadInstance(kInstanceName);
    
}
void FJSP::loadInstance(const string ifn) {
    ifstream ifs(ifn);
    if (!ifs.is_open()) {
        cout << ifn << endl;
        perror("ifn"); exit(0);
    }
    string str_line;
    vector<string>fields_vec;
    if (ifn.find(".fjs") != string::npos)	// for flexible job shop instance
    {
        ifs >> task_num_ >> machine_num_ >> num_mach_per_oper;
        //cout << n << "\t" << m << "\t" << avg_num_mach_per_oper << endl;
        getline(ifs, str_line);	// read the '\n'
        task_times.resize(task_num_ + 1, vector<vector<Process*>>(NULL));
        int task_i = 0;
        while (getline(ifs, str_line)) {
            if (str_line == "")
                continue;
            if (task_i == task_num_)
                break;
            split_generic<string>(fields_vec, str_line, " \t");
            int field_cnt = 0;
            int num_oper = stoi(fields_vec[field_cnt++]);	// number of operation
            task_i += 1;
            task_times[task_i].resize(num_oper + 1, vector<Process*>(NULL));
            total_num_operation += num_oper;
            for (int oper_i = 1; oper_i <= num_oper; oper_i++)	// for each operation
            {
                int num_mach = stoi(fields_vec[field_cnt++]);	// number of process
                job_vec[job_i][oper_i].resize(num_mach + 1, NULL);
                for (int proc_i = 1; proc_i <= num_mach; proc_i++) {
                    int mach = stoi(fields_vec[field_cnt]);
                    field_cnt += 1;
                    int t = stoi(fields_vec[field_cnt]);
                    field_cnt += 1;
                    job_vec[job_i][oper_i][proc_i] = new Process(t, mach);	// machine index +1
                }
            }
        }
    } else // for job shop instance
    {
        ifs >> n >> m;
        cout << n << "\t" << m << "\t" << avg_num_mach_per_oper << endl;
        getline(ifs, str_line);	// read the '\n'
        job_vec.resize(n + 1, vector<vector<Process*>>(NULL));
        int job_i = 0;
        while (getline(ifs, str_line)) {
            cout << str_line << endl;
            split_generic<string>(fields_vec, str_line, " \t");
            int field_cnt = 0;
            int num_oper = m;
            job_i += 1;
            job_vec[job_i].resize(num_oper + 1, vector<Process*>(NULL));
            total_num_operation += num_oper;
            for (int oper_i = 0; oper_i < num_oper; oper_i++)	// for each operation
            {
                int num_mach = 1;	// stoi(fields_vec[field_cnt++]);	// number of process
                job_vec[job_i][oper_i].resize(num_mach + 1, NULL);
                for (int proc_i = 0; proc_i < num_mach; proc_i++) {
                    int mach = stoi(fields_vec[field_cnt]) + 1;
                    field_cnt += 1;
                    int t = stoi(fields_vec[field_cnt]);
                    field_cnt += 1;
                    job_vec[job_i][oper_i][proc_i] = new Process(t, mach);	// machine index +1
                }
            }
        }
    }
    ifs.close();


}




