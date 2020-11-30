#pragma once

class Tilemap 
{
public:
    enum class TileType {
        Floor,
        Wall,
        Stairs,
        TreeA1,
        TreeA2,
        TreeA3,
        TreeB1,
        TreeB2,
        TreeB3,
        NumTypes
    };

    struct TileProperties {

        char* m_SpriteName =  "";
        bool m_CanWalk = true;    

        TileProperties(char* spriteName, bool canWalk)
        {
            m_SpriteName = spriteName;
            m_CanWalk = m_CanWalk; 
        }
    };

public:

    Tilemap(const TileType* pLayout, int width, int height, fw::Mesh* pMesh, fw::ShaderProgram* pShader, fw::Texture* pTexture);
   virtual ~Tilemap();

   void SetTile(char* fileName);

   void Draw();

protected:

    fw::Mesh* m_TileMesh = nullptr;
    TileType* m_pLayout = nullptr;
    fw::ivec2 m_LayoutSize; 


    fw::Spritesheet* m_SpriteSheet = nullptr;
    fw::SpriteInfo m_SpriteInfo;

    fw::ShaderProgram* m_pShader;
    fw::Texture* m_pTexture;

    fw::ivec2 m_TilePos; 

    vec2 m_UVScale = vec2(1,1);
    vec2 m_UVOffset = vec2(0, 0);
    vec2 m_Scale = vec2(1.3,1.3);

    std::vector<TileProperties> m_Properties;
    
};