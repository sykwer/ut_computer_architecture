#ifndef ASSEMBLER_ASSEMBLER_H
#define ASSEMBLER_ASSEMBLER_H

#include <map>
#include <fstream>

using namespace std;

class Assembler {
public:
    void loadLabels(std::ifstream&);
    void assemble(ifstream&);

private:
    std::map<std::string, int> labels;
    int cursor = 0;

    void renderR3(vector<string>&, int, int);
    void renderR2(vector<string>&, int, int);
    void renderR2imm(vector<string>&, int);
    void renderR2Label(vector<string>&, int);
    void renderR1(vector<string>&, int);
    void renderR1imm(vector<string>&, int);
    void renderR1Dpl(vector<string>&, int);
    void renderR0Label(vector<string>&, int);
    string binarize(int , int);
    vector<string> tokenize(string&);
};


#endif //ASSEMBLER_ASSEMBLER_H
