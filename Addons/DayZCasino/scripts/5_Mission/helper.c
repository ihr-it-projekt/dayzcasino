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