#include "pch.h"

#include "../PurgatorySeaCore/GameController.h"

TEST(GameController, gamecontroller_should_be_created)
{
    std::shared_ptr<FGameController> GameController = std::make_shared<FGameController>(); 
    
    EXPECT_TRUE(GameController != nullptr); 
}