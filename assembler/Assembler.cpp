#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <bitset>
#include "Assembler.h"

using namespace std;

enum ops {
    ADD,
    ADDI,
    SUB,
    LUI,
    AND,
    ANDI,
    OR,
    ORI,
    XOR,
    XORI,
    NOR,
    SLL,
    SRL,
    SRA,
    LW,
    LH,
    LB,
    SW,
    SH,
    SB,
    BEQ,
    BNE,
    BLT,
    BLE,
    J,
    JAL,
    JR,
    NOOP,
};

ops hashOps(string str) {
    if (str == "add") return ADD;
    if (str == "addi") return ADDI;
    if (str == "sub") return SUB;
    if (str == "lui") return LUI;
    if (str == "and") return AND;
    if (str == "andi") return ANDI;
    if (str == "or") return OR;
    if (str == "ori") return ORI;
    if (str == "xor") return XOR;
    if (str == "xori") return XORI;
    if (str == "nor") return NOR;
    if (str == "sll") return SLL;
    if (str == "srl") return SRL;
    if (str == "sra") return SRA;
    if (str == "lw") return LW;
    if (str == "lh") return LH;
    if (str == "lb") return LB;
    if (str == "sw") return SW;
    if (str == "sh") return SH;
    if (str == "sb") return SB;
    if (str == "beq") return BEQ;
    if (str == "bne") return BNE;
    if (str == "blt") return BLT;
    if (str == "ble") return BLE;
    if (str == "j") return J;
    if (str == "jal") return JAL;
    if (str == "jr") return JR;
    return NOOP;
}


void Assembler::loadLabels(ifstream &ifs) {
    string str;
    while (getline(ifs, str)) {
        if (str.find(":") != string::npos) {
            str.replace(str.find(":"), 1, " : ");
        }

        replace(str.begin(), str.end(), ',', ' ');

        vector<string> tokens = tokenize(str);

        if (tokens[1] == ":") {
            labels[tokens[0]] = cursor;
        }

        cursor++;
    }

    cursor = 0;
}

void Assembler::assemble(ifstream &ifs) {
    string str;
    while (getline(ifs, str)) {
        if (str.find(":") != string::npos) {
            str.replace(str.find(":"), 1, " : ");
        }

        replace(str.begin(), str.end(), ',', ' ');

        vector<string> tokens = tokenize(str);

        if (tokens[1] == ":") {
            vector<string>::const_iterator first = tokens.begin() + 2;
            vector<string>::const_iterator last = tokens.end();
            vector<string> newvec(first, last);

            tokens = newvec;
        }

        switch (hashOps(tokens[0])) {
            case ADD:
                renderR3(tokens, 0, 0);
                break;
            case ADDI:
                renderR2imm(tokens, 1);
                break;
            case SUB:
                renderR3(tokens, 0, 2);
                break;
            case LUI:
                renderR1imm(tokens, 3);
                break;
            case AND:
                renderR3(tokens, 0, 8);
                break;
            case ANDI:
                renderR2imm(tokens, 4);
                break;
            case OR:
                renderR3(tokens, 0, 9);
                break;
            case ORI:
                renderR2imm(tokens, 5);
                break;
            case XOR:
                renderR3(tokens, 0, 10);
                break;
            case XORI:
                renderR2imm(tokens, 6);
                break;
            case NOR:
                renderR3(tokens, 0, 11);
                break;
            case SLL:
                renderR2(tokens, 0, 16);
                break;
            case SRL:
                renderR2(tokens, 0, 17);
                break;
            case SRA:
                renderR2(tokens, 0, 18);
                break;
            case LW:
                renderR1Dpl(tokens, 16);
                break;
            case LH:
                renderR1Dpl(tokens, 18);
                break;
            case LB:
                renderR1Dpl(tokens, 20);
                break;
            case SW:
                renderR1Dpl(tokens, 24);
                break;
            case SH:
                renderR1Dpl(tokens, 26);
                break;
            case SB:
                renderR1Dpl(tokens, 28);
                break;
            case BEQ:
                renderR2Label(tokens, 32);
                break;
            case BNE:
                renderR2Label(tokens, 33);
                break;
            case BLT:
                renderR2Label(tokens, 34);
                break;
            case BLE:
                renderR2Label(tokens, 35);
                break;
            case J:
                renderR0Label(tokens, 40);
                break;
            case JAL:
                renderR0Label(tokens, 41);
                break;
            case JR:
                renderR1(tokens, 42);
                break;
            default:
                throw runtime_error("Invalid mnemonic in asm instruction");
        }

        cursor++;
    }

    cursor = 0;
}

// op rd rs rt  -> op(6) rs(5) rt(5) rd(5) aux(11)
void Assembler::renderR3(vector<string> &tokens, int op, int aux) {
    if (tokens[1][0] != 'r' || tokens[2][0] != 'r' || tokens[3][0] != 'r') {
        throw invalid_argument("Invalid register identifier");
    }

    string op6 = binarize(6, op);
    string rt5 = binarize(5, stoi(tokens[2].substr(1, -1)));
    string rd5 = binarize(5, stoi(tokens[3].substr(1, -1)));
    string rs5 = binarize(5, stoi(tokens[1].substr(1, -1)));
    string aux11 = binarize(11, aux);

    cout << op6 + rt5 + rd5 + rs5 + aux11 + "\n";
}

