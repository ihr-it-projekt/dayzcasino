static bool DAYZ_CASINO_DEBUG = true;
static string CASINO_CONFIG_PATH = "$profile:dayZCasinoConfig.json";
static int DAYZ_CASINO_SEND_MESSAGE_TO_PLAYER = 99995858587;
static int DAYZ_CASINO_SHUFFEL_BET_DICE = 99995858588;
static int DAYZ_CASINO_RESPONSE_SHUFFEL_BET_DICE = 99995858589;
static int DAYZ_CASINO_RESPONSE_SHUFFEL_BET_DICE_NOT_ENOUGH_BALANCE = 999958585;
static int DAYZ_CASINO_GET_CASINO_CONFIG = 99995858590;
static int DAYZ_CASINO_GET_CASINO_CONFIG_RESPONSE = 99995858591;
static int DAYZ_CASINO_BLACK_JACK_START_GAME = 99995858592;
static int DAYZ_CASINO_BLACK_JACK_START_GAME_RESPONSE = 99995858594;
static int DAYZ_CASINO_BLACK_JACK_START_NEXT_CARD_PLAYER = 99995858595;
static int DAYZ_CASINO_BLACK_JACK_START_NEXT_CARD_PLAYER_RESPONSE = 99995858596;
static int DAYZ_CASINO_BLACK_JACK_NOT_ENOUGH_CHIPS = 99995858593;
static int DAYZ_CASINO_DISTANCE_TO_GAME = 2;

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
		if (!casinoConfig.positionBlackJack) {
			casinoConfig.positionBlackJack = "7237.358398 254.556000 6983.053223";
		}
		
		DebugMessageCasino("has config loaded" + casinoConfig.positionDice);
	} else {
		DebugMessageCasino("config not exists, create new one");
		casinoConfig.positionDice = "7247.358398 254.556000 6983.053223";
		casinoConfig.positionBlackJack = "7237.358398 254.556000 6983.053223";
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