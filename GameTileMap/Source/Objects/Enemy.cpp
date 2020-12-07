#include "GamePCH.h"

#include "Enemy.h"
#include "Tilemap/Pathfinder.h"
#include "Tilemap/Tilemap.h"

// / height
// % width

Enemy::Enemy(std::string name, Pathfinder* pathfinder, Tilemap* tilemap, vec2 pos, fw::Mesh* pMesh, fw::ShaderProgram* pShader, fw::Texture* pTexture, fw::GameCore* pGameCore, fw::vec4 color) :
    fw::GameObject(name, pos, pMesh, pShader, pTexture, pGameCore, color)
{
    m_ObjectName = name;

    m_Spritesheet = new fw::Spritesheet("Data/Textures/Zelda.json");

    m_Speed = 1.0f;

    SetSprite("OctorocDown1");

    m_Pathfinder = pathfinder;
    m_Tilemap = tilemap;

    FindPath();

}

Enemy::~Enemy()
{
    if (m_Spritesheet != nullptr)
    {
        delete m_Spritesheet;
    }
}

void Enemy::Update(float deltaTime)
{
    m_Timer += deltaTime;
    if (m_Timer >= 0.5)
    {
        FindPath();
        m_Timer = 0;
    }
}

void Enemy::FindPath()
{
    int startx = m_Tilemap->GetCurrentTile(vec2(m_Position.x, m_Position.y)).x;
    int starty = m_Tilemap->GetCurrentTile(vec2(m_Position.x, m_Position.y)).y;

    if (m_End == true) {
        m_EndX = (rand() % (int)m_Tilemap->m_TileLayoutSize.x + 1) - 1;
        m_EndY = (rand() % (int)m_Tilemap->m_TileLayoutSize.y + 1) - 1;
        m_End = false;

    }
    bool found = m_Pathfinder->FindPath(startx, starty, m_EndX, m_EndY);
    fw::OutputMessage("Found = %d\n", found);

    if (found == true)
    {
        int path[255];
        int len = m_Pathfinder->GetPath(path, 255, m_EndX, m_EndY);

        if (len > 1)
        {
            int NextTileX = path[len - 2] % ((int)m_Tilemap->m_TileLayoutSize.x);
            int NextTileY = path[len - 2] / ((int)m_Tilemap->m_TileLayoutSize.y);

            if (m_Tilemap->IsTileWalkableAtTilePos(NextTileX, NextTileY) == true)
            {

                vec2 FinalPos((float)NextTileX, (float)NextTileY);

                m_Position = FinalPos;

            }

            fw::OutputMessage("Length = %d\n", len);
            for (int i = 0; i < len; i++)
            {
                fw::OutputMessage("%d\n", path[i]);
            }

            fw::OutputMessage("done\n");
        }
        else
        {
            m_End = true;
        }
    }
    else
    {
        m_End = true;
    }
}

void Enemy::SetSprite(std::string spriteName)
{
    m_SpriteInfo = m_Spritesheet->GetSpriteInfo(spriteName);
    m_UVScale = vec2((float)m_SpriteInfo.SpriteW / m_Spritesheet->GetWidth(), (float)m_SpriteInfo.SpriteH / m_Spritesheet->GetHeight());
    m_UVOffset = vec2((float)m_SpriteInfo.SpriteX / m_Spritesheet->GetWidth(), (float)m_SpriteInfo.SpriteY / m_Spritesheet->GetHeight());
}


