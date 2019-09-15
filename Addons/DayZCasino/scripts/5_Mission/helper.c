static bool DAYZ_CASINO_DEBUG = true;
static string CASINO_CONFIG_PATH = "$profile:dayZCasinoConfig.json";
static int DAYZ_CASINO_SEND_MESSAGE_TO_PLAYER = 99995858587;
static int DAYZ_CASINO_SHUFFEL_BET_DICE = 99995858588;
static int DAYZ_CASINO_RESPONSE_SHUFFEL_BET_DICE = 99995858589;
static int DAYZ_CASINO_RESPONSE_SHUFFEL_BET_DICE_NOT_ENOUGH_BALANCE = 999958585;
static int DAYZ_CASINO_GET_CASINO_CONFIG = 99995858590;
static int DAYZ_CASINO_GET_CASINO_CONFIG_RESPONSE = 99995858591;
static int DAYZ_CASINO_DISTANCE_TO_GAME = 2;

static void DebugMessageCasino(string message) {
    if (DAYZ_CASINO_DEBUG) {
        Print("[DayzCasino] " + message);
        GetGame().AdminLog("[DayzCasino] " + message);
    }
}

static CasinoConfig GetCasinoConfig() {
	ref CasinoConfig casinoConfig = new CasinoConfig;
	
	if (FileExist(CASINO_CONFIG_PATH)) {
		JsonFileLoader<CasinoConfig>.JsonLoadFile(CASINO_CONFIG_PATH, casinoConfig);
		DebugMessageCasino("has config loaded" + casinoConfig.positionDice);
	} else {
		casinoConfig.positionDice = "7190.633789 254.161453 6966.459473";
		JsonFileLoader<CasinoConfig>.JsonSaveFile(CASINO_CONFIG_PATH, casinoConfig);
		DebugMessageCasino("has created config" + casinoConfig.positionDice);
	}
	
	return casinoConfig;
}

static bool IsServerCasino() {
    return GetGame().IsServer();
}

static void SendMessageToPlayerCasino(string message, PlayerBase player) {

    if (GetGame().IsServer()) {
        Param1 <string> message_param = new Param1<string>(message);
        GetGame().RPCSingleParam(player, ERPCs.RPC_USER_ACTION_MESSAGE, message_param, true, player.GetIdentity());
    } else {
        Param2 <PlayerBase, string> parameterMessage = new Param2<PlayerBase, string>(GetGame().GetPlayer(), message);
        GetGame().RPCSingleParam(player, DAYZ_CASINO_SEND_MESSAGE_TO_PLAYER, parameterMessage, true);
    }
}