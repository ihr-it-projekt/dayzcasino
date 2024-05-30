class RatRaceClientEventHandler {
    void HandleEvents(RatRaceMenu rateRaceMenu, PlayerIdentity sender, Object target, int rpc_type, ParamsReadContext ctx) {
        if(IsServerCasino() || !rateRaceMenu.isMenuOpen) {
            return;
        } else if(rpc_type == DAYZ_CASINO_RESPONSE_NEW_RAT_RACE) {
            Param1<ref Race> startRace;
            if(ctx.Read(startRace)) {
                rateRaceMenu.ResetGame(Race.Cast(startRace.param1));
            }
        } else if(rpc_type == DAYZ_CASINO_RESPONSE_START_RAT_RACE) {
            Param3<int, int, ref Race> parameterShuffleResponse;
            if(ctx.Read(parameterShuffleResponse)) {
                rateRaceMenu.lastWinChips = parameterShuffleResponse.param1;
                rateRaceMenu.currentAmount = parameterShuffleResponse.param2;
                rateRaceMenu.AnimateRace(parameterShuffleResponse.param3);
            }
        } else if(rpc_type == DAYZ_CASINO_RESPONSE_RAT_RACE_NOT_ENOUGH_BALANCE) {
            rateRaceMenu.EndGame();
        }
    }
};