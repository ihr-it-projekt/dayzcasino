modded class MissionGameplay 
{
	private ref CasinoConfig casinoConfig;
	private ref BlackJackClientEventHandler blackJackClientEventHandler;
	private ref BetDiceClientEventHandler betDiceClientEventHandler;
	private ref LuckyWheelClientEventHandler luckyWheelClientEventHandler;
	private ref RatRaceClientEventHandler ratRaceClientEventHandler;

	void MissionGameplay() {
		DebugMessageCasino("init Mission MissionGameplay");
		
		GetDayZGame().Event_OnRPC.Insert(HandleEventsCasino);
        Param1<DayZPlayer> paramGetConfig = new Param1<DayZPlayer>(GetGame().GetPlayer());
	    GetGame().RPCSingleParam(paramGetConfig.param1, DAYZ_CASINO_GET_CASINO_CONFIG, paramGetConfig, true);
	}
	
	void ~MissionGameplay() {
		GetDayZGame().Event_OnRPC.Remove(HandleEventsCasino);
	}
	
	void HandleEventsCasino(PlayerIdentity sender, Object target, int rpc_type, ParamsReadContext ctx) {
		if (rpc_type == DAYZ_CASINO_GET_CASINO_CONFIG_RESPONSE) {
			DebugMessageCasino("player receive config");
			Param1 <ref CasinoConfig> casinoConfigParam;
			if (ctx.Read(casinoConfigParam)){
				casinoConfig = casinoConfigParam.param1;
				DebugMessageCasino("player load config");
				GameMenu.Get(casinoConfig);

                blackJackClientEventHandler = new BlackJackClientEventHandler();
                betDiceClientEventHandler = new BetDiceClientEventHandler();
                luckyWheelClientEventHandler = new LuckyWheelClientEventHandler();
				ratRaceClientEventHandler = new RatRaceClientEventHandler();
			}
		} else if (HasClientEventHandler()) {
            blackJackClientEventHandler.HandleEvents(GameMenu.Get().GetBlackJackMenu(), sender, target, rpc_type, ctx);
            betDiceClientEventHandler.HandleEvents(GameMenu.Get().GetBetDiceMenu(), sender, target, rpc_type, ctx);
            luckyWheelClientEventHandler.HandleEvents(GameMenu.Get().GetLuckyWheelMenu(), sender, target, rpc_type, ctx);
            ratRaceClientEventHandler.HandleEvents(GameMenu.Get().GetRatRaceMenu(), sender, target, rpc_type, ctx);
		} else {
            DebugMessageCasino("NO game event handler registered");
		}
	}
	
	override void OnUpdate(float timeslice)
	{
		super.OnUpdate(timeslice);
		autoptr DayZPlayer player = GetGame().GetPlayer();

        if(player) {
            UAInput localInput = GetUApi().GetInputByName("UAInputPlayCasinoGame");
            if (localInput.LocalClick() && GameMenu.Get()){
				BaseMenu currentGameMenu = GameMenu.Get().GetGameMenu(player);
				if (GetGame().GetUIManager().GetMenu() == null && currentGameMenu && !currentGameMenu.isMenuOpen && player.IsAlive()) {
					DebugMessageCasino("key press open");
                    currentGameMenu.Init();
					currentGameMenu.OnShow();
				}
			}

			if (GameMenu.Get() && GameMenu.Get().CanOpenHintToOpenGameMenu(player)){
                GameMenu.Get().GetGameHintMenu().OnShow();
			} else if (GameMenu.Get()) {
                GameMenu.Get().GetGameHintMenu().OnHide();
			}
		}
	}

	private bool HasClientEventHandler() {
	    return null != blackJackClientEventHandler && null != betDiceClientEventHandler && null != luckyWheelClientEventHandler && null != ratRaceClientEventHandler;
	}
}
