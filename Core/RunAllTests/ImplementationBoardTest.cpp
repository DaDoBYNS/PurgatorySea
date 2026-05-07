#include "pch.h"
#include "../PurgatorySeaCore/Board.h"
#include "../PurgatorySeaCore/EnemyBoard.h"


TEST(ImplementationBoard, check_if_board_is_empty_if_not_initialized)
{
    auto Board = std::make_shared<FBoard>();
    auto Ships = Board->GetShips();

    EXPECT_TRUE(Ships.empty());
}

TEST(ImplementationBoard, check_if_board_is_empty_after_initialization)
{
    auto Board = std::make_shared<FBoard>();
    Board->InitPlayerBoard();

    auto Ships = Board->GetShips();

    EXPECT_TRUE(Ships.empty());
}

TEST(ImplementationBoard, check_if_board_starts_with_no_ships)
{
    std::shared_ptr<FBoard> Board = std::make_shared<FBoard>();

    auto Ships = Board->GetShips();

    EXPECT_EQ(Ships.size(), 0);
}

TEST(ImplementationBoard, check_if_board_is_cleared_after_size_change)
{
    std::shared_ptr<FBoard> Board = std::make_shared<FBoard>();

    Board->CreateShip(FPosition{ELetter::A, ENumber::One}, 1, "null");
    Board->SetHeightAndWidth(31, 31);

    auto Ships = Board->GetShips();

    EXPECT_TRUE(Ships.empty());
}

TEST(ImplementationBoard, check_if_place_ship_base_case_works)
{
    std::shared_ptr<FBoard> Board = std::make_shared<FBoard>();
    Board->SetHeightAndWidth(10, 10);
    Board->InitPlayerBoard();

    std::shared_ptr<FShip> Ship = Board->CreateShip(FPosition{ELetter::A, ENumber::One}, 1, "null");

    std::vector<std::shared_ptr<FShip>> Ships = Board->GetShips();

    EXPECT_TRUE(Ship != nullptr);
    EXPECT_EQ(Ships.size(), 1);
    EXPECT_EQ(Ships[0]->GetFirstPosition(), (FPosition{ELetter::A, ENumber::One}));
}

TEST(ImplementationBoard, check_if_place_ship_general_case_works)
{
    std::shared_ptr<FBoard> Board = std::make_shared<FBoard>();
    Board->SetHeightAndWidth(10, 10);
    Board->InitPlayerBoard();

    std::shared_ptr<FShip> Ship = Board->CreateShip(FPosition{ELetter::C, ENumber::Eight}, 1, "null");

    auto Ships = Board->GetShips();

    EXPECT_TRUE(Ship != nullptr);
    EXPECT_EQ(Ships.size(), 1);
    EXPECT_EQ(Ships[0]->GetFirstPosition(), (FPosition{ELetter::C, ENumber::Eight}));
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
    std::shared_ptr<FEnemyBoard> Board = std::make_shared<FEnemyBoard>();

    Board->AddShipPosition({ELetter::A, ENumber::One});
    Board->SetHitPosition({ELetter::B, ENumber::Two});

    Board->InitEnemyBoard();

    EXPECT_TRUE(Board->GetEnemyShipPositions().empty());
    EXPECT_TRUE(Board->GetHitPositions().empty());
}

TEST(ImplementationBoard, check_if_enemy_ship_position_is_added_correctly)
{
    std::shared_ptr<FEnemyBoard> Board = std::make_shared<FEnemyBoard>();

    bool Result = Board->AddShipPosition({ELetter::C, ENumber::Four});

    EXPECT_TRUE(Result);
    EXPECT_EQ(Board->GetEnemyShipPositions().size(), 1);
}

TEST(ImplementationBoard, check_if_enemy_ship_position_cannot_be_duplicated)
{
    std::shared_ptr<FEnemyBoard> Board = std::make_shared<FEnemyBoard>();

    Board->AddShipPosition({ELetter::D, ENumber::Five});
    bool Result = Board->AddShipPosition({ELetter::D, ENumber::Five});

    EXPECT_FALSE(Result);
    EXPECT_EQ(Board->GetEnemyShipPositions().size(), 1);
}

TEST(ImplementationBoard, check_if_hit_is_registered_correctly)
{
    std::shared_ptr<FEnemyBoard> Board = std::make_shared<FEnemyBoard>();

    Board->AddShipPosition({ELetter::B, ENumber::Three});

    auto Result = Board->SetHitPosition({ELetter::B, ENumber::Three});

    EXPECT_EQ(Result, EHitStatus::Hit);

    const auto& Hits = Board->GetHitPositions();
    EXPECT_EQ(Hits.size(), 1);
}

TEST(ImplementationBoard, check_if_miss_is_registered_correctly)
{
    std::shared_ptr<FEnemyBoard> Board = std::make_shared<FEnemyBoard>();

    auto Result = Board->SetHitPosition({ELetter::H, ENumber::Nine});

    EXPECT_EQ(Result, EHitStatus::Miss);

    const auto& Hits = Board->GetHitPositions();
    EXPECT_EQ(Hits.size(), 1);
}

TEST(ImplementationBoard, check_if_duplicate_shot_is_not_added)
{
    std::shared_ptr<FEnemyBoard> Board = std::make_shared<FEnemyBoard>();

    Board->SetHitPosition({ELetter::A, ENumber::One});
    Board->SetHitPosition({ELetter::A, ENumber::One});

    const auto& Hits = Board->GetHitPositions();

    EXPECT_EQ(Hits.size(), 1);
}
