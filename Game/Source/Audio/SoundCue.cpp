#include "GamePCH.h"

#include "SoundCue.h"
#include "SoundPlayer.h"

SoundCue::SoundCue(SoundPlayer* a_SoundPlayer, std::string name)
{
    m_SoundPlayer = a_SoundPlayer;

    m_Mode = ECM_Random;
    m_Index = -1;
    m_TotalWeight = 0;
    m_Name = name;
}

SoundCue::~SoundCue()
{
    //No deletions here, SOund Objects are referenced only.
}

void SoundCue::AddSound(SoundObject* a_Sound, int a_weight)
{
    Sound sound;
    sound.m_Sound = a_Sound;
    sound.m_Weight = a_weight;
    m_TotalWeight += a_weight;
    m_Sounds.push_back(sound);
}

void SoundCue::Play()
{
    switch (m_Mode)
    {
    case ECM_Random:
    {
        //Make sure the member index is an invalid value so mode switching works.
        m_Index = -1;

        //Play a random sound
        int index = rand() % m_Sounds.size();
        m_SoundPlayer->PlaySound(m_Sounds[index].m_Sound);
        break;
    }
    case ECM_Random_Weighted:
    {
        //Make sure the member index is an invalid value so mode switching works.
        m_Index = -1;

        //Play a random sound
        int randWeight = rand() % (m_TotalWeight+1);

        int currentWeightCount = 0;
        for (unsigned int i = 0; i < m_Sounds.size(); i++)
        {
            currentWeightCount += m_Sounds[i].m_Weight;
            if (randWeight <= currentWeightCount)
            {
                m_SoundPlayer->PlaySound(m_Sounds[i].m_Sound);
                break;
            }
        }

        break;
    }
    case ECM_Shuffle:
    case ECM_Shuffle_No_Repeats:
    {
        if (m_Index <0 || m_Index>m_Sounds.size()-1)
        {
            Shuffle();
        }
        m_SoundPlayer->PlaySound(m_Sounds[m_deck[m_Index]].m_Sound);
        m_Index++;
        break;
    }
    default:
    {
        break;
    }
    }
}

void SoundCue::Shuffle()
{
    m_Index = 0;
    switch (m_Mode)
    {
    case ECM_Shuffle:
    {
        m_deck.clear();
        for (int i = 0; i<NUM_SOUNDS; i++)
        {
            int weightValue = rand() % m_TotalWeight;
            int totalWeight = 0;
            for (unsigned int j = 0; j < m_Sounds.size(); j++)
            {
                if (weightValue > totalWeight && weightValue <= totalWeight + m_Sounds[j].m_Weight)
                {
                    m_deck.push_back(j);
                }
                else
                {
                    totalWeight += m_Sounds[j].m_Weight;
                    if (j == m_Sounds.size()-1)
                    {
                        m_deck.push_back(j);
                    }
                }
            }
        }
        break;
    }
    case ECM_Shuffle_No_Repeats:
    {
        m_deck.clear();
        for (unsigned int i = 0; i<m_Sounds.size(); i++)
        {
            m_deck.push_back(i);
        }
        for (unsigned int i = 0; i<m_deck.size()*3; i++)
        {
            int index = i % m_deck.size();
            int randIndex = rand() % m_deck.size();
            int temp = m_deck[index];
            m_deck[index] = m_deck[randIndex];
            m_deck[randIndex] = temp;
        }
        break;
    }
    default:
        break;
    }
}

void SoundCue::GenerateImGuiWindow()
{
    if (ImGui::CollapsingHeader(m_Name.c_str()))
    {
        const char* soundTypes[] = { "Random", "Random Weighted", "Shuffle", "Shuffle - No Repeats" };
        
        if (ImGui::BeginCombo("##combo", soundTypes[m_Mode]))
        {
            for (int i = 0; i < ECueModes::ECM_NUM_TYPES; i++)
            {
                bool is_selected = (m_Mode == i);
                if (ImGui::Selectable(soundTypes[i], is_selected))
                {
                    SetMode(static_cast<ECueModes>(i));
                }
            }

            ImGui::EndCombo();
        }

        std::string modeText = "";
        switch (m_Mode)
        {
        case ECueModes::ECM_Random:
        {
            modeText = "Mode: Random";
            break;
        }
        case ECueModes::ECM_Random_Weighted:
        {
            modeText = "Mode: Random Weighted";
            break;
        }
        case ECueModes::ECM_Shuffle:
        {
            modeText = "Mode: Shuffle";
            break;
        }
        case ECueModes::ECM_Shuffle_No_Repeats:
        {
            modeText = "Mode: Shuffle No Repeats";
            break;
        }
        }

        ImGui::Indent();
        ImGui::Text(soundTypes[m_Mode]);

        if (ImGui::Button("Test"))
        {
            Play();
        }
        ImGui::Unindent();
    }
}

