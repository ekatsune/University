#include <iostream>
#include <map>
#include <vector>
using namespace std;
class Tape {
private:
    enum Symbol {zero, one};
    int position = 0;
    map <int,int> tape;
    int GetSymbol (int positionT);
    void SetSymbol (int positionT, int symbol);
public:
    Tape ();
    int Read();
    void WriteOne();
    void WriteZero();
    void MoveRight();
    void MoveLeft();
    void ShowTape(int radius = 5);
};