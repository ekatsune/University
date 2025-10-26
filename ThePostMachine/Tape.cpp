#include "Tape.hpp"
#include <iostream>
#include <map>

Tape::Tape() {
    tape[position] = zero;
}

int Tape::GetSymbol(int positionT) {
    if (tape.find(positionT) != tape.end()) {
        return tape[positionT];
    }
    return zero;
}

void Tape::SetSymbol(int positionT, int symbol) {
    tape[positionT] = symbol;
}

int Tape::Read() {
    return GetSymbol(position);
}

void Tape::WriteOne() {
    SetSymbol(position, one);
}

void Tape::WriteZero() {
    SetSymbol(position, zero);
}

void Tape::MoveRight() {
    position++;
}

void Tape::MoveLeft() {
    position--;
}

void Tape::ShowTape(int radius) {
    for (int i = position - radius; i <= position + radius; i++) {
        if (i == position) {
            cout << "[" << GetSymbol(i) << "]";
        } else {
            cout << " " << GetSymbol(i) << " ";
        }
    }
    cout << endl;
}