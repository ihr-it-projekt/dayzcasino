class GameMenu
{
	private ref BetDiceMenu betDiceMenu;
	private ref BlackJackMenu blackJackMenu;
	private ref LuckyWheelMenu luckyWheelMenu;
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

    GameHint GetGameHintMenu() {
        if (!gameHint) {
            DebugMessageCasino("No selectedMenu");
            gameHint = new GameHint();
        }

	    return gameHint;
	}

	BaseMenu GetGameMenu(DayZPlayer player) {
		vector posPlayer = player.GetPosition();

        GetBetDiceMenu();
        GetLuckyWheelMenu();
        GetBlackJackMenu();
		
		float playerDistanceToGamePositionBetDice = vector.Distance(casinoConfig.positionDice, posPlayer);
		if (casinoConfig.enabledDice && playerDistanceToGamePositionBetDice <= DAYZ_CASINO_DISTANCE_TO_GAME)
		{
			DebugMessageCasino("in near of bet dice");
			
			return betDiceMenu;
		}
		
		float playerDistanceToGamePositionBlackJack = vector.Distance(casinoConfig.positionBlackJack, posPlayer);
		
		if (casinoConfig.enabledBlackJack && playerDistanceToGamePositionBlackJack <= DAYZ_CASINO_DISTANCE_TO_GAME)
		{
			DebugMessageCasino("in near of black jack");
			
			return blackJackMenu;
		}

        float playerDistanceToGamePositionLuckyWheelMenu = vector.Distance(casinoConfig.positionLuckyWheel, posPlayer);

        if (casinoConfig.enabledLuckyWheel && playerDistanceToGamePositionLuckyWheelMenu <= DAYZ_CASINO_DISTANCE_TO_GAME)
        {
            DebugMessageCasino("in near of lucky wheel");

            return luckyWheelMenu;
        }

		DebugMessageCasino("not in near of a game.");
		return null;
	}

	bool CanOpenHintToOpenGameMenu(DayZPlayer player) {
        vector posPlayer = player.GetPosition();
        GetBetDiceMenu();
        GetLuckyWheelMenu();
        GetBlackJackMenu();

        float playerDistanceToGamePositionBlackJack = vector.Distance(casinoConfig.positionBlackJack, posPlayer);
        float playerDistanceToGamePositionBetDice = vector.Distance(casinoConfig.positionDice, posPlayer);
        float playerDistanceToGamePositionLuckyWheelMenu = vector.Distance(casinoConfig.positionLuckyWheel, posPlayer);

        return (casinoConfig.enabledDice && playerDistanceToGamePositionBetDice <= DAYZ_CASINO_DISTANCE_TO_GAME) || (casinoConfig.enabledBlackJack && playerDistanceToGamePositionBlackJack <= DAYZ_CASINO_DISTANCE_TO_GAME) || (casinoConfig.enabledLuckyWheel && playerDistanceToGamePositionLuckyWheelMenu <= DAYZ_CASINO_DISTANCE_TO_GAME);
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
	}
}