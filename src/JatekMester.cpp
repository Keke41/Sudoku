#include "JatekMester.h"

using namespace genv;

using namespace std;

JatekMester::JatekMester()
{
}

const int XX=800;
const int YY=600;

void clear(canvas& out)
{
    out << move_to(0,0) << color(0,0,0) << box(XX, YY);
}

bool JatekMester::FileBeolvas(vector<int>& szamok)
{
    ifstream infile;
    int szam;
    infile.open ("palya.txt");
    while(!infile.eof())
    {
        infile >> szam;
        szamok.push_back(szam);
    }
    infile.close();
    return szamok.size() == 81;
}

void JatekMester::Indit()
{
    vector<int> szamok;
    FileBeolvas(szamok);

    SudokuTable sudokuTable(make_pair(200,50),szamok);
    Logic logic(sudokuTable);
    sudokuTable.setHandler(new ConflictClickHandler(sudokuTable,logic));

    gout.open(XX,YY);

    event ev;
    while(gin >> ev && ev.keycode != key_escape) {
        gout << clear;
        if(logic.CheckForWin())
        {
            gout << move_to(100,100)
                 << color(0,0,255)
                 << box_to(700,500)
                 << move_to(350,300)
                 << color(255,255,50)
                 << text("Nyertél!");
        }
        else
        {
            sudokuTable.handle(ev);
            sudokuTable.draw();

        }
        gout << refresh;
    }
}
