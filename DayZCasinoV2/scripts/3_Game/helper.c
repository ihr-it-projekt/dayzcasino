
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

