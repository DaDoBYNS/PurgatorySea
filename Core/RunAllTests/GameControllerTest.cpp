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

TEST(GameController, gamecontroller_should_select_ship_at_position)
{
    std::shared_ptr<FGameController> GameController = std::make_shared<FGameController>();
    std::shared_ptr<FBoard> Board = std::make_shared<FBoard>();
    std::shared_ptr<FSelection> Selection = std::make_shared<FSelection>();

    GameController->SetBoard(Board);
    GameController->SetSelection(Selection);
    GameController->GetSelection()->SetBoard(Board);

    GameController->InitGame();

    std::shared_ptr<FShip> Ship = GameController->SelectShipAt(FPosition{ELetter::A, ENumber::Eight});

    EXPECT_TRUE(Ship != nullptr);
    EXPECT_TRUE(Ship->GetIsSelected());
    EXPECT_EQ(GameController->GetSelection()->GetSelectedShip(), Ship);
}

TEST(GameController, gamecontroller_should_clear_selection_when_invalid_ship_name_is_selected)
{
    std::shared_ptr<FGameController> GameController = std::make_shared<FGameController>();
    std::shared_ptr<FBoard> Board = std::make_shared<FBoard>();
    std::shared_ptr<FSelection> Selection = std::make_shared<FSelection>();

    GameController->SetBoard(Board);
    GameController->SetSelection(Selection);
    GameController->GetSelection()->SetBoard(Board);

    GameController->InitGame();

    std::shared_ptr<FShip> Ship = GameController->SelectShipByName("submarine");

    EXPECT_TRUE(Ship != nullptr);
    EXPECT_TRUE(Ship->GetIsSelected());

    std::shared_ptr<FShip> InvalidShip = GameController->SelectShipByName("invalid ship");

    EXPECT_TRUE(InvalidShip == nullptr);
    EXPECT_TRUE(GameController->GetSelection()->GetSelectedShip() == nullptr);
    EXPECT_FALSE(Ship->GetIsSelected());
}

TEST(GameController, gamecontroller_should_not_crash_when_moving_without_selected_ship)
{
    std::shared_ptr<FGameController> GameController = std::make_shared<FGameController>();
    std::shared_ptr<FBoard> Board = std::make_shared<FBoard>();
    std::shared_ptr<FSelection> Selection = std::make_shared<FSelection>();

    GameController->SetBoard(Board);
    GameController->SetSelection(Selection);
    GameController->GetSelection()->SetBoard(Board);

    GameController->InitGame();

    EXPECT_NO_THROW(GameController->MoveShipTo(FPosition{ELetter::C, ENumber::Four}));
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

    EXPECT_EQ(Controller.HasWon(), false);
}

TEST(GameControllerTest, check_shot_position_is_valid_in_bounds)
{
    FGameController Controller;

    EXPECT_TRUE(Controller.IsShotPositionValid({ELetter::A, ENumber::One}));
    EXPECT_TRUE(Controller.IsShotPositionValid({ELetter::J, ENumber::Ten}));
    EXPECT_TRUE(Controller.IsShotPositionValid({ELetter::E, ENumber::Five}));
}

TEST(GameController, gamecontroller_should_rotate_selected_ship_through_selection)
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

    ERotation StartRotation = Ship->GetRotation();

    GameController->RotateSelectedShip();

    EXPECT_TRUE(Ship->GetRotation() != StartRotation);
}



TEST(GameController, gamecontroller_should_be_able_to_empty_selected_ship_when_requested)
{
    std::shared_ptr<FGameController> GameController = std::make_shared<FGameController>();
    std::shared_ptr<FSelection> Selection = std::make_shared<FSelection>();
    std::shared_ptr<FBoard> Board = std::make_shared<FBoard>();

    FPosition StartPosition = FPosition{ELetter::A, ENumber::Eight};

    GameController->SetBoard(Board);
    GameController->SetSelection(Selection);
    GameController->GetSelection()->SetBoard(Board);

    GameController->InitGame();

    auto Ship = GameController->SelectShipAt(StartPosition);
    GameController->EmptySelectedShip(); 
    
    EXPECT_TRUE(GameController->GetSelection()->GetSelectedShip() == nullptr);
}

