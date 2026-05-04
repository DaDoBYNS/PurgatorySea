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

TEST(GameController, gamecontroller_should_give_battleship_the_right_name)
{
    std::shared_ptr<FGameController> GameController = std::make_shared<FGameController>(); 
    std::shared_ptr<FBoard> Board = std::make_shared<FBoard>(); 
    std::shared_ptr<FSelection> Selection = std::make_shared<FSelection>();
    
    GameController->SetBoard(Board);
    GameController->SetSelection(Selection);
    GameController->GetSelection()->SetBoard(Board);
    
    GameController->InitGame(); 
    
    EXPECT_TRUE(GameController->SelectShipByName("battleship") != nullptr); 
}

TEST(GameController, gamecontroller_should_give_aircraftcarrier_the_right_name)
{
    std::shared_ptr<FGameController> GameController = std::make_shared<FGameController>(); 
    std::shared_ptr<FBoard> Board = std::make_shared<FBoard>(); 
    std::shared_ptr<FSelection> Selection = std::make_shared<FSelection>();
    
    GameController->SetBoard(Board);
    GameController->SetSelection(Selection);
    GameController->GetSelection()->SetBoard(Board);
    
    GameController->InitGame(); 
    
    EXPECT_TRUE(GameController->SelectShipByName("aircraft carrier") != nullptr); 
}

