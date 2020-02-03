class CasinoConfig extends BaseConfig
{
    private const static string	SETTINGSFILE = "CasinoConfigV2.json";

	ref CasinoGameSettingLuckyWheel luckyWheelSettings;
	ref CasinoGameSettingBlackjack blackJackSettings;
	ref CasinoGameSettingDice diceSettings;
	ref CasinoGameSettingRatRace ratRaceSettings;
	int configVersion = 1;
	bool enablePlayLogs = true;

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
			
			if (luckyWheelSettings.wheelNumberConfigs.Count() == 0) {
				luckyWheelSettings.CreateNumbers();
				Save(SETTINGSFILE);
			}

			if (blackJackSettings.winFactor == 0) {
				blackJackSettings.winFactor = 1.5;
				blackJackSettings.winFactorBlackJack = 2.0;
				Save(SETTINGSFILE);
			}

			if (!configVersion) {
                configVersion = 1;
                enablePlayLogs = false;
                Save(SETTINGSFILE);
			}
		}
    }
	
	override protected void DoLoad() {
		JsonFileLoader<CasinoConfig>.JsonLoadFile(CONFIGSFOLDER + SETTINGSFILE, this);
	}
	
	override protected void DoSave() {
		JsonFileLoader<CasinoConfig>.JsonSaveFile(CONFIGSFOLDER + SETTINGSFILE, this);
	}
}