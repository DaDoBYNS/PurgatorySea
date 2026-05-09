#include "pch.h"

#include <gtest/gtest.h>

#include "../PurgatorySeaCore/Board.h"
#include "../PurgatorySeaCore/GameController.h"

TEST(ShipSinking, ship_should_not_be_sunk_when_created)
{
    std::shared_ptr<FBoard> Board = std::make_shared<FBoard>();
    std::shared_ptr<FShip> Ship = Board->CreateShip(FPosition{ELetter::A, ENumber::Four}, 1, "null");

    EXPECT_FALSE(Ship->GetIsSunk());
}

TEST(ShipSinking, ship_should_not_be_sunk_when_no_position_was_hit)
{
    std::shared_ptr<FBoard> Board = std::make_shared<FBoard>();
    std::shared_ptr<FGameController> GameController = std::make_shared<FGameController>();

    GameController->SetBoard(Board);

    std::shared_ptr<FShip> Ship = Board->CreateShip(FPosition{ELetter::A, ENumber::Four}, 1, "null");

    EHitStatus Result = GameController->ReceiveShot(FPosition{ELetter::J, ENumber::Eight});

    EXPECT_EQ(Result, EHitStatus::Miss);
    EXPECT_FALSE(Ship->GetIsSunk());
}

TEST(ShipSinking, ship_should_not_be_sunk_when_only_one_position_was_hit)
{
    std::shared_ptr<FBoard> Board = std::make_shared<FBoard>();
    std::shared_ptr<FGameController> GameController = std::make_shared<FGameController>();

    GameController->SetBoard(Board);

    std::shared_ptr<FShip> Ship = Board->CreateShip(FPosition{ELetter::A, ENumber::Four}, 3, "null");

    EHitStatus Result = GameController->ReceiveShot(FPosition{ELetter::A, ENumber::Three});

    EXPECT_EQ(Result, EHitStatus::Hit);
    EXPECT_FALSE(Ship->GetIsSunk());
}

TEST(ShipSinking, ship_should_not_be_sunk_when_not_all_positions_were_hit)
{
    std::shared_ptr<FBoard> Board = std::make_shared<FBoard>();
    std::shared_ptr<FGameController> GameController = std::make_shared<FGameController>();

    GameController->SetBoard(Board);

    std::shared_ptr<FShip> Ship = Board->CreateShip(FPosition{ELetter::A, ENumber::Four}, 3, "null");

    EHitStatus FirstResult = GameController->ReceiveShot(FPosition{ELetter::A, ENumber::Three});
    EHitStatus SecondResult = GameController->ReceiveShot(FPosition{ELetter::A, ENumber::Two});

    EXPECT_EQ(FirstResult, EHitStatus::Hit);
    EXPECT_EQ(SecondResult, EHitStatus::Hit);
    EXPECT_FALSE(Ship->GetIsSunk());
}

TEST(ShipSinking, ship_should_be_sunk_when_all_positions_are_hit)
{
    std::shared_ptr<FBoard> Board = std::make_shared<FBoard>();
    std::shared_ptr<FGameController> GameController = std::make_shared<FGameController>();

    GameController->SetBoard(Board);

    std::shared_ptr<FShip> Ship = Board->CreateShip(FPosition{ELetter::A, ENumber::Four}, 3, "null");

    EHitStatus FirstResult = GameController->ReceiveShot(FPosition{ELetter::A, ENumber::Four});
    EHitStatus SecondResult = GameController->ReceiveShot(FPosition{ELetter::A, ENumber::Three});
    EHitStatus ThirdResult = GameController->ReceiveShot(FPosition{ELetter::A, ENumber::Two});

    EXPECT_EQ(FirstResult, EHitStatus::Hit);
    EXPECT_EQ(SecondResult, EHitStatus::Hit);
    EXPECT_EQ(ThirdResult, EHitStatus::Sink);
    EXPECT_TRUE(Ship->GetIsSunk());
}