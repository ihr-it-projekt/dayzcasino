class BetDiceClientEventHandler
{
    private BetDiceMenu betDiceMenu;

    void BetDiceClientEventHandler(BetDiceMenu betDiceMenu)
    {
        GetDayZGame().Event_OnRPC.Insert(HandleEvents);
        this.betDiceMenu = betDiceMenu;
    }

    void ~BetDiceClientEventHandler()
    {
        GetDayZGame().Event_OnRPC.Remove(HandleEvents);
    }

    void HandleEvents(PlayerIdentity sender, Object target, int rpc_type, ParamsReadContext ctx) {
        if (IsServerCasino()) {
            return;
        }
        if (rpc_type == DAYZ_CASINO_RESPONSE_SHUFFEL_BET_DICE) {
            DebugMessageCasino("receive response shuffle");
            Param3<int, int, int> parameterShuffleResponse;
            if (ctx.Read(parameterShuffleResponse)) {
                DebugMessageCasino("has receive response for bet dice");
                betDiceMenu.winImageNumber = parameterShuffleResponse.param1 - 1;
                betDiceMenu.lastWinChips = parameterShuffleResponse.param2;
                betDiceMenu.currentAmount += parameterShuffleResponse.param2;
                DebugMessageCasino("new amount is " + betDiceMenu.currentAmount);
            }
        }
        if (rpc_type == DAYZ_CASINO_RESPONSE_SHUFFEL_BET_DICE_NOT_ENOUGH_BALANCE) {
            DebugMessageCasino("receive not enough balance");

        }
    }
};