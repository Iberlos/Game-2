#ifndef __SoundCue_H__
#define __SoundCue_H__

class SoundObject;
class SoundPlayer;

enum ECueModes
{
    ECM_Random = 0,
    ECM_Random_Weighted,
    ECM_Shuffle,
    ECM_Shuffle_No_Repeats,
    ECM_NUM_TYPES
};

struct Sound
{
    SoundObject* m_Sound;
    int m_Weight;
};

#define NUM_SOUNDS 5

class SoundCue
{
public:
    SoundCue(SoundPlayer* a_SoundPlayer, std::string name);
    ~SoundCue();

    void AddSound(SoundObject* a_Sound, int a_weight);
    void SetMode(ECueModes a_Mode)
    {
        m_Mode = a_Mode;
        //Reset index as well
        m_Index = -1;
    }
    ECueModes GetMode() { return m_Mode; }
    std::string GetName() { return m_Name; }
    void Play();

    void Shuffle();
    void GenerateImGuiWindow();
protected:

    std::vector<Sound> m_Sounds;
    std::vector<int> m_deck;
    ECueModes m_Mode;
    unsigned int m_Index;
    SoundPlayer* m_SoundPlayer;
    int m_TotalWeight;
    std::string m_Name;
};

#endif