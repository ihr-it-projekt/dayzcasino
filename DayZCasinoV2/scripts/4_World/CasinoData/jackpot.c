class Jackpot extends BaseConfig {
    private const static string	SETTINGSFILE = "dayZCasinoJackpot.json";

    private int currentJackpotLuckyWheel = 0;
    private int minJackpotLuckyWheel;

    void Jackpot(int minJackpotLuckyWheelExt) {
        if(!FileExist(CONFIGSFOLDER + SETTINGSFILE)) {
            minJackpotLuckyWheel = minJackpotLuckyWheelExt;

            if(currentJackpotLuckyWheel < minJackpotLuckyWheel) {
                currentJackpotLuckyWheel = minJackpotLuckyWheel;
            }

            Save(SETTINGSFILE);
        } else {
            Load(SETTINGSFILE);
        }
    }

    int GetJackpotLuckyWheel() {
        return currentJackpotLuckyWheel;
    }

    void UpdateLuckyWheelJackpot(int newJackpotLuckyWheel) {
        currentJackpotLuckyWheel = newJackpotLuckyWheel;

        if(currentJackpotLuckyWheel < minJackpotLuckyWheel) {
            currentJackpotLuckyWheel = minJackpotLuckyWheel;
        }

        Save(SETTINGSFILE);
    }

    override protected void DoLoad() {
        JsonFileLoader<Jackpot>.JsonLoadFile(CONFIGSFOLDER + SETTINGSFILE, this);
    }

    override protected void DoSave() {
        JsonFileLoader<Jackpot>.JsonSaveFile(CONFIGSFOLDER + SETTINGSFILE, this);
    }
};