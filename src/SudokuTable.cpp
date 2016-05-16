#include "SudokuTable.h"

SudokuTable::SudokuTable(pair<int,int> place, vector<int>& initList): Widget(place.first,place.second), _place(place)
{
    subtables.resize(3);
    for(int i=0;i<subtables.size();i++)
    {
        subtables[i].resize(3);
        for(int j=0;j<subtables[i].size();j++)
        {
            vector<int> subInitList;
            for(int a=0;a<3;a++)
            {
                for(int b=0;b<3;b++)
                {
                    subInitList.push_back(initList[j*27+a*9 + i*3 + b]);
                }
            }
            subtables[i][j] = new SudokuSubTable(place,std::make_pair(i,j),subInitList);
        }
    }
}

SudokuTable::~SudokuTable()
{
   for(int i=0;i<subtables.size();i++)
    {
        for(int j=0;j<subtables[i].size();j++)
        {
            delete subtables[i][j];
        }
    }
}

void SudokuTable::draw()
{
    for(int i=0;i<subtables.size();i++)
    {
        for(int j=0;j<subtables[i].size();j++)
        {
            (subtables[i][j])->draw();
        }
    }
}

pair<int,int> SudokuTable::getButtonPosition(int x, int y)
{
    for(int i=0;i<subtables.size();i++)
    {
        for(int j=0;j<subtables[i].size();j++)
        {
            auto btn = subtables[i][j]->getButtonPosition(x,y);
            if(btn.first != -1)
            {
                return make_pair(i*3 + btn.first, j*3 + btn.second);
            }
        }
    }
    return make_pair(-1,-1);
}

int SudokuTable::getButtonvalue(int i, int j)
{
    return subtables[i/3][j/3]->getButtonvalue(i%3,j%3);
}

void SudokuTable::setHandler(ClickHandler *ch) {
    _handler = ch;
}

void SudokuTable::handle(genv::event ev)
{
    if (_handler != nullptr && ev.type == genv::ev_mouse
        && ev.button == genv::btn_left )
        {
            for(int i=0;i<subtables.size();i++)
            {
                for(int j=0;j<subtables[i].size();j++)
                {
                    subtables[i][j]->handle(ev);
                }
            }

            _lastClicked = getButtonPosition(ev.pos_x,ev.pos_y);
            if(_lastClicked.first != -1 && _lastClicked.second != -1)
            {
                _handler->handleClick();
            }
        }
}

bool SudokuTable::contains(int xx, int yy)
{
    for(int i=0;i<subtables.size();i++)
    {
        for(int j=0;j<subtables[i].size();j++)
        {
            if(subtables[i][j]->contains(xx,yy))
            {
                return true;
            }
        }
    }
    return false;
}

void SudokuTable::setConflicts(std::vector<std::pair<int,int>>& conflicts)
{
    for(int i=0;i<subtables.size();i++)
    {
        for(int j=0;j<subtables[i].size();j++)
        {
            subtables[i][j]->ResetConflicts();
        }
    }

    for(int i=0;i<conflicts.size();i++)
    {
        subtables[ conflicts[i].first / 3 ][conflicts[i].second / 3]->setConflict( std::make_pair(conflicts[i].first % 3,conflicts[i].second % 3));
    }
}
