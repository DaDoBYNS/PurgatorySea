#include "pch.h"

#include "../PurgatorySeaCore/Letter.h"
#include "../PurgatorySeaCore/Number.h"
#include "../PurgatorySeaCore/Position.h"
#include "../PurgatorySeaCore/Selection.h"

TEST(ShipsPosition, ship_will_be_selected)
{
    std::shared_ptr<FShip> Ship = std::make_shared<FShip>(FPosition{ELetter::A, ENumber::Three}, 1);
    Ship->SetIsSelected(true);
    
    EXPECT_EQ(Ship->GetIsSelected(), true); 
}

TEST(ShipsPosition, ship_will_be_deselected)
{
    std::shared_ptr<FShip> Ship = std::make_shared<FShip>(FPosition{ELetter::A, ENumber::Three}, 1);
    Ship->SetIsSelected(false);
    
    EXPECT_EQ(Ship->GetIsSelected(), false);
}

TEST(ShipsPosition, ship_should_be_selected_from_selection_class)
{
    std::shared_ptr<FBoard> Board = std::make_shared<FBoard>();
    Board->CreateShip(FPosition{ELetter::A, ENumber::Three}, 1);
    
    FSelection Selection;
    Selection.SetBoard(Board);
    
    std::shared_ptr<FShip> Ship = Selection.SelectShipAt(FPosition{ELetter::A, ENumber::Three});
    
    std::shared_ptr<FShip> SelectedShip = Selection.GetSelectedShip(); 
    
    EXPECT_EQ(Ship, SelectedShip);
}

TEST(ShipsPosition, ship_already_selected_should_change_if_new_valid_selection_is_performed)
{
    std::shared_ptr<FBoard> Board = std::make_shared<FBoard>();
    Board->CreateShip(FPosition{ELetter::A, ENumber::Three}, 1);
    Board->CreateShip(FPosition{ELetter::D, ENumber::Six}, 1);
    
    FSelection Selection;
    Selection.SetBoard(Board);
    
    Selection.SelectShipAt(FPosition{ELetter::A, ENumber::Three});
    std::shared_ptr<FShip> SelectedShip = Selection.GetSelectedShip();
    
    Selection.SelectShipAt(FPosition{ELetter::D, ENumber::Six}); 
    std::shared_ptr<FShip> NewSelectedShip = Selection.GetSelectedShip();
    
    EXPECT_TRUE(NewSelectedShip != SelectedShip);
}

TEST(ShipsPosition, ship_already_selected_should_not_be_valid_if_new_invalid_selection_is_performed)
{
    std::shared_ptr<FBoard> Board = std::make_shared<FBoard>();
    Board->CreateShip(FPosition{ELetter::A, ENumber::Three}, 1);
    
    FSelection Selection;
    Selection.SetBoard(Board);
    
    Selection.SelectShipAt(FPosition{ELetter::A, ENumber::Three});
    std::shared_ptr<FShip> SelectedShip = Selection.GetSelectedShip();
    
    Selection.SelectShipAt(FPosition{ELetter::D, ENumber::Six}); 
    std::shared_ptr<FShip> NewSelectedShip = Selection.GetSelectedShip();
    
    EXPECT_TRUE(NewSelectedShip == nullptr);
}

TEST(ShipsPosition, ship_will_be_selected_given_by_a_position)
{
    std::shared_ptr<FBoard> Board = std::make_shared<FBoard>();
    Board->CreateShip(FPosition{ELetter::A, ENumber::Three}, 1); 
    FSelection Selection;
    Selection.SetBoard(Board);
    
    std::shared_ptr<FShip> Ship = Selection.SelectShipAt(FPosition{ELetter::A, ENumber::Three});
    
    EXPECT_EQ(Ship->GetIsSelected(), true); 
}

TEST(ShipsPosition, ship_will_not_be_selected_given_by_an_empty_position)
{
    std::shared_ptr<FBoard> Board = std::make_shared<FBoard>();
    Board->CreateShip(FPosition{ELetter::A, ENumber::Three}, 1); 
    FSelection Selection;
    Selection.SetBoard(Board);
    
    EXPECT_EQ(Selection.SelectShipAt(FPosition{ELetter::A, ENumber::Four}), nullptr);
}

