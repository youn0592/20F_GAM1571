#pragma once

class Pathfinder;
class Tilemap;

class Enemy : public fw::GameObject
{
public:
    Enemy(std::string name, Pathfinder* pathfinder, Tilemap* tilemap, vec2 pos, fw::Mesh* pMesh, fw::ShaderProgram* pShader, fw::Texture* pTexture, fw::GameCore* pGameCore, fw::vec4 color);
    virtual ~Enemy();

    virtual void Update(float deltaTime) override;

    void FindPath();

    void SetSprite(std::string spriteName);

protected: 
    //Enemy Parms
    std::string m_ObjectName;
    int m_EnemyType;

    //Enemy Speed/Dir
    vec2 m_Dir;
    float m_Speed;
    
    int m_EndX;
    int m_EndY;
    float m_Timer = 0;
    bool m_End = true;

    //Enemy Mesh
    fw::Spritesheet* m_Spritesheet = nullptr;
    fw::SpriteInfo m_SpriteInfo;

    Pathfinder* m_Pathfinder = nullptr;
    Tilemap* m_Tilemap = nullptr;

};