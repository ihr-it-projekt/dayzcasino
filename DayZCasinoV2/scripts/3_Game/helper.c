static void DebugMessageCasino(string message) {
    if(DAYZ_CASINO_DEBUG) {
        Print("[DayZCasino] " + message);
        GetGame().AdminLog("[DayZCasino] " + message);
    }
}

static bool IsServerCasino() {
    return GetGame().IsServer();
}
static bool IsMultiplayerCasino() {
    return GetGame().IsMultiplayer();
}

static bool IsServerAndMultiplayerCasino() {
    return IsMultiplayerCasino() && IsServerCasino();
}
static bool IsClientOrNotMultiplayerCasino() {
    return !IsMultiplayerCasino() || GetGame().IsClient();
}

