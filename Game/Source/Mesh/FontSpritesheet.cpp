#include "GamePCH.h"
#include "FontSpritesheet.h"

FontSpritesheet::FontSpritesheet()
{
    m_Size = 0;
    m_SpritesheetSize = vec2(0.f, 0.f);
}

FontSpritesheet::~FontSpritesheet()
{
    delete[] m_Sprites;
}

void FontSpritesheet::LoadSprites(std::string filename)
{
    //used to store the size of the file
    long filesize;

    //Use the built in function to load a file
    const char* str = LoadCompleteFile(filename.c_str(), &filesize);

    cJSON* jRoot = cJSON_Parse(str);
    cJSON* jFiles = cJSON_GetObjectItem(jRoot, "glyphs");

    //m_SpritesheetSize.x = (float)(cJSON_GetObjectItem(jRoot, "width")->valueint);
    //m_SpritesheetSize.y = (float)(cJSON_GetObjectItem(jRoot, "height")->valueint);
    //temporary hard-coded variables, it's not clear if there is someway to get the sheet size from
    //Brad's JSON file, but I'll keep working on it
    m_SpritesheetSize.x = 204.0f;
    m_SpritesheetSize.y = 254.0f;

    m_Size = cJSON_GetArraySize(jFiles);
    m_Sprites = new SpriteInfo[m_Size];

    for (unsigned int i = 0; i < m_Size; i++)
    {
        cJSON* jSprite = cJSON_GetArrayItem(jFiles, i);
        std::string spriteName = cJSON_GetObjectItem(jSprite, "character")->valuestring;

        cJSON* jSpriteFrame = cJSON_GetObjectItem(jSprite, "frame");

        vec2 spriteSize;
        spriteSize.x = (float)(cJSON_GetObjectItem(jSpriteFrame, "w")->valueint);
        spriteSize.y = (float)(cJSON_GetObjectItem(jSpriteFrame, "h")->valueint) + 2;

        vec2 spriteOffset;
        spriteOffset.x = (float)(cJSON_GetObjectItem(jSpriteFrame, "x")->valueint);
        spriteOffset.y = m_SpritesheetSize.y - ((float)(cJSON_GetObjectItem(jSpriteFrame, "y")->valueint) + spriteSize.y);

        float advanceX = (float)(cJSON_GetObjectItem(jSprite, "advanceX")->valuedouble);

        vec2 spriteBearing;
        spriteBearing.x = (float)(cJSON_GetObjectItem(jSprite, "bearingX")->valuedouble);
        spriteBearing.y = (float)(cJSON_GetObjectItem(jSprite, "bearingY")->valuedouble);

        m_Sprites[i].SetValues((spriteSize / m_SpritesheetSize), (spriteOffset / m_SpritesheetSize), spriteName, advanceX, spriteBearing);
    }

    //Avoid memory leaks
    delete[] str;
}

SpriteInfo* FontSpritesheet::GetSprite(std::string spriteName)
{
    for (unsigned int i = 0; i < m_Size; i++)
    {
        if (spriteName == m_Sprites[i].name)
        {
            return &(m_Sprites[i]);
        }
    }
    return nullptr;
}