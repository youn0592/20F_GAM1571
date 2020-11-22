#pragma once

class PlayerController;

enum PlayerState {
    Idle = 1,
    MoveDown = 2,
    MoveUp = 4,
    MoveRight = 8,
    MoveLeft = 16
};

class Player : public fw::GameObject
{
public:
    Player(std::string name, vec2 pos, PlayerController* pPlayerController, fw::Mesh* pMesh, fw::ShaderProgram* pShader, fw::Texture* pTexture, fw::GameCore* pGameCore, fw::vec4 color);
    virtual ~Player();

    virtual void Update(float deltaTime) override;

    void SetSprite(std::string spriteName);

    void Animation(PlayerState playerState);

protected:

    PlayerController* m_pPlayerController = nullptr;
    fw::Spritesheet* m_Spritesheet = nullptr;
    fw::SpriteInfo m_SpriteInfo;

    float m_AnimTimer = 0;
};
