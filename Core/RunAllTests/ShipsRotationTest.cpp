#include "pch.h"

#include "Board.h"
#include "Rotation.h"

TEST(ShipsRotation, ship_should_spawn_with_vertical_rotation)
{
    std::shared_ptr<FBoard> Board = std::make_shared<FBoard>(); 
    std::shared_ptr<FShip> Ship = Board->CreateShip(FPosition{ELetter::A, ENumber::Four}, 1, "null"); 

    EXPECT_TRUE(Ship->GetRotation() == ERotation::Vertical); 
}

TEST(ShipsRotation, ship_should_change_its_rotation_when_required)
{
    std::shared_ptr<FBoard> Board = std::make_shared<FBoard>(); 
    std::shared_ptr<FShip> Ship = Board->CreateShip(FPosition{ELetter::A, ENumber::Four}, 1, "null"); 

    ERotation StartRotation = Ship->GetRotation();
    
    Ship->SetRotation(ERotation::Horizontal); 
    
    EXPECT_TRUE(Ship->GetRotation() != StartRotation); 
}

