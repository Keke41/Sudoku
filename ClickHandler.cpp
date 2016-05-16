#include "ClickHandler.h"
#include "Button.h"
#include "SudokuTable.h"
using namespace std;
using namespace genv;

void IncreaseClickHandler::handleClick()
{
    btn->increase();
}

void ConflictClickHandler::handleClick()
{
    auto conflictingButtons = logic.GetConflictingButtons();
    sudokuTable.setConflicts(conflictingButtons);
}



