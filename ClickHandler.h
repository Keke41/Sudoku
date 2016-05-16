#ifndef CLICKHANDLER_H
#define CLICKHANDLER_H

#include "graphics.hpp"
#include <vector>
#include <iostream>
#include "Logic.h"

class Button;
class SudokuTable;

class ClickHandler
{
    public:
    virtual void handleClick() = 0;
    virtual ~ClickHandler() = default;
};

class IncreaseClickHandler : public ClickHandler {
    public:
    IncreaseClickHandler(Button* button)
    {
        btn = button;
    }
    virtual void handleClick() override;
    private:
    Button * btn;
};

class ConflictClickHandler : public ClickHandler {
    public:
    ConflictClickHandler(SudokuTable& sTable, Logic& lgic):sudokuTable(sTable),logic(lgic)
    {
    }
    virtual void handleClick() override;
    private:
    Logic& logic;
    SudokuTable& sudokuTable;
    std::vector<std::pair<int,int>> conficts;
};

#endif // CLICKHANDLER_H
