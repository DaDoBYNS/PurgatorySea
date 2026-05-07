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

TEST(GameController, gamecontroller_should_give_swiftboat_the_right_name)
{
    std::shared_ptr<FGameController> GameController = std::make_shared<FGameController>(); 
    std::shared_ptr<FBoard> Board = std::make_shared<FBoard>(); 
    std::shared_ptr<FSelection> Selection = std::make_shared<FSelection>();
    
    GameController->SetBoard(Board);
    GameController->SetSelection(Selection);
    GameController->GetSelection()->SetBoard(Board);
    
    GameController->InitGame(); 
    
    EXPECT_TRUE(GameController->SelectShipByName("swiftboat") != nullptr); 
}

TEST(GameController, gamecontroller_should_give_torpedo_the_right_name)
{
    std::shared_ptr<FGameController> GameController = std::make_shared<FGameController>(); 
    std::shared_ptr<FBoard> Board = std::make_shared<FBoard>(); 
    std::shared_ptr<FSelection> Selection = std::make_shared<FSelection>();
    
    GameController->SetBoard(Board);
    GameController->SetSelection(Selection);
    GameController->GetSelection()->SetBoard(Board);
    
    GameController->InitGame(); 
    
    EXPECT_TRUE(GameController->SelectShipByName("torpedo") != nullptr); 
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

TEST(GameControllerTest, check_shot_position_is_invalid_out_of_bounds)
{
    FGameController Controller;

    EXPECT_FALSE(Controller.IsShotPositionValid({static_cast<ELetter>(-1), ENumber::One}));
    EXPECT_FALSE(Controller.IsShotPositionValid({ELetter::A, static_cast<ENumber>(11)}));
}

TEST(GameControllerTest, receive_shot_should_return_miss_when_no_ship_is_hit)
{
    std::shared_ptr<FGameController> Controller = std::make_shared<FGameController>();
    std::shared_ptr<FBoard> Board = std::make_shared<FBoard>();

    Controller->SetBoard(Board);
    Board->CreateShip({ELetter::A, ENumber::One}, 2, "torpedo");

    EXPECT_EQ(Controller->ReceiveShot({ELetter::C, ENumber::Three}), EHitStatus::Miss);
}

TEST(GameControllerTest, receive_shot_should_return_hit_when_ship_position_is_hit)
{
    std::shared_ptr<FGameController> Controller = std::make_shared<FGameController>();
    std::shared_ptr<FBoard> Board = std::make_shared<FBoard>();

    Controller->SetBoard(Board);
    Board->CreateShip({ELetter::A, ENumber::Two}, 2, "torpedo");

    EXPECT_EQ(Controller->ReceiveShot({ELetter::A, ENumber::Two}), EHitStatus::Hit);
}

TEST(GameControllerTest, receive_shot_should_return_sink_when_all_ship_positions_are_hit)
{
    std::shared_ptr<FGameController> Controller = std::make_shared<FGameController>();
    std::shared_ptr<FBoard> Board = std::make_shared<FBoard>();

    Controller->SetBoard(Board);

    std::shared_ptr<FShip> Ship = Board->CreateShip({ELetter::A, ENumber::Two}, 2, "torpedo");

    EXPECT_EQ(Controller->ReceiveShot({ELetter::A, ENumber::Two}), EHitStatus::Hit);
    EXPECT_EQ(Controller->ReceiveShot({ELetter::A, ENumber::One}), EHitStatus::Sink);

    EXPECT_TRUE(Ship->GetIsSunk());
}

TEST(GameControllerTest, receive_shot_should_return_already_shot_when_same_position_is_received_twice)
{
    std::shared_ptr<FGameController> Controller = std::make_shared<FGameController>();
    std::shared_ptr<FBoard> Board = std::make_shared<FBoard>();

    Controller->SetBoard(Board);
    Board->CreateShip({ELetter::A, ENumber::Two}, 2, "torpedo");

    EXPECT_EQ(Controller->ReceiveShot({ELetter::A, ENumber::Two}), EHitStatus::Hit);
    EXPECT_EQ(Controller->ReceiveShot({ELetter::A, ENumber::Two}), EHitStatus::AlredyShot);
}

TEST(GameControllerTest, receive_shot_should_return_already_shot_when_position_is_out_of_bounds)
{
    std::shared_ptr<FGameController> Controller = std::make_shared<FGameController>();
    std::shared_ptr<FBoard> Board = std::make_shared<FBoard>();

    Controller->SetBoard(Board);

    EXPECT_EQ(
        Controller->ReceiveShot({static_cast<ELetter>(-1), ENumber::One}),
        EHitStatus::AlredyShot
    );
}

TEST(GameControllerTest, register_enemy_board_shot_should_save_miss_result)
{
    FGameController Controller;

    EXPECT_EQ(
        Controller.RegisterEnemyBoardShot({ELetter::B, ENumber::Two}, EHitStatus::Miss),
        EHitStatus::Miss
    );

    std::vector<SEnemyBoard> HitPositions = Controller.GetEnemyBoard().GetHitPositions();

    EXPECT_EQ(HitPositions.size(), 1);
    EXPECT_EQ(HitPositions[0].Position, FPosition({ELetter::B, ENumber::Two}));
    EXPECT_EQ(HitPositions[0].Type, EHitStatus::Miss);
}

TEST(GameControllerTest, register_enemy_board_shot_should_save_hit_result)
{
    FGameController Controller;

    EXPECT_EQ(
        Controller.RegisterEnemyBoardShot({ELetter::C, ENumber::Three}, EHitStatus::Hit),
        EHitStatus::Hit
    );

    std::vector<SEnemyBoard> HitPositions = Controller.GetEnemyBoard().GetHitPositions();

    EXPECT_EQ(HitPositions.size(), 1);
    EXPECT_EQ(HitPositions[0].Position, FPosition({ELetter::C, ENumber::Three}));
    EXPECT_EQ(HitPositions[0].Type, EHitStatus::Hit);
}

TEST(GameControllerTest, register_enemy_board_shot_should_save_sink_result)
{
    FGameController Controller;

    EXPECT_EQ(
        Controller.RegisterEnemyBoardShot({ELetter::D, ENumber::Four}, EHitStatus::Sink),
        EHitStatus::Sink
    );

    std::vector<SEnemyBoard> HitPositions = Controller.GetEnemyBoard().GetHitPositions();

    EXPECT_EQ(HitPositions.size(), 1);
    EXPECT_EQ(HitPositions[0].Position, FPosition({ELetter::D, ENumber::Four}));
    EXPECT_EQ(HitPositions[0].Type, EHitStatus::Sink);
}

TEST(GameControllerTest, register_enemy_board_shot_should_return_already_shot_on_duplicate_position)
{
    FGameController Controller;

    Controller.RegisterEnemyBoardShot({ELetter::E, ENumber::Five}, EHitStatus::Miss);

    EXPECT_EQ(
        Controller.RegisterEnemyBoardShot({ELetter::E, ENumber::Five}, EHitStatus::Hit),
        EHitStatus::AlredyShot
    );

    EXPECT_EQ(Controller.GetEnemyBoard().GetHitPositions().size(), 1);
}

TEST(GameControllerTest, has_won_should_return_false_when_enemy_board_has_no_sink_results)
{
    std::shared_ptr<FGameController> Controller = std::make_shared<FGameController>();
    std::shared_ptr<FBoard> Board = std::make_shared<FBoard>();

    Controller->SetBoard(Board);
    Controller->InitGame();

    EXPECT_FALSE(Controller->HasWon());
}

TEST(GameControllerTest, has_won_should_return_false_when_not_all_enemy_ships_are_sunk)
{
    std::shared_ptr<FGameController> Controller = std::make_shared<FGameController>();
    std::shared_ptr<FBoard> Board = std::make_shared<FBoard>();

    Controller->SetBoard(Board);
    Controller->InitGame();

    Controller->RegisterEnemyBoardShot({ELetter::A, ENumber::One}, EHitStatus::Sink);

    EXPECT_FALSE(Controller->HasWon());
}

TEST(GameControllerTest, has_won_should_return_true_when_all_enemy_ships_are_sunk)
{
    std::shared_ptr<FGameController> Controller = std::make_shared<FGameController>();
    std::shared_ptr<FBoard> Board = std::make_shared<FBoard>();

    Controller->SetBoard(Board);
    Controller->InitGame();

    Controller->RegisterEnemyBoardShot({ELetter::A, ENumber::One}, EHitStatus::Sink);
    Controller->RegisterEnemyBoardShot({ELetter::B, ENumber::One}, EHitStatus::Sink);
    Controller->RegisterEnemyBoardShot({ELetter::C, ENumber::One}, EHitStatus::Sink);
    Controller->RegisterEnemyBoardShot({ELetter::D, ENumber::One}, EHitStatus::Sink);
    Controller->RegisterEnemyBoardShot({ELetter::E, ENumber::One}, EHitStatus::Sink);

    EXPECT_TRUE(Controller->HasWon());
}