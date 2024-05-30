class CasinoConfig extends BaseConfig {
    private const static string	SETTINGSFILE = "CasinoConfigV2.json";

    static ref CasinoConfig instance;

    static CasinoConfig Get() {
        if(!instance) {
            instance = new CasinoConfig();
        }
        return instance;
    }

    ref CasinoGameSettingLuckyWheel luckyWheelSettings;
    ref CasinoGameSettingBlackjack blackJackSettings;
    ref CasinoGameSettingDice diceSettings;
    ref CasinoGameSettingRatRace ratRaceSettings;
    int configVersion = 2;
    bool enablePlayLogs = true;
    ref map <string, int> currencyValues;

    void CasinoConfig() {

        if(!GetGame().IsServer()) {
            GetGame().RPCSingleParam(null, DAYZ_CASINO_GET_CASINO_CONFIG, null, true);
            return;
        }

        if(!FileExist(CONFIGSFOLDER + SETTINGSFILE)) {
            diceSettings = new CasinoGameSettingDice();
            blackJackSettings = new CasinoGameSettingBlackjack();
            luckyWheelSettings = new CasinoGameSettingLuckyWheel();
            ratRaceSettings = new CasinoGameSettingRatRace();
            currencyValues = new map<string, int>;
            currencyValues.Set("CasinoChips", 1);
            Save(SETTINGSFILE);
        } else {
            Load(SETTINGSFILE);
            if(configVersion < 2) {
                configVersion = 2;
                currencyValues = new map<string, int>;
                currencyValues.Set("CasinoChips", 1);

                Save(SETTINGSFILE);
            }
        }
    }

    bool HasType(string type) {
        if(type == diceSettings.gameObject) return true;
        if(type == blackJackSettings.gameObject) return true;
        if(type == luckyWheelSettings.gameObject) return true;
        if(type == ratRaceSettings.gameObject) return true;

        return false;
    }

    override protected void DoLoad() {
        JsonFileLoader<CasinoConfig>.JsonLoadFile(CONFIGSFOLDER + SETTINGSFILE, this);
    }

    override protected void DoSave() {
        JsonFileLoader<CasinoConfig>.JsonSaveFile(CONFIGSFOLDER + SETTINGSFILE, this);
    }
}