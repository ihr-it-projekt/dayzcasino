static void DebugMessageCasino(string message) {
    if (DAYZ_CASINO_DEBUG) {
        Print("[DayZCasino] " + message);
        GetGame().AdminLog("[DayZCasino] " + message);
    }
}

static CasinoConfig GetCasinoConfig() {
	ref CasinoConfig casinoConfig = new CasinoConfig;
	
	if (FileExist(CASINO_CONFIG_PATH)) {
		DebugMessageCasino("try load config");
		JsonFileLoader<CasinoConfig>.JsonLoadFile(CASINO_CONFIG_PATH, casinoConfig);
		
		if (!casinoConfig.positionDice) {
            casinoConfig.positionDice = "7247.358398 254.556000 6983.053223";
        }
        if (!casinoConfig.orientationDice) {
			casinoConfig.orientationDice =  "119.999916 0.000000 0.000000" ;
		}
		if (!casinoConfig.positionBlackJack) {
            casinoConfig.positionBlackJack = "7246.056152 254.571564 6986.960938";
        }
        if (!casinoConfig.orientationBlackJack) {
            casinoConfig.orientationBlackJack = "13.000005 0.000000 0.000000" ;
		}

		DebugMessageCasino("has config loaded" + casinoConfig.positionDice);
	} else {
		DebugMessageCasino("config not exists, create new one");
		casinoConfig.positionDice = "7247.358398 254.556000 6983.053223";
        casinoConfig.orientationDice =  "119.999916 0.000000 0.000000" ;
		casinoConfig.positionBlackJack = "7237.358398 254.556000 6983.053223";
        casinoConfig.orientationBlackJack = "13.000005 0.000000 0.000000" ;
	}
	
	JsonFileLoader<CasinoConfig>.JsonSaveFile(CASINO_CONFIG_PATH, casinoConfig);
	DebugMessageCasino("config has loaded");
	return casinoConfig;
}

static bool IsServerCasino() {
    return GetGame().IsServer();
}

static void SendMessageToPlayerCasino(string message, DayZPlayer player) {
    if (GetGame().IsServer()) {
        Param1 <string> message_param = new Param1<string>(message);
        GetGame().RPCSingleParam(player, ERPCs.RPC_USER_ACTION_MESSAGE, message_param, true, player.GetIdentity());
    } else {
        Param2 <DayZPlayer, string> parameterMessage = new Param2<DayZPlayer, string>(GetGame().GetPlayer(), message);
        GetGame().RPCSingleParam(player, DAYZ_CASINO_SEND_MESSAGE_TO_PLAYER, parameterMessage, true);
    }
}