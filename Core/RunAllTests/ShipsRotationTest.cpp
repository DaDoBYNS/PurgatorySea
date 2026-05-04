#include "pch.h"

#include "Board.h"
#include "Rotation.h"

TEST(ShipsRotation, ship_should_spawn_with_vertical_rotation)
{
    std::shared_ptr<FBoard> Board = std::make_shared<FBoard>(); 
    std::shared_ptr<FShip> Ship = Board->CreateShip(FPosition{ELetter::A, ENumber::Four}, 1, "null"); 

    EXPECT_TRUE(Ship->GetRotation() == ERotation::Vertical); 
}
