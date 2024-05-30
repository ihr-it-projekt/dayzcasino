class GameMenu {
    private static ref GameMenu menu;

    private ref BetDiceMenu betDiceMenu;
    private ref BlackJackMenu blackJackMenu;
    private ref LuckyWheelMenu luckyWheelMenu;
    private ref RatRaceMenu ratRaceMenu;
    private CasinoConfig casinoConfig;

    static GameMenu Get(CasinoConfig casinoConfigExt = null) {
        if(!menu && casinoConfigExt) {
            menu = new GameMenu(casinoConfigExt);
        }

        return menu;
    }

    void GameMenu(CasinoConfig casinoConfigExt) {
        casinoConfig = casinoConfigExt;
    }

    BetDiceMenu GetBetDiceMenu() {
        if(!betDiceMenu) {
            betDiceMenu = new BetDiceMenu();
            betDiceMenu.SetConfig(casinoConfig);
            betDiceMenu.SetWinFactor(casinoConfig.diceSettings.diceWinFactor);
        }

        return betDiceMenu;
    }

    LuckyWheelMenu GetLuckyWheelMenu() {
        if(!luckyWheelMenu) {
            luckyWheelMenu = new LuckyWheelMenu();
            luckyWheelMenu.SetConfig(casinoConfig);
        }

        return luckyWheelMenu;
    }

    BlackJackMenu GetBlackJackMenu() {
        if(!blackJackMenu) {
            blackJackMenu = new BlackJackMenu();
            blackJackMenu.SetConfig(casinoConfig);
        }

        return blackJackMenu;
    }

    RatRaceMenu GetRatRaceMenu() {
        if(!ratRaceMenu) {
            ratRaceMenu = new RatRaceMenu();
            ratRaceMenu.SetConfig(casinoConfig);
        }

        return ratRaceMenu;
    }


    BaseMenu GetGameMenu(vector posPlayer) {
        if(casinoConfig.diceSettings.enabled) {
            foreach(GamePosition position1: casinoConfig.diceSettings.gamePositions) {
                if(vector.Distance(position1.pos, posPlayer) <= DAYZ_CASINO_DISTANCE_TO_GAME) {
                    return GetBetDiceMenu();
                }
            }
        }
        if(casinoConfig.blackJackSettings.enabled) {
            foreach(GamePosition position2: casinoConfig.blackJackSettings.gamePositions) {
                if(vector.Distance(position2.pos, posPlayer) <= DAYZ_CASINO_DISTANCE_TO_GAME) {
                    return GetBlackJackMenu();
                }
            }
        }
        if(casinoConfig.luckyWheelSettings.enabled) {
            foreach(GamePosition position3: casinoConfig.luckyWheelSettings.gamePositions) {
                if(vector.Distance(position3.pos, posPlayer) <= DAYZ_CASINO_DISTANCE_TO_GAME) {
                    return GetLuckyWheelMenu();
                }
            }
        }
        if(casinoConfig.ratRaceSettings.enabled) {
            foreach(GamePosition position4: casinoConfig.ratRaceSettings.gamePositions) {
                if(vector.Distance(position4.pos, posPlayer) <= DAYZ_CASINO_DISTANCE_TO_GAME) {
                    return GetRatRaceMenu();
                }
            }
        }

        return null;
    }

    bool CanCloseGameMenu() {
        bool closed = false;
        if(betDiceMenu && betDiceMenu.CanCloseGameMenu()) {
            closed = true;
        }
        if(blackJackMenu && blackJackMenu.CanCloseGameMenu()) {
            closed = true;
        }
        if(luckyWheelMenu && luckyWheelMenu.CanCloseGameMenu()) {
            closed = true;
        }
        if(ratRaceMenu && ratRaceMenu.CanCloseGameMenu()) {
            closed = true;
        }

        return closed;
    }
}
