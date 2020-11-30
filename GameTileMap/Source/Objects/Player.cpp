#include "GamePCH.h"
#include "Objects/Player.h"
#include "Objects/PlayerController.h"

Player::Player(std::string name, vec2 pos, PlayerController* pPlayerController, fw::Mesh* pMesh, fw::ShaderProgram* pShader, fw::Texture* pTexture, fw::GameCore* pGameCore, fw::vec4 color)
    : fw::GameObject(name, pos, pMesh, pShader, pTexture, pGameCore, color),
     m_pPlayerController(pPlayerController)
{
    m_Spritesheet = new fw::Spritesheet("Data/Textures/Sokoban.json");
    Animation(Idle);
}

Player::~Player()
{
    if (m_Spritesheet != nullptr)
    {
        delete m_Spritesheet;
    }
}

void Player::Update(float deltaTime)
{
    float speed = 4.0f;

    m_AnimTimer += deltaTime;

    vec2 dir;

    if (m_pPlayerController->IsHeld(PlayerController::Mask::Left))
    {
        dir.x += -1;
        Animation(MoveLeft);
    }
    if (m_pPlayerController->IsHeld(PlayerController::Mask::Right))
    {
        dir.x += 1;
        Animation(MoveRight);
    }
    if (m_pPlayerController->IsHeld(PlayerController::Mask::Up))
    {
        dir.y += 1;
        Animation(MoveUp);
    }
    if (m_pPlayerController->IsHeld(PlayerController::Mask::Down))
    {
        dir.y += -1;
        Animation(MoveDown);
    }
    if (dir.x == 0 && dir.y == 0) {
        if (m_pPlayerController->WasNewlyReleased(PlayerController::Mask::Up)) {
            SetSprite("Player/player_08");
        }
        if (m_pPlayerController->WasNewlyReleased(PlayerController::Mask::Down)) {
            SetSprite("Player/player_05");
        }
        if (m_pPlayerController->WasNewlyReleased(PlayerController::Mask::Right)) {
            SetSprite("Player/player_17");
        }
        if (m_pPlayerController->WasNewlyReleased(PlayerController::Mask::Left)) {
            SetSprite("Player/player_20");
        }
        //Animation(Idle);
    }

    dir.normalize();

    //SetSprite("Player/player_15");

    m_Position += dir * speed * deltaTime;

}

void Player::SetSprite(std::string spriteName)
{
    m_SpriteInfo = m_Spritesheet->GetSpriteInfo(spriteName);
    m_UVScale = vec2((float)m_SpriteInfo.SpriteW / m_Spritesheet->GetWidth(), (float)m_SpriteInfo.SpriteH / m_Spritesheet->GetHeight());
    m_UVOffset = vec2((float)m_SpriteInfo.SpriteX / m_Spritesheet->GetWidth(), (float)m_SpriteInfo.SpriteY / m_Spritesheet->GetHeight());
}

void Player::Animation(PlayerState playerState)
{
    switch (playerState)
    {
    case Idle:
        SetSprite("Player/player_05");
        if (m_AnimTimer >= 0) {
            m_AnimTimer = 0;
        }
        break;
    case MoveDown:
    {
        if (m_AnimTimer >= 0) {
            SetSprite("Player/player_06");
        }
        if (m_AnimTimer >= 0.5) {
            SetSprite("Player/player_07");
        }
        if (m_AnimTimer >= 1) {
            m_AnimTimer = 0;
        }
    }
        break;
    case MoveUp:
    {
        if (m_AnimTimer >= 0) {
            SetSprite("Player/player_09");
        }
        if (m_AnimTimer >= 0.5) {
            SetSprite("Player/player_10");
        }
        if (m_AnimTimer >= 1) {
            m_AnimTimer = 0;
        }
    }
        break;

    case MoveRight:
    {
        if (m_AnimTimer >= 0) {
            SetSprite("Player/player_18");
        }
        if (m_AnimTimer >= 0.5) {
            SetSprite("Player/player_17");
        }
        if (m_AnimTimer >= 1) {
            m_AnimTimer = 0;
        }
    }
        break;
    case MoveLeft:
    {
        if (m_AnimTimer >= 0) {
            SetSprite("Player/player_21");
        }
        if (m_AnimTimer >= 0.5) {
            SetSprite("Player/player_20");
        }
        if (m_AnimTimer >= 1) {
            m_AnimTimer = 0;
        }
    }
        break;
    }
}
