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
    auto HitPositions = EBoard->GetHitPositions();

    EXPECT_TRUE(HitPositions.empty());
}

TEST(ImplementationBoard, check_if_enemy_board_is_empty_after_initialization)
{
    auto Board = std::make_shared<FEnemyBoard>();
    Board->InitEnemyBoard();

    auto HitPositions = Board->GetHitPositions();

    EXPECT_TRUE(HitPositions.empty());
}

TEST(ImplementationBoard, check_if_enemy_board_init_clears_all_data)
{
    std::shared_ptr<FEnemyBoard> Board = std::make_shared<FEnemyBoard>();

    Board->SetHitPosition({ELetter::A, ENumber::One}, EHitStatus::Miss);
    Board->SetHitPosition({ELetter::B, ENumber::Two}, EHitStatus::Hit);
    Board->SetHitPosition({ELetter::C, ENumber::Three}, EHitStatus::Sink);

    Board->InitEnemyBoard();

    EXPECT_TRUE(Board->GetHitPositions().empty());
}

TEST(ImplementationBoard, check_if_enemy_board_registers_miss_correctly)
{
    std::shared_ptr<FEnemyBoard> Board = std::make_shared<FEnemyBoard>();

    EHitStatus Result = Board->SetHitPosition({ELetter::H, ENumber::Nine}, EHitStatus::Miss);

    const auto& Hits = Board->GetHitPositions();

    EXPECT_EQ(Result, EHitStatus::Miss);
    EXPECT_EQ(Hits.size(), 1);
    EXPECT_EQ(Hits[0].Position, (FPosition{ELetter::H, ENumber::Nine}));
    EXPECT_EQ(Hits[0].Type, EHitStatus::Miss);
}

TEST(ImplementationBoard, check_if_enemy_board_registers_hit_correctly)
{
    std::shared_ptr<FEnemyBoard> Board = std::make_shared<FEnemyBoard>();

    EHitStatus Result = Board->SetHitPosition({ELetter::B, ENumber::Three}, EHitStatus::Hit);

    const auto& Hits = Board->GetHitPositions();

    EXPECT_EQ(Result, EHitStatus::Hit);
    EXPECT_EQ(Hits.size(), 1);
    EXPECT_EQ(Hits[0].Position, (FPosition{ELetter::B, ENumber::Three}));
    EXPECT_EQ(Hits[0].Type, EHitStatus::Hit);
}

TEST(ImplementationBoard, check_if_enemy_board_registers_sink_correctly)
{
    std::shared_ptr<FEnemyBoard> Board = std::make_shared<FEnemyBoard>();

    EHitStatus Result = Board->SetHitPosition({ELetter::C, ENumber::Four}, EHitStatus::Sink);

    const auto& Hits = Board->GetHitPositions();

    EXPECT_EQ(Result, EHitStatus::Sink);
    EXPECT_EQ(Hits.size(), 1);
    EXPECT_EQ(Hits[0].Position, (FPosition{ELetter::C, ENumber::Four}));
    EXPECT_EQ(Hits[0].Type, EHitStatus::Sink);
}

TEST(ImplementationBoard, check_if_duplicate_enemy_board_shot_is_not_added)
{
    std::shared_ptr<FEnemyBoard> Board = std::make_shared<FEnemyBoard>();

    EHitStatus FirstResult = Board->SetHitPosition({ELetter::A, ENumber::One}, EHitStatus::Miss);
    EHitStatus SecondResult = Board->SetHitPosition({ELetter::A, ENumber::One}, EHitStatus::Hit);

    const auto& Hits = Board->GetHitPositions();

    EXPECT_EQ(FirstResult, EHitStatus::Miss);
    EXPECT_EQ(SecondResult, EHitStatus::AlredyShot);
    EXPECT_EQ(Hits.size(), 1);
    EXPECT_EQ(Hits[0].Type, EHitStatus::Miss);
}

TEST(ImplementationBoard, check_if_enemy_board_counts_sunk_ships_correctly)
{
    std::shared_ptr<FEnemyBoard> Board = std::make_shared<FEnemyBoard>();

    Board->SetHitPosition({ELetter::A, ENumber::One}, EHitStatus::Sink);
    Board->SetHitPosition({ELetter::B, ENumber::Two}, EHitStatus::Hit);
    Board->SetHitPosition({ELetter::C, ENumber::Three}, EHitStatus::Miss);
    Board->SetHitPosition({ELetter::D, ENumber::Four}, EHitStatus::Sink);

    EXPECT_EQ(Board->GetSunkShipsCount(), 2);
}