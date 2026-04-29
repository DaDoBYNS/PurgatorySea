#include "pch.h"
#include "../PurgatorySeaCore/Board.h"
#include "../PurgatorySeaCore/EnemyBoard.h"


TEST(ImplementationBoard, check_if_board_is_empty_if_not_initialized)
{
    auto Board = std::make_shared<FBoard>();
    auto Ships = Board->GetPlayerBoard();

    EXPECT_TRUE(Ships.empty());
}

TEST(ImplementationBoard, check_if_board_is_empty_after_initialization)
{
    auto Board = std::make_shared<FBoard>();
    Board->InitPlayerBoard();

    auto Ships = Board->GetPlayerBoard();

    EXPECT_TRUE(Ships.empty());
}

TEST(ImplementationBoard, check_if_board_starts_with_no_ships)
{
    FBoard Board;

    auto Ships = Board.GetPlayerBoard();

    EXPECT_EQ(Ships.size(), 0);
}

TEST(ImplementationBoard, check_if_board_is_cleared_after_size_change)
{
    FBoard Board;

    Board.PlaceShip({ELetter::A, ENumber::One});
    Board.SetHeightAndWidth(31, 31);

    auto Ships = Board.GetPlayerBoard();

    EXPECT_TRUE(Ships.empty());
}

TEST(ImplementationBoard, check_if_place_ship_base_case_works)
{
    FBoard Board;
    Board.SetHeightAndWidth(10, 10);
    Board.InitPlayerBoard();

    bool Result = Board.PlaceShip({ELetter::A, ENumber::One});

    auto Ships = Board.GetPlayerBoard();

    EXPECT_TRUE(Result);
    EXPECT_EQ(Ships.size(), 1);
    EXPECT_EQ(Ships[0], (FPosition{ELetter::A, ENumber::One}));
}

TEST(ImplementationBoard, check_if_place_ship_general_case_works)
{
    FBoard Board;
    Board.SetHeightAndWidth(10, 10);
    Board.InitPlayerBoard();

    bool Result = Board.PlaceShip({ELetter::C, ENumber::Eight});

    auto Ships = Board.GetPlayerBoard();

    EXPECT_TRUE(Result);
    EXPECT_EQ(Ships.size(), 1);
    EXPECT_EQ(Ships[0], (FPosition{ELetter::C, ENumber::Eight}));
}

TEST(ImplementationBoard, check_if_place_ship_fails_out_of_bounds)
{
    FBoard Board;
    Board.SetHeightAndWidth(5, 5);
    Board.InitPlayerBoard();

    bool Result = Board.PlaceShip({ELetter::J, ENumber::Ten}); // fuori

    EXPECT_FALSE(Result);
    EXPECT_TRUE(Board.GetPlayerBoard().empty());
}

TEST(ImplementationBoard, check_if_place_ship_cannot_duplicate_position)
{
    FBoard Board;
    Board.InitPlayerBoard();

    Board.PlaceShip({ELetter::A, ENumber::One});
    bool Result = Board.PlaceShip({ELetter::A, ENumber::One});

    auto Ships = Board.GetPlayerBoard();

    EXPECT_FALSE(Result);
    EXPECT_EQ(Ships.size(), 1);
}

TEST(ImplementationBoard, check_if_enemy_board_is_empty_if_not_initialized)
{
    auto EBoard = std::make_shared<FEnemyBoard>();
    auto Ships = EBoard->GetEnemyShipPositions();

    EXPECT_TRUE(Ships.empty());
}

TEST(ImplementationBoard, check_if_enemy_board_is_empty_after_initialization)
{
    auto Board = std::make_shared<FEnemyBoard>();
    Board->InitEnemyBoard();

    auto Ships = Board->GetEnemyShipPositions();

    EXPECT_TRUE(Ships.empty());
}

TEST(ImplementationBoard, check_if_enemy_board_init_clears_all_data)
{
    FEnemyBoard Board;

    Board.AddShipPosition({ELetter::A, ENumber::One});
    Board.SetHitPosition({ELetter::B, ENumber::Two});

    Board.InitEnemyBoard();

    EXPECT_TRUE(Board.GetEnemyShipPositions().empty());
    EXPECT_TRUE(Board.GetHitPositions().empty());
}

TEST(ImplementationBoard, check_if_enemy_ship_position_is_added_correctly)
{
    FEnemyBoard Board;

    bool Result = Board.AddShipPosition({ELetter::C, ENumber::Four});

    EXPECT_TRUE(Result);
    EXPECT_EQ(Board.GetEnemyShipPositions().size(), 1);
}

TEST(ImplementationBoard, check_if_enemy_ship_position_cannot_be_duplicated)
{
    FEnemyBoard Board;

    Board.AddShipPosition({ELetter::D, ENumber::Five});
    bool Result = Board.AddShipPosition({ELetter::D, ENumber::Five});

    EXPECT_FALSE(Result);
    EXPECT_EQ(Board.GetEnemyShipPositions().size(), 1);
}

TEST(ImplementationBoard, check_if_hit_is_registered_correctly)
{
    FEnemyBoard Board;

    Board.AddShipPosition({ELetter::B, ENumber::Three});

    auto Result = Board.SetHitPosition({ELetter::B, ENumber::Three});

    EXPECT_EQ(Result, EEnemyTileType::Hit);

    const auto& Hits = Board.GetHitPositions();
    EXPECT_EQ(Hits.size(), 1);
}

TEST(ImplementationBoard, check_if_miss_is_registered_correctly)
{
    FEnemyBoard Board;

    auto Result = Board.SetHitPosition({ELetter::H, ENumber::Nine});

    EXPECT_EQ(Result, EEnemyTileType::Miss);

    const auto& Hits = Board.GetHitPositions();
    EXPECT_EQ(Hits.size(), 1);
}

TEST(ImplementationBoard, check_if_duplicate_shot_is_not_added)
{
    FEnemyBoard Board;

    Board.SetHitPosition({ELetter::A, ENumber::One});
    Board.SetHitPosition({ELetter::A, ENumber::One});

    const auto& Hits = Board.GetHitPositions();

    EXPECT_EQ(Hits.size(), 1);
}
