class BlackJackClientEventHandler
{
    private ref TClassArray currentCardsPlayer;
    private ref TClassArray currentCardsBank;
    private ref CardCollection cardCollection;
    private ref BlackJackMenu blackJackMenu;
    private DayZPlayer player;

    void BlackJackClientEventHandler()
    {
        cardCollection = new CardCollection();
    }

    void HandleEvents(BlackJackMenu blackJackMenu, PlayerIdentity sender, Object target, int rpc_type, ParamsReadContext ctx) {
        player = GetGame().GetPlayer();
        if (IsServerCasino() || !blackJackMenu.isMenuOpen) {
            return;
        }
        if (rpc_type == DAYZ_CASINO_BLACK_JACK_START_GAME_RESPONSE) {
            Param3 <int, int, int> responseStartGame;
            if (ctx.Read(responseStartGame)) {
                int firstCardPlayer = responseStartGame.param1;
                int secondCardPlayer = responseStartGame.param2;
                int firstCardBank = responseStartGame.param3;

                DebugMessageCasino("client first card is " + firstCardPlayer);

                Card firstCard = cardCollection.GetCardByIndex(firstCardPlayer);
                Card secondCard = cardCollection.GetCardByIndex(secondCardPlayer);
                Card firstCardB = cardCollection.GetCardByIndex(firstCardBank);

                blackJackMenu.usedCards.Clear();
                blackJackMenu.usedCards.Insert(firstCardPlayer);
                blackJackMenu.usedCards.Insert(secondCardPlayer);
                blackJackMenu.usedCards.Insert(firstCardBank);

                blackJackMenu.SetStartCards(firstCard, secondCard, firstCardB);

                currentCardsPlayer = new TClassArray;
                currentCardsPlayer.Insert(firstCard);
                currentCardsPlayer.Insert(secondCard);

                currentCardsBank = new TClassArray;
                currentCardsBank.Insert(firstCardB);

                blackJackMenu.ShowPlayButtons();

                blackJackMenu.RefreshCardValues(currentCardsPlayer, currentCardsBank);
            }
        }

        if (rpc_type == DAYZ_CASINO_BLACK_JACK_START_NEXT_CARD_PLAYER_RESPONSE) {
            Param1 <int> responseGetNextPlayerCard;
            if (ctx.Read(responseGetNextPlayerCard)) {
                int nextPlayerCardInt = responseGetNextPlayerCard.param1;
                DebugMessageCasino("client next card is " + nextPlayerCardInt);

                Card nextPlayerCard = cardCollection.GetCardByIndex(nextPlayerCardInt);
                blackJackMenu.SetNextPlayerCard(currentCardsPlayer.Count() + 1, nextPlayerCard)

                currentCardsPlayer.Insert(nextPlayerCard);
                blackJackMenu.usedCards.Insert(nextPlayerCardInt);
                blackJackMenu.RefreshCardValues(currentCardsPlayer, currentCardsBank);
                blackJackMenu.ShowPlayButtons();

                if (blackJackMenu.cardValuePlayer > 21) {
                    GetGame().RPCSingleParam(player, DAYZ_CASINO_BLACK_JACK_LOOSE_PLAYER, new Param2<int, DayZPlayer>(blackJackMenu.GetCurrenBet(), player), true);
                }
            }
        }

        if (rpc_type == DAYZ_CASINO_BLACK_JACK_HOLD_CARD_RESPONSE) {
            Param1 <int> responseGetNextBankCard;
            if (ctx.Read(responseGetNextBankCard)) {
                int nextBankCardInt = responseGetNextBankCard.param1;
                DebugMessageCasino("client bank next card is " + nextBankCardInt);

                Card nextBankCard = cardCollection.GetCardByIndex(nextBankCardInt);
                blackJackMenu.SetNextBankCard(currentCardsBank.Count() + 1, nextBankCard)

                currentCardsBank.Insert(nextBankCard);
                blackJackMenu.usedCards.Insert(nextBankCardInt);
                blackJackMenu.RefreshCardValues(currentCardsPlayer, currentCardsBank);

                if (blackJackMenu.cardValuePlayer <= 21 && blackJackMenu.cardValueBank <= 21){
                    if (blackJackMenu.cardValuePlayer > blackJackMenu.cardValueBank) {
                        DebugMessageCasino("next card");
                        blackJackMenu.HoldCardAction();
                    } else if (blackJackMenu.cardValuePlayer < blackJackMenu.cardValueBank) {
                        DebugMessageCasino("bank win");
                        GetGame().RPCSingleParam(player, DAYZ_CASINO_BLACK_JACK_LOOSE_PLAYER, new
                        Param2<int, DayZPlayer>(blackJackMenu.GetCurrenBet(), player), true);
                    } else if (blackJackMenu.cardValuePlayer == blackJackMenu.cardValueBank) {
                        if (currentCardsPlayer.Count() >= currentCardsBank.Count()) {
                            DebugMessageCasino("bank win with less or same card count");
                            GetGame().RPCSingleParam(player, DAYZ_CASINO_BLACK_JACK_LOOSE_PLAYER, new
                            Param2<int, DayZPlayer>(blackJackMenu.GetCurrenBet(), player), true);
                        } else if (currentCardsPlayer.Count() < currentCardsBank.Count()) {
                            DebugMessageCasino("player win");
                            GetGame().RPCSingleParam(player, DAYZ_CASINO_BLACK_JACK_BANK_LOSE, new
                            Param2<int, DayZPlayer>(blackJackMenu.GetCurrenBet(), player), true);
                        } else {
                            DebugMessageCasino("no condition 2");
                        }
                    } else {
                        DebugMessageCasino("no condition 1");
                    }
                } else if (blackJackMenu.cardValuePlayer <= 21 && blackJackMenu.cardValueBank > 21 && blackJackMenu.cardValuePlayer < blackJackMenu.cardValueBank) {
                    GetGame().RPCSingleParam(player, DAYZ_CASINO_BLACK_JACK_BANK_LOSE, new Param2<int, DayZPlayer>(blackJackMenu.GetCurrenBet(), player), true);
                }
            }
        }

        if (rpc_type == DAYZ_CASINO_BLACK_JACK_BANK_LOSE_RESPONSE) {
            Param2 <int, int> looseBankResponseParam;
            if (ctx.Read(looseBankResponseParam)) {
                DebugMessageCasino("receive win amount of chips" + looseBankResponseParam.param1);
                blackJackMenu.currentAmount = looseBankResponseParam.param1;
                blackJackMenu.lastWinChips = looseBankResponseParam.param2;

                blackJackMenu.WinGame();
            }
        }

        if (rpc_type == DAYZ_CASINO_BLACK_JACK_LOSE_PLAYER_RESPONSE) {
            Param2 <int, int> looseGameResponseParam;
            if (ctx.Read(looseGameResponseParam)) {
                DebugMessageCasino("receive lose amount of chips" + looseGameResponseParam.param1);
                blackJackMenu.currentAmount = looseGameResponseParam.param1;
                blackJackMenu.lastWinChips = looseGameResponseParam.param2;

                blackJackMenu.LoseGame();
            }
        }

        if (rpc_type == DAYZ_CASINO_BLACK_JACK_NOT_ENOUGH_CHIPS) {
            DebugMessageCasino("receive not enough balance");
            blackJackMenu.EndGame();
        }
    }

};