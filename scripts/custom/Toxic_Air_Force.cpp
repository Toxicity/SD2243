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

long long int money;
int costo;

bool GossipHello_Toxic_Air_Force(Player *player, Creature* pCreature)
{
    Config SD2Config;
    if (!SD2Config.SetSource(_SCRIPTDEV2_CONFIG))
        error_log("SD2: Unable to open configuration file. Database will be unaccessible. Configuration values will use default.");
    else
        outstring_log("SD2: Using configuration file %s",_SCRIPTDEV2_CONFIG);
    if (SD2Config.GetIntDefault("ConfVersion", 0) != SD2_CONF_VERSION)
        error_log("SD2: Configuration file version doesn't match expected version. Some config variables may be wrong or missing.");

    if(SD2Config.GetBoolDefault("Toxic_Air_Force.ActifNonActif", false)) // If GMVendor.OnlyGMs is enabled in scriptdev2.conf
		if (player->GetSession()->GetSecurity() == SEC_PLAYER)
		{
			pCreature->MonsterWhisper("Desoler, Je ne m'occupe que des MJ.", player);
			return true;
		}
		
	bool EnableZone = SD2Config.GetBoolDefault("Toxic_Air_Force.EnableZone", false);
	bool EnableZoneDisco = SD2Config.GetBoolDefault("Toxic_Air_Force.EnableZoneDisco", false);
    bool EnableZoneFFA = SD2Config.GetBoolDefault("Toxic_Air_Force.EnableZoneFFa", false);
	bool EnableZoneMetier = SD2Config.GetBoolDefault("Toxic_Air_Force.EnableZoneMetier", false);
	bool EnableZoneCommune = SD2Config.GetBoolDefault("Toxic_Air_Force.EnableZoneCommune", false);
    bool EnableZoneShopping = SD2Config.GetBoolDefault("Toxic_Air_Force.EnableZoneShopping", false);
	bool EnableZoneXP = SD2Config.GetBoolDefault("Toxic_Air_Force.EnableZoneXP", false);
	bool EnableIledesMJ = SD2Config.GetBoolDefault("Toxic_Air_Force.EnableIledesMJ", false);
	bool EnableCubeBlanc = SD2Config.GetBoolDefault("Toxic_Air_Force.EnableCubeBlanc", false);
    bool EnableZoneTeste = SD2Config.GetBoolDefault("Toxic_Air_Force.EnableZoneTeste", false);
	bool EnableZoneXPA = SD2Config.GetBoolDefault("Toxic_Air_Force.EnableZoneXPA", false);
    bool EnableZoneXPB = SD2Config.GetBoolDefault("Toxic_Air_Force.EnableZoneXPB", false);
	bool EnableZoneXPC = SD2Config.GetBoolDefault("Toxic_Air_Force.EnableZoneXPC", false);
	bool EnableZoneXPD = SD2Config.GetBoolDefault("Toxic_Air_Force.EnableZoneXPD", false);
	bool EnableZoneIron = SD2Config.GetBoolDefault("Toxic_Air_Force.EnableZoneIron", false);
	bool EnableTeleportationMJ = SD2Config.GetBoolDefault("Toxic_Air_Force.EnableTeleportationMJ", false);
	bool EnableCataclysme = SD2Config.GetBoolDefault("Toxic_Air_Force.EnableCataclysme", false);
	bool EnableCA = SD2Config.GetBoolDefault("Toxic_Air_Force.EnableCA", false);
	bool EnableVDT = SD2Config.GetBoolDefault("Toxic_Air_Force.EnableVDT", false);
	bool EnableZoneXPE = SD2Config.GetBoolDefault("Toxic_Air_Force.EnableZoneXPE", false);

    if ( player->GetTeam() == ALLIANCE ) {
    player->ADD_GOSSIP_ITEM( 0, "Capitale Alliance"	  , GOSSIP_SENDER_MAIN, 1000); 
	player->ADD_GOSSIP_ITEM( 0, "Capitale Neutre"	  , GOSSIP_SENDER_MAIN, 1001);
	player->ADD_GOSSIP_ITEM( 0, "Outreterre ->"       , GOSSIP_SENDER_MAIN, 1002);
	player->ADD_GOSSIP_ITEM( 0, "Northrend ->"        , GOSSIP_SENDER_MAIN, 1003);
	if(EnableCataclysme)
	player->ADD_GOSSIP_ITEM( 0, "Cataclysme ->"       , GOSSIP_SENDER_MAIN, 1004);
	player->ADD_GOSSIP_ITEM( 0, "Donjons ->"          , GOSSIP_SENDER_MAIN, 1005);
	}  else {
    player->ADD_GOSSIP_ITEM( 0, "Capitale Horde"	  , GOSSIP_SENDER_MAIN, 1007);
	player->ADD_GOSSIP_ITEM( 0, "Capitale Neutre"	  , GOSSIP_SENDER_MAIN, 1001);
	player->ADD_GOSSIP_ITEM( 0, "Outreterre ->"       , GOSSIP_SENDER_MAIN, 1002);
	player->ADD_GOSSIP_ITEM( 0, "Northrend ->"        , GOSSIP_SENDER_MAIN, 1003);
	if(EnableCataclysme)
	player->ADD_GOSSIP_ITEM( 0, "Cataclysme ->"       , GOSSIP_SENDER_MAIN, 1004);
	player->ADD_GOSSIP_ITEM( 0, "Donjons ->"          , GOSSIP_SENDER_MAIN, 1005);
	}
	if(EnableTeleportationMJ)
	if(player->GetSession()->GetSecurity() >= 3){
	player->ADD_GOSSIP_ITEM( 0, "Teleportation MJ ->" , GOSSIP_SENDER_MAIN, 4000);}
	if(EnableZone)
	player->ADD_GOSSIP_ITEM( 0, "Zone"               , GOSSIP_SENDER_MAIN, 3079);
	
	player->SEND_GOSSIP_MENU(3, pCreature->GetObjectGuid());
    return true;
}
void SendDefaultMenu_Toxic_Air_Force(Player* player, Creature* pCreature, uint32 uiAction)
{
    if (player->isInCombat())
    {
        player->CLOSE_GOSSIP_MENU();
        pCreature->MonsterSay("Vous êtes en combat!", LANG_UNIVERSAL, NULL);
	    return;
    }  
    
	Config SD2Config;
	if(!SD2Config.SetSource(_SCRIPTDEV2_CONFIG))
		error_log("SD2: Unable to open configuration file");
		
	bool EnableZone = SD2Config.GetBoolDefault("Toxic_Air_Force.EnableZone", false);
	bool EnableZoneDisco = SD2Config.GetBoolDefault("Toxic_Air_Force.EnableZoneDisco", false);
    bool EnableZoneFFA = SD2Config.GetBoolDefault("Toxic_Air_Force.EnableZoneFFa", false);
	bool EnableZoneMetier = SD2Config.GetBoolDefault("Toxic_Air_Force.EnableZoneMetier", false);
	bool EnableZoneCommune = SD2Config.GetBoolDefault("Toxic_Air_Force.EnableZoneCommune", false);
    bool EnableZoneShopping = SD2Config.GetBoolDefault("Toxic_Air_Force.EnableZoneShopping", false);
	bool EnableZoneXP = SD2Config.GetBoolDefault("Toxic_Air_Force.EnableZoneXP", false);
	bool EnableIledesMJ = SD2Config.GetBoolDefault("Toxic_Air_Force.EnableIledesMJ", false);
	bool EnableCubeBlanc = SD2Config.GetBoolDefault("Toxic_Air_Force.EnableCubeBlanc", false);
    bool EnableZoneTeste = SD2Config.GetBoolDefault("Toxic_Air_Force.EnableZoneTeste", false);
	bool EnableZoneXPA = SD2Config.GetBoolDefault("Toxic_Air_Force.EnableZoneXPA", false);
    bool EnableZoneXPB = SD2Config.GetBoolDefault("Toxic_Air_Force.EnableZoneXPB", false);
	bool EnableZoneXPC = SD2Config.GetBoolDefault("Toxic_Air_Force.EnableZoneXPC", false);
	bool EnableZoneXPD = SD2Config.GetBoolDefault("Toxic_Air_Force.EnableZoneXPD", false);
	bool EnableZoneIron = SD2Config.GetBoolDefault("Toxic_Air_Force.EnableZoneIron", false);
	bool EnableTeleportationMJ = SD2Config.GetBoolDefault("Toxic_Air_Force.EnableTeleportationMJ", false);
	bool EnableCataclysme = SD2Config.GetBoolDefault("Toxic_Air_Force.EnableCataclysme", false);
	bool EnableCA = SD2Config.GetBoolDefault("Toxic_Air_Force.EnableCA", false);
	bool EnableVDT = SD2Config.GetBoolDefault("Toxic_Air_Force.EnableVDT", false);
	bool EnableZoneXPE = SD2Config.GetBoolDefault("Toxic_Air_Force.EnableZoneXPE", false);
	
	money = player-> GetMoney();
    costo = (SD2Config.GetFloatDefault("Toxic_Air_Force.TeleGoldCost",0));

    if (money < costo)
    {
        player->CLOSE_GOSSIP_MENU();
        pCreature->MonsterWhisper("Vous n'avez pas assez d'argent.", player);
	    return;
    }

    switch(uiAction)
    {
        case 1000:
		player->ADD_GOSSIP_ITEM( 2, "Darnassus"              , GOSSIP_SENDER_MAIN, 1014);
		player->ADD_GOSSIP_ITEM( 2, "Exodar"                 , GOSSIP_SENDER_MAIN, 1015);
		player->ADD_GOSSIP_ITEM( 2, "Forgefer"               , GOSSIP_SENDER_MAIN, 1016);
		player->ADD_GOSSIP_ITEM( 2, "Hurlevent"              , GOSSIP_SENDER_MAIN, 1017);
		player->ADD_GOSSIP_ITEM( 0, "Donjons ->"             , GOSSIP_SENDER_MAIN, 1005);
		player->ADD_GOSSIP_ITEM( 0, "<- Menu Principale"     , GOSSIP_SENDER_MAIN, 1024);
		player->SEND_GOSSIP_MENU(4,pCreature->GetObjectGuid());
        break;

        case 1007: //Horde Town
		player->ADD_GOSSIP_ITEM( 2, "Orgrimmar"               , GOSSIP_SENDER_MAIN, 1019);
		player->ADD_GOSSIP_ITEM( 2, "Silvermoon"              , GOSSIP_SENDER_MAIN, 1020);
		player->ADD_GOSSIP_ITEM( 2, "Pitons des Tonnerres"    , GOSSIP_SENDER_MAIN, 1021);
		player->ADD_GOSSIP_ITEM( 2, "Fossoyeuse"              , GOSSIP_SENDER_MAIN, 1022);
		player->ADD_GOSSIP_ITEM( 0, "Donjons ->"              , GOSSIP_SENDER_MAIN, 1005);
		player->ADD_GOSSIP_ITEM( 0, "<- Menu Principale"      , GOSSIP_SENDER_MAIN, 1024);
	    player->SEND_GOSSIP_MENU(5,pCreature->GetObjectGuid());
        break;
		
		case 1002: //Outland Location
		player->ADD_GOSSIP_ITEM( 2, "Les Tranchantes"       , GOSSIP_SENDER_MAIN, 3000);
		player->ADD_GOSSIP_ITEM( 2, "Hellfire Peninsula"           , GOSSIP_SENDER_MAIN, 3001);
		player->ADD_GOSSIP_ITEM( 2, "Peninsule des Flammes infernales"                      , GOSSIP_SENDER_MAIN, 3002);
		player->ADD_GOSSIP_ITEM( 2, "Raz de Neant"                  , GOSSIP_SENDER_MAIN, 3003);
		player->ADD_GOSSIP_ITEM( 2, "vallee d Ombrelune"            , GOSSIP_SENDER_MAIN, 3004);
		player->ADD_GOSSIP_ITEM( 2, "Foret de Terokkar"              , GOSSIP_SENDER_MAIN, 3005);
		player->ADD_GOSSIP_ITEM( 2, "Marecage de Zangar"                  , GOSSIP_SENDER_MAIN, 3006);
		player->ADD_GOSSIP_ITEM( 0, "Donjons ->"                   , GOSSIP_SENDER_MAIN, 1005);
		player->ADD_GOSSIP_ITEM( 0, "<- Menu Principale"           , GOSSIP_SENDER_MAIN, 1024);
	    player->SEND_GOSSIP_MENU(6,pCreature->GetObjectGuid());
        break;
		
		case 1003: //Northrend Location
		player->ADD_GOSSIP_ITEM( 2, "toundra boreenne"                , GOSSIP_SENDER_MAIN, 3007);
		player->ADD_GOSSIP_ITEM( 2, "Crystalsong Forest"           , GOSSIP_SENDER_MAIN, 3008);
		player->ADD_GOSSIP_ITEM( 2, "Foret du Chant de cristal"                 , GOSSIP_SENDER_MAIN, 3009);
		player->ADD_GOSSIP_ITEM( 2, "Les Grisonnes"                , GOSSIP_SENDER_MAIN, 3010);
		player->ADD_GOSSIP_ITEM( 2, "Fjord Hurlant"                , GOSSIP_SENDER_MAIN, 3011);
		player->ADD_GOSSIP_ITEM( 2, "Accostage de Hrothgar"           , GOSSIP_SENDER_MAIN, 3012);
		player->ADD_GOSSIP_ITEM( 2, "La Couronne de glace"                     , GOSSIP_SENDER_MAIN, 3013);
		player->ADD_GOSSIP_ITEM( 2, "bassin de Sholazar"               , GOSSIP_SENDER_MAIN, 3014);
		player->ADD_GOSSIP_ITEM( 2, "Les pics Foudroyes"              , GOSSIP_SENDER_MAIN, 3015);
		player->ADD_GOSSIP_ITEM( 2, "Joug d hiver"                  , GOSSIP_SENDER_MAIN, 3016);
		player->ADD_GOSSIP_ITEM( 2, "Zul'Drak"                     , GOSSIP_SENDER_MAIN, 3017);
		player->ADD_GOSSIP_ITEM( 0, "Donjons ->"                   , GOSSIP_SENDER_MAIN, 1005);
		player->ADD_GOSSIP_ITEM( 0, "<- Menu Principale"           , GOSSIP_SENDER_MAIN, 1024);
	    player->SEND_GOSSIP_MENU(7,pCreature->GetObjectGuid());
        break;

		case 1005: //Dungeons
		player->ADD_GOSSIP_ITEM( 0, "Kalimdor ->"                  , GOSSIP_SENDER_MAIN, 3018);
		player->ADD_GOSSIP_ITEM( 0, "Royaume de l Est ->"          , GOSSIP_SENDER_MAIN, 3019);
		player->ADD_GOSSIP_ITEM( 0, "Outreterre ->"                , GOSSIP_SENDER_MAIN, 3020);
		player->ADD_GOSSIP_ITEM( 0, "Northrend ->"                 , GOSSIP_SENDER_MAIN, 3021);
		player->ADD_GOSSIP_ITEM( 0, "<- Menu Principale"           , GOSSIP_SENDER_MAIN, 1024);
	    player->SEND_GOSSIP_MENU(8,pCreature->GetObjectGuid());
        break;
		
		case 1024:
	    if ( player->GetTeam() == ALLIANCE ) {
        player->ADD_GOSSIP_ITEM( 0, "Capitale Alliance"	  , GOSSIP_SENDER_MAIN, 1000); 
	    player->ADD_GOSSIP_ITEM( 0, "Capitale Neutre"	  , GOSSIP_SENDER_MAIN, 1001);
	    player->ADD_GOSSIP_ITEM( 0, "Outreterre ->"       , GOSSIP_SENDER_MAIN, 1002);
	    player->ADD_GOSSIP_ITEM( 0, "Northrend ->"        , GOSSIP_SENDER_MAIN, 1003);
	    if(EnableCataclysme)
	    player->ADD_GOSSIP_ITEM( 0, "Cataclysme ->"       , GOSSIP_SENDER_MAIN, 1004);
	    player->ADD_GOSSIP_ITEM( 0, "Donjons ->"          , GOSSIP_SENDER_MAIN, 1005);
	    }  else {
        player->ADD_GOSSIP_ITEM( 0, "Capitale Horde"	  , GOSSIP_SENDER_MAIN, 1007);
	    player->ADD_GOSSIP_ITEM( 0, "Capitale Neutre"	  , GOSSIP_SENDER_MAIN, 1001);
	    player->ADD_GOSSIP_ITEM( 0, "Outreterre ->"       , GOSSIP_SENDER_MAIN, 1002);
	    player->ADD_GOSSIP_ITEM( 0, "Northrend ->"        , GOSSIP_SENDER_MAIN, 1003);
	    if(EnableCataclysme)
	    player->ADD_GOSSIP_ITEM( 0, "Cataclysme ->"       , GOSSIP_SENDER_MAIN, 1004);
	    player->ADD_GOSSIP_ITEM( 0, "Donjons ->"          , GOSSIP_SENDER_MAIN, 1005);
	    }
	    if(EnableTeleportationMJ)
	    if(player->GetSession()->GetSecurity() >= 3){
	    player->ADD_GOSSIP_ITEM( 0, "Teleportation MJ ->" , GOSSIP_SENDER_MAIN, 4000);}
	    if(EnableZone)
	    player->ADD_GOSSIP_ITEM( 0, "Zone"               , GOSSIP_SENDER_MAIN, 3079);
	    player->SEND_GOSSIP_MENU(3, pCreature->GetObjectGuid());
	    break;
		
		case 4000:
		if(EnableIledesMJ)
		player->ADD_GOSSIP_ITEM( 2, "Ile des MJ"          , GOSSIP_SENDER_MAIN, 3090);
		if(EnableCubeBlanc)
		player->ADD_GOSSIP_ITEM( 2, "Cube Blanc"          , GOSSIP_SENDER_MAIN, 3091);
		if(EnableZoneTeste)
	    player->ADD_GOSSIP_ITEM( 2, "Zone Teste"          , GOSSIP_SENDER_MAIN, 3092);
		if(EnableZoneIron)
	    player->ADD_GOSSIP_ITEM( 2, "Vieux IronForge"     , GOSSIP_SENDER_MAIN, 3093);
		if(EnableCA)
		player->ADD_GOSSIP_ITEM( 2, "Cratere d'Azshara"     , GOSSIP_SENDER_MAIN, 3094);
		if(EnableVDT)
		player->ADD_GOSSIP_ITEM( 2, "VIllage des Trolls"     , GOSSIP_SENDER_MAIN, 3095);
	    player->ADD_GOSSIP_ITEM( 0, "<- Menu Principale"  , GOSSIP_SENDER_MAIN, 1024);
	    player->SEND_GOSSIP_MENU(9,pCreature->GetObjectGuid());
		break;
		
		case 3079: //Zone (active dans scriptdev2.conf)
		if(EnableZoneXP)
		player->ADD_GOSSIP_ITEM( 0, "Zone XP"             , GOSSIP_SENDER_MAIN, 3085);
		if(EnableZoneFFA)
		player->ADD_GOSSIP_ITEM( 2, "Zone FFA"            , GOSSIP_SENDER_MAIN, 3080);
		if(EnableZoneShopping)
	    player->ADD_GOSSIP_ITEM( 2, "Zone Shopping"       , GOSSIP_SENDER_MAIN, 3081);
		if(EnableZoneDisco)
	    player->ADD_GOSSIP_ITEM( 2, "Zone Disco"          , GOSSIP_SENDER_MAIN, 3082);
		if(EnableZoneMetier)
		player->ADD_GOSSIP_ITEM( 2, "Zone Metier"         , GOSSIP_SENDER_MAIN, 3083);
		if(EnableZoneCommune)
		player->ADD_GOSSIP_ITEM( 2, "Zone Commune"        , GOSSIP_SENDER_MAIN, 3084);
	    player->ADD_GOSSIP_ITEM( 0, "<- Menu Principale"  , GOSSIP_SENDER_MAIN, 1024);
	    player->SEND_GOSSIP_MENU(10,pCreature->GetObjectGuid());
        break;
		
		case 3085:
		if(EnableZoneXPA)
		player->ADD_GOSSIP_ITEM( 2, "Zone XP 1 - 80"                     , GOSSIP_SENDER_MAIN, 3086);
		if(EnableZoneXPB)
		player->ADD_GOSSIP_ITEM( 2, "Zone XP 81 - 100"                    , GOSSIP_SENDER_MAIN, 3087);
		if(EnableZoneXPC)
	    player->ADD_GOSSIP_ITEM( 2, "Zone XP 101 - 150"                   , GOSSIP_SENDER_MAIN, 3088);
		if(EnableZoneXPD)
	    player->ADD_GOSSIP_ITEM( 2, "Zone XP 151 - 200"                  , GOSSIP_SENDER_MAIN, 3089);
		if(EnableZoneXPE)
		player->ADD_GOSSIP_ITEM( 2, "Zone XP 201 - 255"                  , GOSSIP_SENDER_MAIN, 3096);
		player->ADD_GOSSIP_ITEM( 0, "<- Retour"                          , GOSSIP_SENDER_MAIN, 3079);
	    player->ADD_GOSSIP_ITEM( 0, "<- Menu Principale"                 , GOSSIP_SENDER_MAIN, 1024);
	    player->SEND_GOSSIP_MENU(11,pCreature->GetObjectGuid());
		break;
		
		case 3018: //Kalimdor
	    player->ADD_GOSSIP_ITEM( 2, "Profondeurs de Brassenoire"                , GOSSIP_SENDER_MAIN, 3022);
	    player->ADD_GOSSIP_ITEM( 2, "Grottes du temps"                  , GOSSIP_SENDER_MAIN, 3023);
	    player->ADD_GOSSIP_ITEM( 2, "Hache tripes"                        , GOSSIP_SENDER_MAIN, 3024);
	    player->ADD_GOSSIP_ITEM( 2, "Maraudon"                         , GOSSIP_SENDER_MAIN, 3025);
	    player->ADD_GOSSIP_ITEM( 2, "Gouffre de Ragefeu"                   , GOSSIP_SENDER_MAIN, 3026);
	    player->ADD_GOSSIP_ITEM( 2, "Souilles de Tranchebauge"                   , GOSSIP_SENDER_MAIN, 3027);
	    player->ADD_GOSSIP_ITEM( 2, "Kraal de Tranchebauge"                   , GOSSIP_SENDER_MAIN, 3028);
	    player->ADD_GOSSIP_ITEM( 2, "Ruines d'Ahn'Qiraj"               , GOSSIP_SENDER_MAIN, 3029);
	    player->ADD_GOSSIP_ITEM( 2, "Temples d'Ahn'Qiraj"              , GOSSIP_SENDER_MAIN, 3030);
	    player->ADD_GOSSIP_ITEM( 2, "Cavernes des lamentations"                  , GOSSIP_SENDER_MAIN, 3031);
	    player->ADD_GOSSIP_ITEM( 2, "Zul'Farrak"                       , GOSSIP_SENDER_MAIN, 3032);
	    player->ADD_GOSSIP_ITEM( 0, "<- Retour"                        , GOSSIP_SENDER_MAIN, 1005);
	    player->SEND_GOSSIP_MENU(8,pCreature->GetObjectGuid());
        break;  
		
		case 3019: //Eastern Kingdoms 1
	    player->ADD_GOSSIP_ITEM( 2, "Profondeurs de Rochenoire"                 , GOSSIP_SENDER_MAIN, 3033);
	    player->ADD_GOSSIP_ITEM( 2, "Pic de Rochenoire"                  , GOSSIP_SENDER_MAIN, 3034);
	    player->ADD_GOSSIP_ITEM( 2, "Reapaire de l'Aile noire"                   , GOSSIP_SENDER_MAIN, 3035);
	    player->ADD_GOSSIP_ITEM( 2, "Mortemines"                        , GOSSIP_SENDER_MAIN, 3036);
	    player->ADD_GOSSIP_ITEM( 2, "Gnomeregan"                       , GOSSIP_SENDER_MAIN, 3037);
	    player->ADD_GOSSIP_ITEM( 2, "Ile de Quel'Danas"               , GOSSIP_SENDER_MAIN, 3038);
	    player->ADD_GOSSIP_ITEM( 2, "Karazhan"                         , GOSSIP_SENDER_MAIN, 3039);
	    player->ADD_GOSSIP_ITEM( 2, "Le pont de magma"                      , GOSSIP_SENDER_MAIN, 3040);
	    player->ADD_GOSSIP_ITEM( 0, "Suivant ->"                       , GOSSIP_SENDER_MAIN, 3041);
	    player->ADD_GOSSIP_ITEM( 0, "<- Retour"                        , GOSSIP_SENDER_MAIN, 1005);
	    player->SEND_GOSSIP_MENU(8,pCreature->GetObjectGuid());
        break;
		
		case 3041:
		player->ADD_GOSSIP_ITEM( 2, "Monastere ecarlate"                , GOSSIP_SENDER_MAIN, 3042);
	    player->ADD_GOSSIP_ITEM( 2, "Scholomance"                      , GOSSIP_SENDER_MAIN, 3043);
	    player->ADD_GOSSIP_ITEM( 2, "Ombrecroc"                  , GOSSIP_SENDER_MAIN, 3044);
	    player->ADD_GOSSIP_ITEM( 2, "Stratholme"                       , GOSSIP_SENDER_MAIN, 3045);
	    player->ADD_GOSSIP_ITEM( 2, "Temple englouti"                    , GOSSIP_SENDER_MAIN, 3046);
	    player->ADD_GOSSIP_ITEM( 2, "La Prison"                     , GOSSIP_SENDER_MAIN, 3047);
	    player->ADD_GOSSIP_ITEM( 2, "Uldaman"                          , GOSSIP_SENDER_MAIN, 3048);
	    player->ADD_GOSSIP_ITEM( 2, "Zul'Aman"                         , GOSSIP_SENDER_MAIN, 3049);
	    player->ADD_GOSSIP_ITEM( 2, "Zul'Gurub"                        , GOSSIP_SENDER_MAIN, 3050);
	    player->ADD_GOSSIP_ITEM( 0, "<- Retour"                        , GOSSIP_SENDER_MAIN, 1005);
	    player->ADD_GOSSIP_ITEM( 0, "<- Menu Principale"               , GOSSIP_SENDER_MAIN, 1024);
	    player->SEND_GOSSIP_MENU(8,pCreature->GetObjectGuid());
		break;
		
		case 3020: //Outland	
	    player->ADD_GOSSIP_ITEM( 2, "Auchindoun"                       , GOSSIP_SENDER_MAIN, 3051);
	    player->ADD_GOSSIP_ITEM( 2, "Temple Noir"                      , GOSSIP_SENDER_MAIN, 3052);
	    player->ADD_GOSSIP_ITEM( 2, "Reservoir de Glissecroc"               , GOSSIP_SENDER_MAIN, 3053);
	    player->ADD_GOSSIP_ITEM( 2, "Repaire de Gruul"                     , GOSSIP_SENDER_MAIN, 3054);
	    player->ADD_GOSSIP_ITEM( 2, "Citadelle des Flammes infernales"                 , GOSSIP_SENDER_MAIN, 3055);
	    player->ADD_GOSSIP_ITEM( 2, "Oeil de la Tempete"               , GOSSIP_SENDER_MAIN, 3056);
	    player->ADD_GOSSIP_ITEM( 0, "<- Retour"                        , GOSSIP_SENDER_MAIN, 1005);
	    player->ADD_GOSSIP_ITEM( 0, "<- Menu Principale"               , GOSSIP_SENDER_MAIN, 1024);
	    player->SEND_GOSSIP_MENU(8,pCreature->GetObjectGuid());
        break;
		
		case 3021: //Northrend	
	    player->ADD_GOSSIP_ITEM( 2, "Ahn'Kahet"                          , GOSSIP_SENDER_MAIN, 3057);
	    player->ADD_GOSSIP_ITEM( 2, "Azjol-Nerub"                        , GOSSIP_SENDER_MAIN, 3058);
	    player->ADD_GOSSIP_ITEM( 2, "Donjon de Drak'Tharon"                   , GOSSIP_SENDER_MAIN, 3059);
	    player->ADD_GOSSIP_ITEM( 2, "Gun'Drak"                           , GOSSIP_SENDER_MAIN, 3060);
	    player->ADD_GOSSIP_ITEM( 2, "Citadelle de la Courronne de glace" , GOSSIP_SENDER_MAIN, 3061);
	    player->ADD_GOSSIP_ITEM( 2, "Naxxramas"                          , GOSSIP_SENDER_MAIN, 3062);
	    player->ADD_GOSSIP_ITEM( 2, "Repaire d'Onyxia"                      , GOSSIP_SENDER_MAIN, 3063);
	    player->ADD_GOSSIP_ITEM( 2, "Le Nexus"                          , GOSSIP_SENDER_MAIN, 3064);
	    player->ADD_GOSSIP_ITEM( 2, "Le sanctum Obsidien"               , GOSSIP_SENDER_MAIN, 3065);
	    player->ADD_GOSSIP_ITEM( 2, "Donjon d'Utgarde"                       , GOSSIP_SENDER_MAIN, 3066);
	    player->ADD_GOSSIP_ITEM( 2, "Cime d'Utgarde"                   , GOSSIP_SENDER_MAIN, 3067);
	    player->ADD_GOSSIP_ITEM( 2, "Ulduar"                             , GOSSIP_SENDER_MAIN, 3068);
	    player->ADD_GOSSIP_ITEM( 2, "Le fort Pourpre"                        , GOSSIP_SENDER_MAIN, 3069);
	    player->ADD_GOSSIP_ITEM( 0, "<- Retour"                          , GOSSIP_SENDER_MAIN, 1005);
	    player->ADD_GOSSIP_ITEM( 0, "<- Menu Principale"                 , GOSSIP_SENDER_MAIN, 1024);
	    player->SEND_GOSSIP_MENU(8,pCreature->GetObjectGuid());
        break;
		
		case 1001: //Neutral Town
        // Check if player is DK for "Ebon Hold"
        if(player->getClass()==6)
		player->ADD_GOSSIP_ITEM( 2, "Fort d'Ebene"                    , GOSSIP_SENDER_MAIN, 3070);
		player->ADD_GOSSIP_ITEM( 2, "Baie-du-Butin"                    , GOSSIP_SENDER_MAIN, 3071);
		player->ADD_GOSSIP_ITEM( 2, "Dalaran"                      , GOSSIP_SENDER_MAIN, 3072);
		player->ADD_GOSSIP_ITEM( 2, "Long-guet"                     , GOSSIP_SENDER_MAIN, 3073);
		player->ADD_GOSSIP_ITEM( 2, "Gadegetzan"                   , GOSSIP_SENDER_MAIN, 3074);
		player->ADD_GOSSIP_ITEM( 2, "Bourbe-a-Brac"                  , GOSSIP_SENDER_MAIN, 3075);
		player->ADD_GOSSIP_ITEM( 2, "Cabestan"                      , GOSSIP_SENDER_MAIN, 3076);
		player->ADD_GOSSIP_ITEM( 2, "Shattrath City"               , GOSSIP_SENDER_MAIN, 3077);
		player->ADD_GOSSIP_ITEM( 2, "Ile de Quel'Danas"            , GOSSIP_SENDER_MAIN, 3078);
		player->ADD_GOSSIP_ITEM( 0, "Donjons ->"                   , GOSSIP_SENDER_MAIN, 1005);
	    player->ADD_GOSSIP_ITEM( 0, "<- Menu Principale"           , GOSSIP_SENDER_MAIN, 1024);

	    player->SEND_GOSSIP_MENU(12,pCreature->GetObjectGuid());
        break;
		
		case 1014: // Darnassus
        player->CLOSE_GOSSIP_MENU();
        player->TeleportTo(1, 9947.52f, 2482.73f, 1316.21f, 0.0f);
        player->ModifyMoney(-(SD2Config.GetFloatDefault("Toxic_Air_Force.TeleGoldCost",0)));
        break;

        case 1015: // Exodar
	    player->CLOSE_GOSSIP_MENU();
	    player->TeleportTo(530, -3954.20f, -11656.54f, -138.69f, 0.0f);
	    player->ModifyMoney(-(SD2Config.GetFloatDefault("Toxic_Air_Force.TeleGoldCost",0)));
        break;

        case 1016: // Ironforge
	    player->CLOSE_GOSSIP_MENU();
	    player->TeleportTo(0, -4924.07f, -951.95f, 501.55f, 5.40f);
	    player->ModifyMoney(-(SD2Config.GetFloatDefault("Toxic_Air_Force.TeleGoldCost",0)));
        break;

        case 1017: // Stormwind
	    player->CLOSE_GOSSIP_MENU();
	    player->TeleportTo(0, -8960.14f, 516.266f, 96.3568f, 0.0f);
	    player->ModifyMoney(-(SD2Config.GetFloatDefault("Toxic_Air_Force.TeleGoldCost",0)));
        break;

//////////////////////////////////////////////////HORDE///////////////////////////////////////////////////////////////

        case 1019: // Orgrimmar
	    player->CLOSE_GOSSIP_MENU();
	    player->TeleportTo(1, 1552.5f, -4420.66f, 8.94802f, 0.0f);
	    player->ModifyMoney(-(SD2Config.GetFloatDefault("Toxic_Air_Force.TeleGoldCost",0)));
        break;

        case 1020: // Silvermoon
	    player->CLOSE_GOSSIP_MENU();
	    player->TeleportTo(530, 9338.74f, -7277.27f, 13.7895f, 0.0f);
	    player->ModifyMoney(-(SD2Config.GetFloatDefault("Toxic_Air_Force.TeleGoldCost",0)));
        break;

        case 1021: // Pitons des Tonnerres
	    player->CLOSE_GOSSIP_MENU();
	    player->TeleportTo(1, -1290.0f, 147.033997f, 129.682007f, 4.919000f);
	    player->ModifyMoney(-(SD2Config.GetFloatDefault("Toxic_Air_Force.TeleGoldCost",0)));
        break;

        case 1022: // Fossoyeuse
	    player->CLOSE_GOSSIP_MENU();
	    player->TeleportTo(0, 1819.71f, 238.79f, 60.5321f, 0.0f);
	    player->ModifyMoney(-(SD2Config.GetFloatDefault("Toxic_Air_Force.TeleGoldCost",0)));
        break;

//////////////////////////////////////////////////NEUTRAL///////////////////////////////////////////////////////////////

        case 3070:// Ebon Hold
	    player->CLOSE_GOSSIP_MENU();
	    player->TeleportTo(0, 2353.530029f, -5665.819824f, 426.028015f, 0.596f);
	    player->ModifyMoney(-(SD2Config.GetFloatDefault("Toxic_Air_Force.TeleGoldCost",0)));
        break;

        case 3071:// Booty Bay
	    player->CLOSE_GOSSIP_MENU();
	    player->TeleportTo(0, -14438.2f, 472.22f, 15.32f, 0.65f);
	    player->ModifyMoney(-(SD2Config.GetFloatDefault("Toxic_Air_Force.TeleGoldCost",0)));
        break;

        case 3072: //Dalaran
	    player->CLOSE_GOSSIP_MENU();
	    player->TeleportTo(571, 5819.08f, 643.99f, 647.80f, 3.32f);
	    player->ModifyMoney(-(SD2Config.GetFloatDefault("Toxic_Air_Force.TeleGoldCost",0)));
        break;

        case 3073: //Everlook
	    player->CLOSE_GOSSIP_MENU();
	    player->TeleportTo(1, 6724.77f, -4610.68f, 720.78f, 4.78f);
	    player->ModifyMoney(-(SD2Config.GetFloatDefault("Toxic_Air_Force.TeleGoldCost",0)));
        break;

        case 3074: //Gadgetzan
	    player->CLOSE_GOSSIP_MENU();
	    player->TeleportTo(1, -7173.26f, -3785.60f, 8.37f, 6.13f);
	    player->ModifyMoney(-(SD2Config.GetFloatDefault("Toxic_Air_Force.TeleGoldCost",0)));
        break;

        case 3075: //Mudsprocket
	    player->CLOSE_GOSSIP_MENU();
	    player->TeleportTo(1, -4564.79f, -3172.38f, 33.93f, 3.21f);
	    player->ModifyMoney(-(SD2Config.GetFloatDefault("Toxic_Air_Force.TeleGoldCost",0)));
        break;

        case 3076: //Ratchet
	    player->CLOSE_GOSSIP_MENU();
	    player->TeleportTo(1, -956.664f, -3754.71f, 5.33239f, 0.996637f);
	    player->ModifyMoney(-(SD2Config.GetFloatDefault("Toxic_Air_Force.TeleGoldCost",0)));
        break;

        case 3077:// Shattrath City
	    player->CLOSE_GOSSIP_MENU();
	    player->TeleportTo(530, -1850.209961f, 5435.821777f, -10.961435f, 3.403913f);
	    player->ModifyMoney(-(SD2Config.GetFloatDefault("Toxic_Air_Force.TeleGoldCost",0)));
        break;

        case 3078:// Isle Of Quel'Danas
	    player->CLOSE_GOSSIP_MENU();
	    player->TeleportTo(530, 12947.4f, -6893.31f, 5.68398f, 3.09154f);
	    player->ModifyMoney(-(SD2Config.GetFloatDefault("Toxic_Air_Force.TeleGoldCost",0)));
        break;

//////////////////////////////////////////////////OUTLAND LOCATION///////////////////////////////////////////////////////////////

        case 3000:// Blade's Edge Mountains
	    player->CLOSE_GOSSIP_MENU();
	    player->TeleportTo(530, 1589.919312f, 6784.039063f, 135.167633f, 0.506582f);
	    player->ModifyMoney(-(SD2Config.GetFloatDefault("Toxic_Air_Force.TeleGoldCost",0)));
        break;

        case 3001:// Hellfire Peninsula
	    player->CLOSE_GOSSIP_MENU();
	    player->TeleportTo(530, -248.0f, 956.0f, 84.362808f, 1.549591f);
	    player->ModifyMoney(-(SD2Config.GetFloatDefault("Toxic_Air_Force.TeleGoldCost",0)));
        break;

        case 3002: //Nagrand
	    player->CLOSE_GOSSIP_MENU();
	    player->TeleportTo(530, -604.137146f, 8436.199219f, 61.776058f, 3.019857f);
	    player->ModifyMoney(-(SD2Config.GetFloatDefault("Toxic_Air_Force.TeleGoldCost",0)));
        break;

        case 3003: //Netherstorm
	    player->CLOSE_GOSSIP_MENU();
	    player->TeleportTo(530, 3386.022217f, 4225.194824f, 123.685989f, 5.153f);
	    player->ModifyMoney(-(SD2Config.GetFloatDefault("Toxic_Air_Force.TeleGoldCost",0)));
        break;

        case 3004: //Shadowmoon Valley
	    player->CLOSE_GOSSIP_MENU();
	    player->TeleportTo(530, -2901.471680f, 3125.052734f, 26.8999f, 4.464991f);
	    player->ModifyMoney(-(SD2Config.GetFloatDefault("Toxic_Air_Force.TeleGoldCost",0)));
        break;

        case 3005: //Terokkar Forest
	    player->CLOSE_GOSSIP_MENU();
	    player->TeleportTo(530, -2000.469971f, 4451.540039f, 8.379014f, 4.464991f);
	    player->ModifyMoney(-(SD2Config.GetFloatDefault("Toxic_Air_Force.TeleGoldCost",0)));
        break;

        case 3006: //Zangarmarsh
	    player->CLOSE_GOSSIP_MENU();
	    player->TeleportTo(530, -225.6577f, 5435.426270f, 21.574932f, 1.533886f);
	    player->ModifyMoney(-(SD2Config.GetFloatDefault("Toxic_Air_Force.TeleGoldCost",0)));
        break;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////NORTHREND LOCATION///////////////////////////////////////////////////////////////

        case 3007:// Borean Tundra
	    player->CLOSE_GOSSIP_MENU();
	    player->TeleportTo(571, 3256.570068f, 5278.229980f, 40.804588f, 0.246367f);
	    player->ModifyMoney(-(SD2Config.GetFloatDefault("Toxic_Air_Force.TeleGoldCost",0)));
        break;

        case 3008:// Crystalsong Forest
	    player->CLOSE_GOSSIP_MENU();
	    player->TeleportTo(571, 5766.373047f, 655.131287f, 160.944641f, 4.135118f);
	    player->ModifyMoney(-(SD2Config.GetFloatDefault("Toxic_Air_Force.TeleGoldCost",0)));
        break;

        case 3009: //Dragonblight
	    player->CLOSE_GOSSIP_MENU();
	    player->TeleportTo(571, 4103.359863f, 264.477997f, 50.501900f, 3.093490f);
	    player->ModifyMoney(-(SD2Config.GetFloatDefault("Toxic_Air_Force.TeleGoldCost",0)));
        break;

        case 3010: //Grizzly Hills
	    player->CLOSE_GOSSIP_MENU();
	    player->TeleportTo(571, 4391.729980f, -3587.919922f, 238.531006f, 3.575260f);
	    player->ModifyMoney(-(SD2Config.GetFloatDefault("Toxic_Air_Force.TeleGoldCost",0)));
        break;

        case 3011: //Howling Fjord
	    player->CLOSE_GOSSIP_MENU();
	    player->TeleportTo(571, 1902.150024f, -4883.910156f, 171.363007f, 3.115370f);
	    player->ModifyMoney(-(SD2Config.GetFloatDefault("Toxic_Air_Force.TeleGoldCost",0)));
        break;

        case 3012: //Hrothgar's Landing
	    player->CLOSE_GOSSIP_MENU();
	    player->TeleportTo(571, 9982.508789f, 1037.768188f, 15.307539f, 5.512708f);
	    player->ModifyMoney(-(SD2Config.GetFloatDefault("Toxic_Air_Force.TeleGoldCost",0)));
        break;

        case 3013: //Icecrown
	    player->CLOSE_GOSSIP_MENU();
	    player->TeleportTo(571, 7253.640137f, 1644.780029f, 433.679901f, 4.834120f);
	    player->ModifyMoney(-(SD2Config.GetFloatDefault("Toxic_Air_Force.TeleGoldCost",0)));
        break;

        case 3014:// Sholazar Basin
	    player->CLOSE_GOSSIP_MENU();
	    player->TeleportTo(571, 5572.285156f, 5737.171387f, -75.440643f, 1.514785f);
	    player->ModifyMoney(-(SD2Config.GetFloatDefault("Toxic_Air_Force.TeleGoldCost",0)));
        break;

        case 3015:// The Storm Peaks
	    player->CLOSE_GOSSIP_MENU();
	    player->TeleportTo(571, 6119.275391f, -1015.613464f, 408.683258f, 5.175134f);
	    player->ModifyMoney(-(SD2Config.GetFloatDefault("Toxic_Air_Force.TeleGoldCost",0)));
        break;

        case 3016:// Wintergrasp
	    player->CLOSE_GOSSIP_MENU();
	    player->TeleportTo(571, 5212.746582f, 2821.331787f, 409.666840f, 1.840724f);
	    player->ModifyMoney(-(SD2Config.GetFloatDefault("Toxic_Air_Force.TeleGoldCost",0)));
        break;

        case 3017:// Zul'Drak
	    player->CLOSE_GOSSIP_MENU();
	    player->TeleportTo(571, 5560.229980f, -3211.659912f, 371.709015f, 5.550550f);
	    player->ModifyMoney(-(SD2Config.GetFloatDefault("Toxic_Air_Force.TeleGoldCost",0)));
        break;

//////////////////////////////////////////////////KALIMDOR///////////////////////////////////////////////////////////////

        case 3022:// Blackfathom Deeps
	    player->CLOSE_GOSSIP_MENU();
	    player->TeleportTo(1, 4248.72f, 744.35f, -24.67f, 1.34f);
	    player->ModifyMoney(-(SD2Config.GetFloatDefault("Toxic_Air_Force.TeleGoldCost",0)));
        break;
  
        case 3023:// Caverns of Time
	    player->CLOSE_GOSSIP_MENU();
	    player->TeleportTo(1, -8173.66f, -4746.36f, 33.84f, 4.94f);
	    player->ModifyMoney(-(SD2Config.GetFloatDefault("Toxic_Air_Force.TeleGoldCost",0)));
        break;

        case 3024:// Dire Maul
	    player->CLOSE_GOSSIP_MENU();
	    player->TeleportTo(1, -3960.95f, 1130.64f, 161.05f, 0.0f);
	    player->ModifyMoney(-(SD2Config.GetFloatDefault("Toxic_Air_Force.TeleGoldCost",0)));
        break;

        case 3025:// Maraudon
	    player->CLOSE_GOSSIP_MENU();
	    player->TeleportTo(1, -1431.33f, 2962.34f, 98.23f, 4.74f);
	    player->ModifyMoney(-(SD2Config.GetFloatDefault("Toxic_Air_Force.TeleGoldCost",0)));
        break;

        case 3026:// Ragefire Chasm
	    player->CLOSE_GOSSIP_MENU();
	    player->TeleportTo(1, 1814.47f, -4419.46f, -18.78f, 5.28f);
	    player->ModifyMoney(-(SD2Config.GetFloatDefault("Toxic_Air_Force.TeleGoldCost",0)));
        break;

        case 3027:// Razorfen Downs
	    player->CLOSE_GOSSIP_MENU();
	    player->TeleportTo(1, -4657.88f, -2525.59f, 81.4f, 4.16f);
	    player->ModifyMoney(-(SD2Config.GetFloatDefault("Toxic_Air_Force.TeleGoldCost",0)));
        break;
    
        case 3028:// Razorfen Kraul
	    player->CLOSE_GOSSIP_MENU();
	    player->TeleportTo(1, -4463.6f, -1664.53f, 82.26f, 0.85f);
	    player->ModifyMoney(-(SD2Config.GetFloatDefault("Toxic_Air_Force.TeleGoldCost",0)));
        break;

        case 3029:// Ruins of Ahn'Qiraj
	    player->CLOSE_GOSSIP_MENU();
	    player->TeleportTo(1, -8413.33f, 1501.27f, 29.64f, 2.61f);
	    player->ModifyMoney(-(SD2Config.GetFloatDefault("Toxic_Air_Force.TeleGoldCost",0)));
        break;

        case 3030:// Temple of Ahn'Qiraj
	    player->CLOSE_GOSSIP_MENU();
	    player->TeleportTo(1, -8245.837891f, 1983.736206f, 129.071686f, 0.936195f);
	    player->ModifyMoney(-(SD2Config.GetFloatDefault("Toxic_Air_Force.TeleGoldCost",0)));
        break;

        case 3031:// Wailing Caverns
	    player->CLOSE_GOSSIP_MENU();
	    player->TeleportTo(1, -722.53f,-2226.30f,16.94f,2.71f);
	    player->ModifyMoney(-(SD2Config.GetFloatDefault("Toxic_Air_Force.TeleGoldCost",0)));
        break;

        case 3032:// Zul'Farrak
	    player->CLOSE_GOSSIP_MENU();
	    player->TeleportTo(1, -6801.9f, -2890.22f, 8.88f, 6.25f);
	    player->ModifyMoney(-(SD2Config.GetFloatDefault("Toxic_Air_Force.TeleGoldCost",0)));
        break;

//////////////////////////////////////////////////EASTERN KINGDOMS///////////////////////////////////////////////////////////////

        case 3033:// Blackrock Depths
	    player->CLOSE_GOSSIP_MENU();
	    player->TeleportTo(0, -7180.57f, -920.04f, 165.49f, 5.02f);
	    player->ModifyMoney(-(SD2Config.GetFloatDefault("Toxic_Air_Force.TeleGoldCost",0)));
        break;

        case 3034:// Blackrock Spire
	    player->CLOSE_GOSSIP_MENU();
	    player->TeleportTo(0, -7526.77f, -1225.64f, 285.73f, 5.31f);
	    player->ModifyMoney(-(SD2Config.GetFloatDefault("Toxic_Air_Force.TeleGoldCost",0)));
        break;

        case 3035:// Blackwing Lair
	    player->CLOSE_GOSSIP_MENU();
	    player->TeleportTo(469, -7672.61f, -1107.21f, 396.65f, 3.75f);
	    player->ModifyMoney(-(SD2Config.GetFloatDefault("Toxic_Air_Force.TeleGoldCost",0)));
        break;

        case 3036:// Deadmines
	    player->CLOSE_GOSSIP_MENU();
	    player->TeleportTo(0, -11208.2f, 1675.92f, 24.57f, 1.48f);
	    player->ModifyMoney(-(SD2Config.GetFloatDefault("Toxic_Air_Force.TeleGoldCost",0)));
        break;

        case 3037:// Gnomeregan
	    player->CLOSE_GOSSIP_MENU();
	    player->TeleportTo(0, -5163.32f, 927.18f, 257.158f, 1.44f);
	    player->ModifyMoney(-(SD2Config.GetFloatDefault("Toxic_Air_Force.TeleGoldCost",0)));
        break;
 
        case 3038:// Isle Of Quel'Danas
	    player->CLOSE_GOSSIP_MENU();
	    player->TeleportTo(530, 13010.00f, -6907.64f, 9.58f, 4.58f);
	    player->ModifyMoney(-(SD2Config.GetFloatDefault("Toxic_Air_Force.TeleGoldCost",0)));
        break;

        case 3039:// Karazhan
	    player->CLOSE_GOSSIP_MENU();
	    player->TeleportTo(0, -11119.6f, -2011.42f, 47.09f, 0.65f);
	    player->ModifyMoney(-(SD2Config.GetFloatDefault("Toxic_Air_Force.TeleGoldCost",0)));
        break;

        case 3040:// Molten Core
	    player->CLOSE_GOSSIP_MENU();
	    player->TeleportTo(230, 1114.85f, -457.76f, -102.81f, 3.83f);
	    player->ModifyMoney(-(SD2Config.GetFloatDefault("Toxic_Air_Force.TeleGoldCost",0)));
        break;

        case 3042:// Scarlet Monastery
	    player->CLOSE_GOSSIP_MENU();
	    player->TeleportTo(0, 2843.89f,-693.74f,139.32f,5.11f);
	    player->ModifyMoney(-(SD2Config.GetFloatDefault("Toxic_Air_Force.TeleGoldCost",0)));
        break;

        case 3043:// Scholomance
	    player->CLOSE_GOSSIP_MENU();
	    player->TeleportTo(0, 1273.06f, -2574.01f, 92.66f, 2.06f);
	    player->ModifyMoney(-(SD2Config.GetFloatDefault("Toxic_Air_Force.TeleGoldCost",0)));
        break;

        case 3044:// Shadowfang Keep
	    player->CLOSE_GOSSIP_MENU();
	    player->TeleportTo(0, -239.54f, 1550.8f, 76.89f, 1.18f);
	    player->ModifyMoney(-(SD2Config.GetFloatDefault("Toxic_Air_Force.TeleGoldCost",0)));
        break;

        case 3045:// Stratholme
	    player->CLOSE_GOSSIP_MENU();
	    player->TeleportTo(0, 3370.76f, -3343.63f, 142.26f, 5.23f);
	    player->ModifyMoney(-(SD2Config.GetFloatDefault("Toxic_Air_Force.TeleGoldCost",0)));
        break;

        case 3046:// Sunken Temple
	    player->CLOSE_GOSSIP_MENU();
	    player->TeleportTo(0, -10346.92f, -3851.90f, -43.41f, 6.09f);
	    player->ModifyMoney(-(SD2Config.GetFloatDefault("Toxic_Air_Force.TeleGoldCost",0)));
        break;

        case 3047:// The Stockade
	    player->CLOSE_GOSSIP_MENU();
	    player->TeleportTo(0, -8766.89f, 844.6f, 88.43f, 0.69f);
	    player->ModifyMoney(-(SD2Config.GetFloatDefault("Toxic_Air_Force.TeleGoldCost",0)));
        break;
 
        case 3048:// Uldaman
	    player->CLOSE_GOSSIP_MENU();
	    player->TeleportTo(0, -6070.72f, -2955.33f, 209.78f, 0.05f);
	    player->ModifyMoney(-(SD2Config.GetFloatDefault("Toxic_Air_Force.TeleGoldCost",0)));
        break;

        case 3049:// Zul'Aman
	    player->CLOSE_GOSSIP_MENU();
	    player->TeleportTo(530, 6851.09f, -7979.71f, 183.54f, 4.72f);
	    player->ModifyMoney(-(SD2Config.GetFloatDefault("Toxic_Air_Force.TeleGoldCost",0)));
        break;

        case 3050:// Zul'Gurub
	    player->CLOSE_GOSSIP_MENU();
	    player->TeleportTo(0, -11916.4f, -1216.23f, 92.28f, 4.75f);
	    player->ModifyMoney(-(SD2Config.GetFloatDefault("Toxic_Air_Force.TeleGoldCost",0)));
        break;

//////////////////////////////////////////////////OUTLAND///////////////////////////////////////////////////////////////

        case 3051:// Auchindoun
	    player->CLOSE_GOSSIP_MENU();
	    player->TeleportTo(530, -3322.92f, 4931.02f, -100.56f, 1.86f);
	    player->ModifyMoney(-(SD2Config.GetFloatDefault("Toxic_Air_Force.TeleGoldCost",0)));
        break;

        case 3052:// Black Temple
	    player->CLOSE_GOSSIP_MENU();
	    player->TeleportTo(530, -3649.1f, 317.33f, 35.19f, 2.97f);
	    player->ModifyMoney(-(SD2Config.GetFloatDefault("Toxic_Air_Force.TeleGoldCost",0)));
        break;

        case 3053:// Coilfang Reservoir
	    player->CLOSE_GOSSIP_MENU();
	    player->TeleportTo(530, 721.08f, 6846.77f, -68.75f, 0.34f);
	    player->ModifyMoney(-(SD2Config.GetFloatDefault("Toxic_Air_Force.TeleGoldCost",0)));
        break;

        case 3054:// Gruul's Lair
	    player->CLOSE_GOSSIP_MENU();
	    player->TeleportTo(530, 3539.01f, 5082.36f, 1.69f, 0.0f);
	    player->ModifyMoney(-(SD2Config.GetFloatDefault("Toxic_Air_Force.TeleGoldCost",0)));
        break;

        case 3055:// Hellfire Citadel
	    player->CLOSE_GOSSIP_MENU();
	    player->TeleportTo(530, -292.71f, 3146.77f, 31.60f, 2.05f);
	    player->ModifyMoney(-(SD2Config.GetFloatDefault("Toxic_Air_Force.TeleGoldCost",0)));
        break;

        case 3056:// Tempest Keep
	    player->CLOSE_GOSSIP_MENU();
	    player->TeleportTo(530, 3087.62f, 1376.27f, 184.8f, 4.63f);
	    player->ModifyMoney(-(SD2Config.GetFloatDefault("Toxic_Air_Force.TeleGoldCost",0)));
        break;

//////////////////////////////////////////////////NORTHREND///////////////////////////////////////////////////////////////

        case 3057:// Ahn'Kahet
	    player->CLOSE_GOSSIP_MENU();
	    player->TeleportTo(571, 3646.76f, 2045.17f, 1.79f, 4.37f);
	    player->ModifyMoney(-(SD2Config.GetFloatDefault("Toxic_Air_Force.TeleGoldCost",0)));
        break;

        case 3058:// Azjol-Nerub
	    player->CLOSE_GOSSIP_MENU();
	    player->TeleportTo(571, 3675.43f, 2169.00f, 35.90f, 2.29f);
	    player->ModifyMoney(-(SD2Config.GetFloatDefault("Toxic_Air_Force.TeleGoldCost",0)));
        break;

        case 3059:// Drak'Tharon Keep
	    player->CLOSE_GOSSIP_MENU();
	    player->TeleportTo(571, 4450.86f, -2045.25f, 162.83f, 0.00f);
	    player->ModifyMoney(-(SD2Config.GetFloatDefault("Toxic_Air_Force.TeleGoldCost",0)));
        break;

        case 3060:// Gun'Drak
	    player->CLOSE_GOSSIP_MENU();
	    player->TeleportTo(571, 6937.54f, -4455.98f, 450.68f, 1.00f);
	    player->ModifyMoney(-(SD2Config.GetFloatDefault("Toxic_Air_Force.TeleGoldCost",0)));
        break;

        case 3061:// Icecrown Citadel
	    player->CLOSE_GOSSIP_MENU();
	    player->TeleportTo(571, 6139.24f, 2233.72f, 510.79f, 3.56f);
	    player->ModifyMoney(-(SD2Config.GetFloatDefault("Toxic_Air_Force.TeleGoldCost",0)));
        break;

        case 3062:// Naxxramas
	    player->CLOSE_GOSSIP_MENU();
	    player->TeleportTo(571, 3668.72f, -1262.46f, 243.622f, 4.785f);
	    player->ModifyMoney(-(SD2Config.GetFloatDefault("Toxic_Air_Force.TeleGoldCost",0)));
        break;

        case 3063:// Onyxia's Lair
	    player->CLOSE_GOSSIP_MENU();
	    player->TeleportTo(1, -4707.44f, -3726.82f, 54.6723f, 3.8f);
	    player->ModifyMoney(-(SD2Config.GetFloatDefault("Toxic_Air_Force.TeleGoldCost",0)));
        break;

        case 3064:// The Nexus
	    player->CLOSE_GOSSIP_MENU();
	    player->TeleportTo(571, 3789.95f, 6961.48f, 104.23f, 0.28f);
	    player->ModifyMoney(-(SD2Config.GetFloatDefault("Toxic_Air_Force.TeleGoldCost",0)));
        break;

        case 3065:// The Obsidian Sanctum
	    player->CLOSE_GOSSIP_MENU();
	    player->TeleportTo(571, 3625.78f, 280.4f, -120.14f, 3.25f);
	    player->ModifyMoney(-(SD2Config.GetFloatDefault("Toxic_Air_Force.TeleGoldCost",0)));
        break;

        case 3066:// Ulduar
	    player->CLOSE_GOSSIP_MENU();
	    player->TeleportTo(571, 1219.72f, -4865.28f, 41.25f, 0.31f);
	    player->ModifyMoney(-(SD2Config.GetFloatDefault("Toxic_Air_Force.TeleGoldCost",0)));
        break;

        case 3067:// Utgarde Keep
	    player->CLOSE_GOSSIP_MENU();
	    player->TeleportTo(571, 1245.69f, -4856.59f, 216.86f, 3.45f);
	    player->ModifyMoney(-(SD2Config.GetFloatDefault("Toxic_Air_Force.TeleGoldCost",0)));
        break;

        case 3068:// Utgarde Pinnacle
	    player->CLOSE_GOSSIP_MENU();
	    player->TeleportTo(571, 8976.24f, -1281.33f, 1059.01f, 0.58f);
	    player->ModifyMoney(-(SD2Config.GetFloatDefault("Toxic_Air_Force.TeleGoldCost",0)));
        break;

        case 3069:// Violet Hold
	    player->CLOSE_GOSSIP_MENU();
	    player->TeleportTo(571, 5679.82f, 486.80f, 652.40f, 4.08f);
	    player->ModifyMoney(-(SD2Config.GetFloatDefault("Toxic_Air_Force.TeleGoldCost",0)));
        break;
/////////////////////////////////////////Config sd2//////////////////////////////////////////////
        case 3080: //Shopping mall (if enabled in scriptdev2.conf)
	    player->CLOSE_GOSSIP_MENU();
	    // Read coordinates from config file
	    player->TeleportTo(SD2Config.GetFloatDefault("MapIDFFA",13),SD2Config.GetFloatDefault("X_posFFA",0),SD2Config.GetFloatDefault("Y_posFFA",0),SD2Config.GetFloatDefault("Z_posFFA",0),0);
	    player->ModifyMoney(-(SD2Config.GetFloatDefault("Toxic_Air_Force.TeleGoldCost",0)));
        break;
		
		case 3081: //Shopping mall (if enabled in scriptdev2.conf)
	    player->CLOSE_GOSSIP_MENU();
	    // Read coordinates from config file
	    player->TeleportTo(SD2Config.GetFloatDefault("MapIDSHOP",13),SD2Config.GetFloatDefault("X_posSHOP",0),SD2Config.GetFloatDefault("Y_posSHOP",0),SD2Config.GetFloatDefault("Z_posSHOP",0),0);
	    player->ModifyMoney(-(SD2Config.GetFloatDefault("Toxic_Air_Force.TeleGoldCost",0)));
        break;
		
		case 3082: //Shopping mall (if enabled in scriptdev2.conf)
	    player->CLOSE_GOSSIP_MENU();
	    // Read coordinates from config file
	    player->TeleportTo(SD2Config.GetFloatDefault("MapIDDISCO",13),SD2Config.GetFloatDefault("X_posDISCO",0),SD2Config.GetFloatDefault("Y_posDISCO",0),SD2Config.GetFloatDefault("Z_posDISCO",0),0);
	    player->ModifyMoney(-(SD2Config.GetFloatDefault("Toxic_Air_Force.TeleGoldCost",0)));
        break;

		case 3083: //Shopping mall (if enabled in scriptdev2.conf)
	    player->CLOSE_GOSSIP_MENU();
	    // Read coordinates from config file
	    player->TeleportTo(SD2Config.GetFloatDefault("MapIDMETIER",13),SD2Config.GetFloatDefault("X_posMETIER",0),SD2Config.GetFloatDefault("Y_posMETIER",0),SD2Config.GetFloatDefault("Z_posMETIER",0),0);
	    player->ModifyMoney(-(SD2Config.GetFloatDefault("Toxic_Air_Force.TeleGoldCost",0)));
        break;
		
		case 3084: //Shopping mall (if enabled in scriptdev2.conf)
	    player->CLOSE_GOSSIP_MENU();
	    // Read coordinates from config file
	    player->TeleportTo(SD2Config.GetFloatDefault("MapIDCOM",13),SD2Config.GetFloatDefault("X_posCOM",0),SD2Config.GetFloatDefault("Y_posCOM",0),SD2Config.GetFloatDefault("Z_posCOM",0),0);
	    player->ModifyMoney(-(SD2Config.GetFloatDefault("Toxic_Air_Force.TeleGoldCost",0)));
        break;
		
		case 3086: //Shopping mall (if enabled in scriptdev2.conf)
	    player->CLOSE_GOSSIP_MENU();
	    // Read coordinates from config file
	    player->TeleportTo(SD2Config.GetFloatDefault("MapIDXPA",13),SD2Config.GetFloatDefault("X_posXPA",0),SD2Config.GetFloatDefault("Y_posXPA",0),SD2Config.GetFloatDefault("Z_posXPA",0),0);
	    player->ModifyMoney(-(SD2Config.GetFloatDefault("Toxic_Air_Force.TeleGoldCost",0)));
        break;
		
		case 3087: //Shopping mall (if enabled in scriptdev2.conf)
	    player->CLOSE_GOSSIP_MENU();
	    // Read coordinates from config file
	    player->TeleportTo(SD2Config.GetFloatDefault("MapIDXPB",13),SD2Config.GetFloatDefault("X_posXPB",0),SD2Config.GetFloatDefault("Y_posXPB",0),SD2Config.GetFloatDefault("Z_posXPB",0),0);
	    player->ModifyMoney(-(SD2Config.GetFloatDefault("Toxic_Air_Force.TeleGoldCost",0)));
        break;
		
		case 3088: //Shopping mall (if enabled in scriptdev2.conf)
	    player->CLOSE_GOSSIP_MENU();
	    // Read coordinates from config file
	    player->TeleportTo(SD2Config.GetFloatDefault("MapIDXPC",13),SD2Config.GetFloatDefault("X_posXPC",0),SD2Config.GetFloatDefault("Y_posXPC",0),SD2Config.GetFloatDefault("Z_posXPC",0),0);
	    player->ModifyMoney(-(SD2Config.GetFloatDefault("Toxic_Air_Force.TeleGoldCost",0)));
        break;
		
		case 3089: //Shopping mall (if enabled in scriptdev2.conf)
	    player->CLOSE_GOSSIP_MENU();
	    // Read coordinates from config file
	    player->TeleportTo(SD2Config.GetFloatDefault("MapIDXPD",13),SD2Config.GetFloatDefault("X_posXPD",0),SD2Config.GetFloatDefault("Y_posXPD",0),SD2Config.GetFloatDefault("Z_posXPD",0),0);
	    player->ModifyMoney(-(SD2Config.GetFloatDefault("Toxic_Air_Force.TeleGoldCost",0)));
        break;
		
		case 3096: //Shopping mall (if enabled in scriptdev2.conf)
	    player->CLOSE_GOSSIP_MENU();
	    // Read coordinates from config file
	    player->TeleportTo(SD2Config.GetFloatDefault("MapIDXPE",13),SD2Config.GetFloatDefault("X_posXPE",0),SD2Config.GetFloatDefault("Y_posXPE",0),SD2Config.GetFloatDefault("Z_posXPE",0),0);
	    player->ModifyMoney(-(SD2Config.GetFloatDefault("Toxic_Air_Force.TeleGoldCost",0)));
        break;
		
		case 3090: //Shopping mall (if enabled in scriptdev2.conf)
	    player->CLOSE_GOSSIP_MENU();
	    // Read coordinates from config file
	    player->TeleportTo(SD2Config.GetFloatDefault("MapIDMJ",13),SD2Config.GetFloatDefault("X_posMJ",0),SD2Config.GetFloatDefault("Y_posMJ",0),SD2Config.GetFloatDefault("Z_posMJ",0),0);
	    player->ModifyMoney(-(SD2Config.GetFloatDefault("Toxic_Air_Force.TeleGoldCost",0)));
        break;
		
		case 3091: //Shopping mall (if enabled in scriptdev2.conf)
	    player->CLOSE_GOSSIP_MENU();
	    // Read coordinates from config file
	    player->TeleportTo(SD2Config.GetFloatDefault("MapIDCUBE",13),SD2Config.GetFloatDefault("X_posCUBE",0),SD2Config.GetFloatDefault("Y_posCUBE",0),SD2Config.GetFloatDefault("Z_posCUBE",0),0);
	    player->ModifyMoney(-(SD2Config.GetFloatDefault("Toxic_Air_Force.TeleGoldCost",0)));
        break;
		
		case 3092: //Shopping mall (if enabled in scriptdev2.conf)
	    player->CLOSE_GOSSIP_MENU();
	    // Read coordinates from config file
	    player->TeleportTo(SD2Config.GetFloatDefault("MapIDZT",13),SD2Config.GetFloatDefault("X_posZT",0),SD2Config.GetFloatDefault("Y_posZT",0),SD2Config.GetFloatDefault("Z_posZT",0),0);
	    player->ModifyMoney(-(SD2Config.GetFloatDefault("Toxic_Air_Force.TeleGoldCost",0)));
        break;
		
		case 3093: //Shopping mall (if enabled in scriptdev2.conf)
	    player->CLOSE_GOSSIP_MENU();
	    // Read coordinates from config file
	    player->TeleportTo(SD2Config.GetFloatDefault("MapIDIR",13),SD2Config.GetFloatDefault("X_posIR",0),SD2Config.GetFloatDefault("Y_posIR",0),SD2Config.GetFloatDefault("Z_posIR",0),0);
	    player->ModifyMoney(-(SD2Config.GetFloatDefault("Toxic_Air_Force.TeleGoldCost",0)));
        break;
		
		case 3094: //Shopping mall (if enabled in scriptdev2.conf)
	    player->CLOSE_GOSSIP_MENU();
	    // Read coordinates from config file
	    player->TeleportTo(SD2Config.GetFloatDefault("MapIDCA",13),SD2Config.GetFloatDefault("X_posCA",0),SD2Config.GetFloatDefault("Y_posCA",0),SD2Config.GetFloatDefault("Z_posCA",0),0);
	    player->ModifyMoney(-(SD2Config.GetFloatDefault("Toxic_Air_Force.TeleGoldCost",0)));
        break;
		
		case 3095: //Shopping mall (if enabled in scriptdev2.conf)
	    player->CLOSE_GOSSIP_MENU();
	    // Read coordinates from config file
	    player->TeleportTo(SD2Config.GetFloatDefault("MapIDVDT",13),SD2Config.GetFloatDefault("X_posVDT",0),SD2Config.GetFloatDefault("Y_posVDT",0),SD2Config.GetFloatDefault("Z_posVDT",0),0);
	    player->ModifyMoney(-(SD2Config.GetFloatDefault("Toxic_Air_Force.TeleGoldCost",0)));
        break;
			

    } // end of switch
} //end of function
bool GossipSelect_Toxic_Air_Force(Player* player, Creature* pCreature, uint32 uiSender, uint32 uiAction)
{
	// Main menu
	if (uiSender == GOSSIP_SENDER_MAIN)
	SendDefaultMenu_Toxic_Air_Force(player, pCreature, uiAction);

return true;
}
void AddSC_Toxic_Air_Force()
{
    Script *newscript;

	newscript = new Script;
    newscript->Name = "Toxic_Air_Force";
    newscript->pGossipHello = &GossipHello_Toxic_Air_Force;
    newscript->pGossipSelect = &GossipSelect_Toxic_Air_Force;
    newscript->RegisterSelf();
}