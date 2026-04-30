#include "pch.h"

#include "../PurgatorySeaCore/Board.h"
#include "../PurgatorySeaCore/GameController.h"
#include "../PurgatorySeaCore/Selection.h"

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

TEST(GameController, gamecontroller_should_receive_selection_reference)
{
    std::shared_ptr<FGameController> GameController = std::make_shared<FGameController>(); 
    std::shared_ptr<FSelection> Selection = std::make_shared<FSelection>(); 

    GameController->SetSelection(Selection); 
    
    EXPECT_TRUE(GameController->GetSelection() != nullptr); 
}

TEST(GameController, gamecontroller_should_be_initialized_with_starting_ships)
{
    int StartingShipNumber = 5; 
    std::shared_ptr<FGameController> GameController = std::make_shared<FGameController>(); 
    std::shared_ptr<FBoard> Board = std::make_shared<FBoard>(); 
    
    GameController->SetBoard(Board);
    GameController->InitGame(); 
    
    EXPECT_EQ(GameController->GetBoard()->GetShips().size(), StartingShipNumber); 
}
