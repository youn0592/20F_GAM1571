#pragma once

namespace fw{

    struct SpriteInfo {
        const char* spriteName = 0;
        float SpriteX = 0;
        float SpriteY = 0;
        float SpriteW = 0;
        float SpriteH = 0;
    };

class Spritesheet {
public:
    Spritesheet(char* fileName);
    virtual ~Spritesheet();

    void SetSprite(char* fileName);

    SpriteInfo GetSpriteInfo(std::string spriteName);

protected:

    rapidjson::Document m_Document;
    std::vector<SpriteInfo> m_Sprites;

    };
} // namespace fw
