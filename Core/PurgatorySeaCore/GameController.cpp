#include "GameController.h"

FGameController::FGameController()
{}

void FGameController::SetBoard(std::shared_ptr<FBoard>& InBoard)
{
    Board = InBoard;
}

std::shared_ptr<FBoard> FGameController::GetBoard()
{
    return Board;
}