// op rd rs shift -> op(6) rs(5) r0(5) rd(5) shift(5) aux(6)
void Assembler::renderR2(vector<string> &tokens, int op, int aux) {
    if (tokens[1][0] != 'r' || tokens[2][0] != 'r') {
        throw invalid_argument("Invalid register identifier");
    }

    string op6 = binarize(6, op);
    string rs5 = binarize(5, stoi(tokens[2].substr(1, -1)));
    string ro5 = binarize(5, 0);
    string rd5 = binarize(5, stoi(tokens[1].substr(1, -1)));
    string shift5 = binarize(5, stoi(tokens[3]));
    string aux6 = binarize(6, aux);

    cout << op6 + rs5 + ro5 + rd5 + shift5 + aux6 + "\n";
}

// op rt rs imm -> op(6) rs(5) rt(5) imm(16)
void Assembler::renderR2imm(vector<string> &tokens, int op) {
    if (tokens[1][0] != 'r' || tokens[2][0] != 'r') {
        throw invalid_argument("Invalid register identifier");
    }

    string op6 = binarize(6, op);
    string rs5 = binarize(5, stoi(tokens[2].substr(1, -1)));
    string rt5 = binarize(5, stoi(tokens[1].substr(1, -1)));
    string imm16 = binarize(16, stoi(tokens[3]));

    cout << op6 + rs5 + rt5 + imm16 + "\n";
}

// op rt rs label -> op(6) rs(5) rt(5) {label - i -1}(16)
void Assembler::renderR2Label(vector<string> &tokens, int op) {
    if (tokens[1][0] != 'r' || tokens[2][0] != 'r') {
        throw invalid_argument("Invalid register identifier");
    }

    string op6 = binarize(6, op);
    string rs5 = binarize(5, stoi(tokens[2].substr(1, -1)));
    string rt5 = binarize(5, stoi(tokens[1].substr(1, -1)));
    string label16 = binarize(16, labels[tokens[3]] - cursor - 1);

    cout << op6 + rs5 + rt5 + label16 + "\n";
}

// op rs -> op(6) rs(5) r0(5) r0(5) aux(11)
void Assembler::renderR1(vector<string> &tokens, int op) {
    if (tokens[1][0] != 'r') {
        throw invalid_argument("Invalid register identifier");
    }

    string op6 = binarize(6, op);
    string rs5 = binarize(5, stoi(tokens[1].substr(1, -1)));
    string ro5_1 = binarize(5, 0);
    string ro5_2 = binarize(5, 0);
    string aux11 = binarize(11, 0);

    cout << op6 + rs5 + ro5_1 + ro5_2 + aux11 + "\n";
}

// op rt imm -> op(6) r0(5) rt(5) imm(16)
void Assembler::renderR1imm(vector<string> &tokens, int op) {
    if (tokens[1][0] != 'r') {
        throw invalid_argument("Invalid register identifier");
    }

    string op6 = binarize(6, op);
    string ro5 = binarize(5, 0);
    string rt5 = binarize(5, stoi(tokens[1].substr(1, -1)));
    string imm16 = binarize(16, stoi(tokens[2]));

    cout << op6 + ro5 + rt5 + imm16 + "\n";
}

// op rt dpl(rs) -> op(6) rs(5) rt(5) dpl(16)
void Assembler::renderR1Dpl(vector<string> &tokens, int op) {
    if (tokens[1][0] != 'r') {
        throw invalid_argument("Invalid register identifier");
    }

    // TODO: validate token[2] string format

    int dpl;
    int rs_i;
    sscanf(tokens[2].c_str(), "%d(r%d)", &dpl, &rs_i);

    string op6 = binarize(6, op);
    string rs5 = binarize(5, rs_i);
    string rt5 = binarize(5, stoi(tokens[1].substr(1, -1)));
    string dpl16 = binarize(16, dpl);

    cout << op6 + rs5 + rt5 + dpl16 + "\n";
}

// op label -> op(6) label(26)
void Assembler::renderR0Label(vector<string> &tokens, int op) {
    string op6 = binarize(6, op);
    string label26 = binarize(26, labels[tokens[1]]);

    cout << op6 + label26 + "\n";
}

string Assembler::binarize(int digit, int value) {
    unsigned int u_value = (unsigned int) value;

    int *digits = new int[digit];
    int i = 0, r;
    stringstream ss;

    for (int j = 0; j < digit; j++) {
        digits[j] = 0;
    }

    while (u_value != 0 && i < digit) {
        r = u_value % 2;
        digits[i++] = r;
        u_value /= 2;
    }

    for (int j = digit - 1; j >= 0; j--) {
        ss << digits[j];
    }

    delete[] digits;

    return ss.str() + "_";
}

vector<string> Assembler::tokenize(string &str) {
    string buf;
    stringstream ss(str);
    vector<string> tokens;

    while (ss >> buf) {
        tokens.push_back(buf);
    }

    return tokens;
}

