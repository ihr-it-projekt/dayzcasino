class CasinoConfig extends BaseConfig
{
    private const static string			SETTINGSFILE			= "CasinoConfigV2.json";

	ref CasinoGameSettingLuckyWheel luckyWheelSettings;
	ref CasinoGameSettingBlackjack blackJackSettings;
	ref CasinoGameSettingDice diceSettings;
	ref CasinoGameSettingRatRace ratRaceSettings;

    void CasinoConfig()
    {
  		if (!FileExist(CONFIGSFOLDER + SETTINGSFILE))
		{
			diceSettings = new CasinoGameSettingDice();
			blackJackSettings = new CasinoGameSettingBlackjack();
			luckyWheelSettings = new CasinoGameSettingLuckyWheel();
            ratRaceSettings = new CasinoGameSettingRatRace();

			Save(SETTINGSFILE);
		} else {
			Load(SETTINGSFILE);
		}
    }
	
	override protected void DoLoad() {
		JsonFileLoader<CasinoConfig>.JsonLoadFile(CONFIGSFOLDER + SETTINGSFILE, this);
	}
	
	override protected void DoSave() {
		JsonFileLoader<CasinoConfig>.JsonSaveFile(CONFIGSFOLDER + SETTINGSFILE, this);
	}
}