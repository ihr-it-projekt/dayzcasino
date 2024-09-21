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
    int configVersion = 3;
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
            currencyValues.Set("CasinoChip", 1);
            currencyValues.Set("CasinoChip_Red", 10);
            currencyValues.Set("CasinoChip_Green", 100);
            currencyValues.Set("CasinoChip_Blue", 1000);
            currencyValues.Set("CasinoChip_Yellow", 10000);
            configVersion = 3;
            Save(SETTINGSFILE);
        } else {
            Load(SETTINGSFILE);
            if(configVersion < 2) {
                configVersion = 2;
                currencyValues = new map<string, int>;
                currencyValues.Set("CasinoChip", 1);

                Save(SETTINGSFILE);
            }

            if(configVersion < 3) {
                configVersion = 3;
                if (currencyValues.Contains("CasinoChips")) {
                    currencyValues.Set("CasinoChip_Red", 10);
                    currencyValues.Set("CasinoChip_Green", 100);
                    currencyValues.Set("CasinoChip_Blue", 1000);
                    currencyValues.Set("CasinoChip_Yellow", 10000);
                }
                Save(SETTINGSFILE);
            }

            if(configVersion < 4) {
                configVersion = 4;
                if (currencyValues.Contains("CasinoChips")) {
                    currencyValues.Set("CasinoChip", 1);
                    currencyValues.Remove("CasinoChips");
                }
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

    bool HasPosition(vector pos) {
        if(diceSettings.enabled) {
            foreach(GamePosition positionDice: diceSettings.gamePositions) {
                if(positionDice.pos == pos) return true;
            }
        }
        if(blackJackSettings.enabled) {
            foreach(GamePosition positionBlackJack: blackJackSettings.gamePositions) {
                if(positionBlackJack.pos == pos) return true;
            }
        }
        if(luckyWheelSettings.enabled) {
            foreach(GamePosition positionLuckyWeel: luckyWheelSettings.gamePositions) {
                if(positionLuckyWeel.pos == pos) return true;
            }
        }
        if(ratRaceSettings.enabled) {
            foreach(GamePosition positionRatRace: ratRaceSettings.gamePositions) {
                if(positionRatRace.pos == pos) return true;
            }
        }

        return false;
    }

    override protected void DoLoad() {
        JsonFileLoader<CasinoConfig>.JsonLoadFile(CONFIGSFOLDER + SETTINGSFILE, this);
    }

    override protected void DoSave() {
        JsonFileLoader<CasinoConfig>.JsonSaveFile(CONFIGSFOLDER + SETTINGSFILE, this);
    }
}