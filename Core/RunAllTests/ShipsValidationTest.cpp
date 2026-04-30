#include "pch.h"

#include "../PurgatorySeaCore/Board.h"
#include "../PurgatorySeaCore/Selection.h"
#include "../PurgatorySeaCore/Validation.h"


TEST(ShipsValidation, validation_should_pass_when_all_ships_are_inside_board)
{
    std::shared_ptr<FValidation> Validation = std::make_shared<FValidation>(); 
    std::shared_ptr<FBoard> Board = std::make_shared<FBoard>(); 
    
    Validation->SetBoard(Board); 
    
    Board->CreateShip(FPosition{ELetter::B, ENumber::Four}, 3);
    Board->CreateShip(FPosition{ELetter::C, ENumber::Four}, 3);
    Board->CreateShip(FPosition{ELetter::D, ENumber::Four}, 3);
    
    Validation->ValidateShips(); 
    EXPECT_TRUE(Validation->GetIsValid());
} 

TEST(ShipsValidation, validation_should_fail_when_a_ship_is_partially_outside_board)
{
    std::shared_ptr<FValidation> Validation = std::make_shared<FValidation>(); 
    std::shared_ptr<FBoard> Board = std::make_shared<FBoard>(); 
    
    Validation->SetBoard(Board); 
    
    Board->CreateShip(FPosition{ELetter::B, ENumber::Two}, 3);
    
    Validation->ValidateShips(); 
    EXPECT_FALSE(Validation->GetIsValid());
}

TEST(ShipsValidation, validation_should_fail_when_two_ships_overlap)
{
    std::shared_ptr<FValidation> Validation = std::make_shared<FValidation>(); 
    std::shared_ptr<FBoard> Board = std::make_shared<FBoard>(); 
    
    Validation->SetBoard(Board); 
    
    Board->CreateShip(FPosition{ELetter::B, ENumber::Four}, 3);
    Board->CreateShip(FPosition{ELetter::B, ENumber::Six}, 5);
    
    Validation->ValidateShips(); 
    EXPECT_FALSE(Validation->GetIsValid()); 
} 

TEST(ShipsValidation, validation_should_report_outside_board_with_error_highlight)
{
    std::shared_ptr<FValidation> Validation = std::make_shared<FValidation>(); 
    std::shared_ptr<FBoard> Board = std::make_shared<FBoard>(); 
    
    Validation->SetBoard(Board); 
    
    std::shared_ptr<FShip> Ship = Board->CreateShip(FPosition{ELetter::D, ENumber::Two}, 3);
    
    Validation->ValidateShips(); 
    EXPECT_TRUE(Ship->GetIsErrorHighlighted()); 
} 

TEST(ShipsValidation, validation_should_report_overlap_with_error_highlight)
{
    std::shared_ptr<FValidation> Validation = std::make_shared<FValidation>(); 
    std::shared_ptr<FBoard> Board = std::make_shared<FBoard>(); 
    
    Validation->SetBoard(Board); 
    
    std::shared_ptr<FShip> Ship = Board->CreateShip(FPosition{ELetter::D, ENumber::Five}, 3);
    Board->CreateShip(FPosition{ELetter::D, ENumber::Six}, 3);
    
    Validation->ValidateShips(); 
    EXPECT_TRUE(Ship->GetIsErrorHighlighted()); 
} 

TEST(ShipsValidation, validation_should_report_an_error_to_multiple_ships_with_error_highlight)
{
    std::shared_ptr<FValidation> Validation = std::make_shared<FValidation>(); 
    std::shared_ptr<FBoard> Board = std::make_shared<FBoard>(); 
    
    Validation->SetBoard(Board); 
    
    std::shared_ptr<FShip> Ship = Board->CreateShip(FPosition{ELetter::D, ENumber::Five}, 3);
    std::shared_ptr<FShip> SecondShip = Board->CreateShip(FPosition{ELetter::D, ENumber::Six}, 3);
    std::shared_ptr<FShip> ThirdShip = Board->CreateShip(FPosition{ELetter::D, ENumber::Six}, 3);
    
    Validation->ValidateShips();
    EXPECT_TRUE(Ship->GetIsErrorHighlighted() && SecondShip->GetIsErrorHighlighted() && ThirdShip->GetIsErrorHighlighted()); 
} 

TEST(ShipsValidation, validation_should_remove_error_highlight_to_a_valid_ship)
{
    std::shared_ptr<FValidation> Validation = std::make_shared<FValidation>(); 
    std::shared_ptr<FBoard> Board = std::make_shared<FBoard>(); 
    
    Validation->SetBoard(Board); 
    
    std::shared_ptr<FShip> Ship = Board->CreateShip(FPosition{ELetter::D, ENumber::Five}, 3);
    std::shared_ptr<FShip> SecondShip = Board->CreateShip(FPosition{ELetter::D, ENumber::Six}, 3);
    std::shared_ptr<FShip> ThirdShip = Board->CreateShip(FPosition{ELetter::D, ENumber::Six}, 3);
    
    Validation->ValidateShips();
    bool bWasInErrorHighlight = Ship->GetIsErrorHighlighted(); 
    
    FSelection Selection; 
    Selection.SetBoard(Board);
    
    Selection.SelectShipAt(FPosition{ELetter::D, ENumber::Five}); 
    Selection.MoveShipTo(FPosition{ELetter::G, ENumber::Eight}); 
    Validation->ValidateShips();
    
    EXPECT_TRUE(bWasInErrorHighlight && !Ship->GetIsErrorHighlighted()); 
} 
