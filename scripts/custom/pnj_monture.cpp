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

 bool GossipHello_pnj_monture(Player* player, Creature* pCreature) 
{   
    Config SD2Config;
    if (!SD2Config.SetSource(_SCRIPTDEV2_CONFIG))
        error_log("SD2: Unable to open configuration file. Database will be unaccessible. Configuration values will use default.");
    else
        outstring_log("SD2: Using configuration file %s",_SCRIPTDEV2_CONFIG);
    if (SD2Config.GetIntDefault("ConfVersion", 0) != SD2_CONF_VERSION)
        error_log("SD2: Configuration file version doesn't match expected version. Some config variables may be wrong or missing.");
     if(SD2Config.GetBoolDefault("pnj_monture.ActifNonActif", false)) // If GMVendor.OnlyGMs is enabled in scriptdev2.conf
	 if (player->GetSession()->GetSecurity() == SEC_PLAYER)
		{
			pCreature->MonsterWhisper("Desoler, Je ne m'occupe que des MJ.", player);
			return true;
		}
	
    bool EnableMT = SD2Config.GetBoolDefault("pnj_monture.EnableMT", false);
	bool EnableMV = SD2Config.GetBoolDefault("pnj_monture.EnableMV", false);
    
	if(EnableMT)
    player->ADD_GOSSIP_ITEM( 4,  "Louer une monture terrestre !", GOSSIP_SENDER_MAIN, 1000);
	if(EnableMV)
	player->ADD_GOSSIP_ITEM( 4,  "Louer une monture Volante !", GOSSIP_SENDER_MAIN, 1003);
	if (player->GetSession()->GetSecurity() >= 3){
	player->ADD_GOSSIP_ITEM( 4,  "Monture du maitre", GOSSIP_SENDER_MAIN, 1002);
	}
    player->ADD_GOSSIP_ITEM( 0, "Au revoir !", GOSSIP_SENDER_MAIN, 1001);

    player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE,pCreature->GetObjectGuid());
    return true;
 }
