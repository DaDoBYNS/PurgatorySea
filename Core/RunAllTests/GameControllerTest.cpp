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

TEST(GameController, gamecontroller_should_be_ready_to_start_the_game)
{
    std::shared_ptr<FGameController> GameController = std::make_shared<FGameController>(); 
    std::shared_ptr<FBoard> Board = std::make_shared<FBoard>(); 
    
    GameController->SetBoard(Board);
    GameController->InitGame(); 
    
    EXPECT_EQ(GameController->GetIsGameReady(), true); 
}

TEST(GameController, gamecontroller_should_select_ship_through_selection)
{
    std::shared_ptr<FGameController> GameController = std::make_shared<FGameController>();
    std::shared_ptr<FSelection> Selection = std::make_shared<FSelection>();
    std::shared_ptr<FBoard> Board = std::make_shared<FBoard>(); 
    
    GameController->SetBoard(Board);
    GameController->SetSelection(Selection);
    GameController->GetSelection()->SetBoard(Board);
    
    GameController->InitGame(); 
    std::shared_ptr<FShip> Ship = GameController->SelectShipAt(FPosition{ELetter::A, ENumber::Eight}); 
    
    EXPECT_EQ(Ship->GetIsSelected(), true); 
}

TEST(GameController, gamecontroller_should_move_selected_ship_through_selection)
{
    std::shared_ptr<FGameController> GameController = std::make_shared<FGameController>();
    std::shared_ptr<FSelection> Selection = std::make_shared<FSelection>();
    std::shared_ptr<FBoard> Board = std::make_shared<FBoard>(); 
    
    FPosition StartPosition = FPosition{ELetter::A, ENumber::Eight}; 
    
    GameController->SetBoard(Board);
    GameController->SetSelection(Selection);
    GameController->GetSelection()->SetBoard(Board);
    
    GameController->InitGame(); 
    std::shared_ptr<FShip> Ship = GameController->SelectShipAt(StartPosition); 
    
    GameController->MoveShipTo(FPosition{ELetter::I, ENumber::Eight}); 
    
    EXPECT_TRUE(Ship->GetFirstPosition() != StartPosition); 
} 