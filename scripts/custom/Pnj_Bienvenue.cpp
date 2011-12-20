#include "precompiled.h"
#include "../../../../shared/Config/Config.h"
#include "../../config.h"
#include "Config/Config.h"
#include "Database/DatabaseEnv.h"
#include "DBCStores.h"
#include "ObjectMgr.h"
#include "ProgressBar.h"
#include "../system/ScriptLoader.h"
#include "../system/system.h"
#include "../../../game/ScriptMgr.h"
#include "CustomTrainer.h"

#define START_ADVENTURE "Start the adventure"
#define START_LEVEL_UP "Go to level 70"
#define GOODBYE "Bye"
#define REWARD_PAGE "Go Back"
#define CONFIRME_CHOICE "Confirm my choice"
#define GOODBYE_PLAYER "GoodBye Man"
#define IN_COMBAT "You are in combat!"

#define REQUETE_CHOICE_1 "UPDATE `characters_begin` SET `begin` = 1 WHERE `guid` = %u"
#define REQUETE_CHOICE_2 "UPDATE `characters_begin` SET `begin` = 2 WHERE `guid` = %u"

DatabaseType CharacterDatabase;
DatabaseType LoginDatabase;
DatabaseType WorldDatabase;

void wait(long seconds)
{
	seconds = seconds * 1000;
	Sleep(seconds);
}

