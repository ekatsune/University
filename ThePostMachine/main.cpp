#include <iostream>
#include <iostream>
#include <fstream>
#include "Machine.hpp"
using namespace std;

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " <program_file> [-log]" << endl;
        return 1;
    }

    string filename = argv[1];
    bool logging = false;
    if (argc > 2 && string(argv[2]) == "-log") {
        logging = true;
    }

    ifstream fin(filename);
    if (!fin.is_open()) {
        cerr << "Error: cannot open file " << filename << endl;
        return 1;
    }

    Machine machine;
    machine.loadProgram(fin);  // загрузка правил
    machine.loadTape(fin);     // загрузка начальной ленты

    cout << "Program loaded. Starting execution...\n";

    if (logging) {
        machine.run();  // run вызывает showState() на каждом шаге
    } else {
        // без логов: просто выполним и в конце покажем состояние
        machine.run();
        machine.showState();
    }

    return 0;
}