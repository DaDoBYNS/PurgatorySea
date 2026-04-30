#include "pch.h"

#include "../PurgatorySeaCore/Board.h"
#include "../PurgatorySeaCore/GameController.h"

TEST(GameController, gamecontroller_should_be_created)
{
    std::shared_ptr<FGameController> GameController = std::make_shared<FGameController>(); 
    
    EXPECT_TRUE(GameController != nullptr); 
}

TEST(GameController, gamecontroller_should_receive_board_reference)
{
    std::shared_ptr<FGameController> GameController = std::make_shared<FGameController>(); 
    std::shared_ptr<FBoard> Board = std::make_shared<FBoard>(); 

    GameController->SetBoard(Board); 
    
    EXPECT_TRUE(GameController->GetBoard() != nullptr); 
}