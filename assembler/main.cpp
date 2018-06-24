#include <iostream>
#include <fstream>
#include "Assembler.h"

using namespace std;

void loadLabels(Assembler& assembler, string asmFile) {
    ifstream ifs(asmFile);

    if (ifs.fail()) {
        cerr << "Fail to read asm file";
    }

    assembler.loadLabels(ifs);
    ifs.close();
}

void assemble(Assembler& assembler, string asmFile) {
    ifstream ifs(asmFile);

    if (ifs.fail()) {
        cerr << "Fail to read asm file";
    }

    assembler.assemble(ifs);
    ifs.close();
}

int main(int argc, char* argv[]) {
    Assembler assembler;
    string asmFile = argv[1];

    loadLabels(assembler, asmFile);
    assemble(assembler, asmFile);

    return 0;
}
