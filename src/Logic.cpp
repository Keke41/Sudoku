#include <algorithm>
#include "Logic.h"
#include "SudokuTable.h"
Logic::Logic(SudokuTable& sTable):sudokuTable(sTable)
{

}

Logic::~Logic()
{
    //dtor
}

bool Logic::CheckForWin()
{
    for(int i=0;i<9;i++)
    {
        for(int j=0;j<9;j++)
        {
            if(sudokuTable.getButtonvalue(i,j) == 0)
            {
                return false;
            }
        }
    }

    return GetConflictingButtons().size() == 0;
}

std::vector<std::pair<int,int>> Logic::GetConflictingButtons()
{
    auto lastClicked = sudokuTable.getLastCLicked();
    std::vector<std::pair<int,int>> conflicts;
    HorizontalCheck(lastClicked.first, conflicts);
    VerticalCheck(lastClicked.second, conflicts);
    SubCheck(std::make_pair(lastClicked.first / 3, lastClicked.second / 3), conflicts);

    int confNum = conflicts.size();
    return conflicts;
}

void Logic::HorizontalCheck(int row,std::vector<std::pair<int,int>>& conflicts)
{
    for(int i=0;i<9;i++)
    {
        for(int j=i+1;j<9;j++)
        {
            if(i != j)
            {
                int num1 = sudokuTable.getButtonvalue(row,i);
                int num2 = sudokuTable.getButtonvalue(row,j);
                if(num1 != 0 && num2 != 0 && num1 == num2)
                {
                    conflicts.push_back(std::make_pair(row,i));
                    conflicts.push_back(std::make_pair(row,j));
                }
            }
        }
    }
}

void Logic::VerticalCheck(int col,std::vector<std::pair<int,int>>& conflicts)
{
    for(int i=0;i<9;i++)
    {
        for(int j=i+1;j<9;j++)
        {
            if(i!=j)
            {
                int num1 = sudokuTable.getButtonvalue(i,col);
                int num2 = sudokuTable.getButtonvalue(j,col);
                if(num1 != 0 && num2 != 0 && num1 == num2)
                {
                    conflicts.push_back(std::make_pair(i,col));
                    conflicts.push_back(std::make_pair(j,col));
                }
            }
        }
    }
}

void Logic::SubCheck(std::pair<int,int> subNum,std::vector<std::pair<int,int>>& conflicts)
{
    vector<int> tempNumbers;
    vector<int> dupNumbers;
    for(int i=subNum.first * 3;i<subNum.first * 3 + 3;i++)
    {
        for(int j=subNum.second * 3;j<subNum.second * 3 + 3;j++)
        {
            int num = sudokuTable.getButtonvalue(i,j);
            if(num !=0)
            {
                if(std::find(tempNumbers.begin(), tempNumbers.end(), num) != tempNumbers.end())
                {
                   dupNumbers.push_back(num);
                }
                tempNumbers.push_back(num);
            }
        }
    }

        for(int i=subNum.first * 3;i<subNum.first * 3 + 3;i++)
        {
            for(int j=subNum.second * 3;j<subNum.second * 3 + 3;j++)
            {
                int num = sudokuTable.getButtonvalue(i,j);
                if(std::find(dupNumbers.begin(), dupNumbers.end(), num) != dupNumbers.end())
                {
                    conflicts.push_back(std::make_pair(i,j));
                }
            }
        }
}
