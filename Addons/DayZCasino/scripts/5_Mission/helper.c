static void DebugMessageCasino(string message) {
    if (DAYZ_CASINO_DEBUG) {
        Print("DayzCasino " + message);
        GetGame().AdminLog("<DayzCasino>" + message);
    }
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