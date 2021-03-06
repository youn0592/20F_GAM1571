#include "GamePCH.h"

#include "Tilemap.h"

Tilemap::Tilemap(const TileType* pLayout, int width, int height, fw::Mesh* pMesh, fw::ShaderProgram* pShader, fw::Texture* pTexture)
{

    assert(pLayout != nullptr);
    assert(width > 0);
    assert(height > 0);


    m_pLayout = new TileType[width * height];
    for(int i = 0; i < width * height; i++)
    {
        m_pLayout[i] = pLayout[i];
    }

    m_SpriteSheet = new fw::Spritesheet("Data/Textures/Zelda.json");

    m_pShader = pShader;
    m_pTexture = pTexture;

    m_TileMesh = pMesh;

    m_TileLayoutSize.x = width;
    m_TileLayoutSize.y = height;

    m_Properties.push_back(TileProperties("TileEmpty", true));
    m_Properties.push_back(TileProperties("TileMountain5", false));
    m_Properties.push_back(TileProperties("TileStairs", true));
    m_Properties.push_back(TileProperties("TileTree1", false));
    m_Properties.push_back(TileProperties("TileTree2", false));
    m_Properties.push_back(TileProperties("TileTree3", false));
    m_Properties.push_back(TileProperties("TileTree4", false));
    m_Properties.push_back(TileProperties("TileTree5", false));
    m_Properties.push_back(TileProperties("TileTree6", false));
        


}

Tilemap::~Tilemap()
{
    delete m_SpriteSheet;
    delete[] m_pLayout;
}

void Tilemap::SetTile(char* fileName)
{
    m_SpriteInfo = m_SpriteSheet->GetSpriteInfo(fileName);
    m_UVOffset = vec2((float)m_SpriteInfo.SpriteX / m_SpriteSheet->GetWidth(), (float)m_SpriteInfo.SpriteY / m_SpriteSheet->GetHeight());
    m_UVScale = vec2((float)m_SpriteInfo.SpriteW / m_SpriteSheet->GetWidth(), (float)m_SpriteInfo.SpriteH / m_SpriteSheet->GetHeight());
}

void Tilemap::Draw()
{

    for(int x = 0; x < m_TileLayoutSize.x; x++)
    {
        for(int y = 0; y < m_TileLayoutSize.y; y++)
        {
            int TileIndex = y * m_TileLayoutSize.y + x;
            char* name = m_Properties.at((int)m_pLayout[TileIndex]).m_SpriteName;
            SetTile(name);
            
            vec2 pos = vec2(x * m_Scale.x, (m_TileLayoutSize.y - y - 1) * m_Scale.y) + vec2(0,0); //Temp Offset of level


            m_TileMesh->Draw(pos, m_pShader, m_pTexture, fw::vec4::Green(), m_UVScale, m_UVOffset, m_Scale);
            
        }
    }
}

vec2 Tilemap::GetCurrentTile(vec2 tilePos)
{
    fw::vec2 TilePos = fw::vec2(tilePos.x / m_Scale.x, tilePos.y / m_Scale.y);

    return TilePos;
}

bool Tilemap::IsTileWalkableAtTilePos(int x, int y)
{
    if (x < 0 || x >= m_TileLayoutSize.x || y < 0 || y >= m_TileLayoutSize.y)
    {
        return false;
    }

    int num = y * m_TileLayoutSize.x + x;
    return m_Properties.at(int(m_pLayout[num])).m_CanWalk;
}