TEST(ShipsPosition, ship_will_be_selected_given_by_a_position_among_other_ships)
{
    std::shared_ptr<FBoard> Board = std::make_shared<FBoard>();
    FSelection Selection; 
    Selection.SetBoard(Board);
    Board->CreateShip(FPosition{ELetter::A, ENumber::Four}, 1); 
    Board->CreateShip(FPosition{ELetter::B, ENumber::Four}, 1); 
    Board->CreateShip(FPosition{ELetter::C, ENumber::Four}, 1); 
    Board->CreateShip(FPosition{ELetter::D, ENumber::Four}, 1); 
    
    std::shared_ptr<FShip> Ship = Selection.SelectShipAt(FPosition{ELetter::B, ENumber::Four}); 
    
    EXPECT_EQ(Ship->GetIsSelected(), true); 
}

TEST(ShipsPosition, created_ship_should_have_correct_dimension)
{
    std::shared_ptr<FBoard> Board = std::make_shared<FBoard>();

    std::shared_ptr<FShip> Ship = Board->CreateShip(FPosition{ELetter::A, ENumber::Three}, 3);

    EXPECT_EQ(Ship->GetDimension(), 3);
}

TEST(ShipsPosition, ship_should_be_selectable_at_different_positions)
{
    std::shared_ptr<FBoard> Board = std::make_shared<FBoard>();
    Board->CreateShip(FPosition{ELetter::B, ENumber::Four}, 3);
    
    FSelection Selection;
    Selection.SetBoard(Board);
    std::shared_ptr<FShip> Ship = Selection.SelectShipAt(FPosition{ELetter::B, ENumber::Four}); 
    
    EXPECT_EQ(Ship->GetIsSelected(), true); 
    
    Ship->SetIsSelected(false);
    Ship = Selection.SelectShipAt(FPosition{ELetter::B, ENumber::Three}); 
    
    EXPECT_EQ(Ship->GetIsSelected(), true); 
    
    Ship->SetIsSelected(false);
    Ship = Selection.SelectShipAt(FPosition{ELetter::B, ENumber::Two}); 
    
    EXPECT_EQ(Ship->GetIsSelected(), true); 
}

TEST(ShipsPosition, ship_selection_should_always_be_in_the_first_position)
{
    FPosition StartPosition = FPosition{ELetter::B, ENumber::Four}; 
    std::shared_ptr<FBoard> Board = std::make_shared<FBoard>();
    Board->CreateShip(FPosition{ELetter::B, ENumber::Four}, 3);
    
    FSelection Selection;
    Selection.SetBoard(Board);
    std::shared_ptr<FShip> Ship = Selection.SelectShipAt(StartPosition); 
    
    EXPECT_TRUE((Ship->GetFirstPosition() == StartPosition)); 
    
    Ship->SetIsSelected(false);
    Ship = Selection.SelectShipAt(FPosition{ELetter::B, ENumber::Three}); 
    
    EXPECT_TRUE((Ship->GetFirstPosition() == StartPosition)); 
    
    Ship->SetIsSelected(false);
    Ship = Selection.SelectShipAt(FPosition{ELetter::B, ENumber::Two}); 
    
    EXPECT_TRUE((Ship->GetFirstPosition() == StartPosition)); 
}
 
TEST(ShipsPosition, ship_can_be_created_even_if_partially_outside_board)
{
    FPosition StartPosition = FPosition{ELetter::B, ENumber::Two}; 
    std::shared_ptr<FBoard> Board = std::make_shared<FBoard>();
    
    std::shared_ptr<FShip> Ship = Board->CreateShip(StartPosition, 3);
 
    EXPECT_TRUE(Ship != nullptr);
}

TEST(ShipsPosition, ship_should_be_selectable_even_if_partially_outside_board)
{
    FPosition StartPosition = FPosition{ELetter::B, ENumber::Two}; 
    std::shared_ptr<FBoard> Board = std::make_shared<FBoard>();
    
    Board->CreateShip(StartPosition, 3);
    
    FSelection Selection;
    Selection.SetBoard(Board);
    
    std::shared_ptr<FShip> Ship = Selection.SelectShipAt(FPosition{ELetter::B, -1});
 
    EXPECT_TRUE(Ship->GetIsSelected());
}

TEST(ShipsPosition, existing_ship_should_be_able_to_move_to_a_new_position)
{
    std::shared_ptr<FBoard> Board = std::make_shared<FBoard>();
    Board->CreateShip(FPosition{ELetter::B, ENumber::Two}, 3);
    
    FSelection Selection;
    Selection.SetBoard(Board);
    
    Selection.SelectShipAt(FPosition{ELetter::B, ENumber::Two});
    
    FPosition StartPosition = Selection.GetSelectedShip()->GetFirstPosition();
    
    Selection.MoveShipTo(FPosition{ELetter::C,ENumber::Four}); 
    
    EXPECT_TRUE(StartPosition != Selection.GetSelectedShip()->GetFirstPosition()); 
}