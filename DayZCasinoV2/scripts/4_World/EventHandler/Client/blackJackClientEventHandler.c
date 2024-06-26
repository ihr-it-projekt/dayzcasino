class BlackJackClientEventHandler {
    private ref array<CasinoCard> currentCardsPlayer;
    private ref array<CasinoCard> currentCardsBank;
    private ref CardCollection cardCollection;
    private DayZPlayer player;

    void BlackJackClientEventHandler() {
        cardCollection = new CardCollection();
    }

    void HandleEvents(BlackJackMenu blackJackMenu, PlayerIdentity sender, Object target, int rpc_type, ParamsReadContext ctx) {
        player = GetGame().GetPlayer();
        if(IsServerCasino() || !blackJackMenu.isMenuOpen) {
            return;
        } else if(rpc_type == DAYZ_CASINO_BLACK_JACK_START_GAME_RESPONSE) {
            Param3 <int, int, int> responseStartGame;
            if(ctx.Read(responseStartGame)) {
                int firstCardPlayer = responseStartGame.param1;
                int secondCardPlayer = responseStartGame.param2;
                int firstCardBank = responseStartGame.param3;

                CasinoCard firstCard = cardCollection.GetCardByIndex(firstCardPlayer);
                CasinoCard secondCard = cardCollection.GetCardByIndex(secondCardPlayer);
                CasinoCard firstCardB = cardCollection.GetCardByIndex(firstCardBank);

                blackJackMenu.usedCards.Clear();
                blackJackMenu.usedCards.Insert(firstCardPlayer);
                blackJackMenu.usedCards.Insert(secondCardPlayer);
                blackJackMenu.usedCards.Insert(firstCardBank);

                blackJackMenu.SetStartCards(firstCard, secondCard, firstCardB);

                currentCardsPlayer = new array<CasinoCard>;
                currentCardsPlayer.Insert(firstCard);
                currentCardsPlayer.Insert(secondCard);

                currentCardsBank = new array<CasinoCard>;
                currentCardsBank.Insert(firstCardB);

                blackJackMenu.ShowPlayButtons();

                blackJackMenu.RefreshCardValues(currentCardsPlayer, currentCardsBank);

                if(blackJackMenu.cardValuePlayer == 21) {
                    GetGame().RPCSingleParam(player, DAYZ_CASINO_BLACK_JACK_PLAYER_HAS_BLACKJACK, new Param2<int, DayZPlayer>(blackJackMenu.GetCurrenBet(), player), true);
                    blackJackMenu.HidePlayButtons();
                }
            }
        } else if(rpc_type == DAYZ_CASINO_BLACK_JACK_START_NEXT_CARD_PLAYER_RESPONSE) {
            Param1 <int> responseGetNextPlayerCard;
            if(ctx.Read(responseGetNextPlayerCard)) {
                int nextPlayerCardInt = responseGetNextPlayerCard.param1;

                CasinoCard nextPlayerCard = cardCollection.GetCardByIndex(nextPlayerCardInt);
                blackJackMenu.SetNextPlayerCard(currentCardsPlayer.Count() + 1, nextPlayerCard);

                currentCardsPlayer.Insert(nextPlayerCard);
                blackJackMenu.usedCards.Insert(nextPlayerCardInt);
                blackJackMenu.RefreshCardValues(currentCardsPlayer, currentCardsBank);
                blackJackMenu.ShowPlayButtons();

                if(blackJackMenu.cardValuePlayer > 21) {
                    GetGame().RPCSingleParam(player, DAYZ_CASINO_BLACK_JACK_LOOSE_PLAYER, new
                                             Param2<int, DayZPlayer>(blackJackMenu.GetCurrenBet(), player), true);
                }
            }
        } else if(rpc_type == DAYZ_CASINO_BLACK_JACK_HOLD_CARD_RESPONSE) {
            Param1 <int> responseGetNextBankCard;
            if(ctx.Read(responseGetNextBankCard)) {
                int nextBankCardInt = responseGetNextBankCard.param1;

                CasinoCard nextBankCard = cardCollection.GetCardByIndex(nextBankCardInt);
                blackJackMenu.SetNextBankCard(currentCardsBank.Count() + 1, nextBankCard);

                currentCardsBank.Insert(nextBankCard);
                blackJackMenu.usedCards.Insert(nextBankCardInt);
                blackJackMenu.RefreshCardValues(currentCardsPlayer, currentCardsBank);

                if(blackJackMenu.cardValuePlayer <= 21 && blackJackMenu.cardValueBank <= 16) {
                    blackJackMenu.HoldCardAction();
                } else if(blackJackMenu.cardValuePlayer < 22 && blackJackMenu.cardValueBank < 22) {
                    if(blackJackMenu.cardValuePlayer < blackJackMenu.cardValueBank) {
                        GetGame().RPCSingleParam(player, DAYZ_CASINO_BLACK_JACK_LOOSE_PLAYER, new Param2<int, DayZPlayer>(blackJackMenu.GetCurrenBet(), player), true);
                    } else if(blackJackMenu.cardValuePlayer == blackJackMenu.cardValueBank) {
                        GetGame().RPCSingleParam(player, DAYZ_CASINO_BLACK_JACK_DRAW_GAME, new Param2<int, DayZPlayer>(blackJackMenu.GetCurrenBet(), player), true);
                    } else if(blackJackMenu.cardValuePlayer == 21) {
                        GetGame().RPCSingleParam(player, DAYZ_CASINO_BLACK_JACK_PLAYER_HAS_BLACKJACK, new Param2<int, DayZPlayer>(blackJackMenu.GetCurrenBet(), player), true);
                    } else if(blackJackMenu.cardValuePlayer > blackJackMenu.cardValueBank) {
                        GetGame().RPCSingleParam(player, DAYZ_CASINO_BLACK_JACK_BANK_LOSE, new Param2<int, DayZPlayer>(blackJackMenu.GetCurrenBet(), player), true);
                    }
                } else if(blackJackMenu.cardValuePlayer <= 21 && blackJackMenu.cardValueBank > 21 && blackJackMenu.cardValuePlayer < blackJackMenu.cardValueBank) {
                    GetGame().RPCSingleParam(player, DAYZ_CASINO_BLACK_JACK_BANK_LOSE, new Param2<int, DayZPlayer>(blackJackMenu.GetCurrenBet(), player), true);
                }
            }
        } else if(rpc_type == DAYZ_CASINO_BLACK_JACK_BANK_LOSE_RESPONSE || rpc_type == DAYZ_CASINO_BLACK_JACK_DRAW_GAME_RESPONSE || rpc_type == DAYZ_CASINO_BLACK_JACK_PLAYER_HAS_BLACKJACK_RESPONSE) {
            Param2 <int, int> endGameResponse;
            if(ctx.Read(endGameResponse)) {
                blackJackMenu.currentAmount = endGameResponse.param1;
                blackJackMenu.lastWinChips = endGameResponse.param2;

                blackJackMenu.WinGame();
            }
        } else if(rpc_type == DAYZ_CASINO_BLACK_JACK_LOOSE_PLAYER_RESPONSE) {
            Param2 <int, int> looseGameResponseParam;
            if(ctx.Read(looseGameResponseParam)) {
                blackJackMenu.currentAmount = looseGameResponseParam.param1;
                blackJackMenu.lastWinChips = looseGameResponseParam.param2;

                blackJackMenu.LoseGame();
            }
        } else if(rpc_type == DAYZ_CASINO_BLACK_JACK_NOT_ENOUGH_CHIPS) {
            blackJackMenu.EndGame();
        }
    }
};