#pragma once

namespace fw{

    struct SpriteInfo {
        const char* spriteName = 0;
        int SpriteX = 0;
        int SpriteY = 0;
        int SpriteW = 0;
        int  SpriteH = 0;
    };

class Spritesheet {
public:
    Spritesheet(char* fileName);
    virtual ~Spritesheet();

    void SetSprite(char* fileName);

    SpriteInfo GetSpriteInfo(std::string spriteName);

    int GetWidth();
    int GetHeight();

protected:

    rapidjson::Document m_Document;
    std::vector<SpriteInfo> m_Sprites;

    int m_Width;
    int m_Height;
    };
} // namespace fw
