/* Copyright (C) 2006 - 2011 ScriptDev2 <http://www.scriptdev2.com/>
 * This program is free software licensed under GPL version 2
 * Please see the included DOCS/LICENSE.TXT for more information */

#ifndef DEF_SETHEKK_HALLS_H
#define DEF_SETHEKK_HALLS_H

enum
{
    MAX_ENCOUNTER               = 3,

    TYPE_SYTH                   = 0,
    TYPE_ANZU                   = 1,
    TYPE_IKISS                  = 2,

    GO_IKISS_DOOR               = 177203,
};

class MANGOS_DLL_DECL instance_sethekk_halls : public ScriptedInstance
{
    public:
        instance_sethekk_halls(Map* pMap);
        ~instance_sethekk_halls() {}

        void Initialize();
        void OnObjectCreate(GameObject* pGo);

        void SetData(uint32 uiType, uint32 uiData);
        uint32 GetData(uint32 uiType);

        const char* Save() { return m_strInstData.c_str(); }
        void Load(const char* chrIn);

    private:
        uint32 m_auiEncounter[MAX_ENCOUNTER];
        std::string m_strInstData;
};

#endif
