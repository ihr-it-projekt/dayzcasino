class CasinoGameSettingLuckyWheel extends CasinoGameSetting
{
    int minBet        = 10;
    int maxBet        = 10000;
    int diceWinFactor = 2;

    void CasinoGameSettingDice()
    {
        gameType = DAYZ_CASINO_TYPE_LUCKY_WHEEL_GAME;
        gamePositions = new array<GamePosition>;
        gamePositions.Insert(new GamePostion("8349.441406 293.181458 5973.501953", "97.000015 0.000000 0.000000"));
    }
}