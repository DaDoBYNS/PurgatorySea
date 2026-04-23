#include "Board.h"

FBoard::FBoard()
    : bInitTest(false)
{}

bool FBoard::GetInitTest()
{
    return bInitTest;
}

void FBoard::SetInitTest(bool bInInitTest)
{
    bInitTest = bInInitTest;
}