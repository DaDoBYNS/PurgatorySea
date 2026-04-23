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

TEST(ShipsPosition, ship_will_be_selected_given_by_a_position)
{
    FSelection Selection; 
    std::shared_ptr<FShip> Ship = Selection.GetShipAt(FPosition{ELetter::A, ENumber::Four}); 
    
    EXPECT_EQ(Ship->GetIsSelected(), true); 
}

TEST(ShipsPosition, ship_will_be_deselected)
{
    std::shared_ptr<FShip> Ship = std::make_shared<FShip>();
    Ship->SetIsSelected(false);
    
    EXPECT_EQ(Ship->GetIsSelected(), false);
}