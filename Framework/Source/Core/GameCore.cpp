#include "FrameworkPCH.h"

#include "GameCore.h"


namespace fw {

    GameCore::GameCore(FWCore* pFramework)
    {
        m_pFrameWork = pFramework;
    }

    GameCore::~GameCore()
    {

    }

    fw::FWCore* GameCore::GetFramework()
    {
        return m_pFrameWork;
    }
} //Namespace fw