bool GossipHello_Pnj_depart(Player* player, Creature* pCreature)
{
    Config SD2Config;
    if (!SD2Config.SetSource(_SCRIPTDEV2_CONFIG))
        error_log("SD2: Unable to open configuration file. Database will be unaccessible. Configuration values will use default.");
    else
        outstring_log("SD2: Using configuration file %s",_SCRIPTDEV2_CONFIG);
    if (SD2Config.GetIntDefault("ConfVersion", 0) != SD2_CONF_VERSION)
        error_log("SD2: Configuration file version doesn't match expected version. Some config variables may be wrong or missing.");

    QueryResult *result;
	result = CharacterDatabase.PQuery("SELECT `begin` FROM `characters_begin` WHERE `guid` = %u", player->GetGUIDLow());
    Field *fields = result->Fetch();
    uint32 begin = fields[0].GetUInt32();

	if(result)
	{	
	   if(begin == 0) //Nouveau joueur
	    {	
           player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, START_ADVENTURE  ,GOSSIP_SENDER_MAIN, 1000);
	       player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, START_LEVEL_UP   ,GOSSIP_SENDER_MAIN, 1001);
		   player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, GOODBYE          ,GOSSIP_SENDER_MAIN, 1003);
		   player->SEND_GOSSIP_MENU(5, pCreature->GetObjectGuid());
           return true;
	    }
	   else
	    {	
		   player->RemoveAurasDueToSpell(38505);
           player->SEND_GOSSIP_MENU(6, pCreature->GetObjectGuid());
		   return true;
	    }
	}
	return false; 
}
void SendDefaultMenu_Pnj_depart(Player* player, Creature* pCreature, uint32 uiAction)
{
	if (player->isInCombat())
    {
        player->CLOSE_GOSSIP_MENU();
        pCreature->MonsterSay(IN_COMBAT, LANG_UNIVERSAL, NULL);
	    return;
    }  

	Config SD2Config;
    if (!SD2Config.SetSource(_SCRIPTDEV2_CONFIG))
        error_log("SD2: Unable to open configuration file. Database will be unaccessible. Configuration values will use default.");
    else
        outstring_log("SD2: Using configuration file %s",_SCRIPTDEV2_CONFIG);
    if (SD2Config.GetIntDefault("ConfVersion", 0) != SD2_CONF_VERSION)
        error_log("SD2: Configuration file version doesn't match expected version. Some config variables may be wrong or missing.");
    
    switch(uiAction)
    { 
		    case 1003:
            player->CLOSE_GOSSIP_MENU();
			pCreature->MonsterWhisper(GOODBYE_PLAYER, player);
		    break;

	        case 1005:
            player->SetLevel(70);
            player->resetTalents(true);
            player->InitStatsForLevel(true);
            player->SaveToDB();

            wait(1);

			for (uint32 i = 0; i <LIMITE_COMP_ARME; i++)
            player->learnSpell(comp_arme[i],false);

			player->UpdateSkillsToMaxSkillsForLevel(); 
			player->SetTaxiCheater(true);

            wait(1);

			if(player->getClass() == 4)
			{			
			   for (uint32 i = 0; i <LIMITE_ROGUE; i++)
               player->learnSpell(rogue_sort[i],false);
			}

            if(player->getClass() == 1)
			{ 
			   for (uint32 i = 0; i <LIMITE_WARRIOR; i++)
               player->learnSpell(warrior_sort[i],false);
			}
            
            if(player->getClass() == 2)
			{ 
			   for (uint32 i = 0; i <LIMITE_PALADIN; i++)
               player->learnSpell(paladin_sort[i],false);
			}

			if(player->getClass() == 3)
			{ 
			   for (uint32 i = 0; i <LIMITE_HUNTER; i++)
               player->learnSpell(hunter_sort[i],false);
			}

            if(player->getClass() == 5)
			{ 
			   for (uint32 i = 0; i <LIMITE_PRIEST; i++)
               player->learnSpell(priest_sort[i],false);
			}

			if(player->getClass() == 7)
			{ 
			   for (uint32 i = 0; i <LIMITE_SHAMAN; i++)
               player->learnSpell(shaman_sort[i],false);
			}
            
			if(player->getClass() == 8)
			{ 
			   for (uint32 i = 0; i <LIMITE_MAGE; i++)
               player->learnSpell(mage_sort[i],false);
			}

			if(player->getClass() == 9)
			{ 
			   for (uint32 i = 0; i <LIMITE_WARLOCK; i++)
               player->learnSpell(warlock_sort[i],false);
			}

            if(player->getClass() == 11)
			{ 
			   for (uint32 i = 0; i <LIMITE_DRUID; i++)
               player->learnSpell(druid_sort[i],false);
			}

			wait(1);

			if (player->GetTeam() == ALLIANCE )
			{
			   player->TeleportTo(0, -8960.14f, 516.266f, 96.3568f, 0.0f);
			}
			else
			{
			   player->TeleportTo(1, 1552.5f, -4420.66f, 8.94802f, 0.0f);
			}
			player->RemoveAurasDueToSpell(38505);
            CharacterDatabase.PExecute(REQUETE_CHOICE_2, player->GetGUIDLow());
			player->CLOSE_GOSSIP_MENU();
			break;

			case 1001:
			player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, CONFIRME_CHOICE  ,GOSSIP_SENDER_MAIN, 1005);
	        player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, REWARD_PAGE            ,GOSSIP_SENDER_MAIN, 1070);
            player->SEND_GOSSIP_MENU(4, pCreature->GetObjectGuid());
			break;
 
			case 1000:
            player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, CONFIRME_CHOICE  ,GOSSIP_SENDER_MAIN, 1004);
			player->ADD_GOSSIP_ITEM( GOSSIP_ICON_CHAT, REWARD_PAGE            ,GOSSIP_SENDER_MAIN, 1070);
            player->SEND_GOSSIP_MENU(3, pCreature->GetObjectGuid());
            break;
            
			case 1004:
			player->learnSpell((SD2Config.GetFloatDefault("pnj_Bienvenue.SpellMount",0)), true); // mount 6653
			player->learnSpell((SD2Config.GetFloatDefault("pnj_Bienvenue.SpellMiniPet",0)), true); // mini-pet 51716
			player->learnSpell(33388, false); // apprenti mount 
			player->RemoveAurasDueToSpell(38505);
			CharacterDatabase.PExecute(REQUETE_CHOICE_1, player->GetGUIDLow());			
			player->DestroyItemCount(6948, 1, true);
     		player->CLOSE_GOSSIP_MENU();
			break;

			case 1070:
			player->ADD_GOSSIP_ITEM( 0, START_ADVENTURE  ,GOSSIP_SENDER_MAIN, 1000);
	        player->ADD_GOSSIP_ITEM( 0, START_LEVEL_UP   ,GOSSIP_SENDER_MAIN, 1001);
			player->ADD_GOSSIP_ITEM( 0, GOODBYE          ,GOSSIP_SENDER_MAIN, 1003);
            player->SEND_GOSSIP_MENU(5, pCreature->GetObjectGuid());
			break;
	}
}
bool GossipSelect_Pnj_depart(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction)
{
	// Main menu
	if (uiSender == GOSSIP_SENDER_MAIN)
	SendDefaultMenu_Pnj_depart(pPlayer, pCreature, uiAction);

return true;
}
void AddSC_Pnj_depart()
{
     Script *newscript;
     newscript = new Script;
     newscript->Name = "Pnj_depart";
     newscript->pGossipHello = &GossipHello_Pnj_depart;
     newscript->pGossipSelect = &GossipSelect_Pnj_depart;
     newscript->RegisterSelf();
}