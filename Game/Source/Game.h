#pragma once

class Player;
class PlayerController;

class Game : public fw::GameCore
{
public:
    Game(fw::FWCore* pFramework);
    virtual ~Game() override;

    void Init();

    void CreateMesh();

    virtual void StartFrame(float deltaTime) override;

    virtual void OnEvent(fw::Event* pEvent) override;
    virtual void Update(float deltaTime) override;
    virtual void Draw() override;

    void GameText();



    Player* GetPlayer() { return m_pPlayer; }

protected:

    //Circle Members
    int m_verts = 15;
    float m_Rads = 0.3f;
    fw::vec2 m_Mid = vec2(5, 5);
    bool m_isFilled = true;
    int m_enemySpawns = 1;

    //Arena Members
    float m_ArenaRad = 5.0f;;

    //Timers
    float m_Timer = 0.0f;
    float m_TimerSpawn = 0.7f;
    float m_LevelTimer = 0;
    float m_SurvivalTimer = 0;
    
    bool m_MenuActive = true;
    bool m_LevelActive = true;
    bool m_HasLost = false;
    bool m_HasWon = false;
    bool m_Transition = false;

    int m_Level = 1;

    vec2 m_playerPosition;

    //Shaders / ImGui
    fw::ShaderProgram* m_pShader = nullptr;
    fw::ImGuiManager* m_pImGuiManager = nullptr;

    //Meshes
    fw::Mesh* m_Arena = nullptr;
    fw::Mesh* m_Character = nullptr;

    //Enemies
    fw::Mesh* m_EnemyGreen = nullptr;
    fw::Mesh* m_EnemyWhite = nullptr;
    fw::Mesh* m_EnemyYellow = nullptr;

    Player* m_pPlayer = nullptr;
    std::vector<fw::GameObject*> m_pObjects;
    PlayerController* m_pPlayerController = nullptr;

    //Settings

    bool m_VSyncEnabled = true;
};