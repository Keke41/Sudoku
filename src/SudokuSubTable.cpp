#include "SudokuSubTable.h"

SudokuSubTable::SudokuSubTable(pair<int,int> place, pair<int,int> position, vector<int>& subInitList):Widget(place.first,place.second), _place(place),_position(position)
{
    buttons.resize(3);
    for(int i=0;i<buttons.size();i++)
    {
        buttons[i].resize(3);
        for(int j=0;j<buttons[i].size();j++)
        {
            buttons[i][j] = new Button(_place.first + _position.first *120 + i*35, _place.second + _position.second *120 + j*35, subInitList[j*3+i]);
            buttons[i][j]->setHandler(new IncreaseClickHandler(buttons[i][j]));
        }
    }
}

SudokuSubTable::~SudokuSubTable()
{
    for(int i=0;i<buttons.size();i++)
    {
        for(int j=0;j<buttons[i].size();j++)
        {
            delete buttons[i][j];
        }
    }
}

int SudokuSubTable::getValue(pair<int,int> pos)
{
    return (buttons[pos.first][pos.second])->getValue();
}

void SudokuSubTable::draw()
{
    for(int i=0;i<buttons.size();i++)
    {
        for(int j=0;j<buttons[i].size();j++)
        {
            buttons[i][j]->draw();
        }
    }
}

void SudokuSubTable::handle(genv::event ev)
{
    for(int i=0;i<buttons.size();i++)
    {
        for(int j=0;j<buttons[i].size();j++)
        {
            buttons[i][j]->handle(ev);
        }
    }
}

pair<int,int> SudokuSubTable::getButtonPosition(int xx, int yy)
{
    for(int i=0;i<buttons.size();i++)
    {
        for(int j=0;j<buttons[i].size();j++)
        {
            if(buttons[i][j]->contains(xx,yy))
            {
                return make_pair(i,j);
            }
        }
    }
    return make_pair(-1,-1);
}

int SudokuSubTable::getButtonvalue(int i, int j)
{
    return buttons[i][j]->getValue();
}

bool SudokuSubTable::contains(int xx, int yy)
{
    for(int i=0;i<buttons.size();i++)
    {
        for(int j=0;j<buttons[i].size();j++)
        {
            if(buttons[i][j]->contains(xx,yy))
            {
                return true;
            }
        }
    }
    return false;
}

void SudokuSubTable::ResetConflicts()
{
    for(int i=0;i<buttons.size();i++)
    {
        for(int j=0;j<buttons[i].size();j++)
        {
            buttons[i][j]->setConflict(false);
        }
    }
}

void SudokuSubTable::setConflict(std::pair<int,int> conflict)
{
    buttons[conflict.first][conflict.second]->setConflict(true);
}

