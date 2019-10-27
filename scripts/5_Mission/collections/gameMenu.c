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
            betDiceMenu = new BetDiceMenu(casinoConfig.positionDice);
			betDiceMenu.SetWinFactor(casinoConfig.diceWinFactor);
        }

	    return betDiceMenu;
	}

    LuckyWheelMenu GetLuckyWheelMenu() {
        if (!luckyWheelMenu) {
            DebugMessageCasino("No selectedMenu");
            luckyWheelMenu = new LuckyWheelMenu(casinoConfig.positionLuckyWheel);
            luckyWheelMenu.SetConfig(casinoConfig);
        }

	    return luckyWheelMenu;
	}

    BlackJackMenu GetBlackJackMenu() {
        if (!blackJackMenu) {
            DebugMessageCasino("No selectedMenu");
            blackJackMenu = new BlackJackMenu(casinoConfig.positionBlackJack);
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
		
		float playerDistanceToGamePositionBetDice = vector.Distance(betDiceMenu.GetPosition(), posPlayer);
		if (casinoConfig.enabledDice && playerDistanceToGamePositionBetDice <= DAYZ_CASINO_DISTANCE_TO_GAME)
		{
			DebugMessageCasino("in near of bet dice");
			
			return betDiceMenu;
		}
		
		float playerDistanceToGamePositionBlackJack = vector.Distance( blackJackMenu.GetPosition(), posPlayer);
		
		if (casinoConfig.enabledBlackJack && playerDistanceToGamePositionBlackJack <= DAYZ_CASINO_DISTANCE_TO_GAME)
		{
			DebugMessageCasino("in near of black jack");
			
			return blackJackMenu;
		}

        float playerDistanceToGamePositionLuckyWheelMenu = vector.Distance(luckyWheelMenu.GetPosition(), posPlayer);

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

        float playerDistanceToGamePositionBlackJack = vector.Distance(blackJackMenu.GetPosition(), posPlayer);
        float playerDistanceToGamePositionBetDice = vector.Distance(betDiceMenu.GetPosition(), posPlayer);
        float playerDistanceToGamePositionLuckyWheelMenu = vector.Distance(luckyWheelMenu.GetPosition(), posPlayer);

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