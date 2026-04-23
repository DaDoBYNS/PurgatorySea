#include "pch.h"

#include "../PurgatorySeaCore/Letter.h"
#include "../PurgatorySeaCore/Number.h"
#include "../PurgatorySeaCore/Position.h"
#include "../PurgatorySeaCore/Selection.h"

TEST(ShipsPosition, ship_will_be_selected)
{
    std::shared_ptr<FShip> Ship = std::make_shared<FShip>();
    Ship->SetIsSelected(true);
    
    EXPECT_EQ(Ship->GetIsSelected(), true); 
}

TEST(ShipsPosition, ship_will_be_deselected)
{
    std::shared_ptr<FShip> Ship = std::make_shared<FShip>();
    Ship->SetIsSelected(false);
    
    EXPECT_EQ(Ship->GetIsSelected(), false);
}

TEST(ShipsPosition, ship_will_be_selected_given_by_a_position)
{
    std::shared_ptr<FBoard> Board = std::make_shared<FBoard>();
    Board->CreateShip(3); 
    FSelection Selection;
    Selection.SetBoard(Board);
    
    std::shared_ptr<FShip> Ship = Selection.GetShipAt(FPosition{ELetter::A, ENumber::Three});
    
    EXPECT_EQ(Ship->GetIsSelected(), true); 
}

TEST(ShipsPosition, ship_will_not_be_selected_given_by_a_position)
{
    std::shared_ptr<FBoard> Board = std::make_shared<FBoard>();
    Board->CreateShip(3); 
    FSelection Selection;
    Selection.SetBoard(Board);
    
    EXPECT_EQ(Selection.GetShipAt(FPosition{ELetter::A, ENumber::Four}), nullptr);
}

TEST(ShipsPosition, ship_will_be_selected_given_by_a_position_among_other_ships)
{
    std::shared_ptr<FBoard> Board = std::make_shared<FBoard>();
    FSelection Selection; 
    Selection.SetBoard(Board);
    Board->CreateShip(3); 
    Board->CreateShip(3); 
    Board->CreateShip(3); 
    Board->CreateShip(4); 
    
    std::shared_ptr<FShip> Ship = Selection.GetShipAt(FPosition{ELetter::A, ENumber::Four}); 
    
    EXPECT_EQ(Ship->GetIsSelected(), true); 
}