TEST(GameController, gamecontroller_should_give_submarine_the_right_name)
{
    std::shared_ptr<FGameController> GameController = std::make_shared<FGameController>(); 
    std::shared_ptr<FBoard> Board = std::make_shared<FBoard>(); 
    std::shared_ptr<FSelection> Selection = std::make_shared<FSelection>();
    
    GameController->SetBoard(Board);
    GameController->SetSelection(Selection);
    GameController->GetSelection()->SetBoard(Board);
    
    GameController->InitGame(); 
    
    EXPECT_TRUE(GameController->SelectShipByName("submarine") != nullptr); 
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

TEST(GameControllerTest, check_no_winner_if_no_ships_registered)
{
    FGameController Controller;

    EXPECT_EQ(Controller.CheckWinner(), 0);
}

TEST(GameControllerTest, check_no_winner_at_start)
{
    FGameController Controller;
    Controller.SetPlayer1ShipPositions({{ELetter::A, ENumber::One}});
    Controller.SetPlayer2ShipPositions({{ELetter::B, ENumber::Two}});

    EXPECT_EQ(Controller.CheckWinner(), 0);
}

TEST(GameControllerTest, check_if_positions_player_1_is_inizialized_correctly)
{
    FGameController Controller;
    Controller.SetPlayer1ShipPositions({{ELetter::C, ENumber::Five}});

    EXPECT_EQ(Controller.GetPlayer1ShipPositions().GetEnemyShipPositions().empty(), false);
}

TEST(GameControllerTest, check_if_positions_player_2_is_inizialized_correctly)
{
    FGameController Controller;
    Controller.SetPlayer2ShipPositions({{ELetter::F, ENumber::Seven}});

    EXPECT_EQ(Controller.GetPlayer2ShipPositions().GetEnemyShipPositions().empty(), false);
}

TEST(GameControllerTest, check_player1_can_hit_all_enemy_ships)
{
    FGameController Controller;
    Controller.SetPlayer2ShipPositions({{ELetter::A, ENumber::One}, {ELetter::A, ENumber::Two}});
    Controller.SetPlayer1ShipPositions({{ELetter::H, ENumber::Eight}});

    EXPECT_EQ(Controller.Player1Shoot({ELetter::A, ENumber::One}), EEnemyTileType::Hit);
    
    EXPECT_EQ(Controller.Player1Shoot({ELetter::A, ENumber::Two}), EEnemyTileType::Hit);
}

TEST(GameControllerTest, check_player2_can_hit_all_enemy_ships)
{
    FGameController Controller;
    Controller.SetPlayer1ShipPositions({{ELetter::C, ENumber::Eight}, {ELetter::C, ENumber::Nine}});
    Controller.SetPlayer2ShipPositions({{ELetter::H, ENumber::Eight}});

    EXPECT_EQ(Controller.Player2Shoot({ELetter::C, ENumber::Eight}), EEnemyTileType::Hit);
    
    EXPECT_EQ(Controller.Player2Shoot({ELetter::C, ENumber::Nine}), EEnemyTileType::Hit);
}

TEST(GameControllerTest, check_player1_can_hit_all_enemy_ships_x)
{
    FGameController Controller;
    Controller.SetPlayer2ShipPositions({{ELetter::A, ENumber::One}, {ELetter::A, ENumber::Two}});
    Controller.SetPlayer1ShipPositions({{ELetter::H, ENumber::Eight}});

    Controller.Player1Shoot({ELetter::A, ENumber::One});
    Controller.Player1Shoot({ELetter::A, ENumber::Two});
    
    EXPECT_EQ(Controller.CheckWinner(), 1);
}

TEST(GameControllerTest, check_player2_can_hit_all_enemy_ships_x)
{
    FGameController Controller;
    Controller.SetPlayer1ShipPositions({{ELetter::C, ENumber::Eight}, {ELetter::C, ENumber::Nine}});
    Controller.SetPlayer2ShipPositions({{ELetter::H, ENumber::Eight}});

    Controller.Player2Shoot({ELetter::C, ENumber::Eight});
    Controller.Player2Shoot({ELetter::C, ENumber::Nine});
    
    EXPECT_EQ(Controller.CheckWinner(), 2);
}

TEST(GameControllerTest, check_no_winner_after_partial_hits)
{
    FGameController Controller;
    Controller.SetPlayer2ShipPositions({{ELetter::A, ENumber::One}, {ELetter::A, ENumber::Two}});
    Controller.SetPlayer1ShipPositions({{ELetter::H, ENumber::Eight}});

    Controller.Player1Shoot({ELetter::A, ENumber::One});

    EXPECT_EQ(Controller.CheckWinner(), 0);
}

TEST(GameControllerTest, check_miss_does_not_trigger_win)
{
    FGameController Controller;
    Controller.SetPlayer2ShipPositions({{ELetter::A, ENumber::One}});
    Controller.SetPlayer1ShipPositions({{ELetter::H, ENumber::Eight}});

    EXPECT_EQ(Controller.Player1Shoot({ELetter::B, ENumber::Two}), EEnemyTileType::Miss);

    EXPECT_EQ(Controller.Player1Shoot({ELetter::B, ENumber::Two}), EEnemyTileType::AlredyShot);
    
    EXPECT_EQ(Controller.CheckWinner(), 0);
}

TEST(GameControllerTest, check_multiple_shot_to_win)
{
    FGameController Controller;
    Controller.SetPlayer2ShipPositions({{ELetter::A, ENumber::One}});
    Controller.SetPlayer1ShipPositions({{ELetter::H, ENumber::Eight}});

    Controller.Player1Shoot({ELetter::B, ENumber::Two});
    Controller.Player2Shoot({ELetter::A, ENumber::One});
    Controller.Player1Shoot({ELetter::C, ENumber::Two});
    Controller.Player2Shoot({ELetter::H, ENumber::Eight});
    
    EXPECT_EQ(Controller.CheckWinner(), 2);
}

TEST(GameControllerTest, check_multiple_shot_to_win_and_multiple_ships)
{
    FGameController Controller;
    Controller.SetPlayer2ShipPositions({{ELetter::A, ENumber::One}, {ELetter::A, ENumber::Two}});
    Controller.SetPlayer1ShipPositions({{ELetter::H, ENumber::Eight}});

    Controller.Player1Shoot({ELetter::A, ENumber::Two});
    Controller.Player2Shoot({ELetter::A, ENumber::One});
    Controller.Player1Shoot({ELetter::C, ENumber::Two});
    Controller.Player2Shoot({ELetter::H, ENumber::Six});
    Controller.Player1Shoot({ELetter::A, ENumber::One});
    
    EXPECT_EQ(Controller.CheckWinner(), 1);
}
