#include "GamePCH.h"

#include "Game.h"
#include "Objects/Player.h"
#include "Objects/PlayerController.h"
#include "Objects/Shapes.h"
#include "Objects/Enemy.h"
#include "Events/GameEvents.h"
#include "Tilemap/Tilemap.h"
#include "Tilemap/Layouts.h"
#include "Tilemap/Pathfinder.h"

Game::Game(fw::FWCore* pFramework) : fw::GameCore(pFramework)
{
    /*wglSwapInterval(m_VSyncEnabled ? 1 : 0);*/
}

Game::~Game()
{
    for (std::pair<std::string, fw::ShaderProgram*> object : m_pShaders)
    {
        delete object.second;
    }

    for (std::pair<std::string, fw::Mesh*> object : m_pMeshes)
    {
        delete object.second;
    }

    for (std::pair<std::string, fw::Texture*> object : m_pTextures)
    {
        delete object.second;
    }

    for (fw::GameObject* pObject : m_Objects)
    {
        delete pObject;
    }

    delete m_pPlayerController;

    delete m_pEventManager;
    delete m_pImGuiManager;
    delete m_TileMap;
    delete m_Pathfinder;
}

void Game::Init()
{
    // OpenGL Settings.
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    m_pImGuiManager = new fw::ImGuiManager(m_pFrameWork);
    m_pImGuiManager->Init();

    m_pEventManager = new fw::EventManager();

    m_pPlayerController = new PlayerController();


    // Load some shaders.
    m_pShaders["Basic"] = new fw::ShaderProgram("Data/Basic.vert", "Data/Basic.frag");

    // Create some meshes.
    m_pMeshes["Player"] = new fw::Mesh(meshPrimType_Sprite, meshNumVerts_Sprite, meshAttribs_Sprite);
    m_pMeshes["Tilemap"] = new fw::Mesh(meshPrimType_Sprite, meshNumVerts_Sprite, meshAttribs_Sprite);

    // Load some textures.
    m_pTextures["Player"] = new fw::Texture("Data/Textures/Sokoban.png");
    m_pTextures["World"] = new fw::Texture("Data/Textures/Zelda.png");

    m_TileMap = new Tilemap(level1Layout, level1Layout_Width, level1Layout_Height, m_pMeshes["Tilemap"], m_pShaders["Basic"], m_pTextures["World"]);
    m_Pathfinder = new Pathfinder(m_TileMap, level1Layout_Width, level1Layout_Height);
    
    // Create some GameObjects.
    m_pPlayer = new Player("Player", vec2(5, 5), m_pPlayerController, m_pMeshes["Player"], m_pShaders["Basic"], m_pTextures["Player"], this, fw::vec4::Green());
    m_Objects.push_back(m_pPlayer);

    m_Enemy = new Enemy("Enemy", m_Pathfinder, m_TileMap, vec2(2,2), m_pMeshes["Player"], m_pShaders["Basic"], m_pTextures["World"], this, fw::vec4::Green());
    m_Objects.push_back(m_Enemy);

    //Pathfinder init
    {
        int startx = 1;
        int starty = 1;
        int endx = 10;
        int endy = 10;
        bool found = m_Pathfinder->FindPath(startx, starty, endx, endy);

     
        fw::OutputMessage("Found = %d\n", found);

        int path[255];
        int len = m_Pathfinder->GetPath(path, 255, endx, endy);

        fw::OutputMessage("Length = %d\n", len);
        for (int i = 0; i < len; i++)
        {
            fw::OutputMessage("%d\n", path[i]);
        }

        fw::OutputMessage("done\n");
    }
}

void Game::StartFrame(float deltaTime)
{
    m_pImGuiManager->StartFrame(deltaTime);

    m_pPlayerController->StartFrame();

    // Process our events.
    m_pEventManager->DispatchAllEvents(deltaTime, this);
}

void Game::OnEvent(fw::Event* pEvent)
{
    m_pPlayerController->OnEvent(pEvent);

    if (pEvent->GetType() == RemoveFromGameEvent::GetStaticEventType())
    {
        RemoveFromGameEvent* pRemoveFromGameEvent = static_cast<RemoveFromGameEvent*>(pEvent);
        fw::GameObject* pObject = pRemoveFromGameEvent->GetGameObject();

        auto it = std::find(m_Objects.begin(), m_Objects.end(), pObject);
        m_Objects.erase(it);

        delete pObject;
    }
}

void Game::Update(float deltaTime)
{
    // Display framerate.
    ImGui::Text("%0.2f", 1 / deltaTime);

    for (auto it = m_Objects.begin(); it != m_Objects.end(); it++)
    {
        fw::GameObject* pObject = *it;
        pObject->Update(deltaTime);
    }

    // Debug imgui stuff.
    {
        if (ImGui::Checkbox("VSync", &m_VSyncEnabled))
        {
            wglSwapInterval(m_VSyncEnabled ? 1 : 0);
        }
    }
}

void Game::Draw()
{
    glClearColor(0, 0, 1.0f, 0);
    glClear(GL_COLOR_BUFFER_BIT);

    glPointSize(10);

    m_TileMap->Draw();

    for (auto it = m_Objects.begin(); it != m_Objects.end(); it++)
    {
        fw::GameObject* pObject = *it;
        pObject->Draw();
    }


    m_pImGuiManager->EndFrame();
}
