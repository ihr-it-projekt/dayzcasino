class GameMenu
{
	private ref BetDiceMenu betDiceMenu;
	private ref BlackJackMenu blackJackMenu;
	private ref LuckyWheelMenu luckyWheelMenu;
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
        }

	    return betDiceMenu;
	}

    LuckyWheelMenu GetLuckyWheelMenu() {
        if (!luckyWheelMenu) {
            DebugMessageCasino("No selectedMenu");
            luckyWheelMenu = new LuckyWheelMenu(casinoConfig.positionDice);
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

	BaseMenu GetGameMenu(DayZPlayer player) {
		vector posPlayer = player.GetPosition();

        GetBetDiceMenu();
        GetLuckyWheelMenu();
        GetBlackJackMenu();
		
		vector posPlayBetDice = betDiceMenu.GetPosition();
		float playerDistanceToGamePositionBetDice = vector.Distance(posPlayBetDice, posPlayer);

		if (casinoConfig.enabledDice && playerDistanceToGamePositionBetDice <= DAYZ_CASINO_DISTANCE_TO_GAME)
		{
			DebugMessageCasino("in near of bet dice");
			
			return betDiceMenu;
		}
		
		vector posPlayBlackJack = blackJackMenu.GetPosition();
		float playerDistanceToGamePositionBlackJack = vector.Distance(posPlayBlackJack, posPlayer);
		
		if (casinoConfig.enabledBlackJack && playerDistanceToGamePositionBlackJack <= DAYZ_CASINO_DISTANCE_TO_GAME)
		{
			DebugMessageCasino("in near of black jack");
			
			return blackJackMenu;
		}

        vector posLuckyWheelMenu= luckyWheelMenu.GetPosition();
        float playerDistanceToGamePositionLuckyWheelMenu = vector.Distance(posLuckyWheelMenu, posPlayer);

        if (casinoConfig.enabledLuckyWheel && playerDistanceToGamePositionLuckyWheelMenu <= DAYZ_CASINO_DISTANCE_TO_GAME || DAYZ_CASINO_DEBUG)
        {
            DebugMessageCasino("in near of lucky wheel");

            return luckyWheelMenu;
        }

		DebugMessageCasino("not in near of a game.");
		return null;
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