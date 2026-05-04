#pragma once
#include <vector>

#include "Position.h"
#include "TileType.h"

struct SEnemyBoard
{
    FPosition Position;
    EEnemyTileType Type;
};


class FEnemyBoard
{
    
    std::vector<FPosition> EnemyShipPosition;
    std::vector<SEnemyBoard> HitPositions;
    
public:
    FEnemyBoard();
    
    void InitEnemyBoard();
    
    bool AddShipPosition(FPosition ShipPosition);
    
    EEnemyTileType SetHitPosition(FPosition HitPosition);
    
    bool CheckShot(FPosition HitPosition);
    
    std::vector<FPosition> GetEnemyShipPositions() const;
    std::vector<SEnemyBoard> GetHitPositions() const;
};
