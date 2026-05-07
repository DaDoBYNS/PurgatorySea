#include "pch.h"

#include <gtest/gtest.h>

#include "Board.h"
#include "GameController.h"

TEST(ShipSinking, ship_should_not_be_sunk_when_created)
{
    std::shared_ptr<FBoard> Board = std::make_shared<FBoard>();
    std::shared_ptr<FShip> Ship = Board->CreateShip(FPosition{ELetter::A, ENumber::Four}, 1, "null");
    
    EXPECT_TRUE(!Ship->GetIsSunk()); 
}

TEST(ShipSinking, ship_should_not_be_sunk_when_no_position_was_hit)
{
    std::shared_ptr<FBoard> Board = std::make_shared<FBoard>();
    std::shared_ptr<FGameController> GameController = std::make_shared<FGameController>();
    std::shared_ptr<FSelection> Selection = std::make_shared<FSelection>();
    GameController->SetBoard(Board);
    GameController->SetSelection(Selection);
    GameController->GetSelection()->SetBoard(Board);
    
    std::shared_ptr<FShip> Ship = Board->CreateShip(FPosition{ELetter::A, ENumber::Four}, 1, "null");
    GameController->Shoot(FPosition{ELetter::J, ENumber::Eight}); 
    
    EXPECT_TRUE(!Ship->GetIsSunk()); 
}
