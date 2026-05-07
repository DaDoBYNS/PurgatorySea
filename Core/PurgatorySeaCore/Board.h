#pragma once
#include <memory>
#include <vector>

#include "HitStatus.h"
#include "Position.h"
#include "Ship.h"

class FBoard
{
    std::vector<std::shared_ptr<FShip>> Ships;
    std::vector<FPosition> ReceivedShots;

    int Height;
    int Width;

public:
    FBoard();

    void InitPlayerBoard();

    std::shared_ptr<FShip> CreateShip(FPosition InPosition, int InDimension, const char* InName);

    EHitStatus ReceiveShot(FPosition ShotPosition);
    bool HasReceivedShot(FPosition ShotPosition) const;

    void SetHeightAndWidth(int NewHeight, int NewWidth);
    
    bool AreAllShipsSunk() const;

    std::vector<std::shared_ptr<FShip>> GetShips();
    std::vector<FPosition> GetReceivedShots() const;

    int GetHeight() const;
    int GetWidth() const;
};