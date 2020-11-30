#include "FrameworkPCH.h"
#include "Framework.h"
#include "GameObject.h"

namespace fw {
    GameObject::GameObject(std::string name, vec2 pos, Mesh* pMesh, ShaderProgram* pShader, Texture* pTexture, GameCore* pGameCore, vec4 color)
    {
        m_pMesh = pMesh;
        m_pShader = pShader;
        m_pTexture = pTexture;
        m_Position = pos;
        m_pGameCore = pGameCore;
        m_Name = name;
        m_Color = color;
    }

    GameObject::~GameObject()
    {
    }

    void GameObject::Update(float deltaTime)
    {
    }

    void GameObject::Draw()
    {
        m_pMesh->Draw(m_Position, m_pShader, m_pTexture, m_Color, m_UVScale, m_UVOffset, m_Scale);
    }

    void GameObject::GetFrameWork()
    {
        m_pGameCore->GetFramework();
    }
    void GameObject::SetPosition(vec2 pos)
    {
        m_Position = pos;
    }

    vec2 GameObject::GetPosition()
    {
        return m_Position;
    }
    void GameObject::SetTexture(Texture* pTexture)
    {
        m_pTexture = pTexture;
    }
    std::string GameObject::GetName()
    {
        return m_Name;
    }
    float GameObject::GetRadius()
    {
        return m_pMesh->GetRadius();
    }
    void GameObject::SetColor(vec4 color)
    {
        m_Color = color;
    }
}
