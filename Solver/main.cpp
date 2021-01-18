#include "solver.h"
#include <iostream>
using namespace std;
using namespace ck;

constexpr char help_info[] = {
"Input switch is as follows:\n\
 fjsp.exe inPathFile outPathFile timeout_seconds rand_seed \n\
The four elements are necessary." };

static const vector<std::string> instList({
    "DSJC125.1.col",
    "DSJC250.1.col",
    "DSJC250.5.col",
    "DSJC250.9.col",
    "DSJC500.1.col",
    "DSJC500.5.col",
    "DSJC500.9.col",
    "DSJC1000.1.col",
    "DSJC1000.5.col",
    "DSJC1000.9.col"
    });
int main(int argc, char *argv[]) {
    FJSP::Configure cfg;
    if (argc != 5) {
        cout << "输入格式有误！，请重新输入!" << endl;
        cout << help_info << endl;
    }
    cfg.inPathFile = argv[1];
    cfg.outPathFile = argv[2];
    cfg.timeout_seconds = atoi(argv[3]);
    cfg.timeout_seconds = atol(argv[4]);
    FJSP solver(cfg);
    solver.Solve();
    getchar();
    return 0;
}