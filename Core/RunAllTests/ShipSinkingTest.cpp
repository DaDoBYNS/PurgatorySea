#include "pch.h"

#include <gtest/gtest.h>

#include "Board.h"

TEST(ShipSinking, ship_should_not_be_sunk_when_created)
{
    std::shared_ptr<FBoard> Board = std::make_shared<FBoard>();
    std::shared_ptr<FShip> Ship = Board->CreateShip(FPosition{ELetter::A, ENumber::Four}, 1, "null");
    
    EXPECT_TRUE(!Ship->GetIsSunk()); 
}
