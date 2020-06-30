#pragma once

struct SpriteInfo
{
    vec2 uvScale;
    vec2 uvOff;
    vec2 bearing;
    float advanceX;
    std::string name;

    void SetValues(vec2 scale, vec2 offset, std::string spriteName, float advX, vec2 pos)
    {
        uvScale = scale;
        uvOff = offset;
        name = spriteName;
        advanceX = advX;
        bearing = pos;
    }
};

class FontSpritesheet
{
public:
    FontSpritesheet();
    virtual ~FontSpritesheet();

    virtual void LoadSprites(std::string filename);

    SpriteInfo* GetSprite(std::string spriteName);

    vec2 GetSpritesheetSize() { return m_SpritesheetSize; }
private:
    SpriteInfo * m_Sprites;
    vec2 m_SpritesheetSize;
    unsigned int m_Size;
};
