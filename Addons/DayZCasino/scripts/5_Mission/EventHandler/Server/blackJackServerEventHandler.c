class BlackJackServerEventHandler
{
    private ref DayZCasinoPlayerInventory inventory;
    private ref CardCollection cardCollection;
    private DayZPlayer player;

    void BlackJackServerEventHandler() {
        inventory = new DayZCasinoPlayerInventory;
        cardCollection = new CardCollection();
        DebugMessageCasino("Register BJSEH");
        GetDayZGame().Event_OnRPC.Insert(HandleEvents);
    }

    void ~BlackJackServerEventHandler() {
        GetDayZGame().Event_OnRPC.Remove(HandleEvents);
    }

    void HandleEvents(PlayerIdentity sender, Object target, int rpc_type, ParamsReadContext ctx) {
        if (!IsServerCasino()) {
            return;
        }

        if (rpc_type == DAYZ_CASINO_BLACK_JACK_START_GAME) {
            Param2<int, DayZPlayer> startGame;
            if (ctx.Read(startGame)) {
                player = startGame.param2;
                if (inventory.PlayerHasEnoughChips(player, startGame.param1)) {
                    inventory.AddChipsToPlayer(player, startGame.param1 * - 1);
                    TIntArray cardAllreadyUsedServer = new TIntArray;
                    int firstCardPlayerServer = cardCollection.GetRandomCardIndex(cardAllreadyUsedServer);
                    cardAllreadyUsedServer.Insert(firstCardPlayerServer);
                    int secondCardPlayerServer = cardCollection.GetRandomCardIndex(cardAllreadyUsedServer);
                    cardAllreadyUsedServer.Insert(secondCardPlayerServer);
                    int firstCardBankServer = cardCollection.GetRandomCardIndex(cardAllreadyUsedServer);
                    cardAllreadyUsedServer.Insert(firstCardBankServer);

                    DebugMessageCasino("client first card is " + firstCardPlayerServer);

                    GetGame().RPCSingleParam(player, DAYZ_CASINO_BLACK_JACK_START_GAME_RESPONSE, new Param3<int, int, int>(firstCardPlayerServer, secondCardPlayerServer, firstCardBankServer), true, player.GetIdentity());
                } else {
                    GetGame().RPCSingleParam(player, DAYZ_CASINO_BLACK_JACK_NOT_ENOUGH_CHIPS, new Param1<bool>(true), true, player.GetIdentity());
                }
            }
        }

        if (rpc_type == DAYZ_CASINO_BLACK_JACK_START_NEXT_CARD_PLAYER) {
            Param2 <ref TIntArray, DayZPlayer> nextCardParam;
            if (ctx.Read(nextCardParam)) {
                player = nextCardParam.param2;

                DebugMessageCasino("receive next card" + nextCardParam.param1);

                int newPlayerCard = cardCollection.GetRandomCardIndex(nextCardParam.param1);

                DebugMessageCasino("new card server is " + newPlayerCard);

                GetGame().RPCSingleParam(player, DAYZ_CASINO_BLACK_JACK_START_NEXT_CARD_PLAYER_RESPONSE, new
                Param1<int>(newPlayerCard), true, player.GetIdentity());
            }
        }

        if (rpc_type == DAYZ_CASINO_BLACK_JACK_HOLD_CARD) {
            Param2 < ref TIntArray, DayZPlayer > holdCardParam;
            if (ctx.Read(holdCardParam)) {
                player = holdCardParam.param2;

                DebugMessageCasino("receive new bank card" + holdCardParam.param1);

                int newBankCard = cardCollection.GetRandomCardIndex(holdCardParam.param1);

                DebugMessageCasino("new card server is " + newPlayerCard);

                GetGame().RPCSingleParam(player, DAYZ_CASINO_BLACK_JACK_HOLD_CARD_RESPONSE, new
                Param1<int>(newBankCard), true, player.GetIdentity());
            }
        }

        if (rpc_type == DAYZ_CASINO_BLACK_JACK_LOOSE_PLAYER) {
            Param2<int, DayZPlayer> looseGameParam;
            if (ctx.Read(looseGameParam)) {
                player = looseGameParam.param2;

                DebugMessageCasino("receive lose game " + looseGameParam.param1);

                GetGame().RPCSingleParam(player, DAYZ_CASINO_BLACK_JACK_LOSE_PLAYER_RESPONSE, new Param2<int, int>(inventory.GetPlayerChipsAmount(player), looseGameParam.param1 * -1), true, player.GetIdentity());
            }
        }

        if (rpc_type == DAYZ_CASINO_BLACK_JACK_BANK_LOSE) {
            Param2<int, DayZPlayer> winGameParam;
            if (ctx.Read(winGameParam)) {
                player = winGameParam.param2;

                inventory.AddChipsToPlayer(player, winGameParam.param1 * 2);

                DebugMessageCasino("receive bank lose game " + winGameParam.param1 * 2);

                GetGame().RPCSingleParam(player, DAYZ_CASINO_BLACK_JACK_BANK_LOSE_RESPONSE, new Param2<int, int>(inventory.GetPlayerChipsAmount(player), winGameParam.param1 * 2), true, player.GetIdentity());
            }
        }

    }
};