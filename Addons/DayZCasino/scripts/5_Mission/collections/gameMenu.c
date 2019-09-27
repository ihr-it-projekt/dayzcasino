class GameMenu
{
	private ref BetDiceMenu betDiceMenu;
	private ref BlackJackMenu blackJackMenu;
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

    BlackJackMenu GetBlackJackMenu() {
        if (!blackJackMenu) {
            DebugMessageCasino("No selectedMenu");
            blackJackMenu = new BlackJackMenu(casinoConfig.positionBlackJack);
        }

	    return blackJackMenu;
	}

	BaseMenu GetGameMenu(DayZPlayer player) {
		vector posPlayer = player.GetPosition();

        GetBetDiceMenu()
        GetBlackJackMenu()
		
		vector posPlayBetDice = betDiceMenu.GetPosition();
		float playerDistanceToGamePositionBetDice = vector.Distance(posPlayBetDice, posPlayer);

		if (playerDistanceToGamePositionBetDice <= DAYZ_CASINO_DISTANCE_TO_GAME)
		{
			DebugMessageCasino("in near of bet dice");
			
			return betDiceMenu;
		}
		
		vector posPlayBlackJack = blackJackMenu.GetPosition();
		float playerDistanceToGamePositionBlackJack = vector.Distance(posPlayBlackJack, posPlayer);
		
		if (playerDistanceToGamePositionBlackJack <= DAYZ_CASINO_DISTANCE_TO_GAME || DAYZ_CASINO_DEBUG)
		{
			DebugMessageCasino("in near of black jack");
			
			return blackJackMenu;
		}
	
		DebugMessageCasino("not in near of a game.");
		return null;
	}
	
	void CloseAllMenu(){
		if (betDiceMenu) {
			DebugMessageCasino("No selectedMenu");
			betDiceMenu.Close();
		}
		if (blackJackMenu) {
			DebugMessageCasino("No selectedMenu");
			blackJackMenu.Close();
		}
	}
}