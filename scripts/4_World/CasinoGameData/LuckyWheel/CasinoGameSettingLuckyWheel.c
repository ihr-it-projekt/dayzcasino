class CasinoGameSettingLuckyWheel extends CasinoGameSetting
{
 	int chipsBet = 50;
    int minJackpot = 500;
    int maxJackpot = 10000;
    static int GAME_TYPE = DAYZ_CASINO_TYPE_LUCKY_WHEEL_GAME;

    void CasinoGameSettingLuckyWheel()
    {
        gamePositions = new array<ref GamePosition>;
        gamePositions.Insert(new GamePosition("8349.441406 293.181458 5973.501953", "97.000015 0.000000 0.000000"));
    }
}