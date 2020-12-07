#include "GamePCH.h"

#include "Tilemap.h"
#include "Layouts.h"

using TT = Tilemap::TileType;

const int level1Layout_Height = 11;
const int level1Layout_Width = 11;

const Tilemap::TileType level1Layout[]
{
    TT::Wall, TT::Wall,   TT::Wall,   TT::Wall,   TT::Wall,  TT::Wall,  TT::Wall,  TT::Wall,  TT::Wall,  TT::Wall,   TT::Wall,
    TT::Wall, TT::TreeA1, TT::TreeA2, TT::TreeA3, TT::Floor, TT::Floor, TT::Floor, TT::Floor, TT::Floor, TT::Stairs, TT::Wall,
    TT::Wall, TT::TreeB1, TT::TreeB2, TT::TreeB3, TT::Floor, TT::Floor, TT::Floor, TT::Floor, TT::Floor, TT::Floor,  TT::Wall,
    TT::Wall, TT::Floor,  TT::Floor,  TT::Floor,  TT::Floor, TT::Floor, TT::Floor, TT::Floor, TT::Floor, TT::Floor,  TT::Wall,
    TT::Wall, TT::Floor,  TT::Floor,  TT::Floor,  TT::Floor, TT::Floor, TT::Floor, TT::Floor, TT::Floor, TT::Floor,  TT::Wall,
    TT::Wall, TT::Floor,  TT::Floor,  TT::Floor,  TT::Floor, TT::Floor, TT::Floor, TT::Floor, TT::Floor, TT::Floor,  TT::Wall,
    TT::Wall, TT::Floor,  TT::Floor,  TT::Floor,  TT::Floor, TT::Floor, TT::Floor, TT::Floor, TT::Floor, TT::Floor,  TT::Wall,
    TT::Wall, TT::Floor,  TT::Floor,  TT::Floor,  TT::Floor, TT::Floor, TT::Floor, TT::Floor, TT::Floor, TT::Floor,  TT::Wall,
    TT::Wall, TT::Floor,  TT::Floor,  TT::Floor,  TT::Floor, TT::Floor, TT::Floor, TT::Floor, TT::Floor, TT::Floor,  TT::Wall,
    TT::Wall, TT::Floor,  TT::Floor,  TT::Floor,  TT::Floor, TT::Floor, TT::Floor, TT::Floor, TT::Floor, TT::Floor,  TT::Wall,
    TT::Wall, TT::Wall,   TT::Wall,   TT::Wall,   TT::Wall,  TT::Wall,  TT::Wall,  TT::Wall,  TT::Wall, TT::Wall,   TT::Wall,
};