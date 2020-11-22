#include "FrameworkPCH.h"
#include "Spritesheet.h"
#include "Math/Vector.h"
#include "Utility/Helpers.h"
#include "../Libraries/rapidjson/document.h"

namespace fw {

    Spritesheet::Spritesheet(char* fileName)
    {
        SetSprite(fileName);
    }

    Spritesheet::~Spritesheet()
    {
    }

    void Spritesheet::SetSprite(char* fileName)
    {
        char* JsonString = LoadCompleteFile(fileName, nullptr);
        m_Document.Parse(JsonString);
        delete[] JsonString;

        for (auto& arr : m_Document["Sprites"].GetArray()) {
            SpriteInfo tempSI;
            tempSI.spriteName = arr["Name"].GetString();
            tempSI.SpriteX = arr["X"].GetInt();
            tempSI.SpriteY = arr["Y"].GetInt();
            tempSI.SpriteH = arr["H"].GetInt();
            tempSI.SpriteW = arr["W"].GetInt();

            m_Sprites.push_back(tempSI);
        }
    }

    SpriteInfo Spritesheet::GetSpriteInfo(std::string sprite)
    {
        SpriteInfo temp;
        for (int i = 0; i < m_Sprites.size(); i++) 
        {
            if (m_Sprites.at(i).spriteName == sprite)
            {
                temp = m_Sprites.at(i);
            }
        }

        assert(temp.spriteName != nullptr);

        return temp;
    }

} // namespace fw