TEST(GameController, gamecontroller_should_not_crash_when_empty_invalid_selected_ship)
{
    std::shared_ptr<FGameController> GameController = std::make_shared<FGameController>();
    std::shared_ptr<FSelection> Selection = std::make_shared<FSelection>();
    std::shared_ptr<FBoard> Board = std::make_shared<FBoard>();

    GameController->SetBoard(Board);
    GameController->SetSelection(Selection);
    GameController->GetSelection()->SetBoard(Board);
    
    EXPECT_NO_THROW(GameController->EmptySelectedShip());
}

TEST(GameControllerTest, check_no_winner_at_start)
{
    FGameController Controller;
    Controller.SetEnemyShipPositions({{ELetter::A, ENumber::One}});

    EXPECT_FALSE(Controller.HasWon());
}

TEST(GameControllerTest, check_enemy_positions_initialized_correctly)
{
    FGameController Controller;
    Controller.SetEnemyShipPositions({{ELetter::C, ENumber::Five}});

    EXPECT_FALSE(Controller.GetEnemyBoard().GetEnemyShipPositions().empty());
}

TEST(GameControllerTest, check_shoot_returns_hit_on_ship_position)
{
    FGameController Controller;
    Controller.SetEnemyShipPositions({{ELetter::A, ENumber::One}});

    EXPECT_EQ(Controller.Shoot({ELetter::A, ENumber::One}), EEnemyTileType::Hit);
}

TEST(GameControllerTest, check_shoot_returns_miss_on_empty_position)
{
    FGameController Controller;
    Controller.SetEnemyShipPositions({{ELetter::A, ENumber::One}});

    EXPECT_EQ(Controller.Shoot({ELetter::B, ENumber::Two}), EEnemyTileType::Miss);
}

TEST(GameControllerTest, check_shoot_returns_already_shot_on_duplicate)
{
    FGameController Controller;
    Controller.SetEnemyShipPositions({{ELetter::A, ENumber::One}});

    Controller.Shoot({ELetter::A, ENumber::One});
    EXPECT_EQ(Controller.Shoot({ELetter::A, ENumber::One}), EEnemyTileType::AlredyShot);
}

TEST(GameControllerTest, check_shoot_returns_invalid_out_of_bounds)
{
    FGameController Controller;
    Controller.SetEnemyShipPositions({{ELetter::A, ENumber::One}});

    EXPECT_EQ(Controller.Shoot({static_cast<ELetter>(-1), ENumber::One}), EEnemyTileType::AlredyShot);
}

TEST(GameControllerTest, check_player_wins_after_hitting_all_enemy_ships)
{
    FGameController Controller;
    Controller.SetEnemyShipPositions({{ELetter::A, ENumber::One}, {ELetter::A, ENumber::Two}});

    Controller.Shoot({ELetter::A, ENumber::One});
    Controller.Shoot({ELetter::A, ENumber::Two});

    EXPECT_TRUE(Controller.HasWon());
}

TEST(GameControllerTest, check_no_winner_after_partial_hits)
{
    FGameController Controller;
    Controller.SetEnemyShipPositions({{ELetter::A, ENumber::One}, {ELetter::A, ENumber::Two}});

    Controller.Shoot({ELetter::A, ENumber::One});

    EXPECT_FALSE(Controller.HasWon());
}

TEST(GameControllerTest, check_miss_does_not_trigger_win)
{
    FGameController Controller;
    Controller.SetEnemyShipPositions({{ELetter::A, ENumber::One}});

    Controller.Shoot({ELetter::B, ENumber::Two});

    EXPECT_FALSE(Controller.HasWon());
}

TEST(GameControllerTest, check_shot_position_is_invalid_out_of_bounds)
{
    FGameController Controller;

    EXPECT_FALSE(Controller.IsShotPositionValid({static_cast<ELetter>(-1), ENumber::One}));
    EXPECT_FALSE(Controller.IsShotPositionValid({ELetter::A, static_cast<ENumber>(11)}));
}