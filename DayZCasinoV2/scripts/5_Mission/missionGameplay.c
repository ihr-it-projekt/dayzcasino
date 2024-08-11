modded class MissionGameplay {
    private ref BlackJackClientEventHandler blackJackClientEventHandler;
    private ref BetDiceClientEventHandler betDiceClientEventHandler;
    private ref LuckyWheelClientEventHandler luckyWheelClientEventHandler;
    private ref RatRaceClientEventHandler ratRaceClientEventHandler;

    override void OnMissionStart() {
        super.OnInit();
        GetDayZGame().Event_OnRPC.Insert(HandleEventsCasino);
        Param1<DayZPlayer> paramGetConfig = new Param1<DayZPlayer>(GetGame().GetPlayer());
        GetGame().RPCSingleParam(paramGetConfig.param1, DAYZ_CASINO_GET_CASINO_CONFIG, paramGetConfig, true);
    }

    override void OnMissionFinish() {
        super.OnMissionFinish();
        GetDayZGame().Event_OnRPC.Remove(HandleEventsCasino);
    }

    void HandleEventsCasino(PlayerIdentity sender, Object target, int rpc_type, ParamsReadContext ctx) {
        if(rpc_type == DAYZ_CASINO_GET_CASINO_CONFIG_RESPONSE) {
            Param1 <ref CasinoConfig> casinoConfigParam;
            if(ctx.Read(casinoConfigParam)) {
                CasinoConfig.instance = casinoConfigParam.param1;
                GameMenu.Get(CasinoConfig.instance);

                blackJackClientEventHandler = new BlackJackClientEventHandler();
                betDiceClientEventHandler = new BetDiceClientEventHandler();
                luckyWheelClientEventHandler = new LuckyWheelClientEventHandler();
                ratRaceClientEventHandler = new RatRaceClientEventHandler();
            }
        } else if(HasClientEventHandler()) {
            blackJackClientEventHandler.HandleEvents(GameMenu.Get().GetBlackJackMenu(), sender, target, rpc_type, ctx);
            betDiceClientEventHandler.HandleEvents(GameMenu.Get().GetBetDiceMenu(), sender, target, rpc_type, ctx);
            luckyWheelClientEventHandler.HandleEvents(GameMenu.Get().GetLuckyWheelMenu(), sender, target, rpc_type, ctx);
            ratRaceClientEventHandler.HandleEvents(GameMenu.Get().GetRatRaceMenu(), sender, target, rpc_type, ctx);
        }
    }

    private bool HasClientEventHandler() {
        return null != blackJackClientEventHandler && null != betDiceClientEventHandler && null != luckyWheelClientEventHandler && null != ratRaceClientEventHandler;
    }
}
