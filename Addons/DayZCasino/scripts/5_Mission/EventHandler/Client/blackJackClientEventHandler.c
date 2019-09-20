class BlackJackClientEventHandler
{
    private ref TClassArray currentCardsPlayer;
    private ref TClassArray currentCardsBank;
    private ref CardCollection cardCollection;
    private BlackJackMenu blackJackMenu;
    private DayZPlayer player;


    void BlackJackClientEventHandler(BlackJackMenu blackJackMenu)
    {
        GetDayZGame().Event_OnRPC.Insert(HandleEvents);
        this.blackJackMenu = blackJackMenu;
        cardCollection = new CardCollection();
    }

    void ~BlackJackClientEventHandler()
    {
        GetDayZGame().Event_OnRPC.Remove(HandleEvents);
    }

    void HandleEvents(PlayerIdentity sender, Object target, int rpc_type, ParamsReadContext ctx) {
        player = GetGame().GetPlayer();
        if (IsServerCasino()) {
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

                RefreshCardValues();
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

                RefreshCardValues();

                if (blackJackMenu.cardValuePlayer > 21) {
                    GetGame().RPCSingleParam(player, DAYZ_CASINO_BLACK_JACK_LOOSE_PLAYER, new Param2<int, DayZPlayer>(blackJackMenu.GetCurrenBet(), player), true);
                }
            }
        }

        if (rpc_type == DAYZ_CASINO_BLACK_JACK_LOSE_PLAYER_RESPONSE) {
            Param1 <int> looseGameResponseParam;
            if (ctx.Read(looseGameResponseParam)) {
                DebugMessageCasino("receive lose amount of chips" + looseGameResponseParam.param1);
                blackJackMenu.currentAmount = looseGameResponseParam.param1;

                blackJackMenu.LoseGame();
            }
        }

        if (rpc_type == DAYZ_CASINO_BLACK_JACK_NOT_ENOUGH_CHIPS) {
            DebugMessageCasino("receive not enough balance");
            blackJackMenu.EndGame();
        }
    }

    private void RefreshCardValues() {
        int maxValuePlayer = GetCurrentCardSum(currentCardsPlayer, true);
        int minValuePlayer = GetCurrentCardSum(currentCardsPlayer);

        int maxValueBank = GetCurrentCardSum(currentCardsBank, true);
        int minValueBank = GetCurrentCardSum(currentCardsBank);

        string showValuePlayer = "" + minValuePlayer + "/" + maxValuePlayer;
        blackJackMenu.cardValuePlayer = maxValuePlayer;
        if (maxValuePlayer == minValuePlayer || maxValuePlayer > 21) {
            blackJackMenu.cardValuePlayer = minValuePlayer;
            showValuePlayer = "" + minValuePlayer;
        }

        string showValueBank = "" + minValueBank + "/" + maxValueBank;
        blackJackMenu.cardValueBank = maxValueBank;
        if (minValueBank == maxValueBank || maxValueBank > 21) {
            showValueBank = "" + minValueBank;
            blackJackMenu.cardValueBank = minValueBank;
        }

        blackJackMenu.RefreshPoints(showValuePlayer, showValueBank);
    }

    private int GetCurrentCardSum(TClassArray cards, bool max = false) {
        int value = 0;
        foreach(int index, Card card: cards){
            DebugMessageCasino("card value is " + card.GetValue());
            value += card.GetValue();
            if (false == max && card.IsAss()) {
                value -= 10;
            }
        }

        return value;
    }

};