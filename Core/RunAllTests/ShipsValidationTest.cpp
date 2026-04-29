#include "pch.h"

#include "../PurgatorySeaCore/Board.h"
#include "../PurgatorySeaCore/Validation.h"


TEST(ShipsValidation, validation_should_pass_when_all_ships_are_inside_board)
{
    std::shared_ptr<FValidation> Validation = std::make_shared<FValidation>(); 
    std::shared_ptr<FBoard> Board = std::make_shared<FBoard>(); 
    
    Validation->SetBoard(Board); 
    
    Board->CreateShip(FPosition{ELetter::B, ENumber::Four}, 3);
    Board->CreateShip(FPosition{ELetter::B, ENumber::Four}, 3);
    Board->CreateShip(FPosition{ELetter::B, ENumber::Four}, 3);
    
    Validation->ValidateShips(); 
    EXPECT_TRUE(Validation->GetIsValid());
} 

TEST(ShipsValidation, validation_should_fail_when_a_ship_is_partially_outside_board)
{
    std::shared_ptr<FValidation> Validation = std::make_shared<FValidation>(); 
    std::shared_ptr<FBoard> Board = std::make_shared<FBoard>(); 
    
    Validation->SetBoard(Board); 
    
    Board->CreateShip(FPosition{ELetter::B, ENumber::Four}, 3);
    Board->CreateShip(FPosition{ELetter::B, ENumber::Four}, 3);
    Board->CreateShip(FPosition{ELetter::B, ENumber::Two}, 3);
    
    Validation->ValidateShips(); 
    EXPECT_FALSE(Validation->GetIsValid());
}