void SendDefaultMenu_pnj_monture(Player *player, Creature *pCreature, uint32 uiAction )
 {
    if (player->isInCombat())
    {
    player->CLOSE_GOSSIP_MENU();
    pCreature->MonsterSay("Vous etes en combat!", LANG_UNIVERSAL, NULL);
	return;
    }      
	
	Config SD2Config;
    if (!SD2Config.SetSource(_SCRIPTDEV2_CONFIG))
        error_log("SD2: Unable to open configuration file. Database will be unaccessible. Configuration values will use default.");
    else
        outstring_log("SD2: Using configuration file %s",_SCRIPTDEV2_CONFIG);
    if (SD2Config.GetIntDefault("ConfVersion", 0) != SD2_CONF_VERSION)
        error_log("SD2: Configuration file version doesn't match expected version. Some config variables may be wrong or missing.");
    
    bool EnableMT = SD2Config.GetBoolDefault("pnj_monture.EnableMT", false);
	bool EnableMV = SD2Config.GetBoolDefault("pnj_monture.EnableMV", false);

    int money = player->GetMoney();
    int gold = (SD2Config.GetFloatDefault("pnj_monture.CountLoc",0));

        if (money < gold ) 
        {
            player->CLOSE_GOSSIP_MENU();
            pCreature->MonsterWhisper("Vous n'avez pas assez d'argent!", player);
            return;
        }
		if( player->getLevel() < (SD2Config.GetFloatDefault("pnj_monture.LouReqLevel",0))) 
        {
	       player->CLOSE_GOSSIP_MENU();
           pCreature->MonsterSay("Vous n'avez pas le level recquis", LANG_UNIVERSAL, NULL);
           return;
        }
        switch(uiAction)
        {

               case 1000:
               player->ADD_GOSSIP_ITEM( 5, "MotoBecane"                , GOSSIP_SENDER_MAIN, 1);
               player->ADD_GOSSIP_ITEM( 5, "Belier rapide"             , GOSSIP_SENDER_MAIN, 2);
               player->ADD_GOSSIP_ITEM( 5, "Destrier d argent"         , GOSSIP_SENDER_MAIN, 3);
               player->ADD_GOSSIP_ITEM( 5, "Elekk"                     , GOSSIP_SENDER_MAIN, 4);
               player->ADD_GOSSIP_ITEM( 5, "Mecanotrotteur"            , GOSSIP_SENDER_MAIN, 5);
               player->ADD_GOSSIP_ITEM( 5, "sabre de givre"            , GOSSIP_SENDER_MAIN, 7);
               player->ADD_GOSSIP_ITEM( 5, "Cheval de guerre"          , GOSSIP_SENDER_MAIN, 11);
               player->ADD_GOSSIP_ITEM( 5, "Loup des bois"             , GOSSIP_SENDER_MAIN, 12);
               player->ADD_GOSSIP_ITEM( 5, "Destrier dargent"           , GOSSIP_SENDER_MAIN, 3);
               player->ADD_GOSSIP_ITEM( 5, "Ours de guerre"            , GOSSIP_SENDER_MAIN, 15);
               player->ADD_GOSSIP_ITEM( 5, "Kodo de guerre noir"       , GOSSIP_SENDER_MAIN, 16);
               player->ADD_GOSSIP_ITEM( 0, "Retour !", GOSSIP_SENDER_MAIN, 2000);
               player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE,pCreature->GetObjectGuid());
               break;

			   case 1003:
			   player->ADD_GOSSIP_ITEM( 5, "Raie du Neant Argentee"    , GOSSIP_SENDER_MAIN, 20);
               player->ADD_GOSSIP_ITEM( 5, "Drake du Neant impitoyable", GOSSIP_SENDER_MAIN, 21);
               player->ADD_GOSSIP_ITEM( 5, "Faucon-dragon bleu"        , GOSSIP_SENDER_MAIN, 22);
               player->ADD_GOSSIP_ITEM( 5, "Renes de proto-drake noir" , GOSSIP_SENDER_MAIN, 23);
			   player->ADD_GOSSIP_ITEM( 0, "Retour !", GOSSIP_SENDER_MAIN, 2000);
			   player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE,pCreature->GetObjectGuid());
			   break;
			   
			   case 1002:
               player->CLOSE_GOSSIP_MENU();
               player->RemoveSpellsCausingAura(SPELL_AURA_MOUNTED);
               player->CastSpell (player, (SD2Config.GetFloatDefault("pnj_monture.SpellMonteGM",0)), true);
               break;
			   
			   case 20:
			   player->CLOSE_GOSSIP_MENU();
			   player->RemoveSpellsCausingAura(SPELL_AURA_MOUNTED);
               player->CastSpell (player, 39802, true);
               player->ModifyMoney(-(SD2Config.GetFloatDefault("pnj_monture.CountLoc",0)));
			   break;
			   
			   case 21:
			   player->CLOSE_GOSSIP_MENU();
			   player->RemoveSpellsCausingAura(SPELL_AURA_MOUNTED);
               player->CastSpell (player, 44744, true);
               player->ModifyMoney(-(SD2Config.GetFloatDefault("pnj_monture.CountLoc",0)));
			   break;
			   
			   case 22:
			   player->CLOSE_GOSSIP_MENU();
			   player->RemoveSpellsCausingAura(SPELL_AURA_MOUNTED);
               player->CastSpell (player, 61996, true);
               player->ModifyMoney(-(SD2Config.GetFloatDefault("pnj_monture.CountLoc",0)));
			   break;
			   
			   case 23:
			   player->CLOSE_GOSSIP_MENU();
			   player->RemoveSpellsCausingAura(SPELL_AURA_MOUNTED);
               player->CastSpell (player, 59976, true);
               player->ModifyMoney(-(SD2Config.GetFloatDefault("pnj_monture.CountLoc",0)));
			   break;


			   case 1001:
			   player->CLOSE_GOSSIP_MENU();
               player->RemoveSpellsCausingAura(SPELL_AURA_MOUNTED);
               pCreature->MonsterWhisper("Au revoir, aventurier !",player);
			   break;
             
               case 1:
               player->CLOSE_GOSSIP_MENU();
               player->RemoveSpellsCausingAura(SPELL_AURA_MOUNTED);
               player->CastSpell (player, 60424, true);
               player->ModifyMoney(-(SD2Config.GetFloatDefault("pnj_monture.CountLoc",0)));
               break;
               
               case 2:
               player->CLOSE_GOSSIP_MENU();
			   player->RemoveSpellsCausingAura(SPELL_AURA_MOUNTED);
               player->CastSpell (player, 23240, true);
               player->ModifyMoney(-(SD2Config.GetFloatDefault("pnj_monture.CountLoc",0)));
               break;
               
               case 3:
               player->CLOSE_GOSSIP_MENU();
               player->RemoveSpellsCausingAura(SPELL_AURA_MOUNTED);
               player->CastSpell (player, 66906, true);
               player->ModifyMoney(-(SD2Config.GetFloatDefault("pnj_monture.CountLoc",0)));
               break;
               
               case 4:
               player->CLOSE_GOSSIP_MENU();
               player->RemoveSpellsCausingAura(SPELL_AURA_MOUNTED);
               player->CastSpell (player, 63639, true);
               player->ModifyMoney(-(SD2Config.GetFloatDefault("pnj_monture.CountLoc",0)));
               break;
               
               case 5:
               player->CLOSE_GOSSIP_MENU();
               player->RemoveSpellsCausingAura(SPELL_AURA_MOUNTED);
               player->CastSpell (player, 23223, true);
               player->ModifyMoney(-(SD2Config.GetFloatDefault("pnj_monture.CountLoc",0)));
               break;
                
               case 6:
               player->CLOSE_GOSSIP_MENU();
               player->RemoveSpellsCausingAura(SPELL_AURA_MOUNTED);
               player->CastSpell (player, 61465, true);
               player->ModifyMoney(-(SD2Config.GetFloatDefault("pnj_monture.CountLoc",0)));
               break;
                
              case 7:
              player->CLOSE_GOSSIP_MENU();
              player->RemoveSpellsCausingAura(SPELL_AURA_MOUNTED);
              player->CastSpell (player, 23221, true);
              player->ModifyMoney(-(SD2Config.GetFloatDefault("pnj_monture.CountLoc",0)));
              break;

                
              case 11:
              player->CLOSE_GOSSIP_MENU();
              player->RemoveSpellsCausingAura(SPELL_AURA_MOUNTED);
              player->CastSpell (player, 63643, true);
              player->ModifyMoney(-(SD2Config.GetFloatDefault("pnj_monture.CountLoc",0)));
              break;
               
              case 12:
              player->CLOSE_GOSSIP_MENU();
              player->RemoveSpellsCausingAura(SPELL_AURA_MOUNTED);
              player->CastSpell (player, 23251, true);
              player->ModifyMoney(-(SD2Config.GetFloatDefault("pnj_monture.CountLoc",0)));
              break;
                
              case 13:
              player->CLOSE_GOSSIP_MENU();
              player->RemoveSpellsCausingAura(SPELL_AURA_MOUNTED);
              player->CastSpell (player, 60424, true);
              player->ModifyMoney(-(SD2Config.GetFloatDefault("pnj_monture.CountLoc",0)));
              break;
            
              case 14:
              player->CLOSE_GOSSIP_MENU();
			  player->RemoveSpellsCausingAura(SPELL_AURA_MOUNTED);
              player->CastSpell (player, 61647, true);
              player->ModifyMoney(-(SD2Config.GetFloatDefault("pnj_monture.CountLoc",0)));
              break;
                
              case 15:
              player->CLOSE_GOSSIP_MENU();
              player->RemoveSpellsCausingAura(SPELL_AURA_MOUNTED);
              player->CastSpell (player, 60119, true);
              player->ModifyMoney(-(SD2Config.GetFloatDefault("pnj_monture.CountLoc",0)));
              break;
               
              case 16:
              player->CLOSE_GOSSIP_MENU();
              player->RemoveSpellsCausingAura(SPELL_AURA_MOUNTED);
              player->CastSpell (player, 22718, true);
              player->ModifyMoney(-(SD2Config.GetFloatDefault("pnj_monture.CountLoc",0)));
              break;

			  case 2000:
              if(EnableMT)
              player->ADD_GOSSIP_ITEM( 4,  "Louer une monture terrestre !", GOSSIP_SENDER_MAIN, 1000);
	          if(EnableMV)
	          player->ADD_GOSSIP_ITEM( 4,  "Louer une monture Volante !", GOSSIP_SENDER_MAIN, 1003);
	          if (player->GetSession()->GetSecurity() >= 3){
	          player->ADD_GOSSIP_ITEM( 4,  "Monture du maitre", GOSSIP_SENDER_MAIN, 1002);
	          }
              player->ADD_GOSSIP_ITEM( 0, "Au revoir !", GOSSIP_SENDER_MAIN, 1001);
              player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE,pCreature->GetObjectGuid());
              break;
        }
  }
  
bool GossipSelect_pnj_monture(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction)
{
      
     if (uiSender == GOSSIP_SENDER_MAIN)
      SendDefaultMenu_pnj_monture(pPlayer, pCreature, uiAction);
      return true;
        
}
void AddSC_pnj_monture()
{
Script *newscript;
newscript = new Script;
newscript->Name = "pnj_monture";
newscript->pGossipHello = &GossipHello_pnj_monture;
newscript->pGossipSelect = &GossipSelect_pnj_monture;
newscript->RegisterSelf();
}