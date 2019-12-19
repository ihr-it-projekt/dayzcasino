class CasinoGameSettingBlackjack extends CasinoGameSetting
{
    int minBet  = 10;
    int maxBet  = 10000;

    void CasinoGameSettingBlackjack()
    {
        gameType = DAYZ_CASINO_TYPE_BLACKJACK_GAME;
        gamePositions = new array<ref GamePosition>;
        gamePositions.Insert(new GamePosition("8349.769531 293.181458 5976.001953", "49.000000 0.000000 0.000000"));
    }
}