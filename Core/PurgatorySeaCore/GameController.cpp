#include "GameController.h"

FGameController::FGameController()
{}

void FGameController::SetBoard(std::shared_ptr<FBoard>& InBoard)
{
    Board = InBoard;
}

void FGameController::SetSelection(std::shared_ptr<FSelection>& InSelection)
{
    Selection = InSelection;    
}

std::shared_ptr<FSelection> FGameController::GetSelection()
{
    return Selection; 
}

std::shared_ptr<FBoard> FGameController::GetBoard()
{
    return Board;
}
