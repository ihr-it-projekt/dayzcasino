class GameMenu
{
	private ref BetDiceMenu betDiceMenu;
	private ref BlackJackMenu blackJackMenu;
	private ref LuckyWheelMenu luckyWheelMenu;
	private ref RatRaceMenu ratRaceMenu;
	private ref GameHint gameHint;
	private CasinoConfig casinoConfig;
	
	void GameMenu(CasinoConfig casinoConfigExt) {
		DebugMessageCasino("Load GameMenu");
		casinoConfig = casinoConfigExt;
		DebugMessageCasino("check config dice menu" + casinoConfig.positionDice);
	}

    BetDiceMenu GetBetDiceMenu() {
        if (!betDiceMenu) {
            DebugMessageCasino("No selectedMenu");
            betDiceMenu = new BetDiceMenu();
			betDiceMenu.SetConfig(casinoConfig);
        }

	    return betDiceMenu;
	}

    LuckyWheelMenu GetLuckyWheelMenu() {
        if (!luckyWheelMenu) {
            DebugMessageCasino("No selectedMenu");
            luckyWheelMenu = new LuckyWheelMenu();
            luckyWheelMenu.SetConfig(casinoConfig);
        }

	    return luckyWheelMenu;
	}

    BlackJackMenu GetBlackJackMenu() {
        if (!blackJackMenu) {
            DebugMessageCasino("No selectedMenu");
            blackJackMenu = new BlackJackMenu();
			blackJackMenu.SetConfig(casinoConfig);
        }

	    return blackJackMenu;
	}
	
	RatRaceMenu GetRatRaceMenu() {
        if (!ratRaceMenu) {
            DebugMessageCasino("No selectedMenu");
            ratRaceMenu = new RatRaceMenu();
			ratRaceMenu.SetConfig(casinoConfig);
        }

	    return ratRaceMenu;
	}

    GameHint GetGameHintMenu() {
        if (!gameHint) {
            DebugMessageCasino("No selectedMenu");
            gameHint = new GameHint();
        }

	    return gameHint;
	}

	BaseMenu GetGameMenu(DayZPlayer player) {
		vector posPlayer = player.GetPosition();

		float playerDistanceToGamePositionBetDice = vector.Distance(casinoConfig.positionDice, posPlayer);
		if (casinoConfig.enabledDice && playerDistanceToGamePositionBetDice <= DAYZ_CASINO_DISTANCE_TO_GAME)
		{
			DebugMessageCasino("in near of bet dice");
			
			return GetBetDiceMenu();
		}
		
		float playerDistanceToGamePositionBlackJack = vector.Distance(casinoConfig.positionBlackJack, posPlayer);
		
		if (casinoConfig.enabledBlackJack && playerDistanceToGamePositionBlackJack <= DAYZ_CASINO_DISTANCE_TO_GAME)
		{
			DebugMessageCasino("in near of black jack");
			
			return GetBlackJackMenu();
		}

        float playerDistanceToGamePositionLuckyWheelMenu = vector.Distance(casinoConfig.positionLuckyWheel, posPlayer);

        if (casinoConfig.enabledLuckyWheel && playerDistanceToGamePositionLuckyWheelMenu <= DAYZ_CASINO_DISTANCE_TO_GAME)
        {
            DebugMessageCasino("in near of lucky wheel");

            return GetLuckyWheelMenu();
        }
		
		float playerDistanceToGamePositionRatRaceMenu = vector.Distance(casinoConfig.positionRatRace, posPlayer);
		
		if (casinoConfig.enabledRatRace && playerDistanceToGamePositionRatRaceMenu <= DAYZ_CASINO_DISTANCE_TO_GAME)
        {
            DebugMessageCasino("in near of rat race");

            return GetRatRaceMenu();
        }

		DebugMessageCasino("not in near of a game.");
		return null;
	}

	bool CanOpenHintToOpenGameMenu(DayZPlayer player) {
        vector posPlayer = player.GetPosition();

        if(casinoConfig.enabledDice && vector.Distance(casinoConfig.positionDice, posPlayer) <= DAYZ_CASINO_DISTANCE_TO_GAME){
			return true;
		} else if(casinoConfig.enabledLuckyWheel && vector.Distance(casinoConfig.positionLuckyWheel, posPlayer) <= DAYZ_CASINO_DISTANCE_TO_GAME){
			return true;
		} else if(casinoConfig.enabledBlackJack && vector.Distance(casinoConfig.positionBlackJack, posPlayer) <= DAYZ_CASINO_DISTANCE_TO_GAME){
			return true;
		} else if(casinoConfig.enabledRatRace && vector.Distance(casinoConfig.positionRatRace, posPlayer) <= DAYZ_CASINO_DISTANCE_TO_GAME){
			return true;
		} 
        
        return false;
	}
	
	void CloseAllMenu(){
		if (betDiceMenu) {
			betDiceMenu.Close();
		}
		if (blackJackMenu) {
			blackJackMenu.Close();
		}
		if (luckyWheelMenu) {
            luckyWheelMenu.Close();
		}
		if (ratRaceMenu) {
            ratRaceMenu.Close();
		}
	}
}