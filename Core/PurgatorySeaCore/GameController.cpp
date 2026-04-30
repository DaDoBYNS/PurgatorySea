#include "GameController.h"

FGameController::FGameController()
    : bIsGameReady(false)
{}

void FGameController::InitGame()
{
    Board->CreateShip(FPosition{ELetter::A, ENumber::Eight}, 2);
    Board->CreateShip(FPosition{ELetter::B, ENumber::Eight}, 3);
    Board->CreateShip(FPosition{ELetter::C, ENumber::Eight}, 3);
    Board->CreateShip(FPosition{ELetter::D, ENumber::Eight}, 4);
    Board->CreateShip(FPosition{ELetter::E, ENumber::Eight}, 5);
    
    bIsGameReady = true;
}

void FGameController::SetBoard(std::shared_ptr<FBoard>& InBoard)
{
    Board = InBoard;
}

void FGameController::SetSelection(std::shared_ptr<FSelection>& InSelection)
{
    Selection = InSelection;    
}

std::shared_ptr<FBoard> FGameController::GetBoard() const
{
    return Board;
}

std::shared_ptr<FSelection> FGameController::GetSelection() const
{
    return Selection; 
}

bool FGameController::GetIsGameReady() const
{
    return bIsGameReady; 
}