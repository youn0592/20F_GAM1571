#include "GamePCH.h"

#include "Objects/Player.h"
#include "Objects/PlayerController.h"

Player::Player(std::string name, vec2 pos, PlayerController* pPlayerController, fw::Mesh* pMesh, fw::ShaderProgram* pShader, fw::Texture* pTexture, fw::GameCore* pGameCore, fw::vec4 color)
    : fw::GameObject(name, pos, pMesh, pShader, pTexture, pGameCore, color),
     m_pPlayerController(pPlayerController)
{
}

Player::~Player()
{
}

void Player::Update(float deltaTime)
{
    float speed = 4.0f;

    vec2 dir;

    if (m_pPlayerController->IsHeld(PlayerController::Mask::Left))
    {
        dir.x += -1;
    }
    if (m_pPlayerController->IsHeld(PlayerController::Mask::Right))
    {
        dir.x += 1;
    }
    if (m_pPlayerController->IsHeld(PlayerController::Mask::Up))
    {
        dir.y += 1;
    }
    if (m_pPlayerController->IsHeld(PlayerController::Mask::Down))
    {
        dir.y += -1;
    }

    dir.normalize();

    m_UVScale = vec2(64.0 / 1024.0, 64.0 / 512.0);
    m_UVOffset = vec2(780.0 / 1024.0, 383.0 / 512.0);

    m_Position += dir * speed * deltaTime;


}
