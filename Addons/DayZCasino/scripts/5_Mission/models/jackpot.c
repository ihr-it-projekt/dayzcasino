class Jackpot
{
    private static string CASINO_JACK_POT_PATH = "$profile:dayZCasinoJackpot.json";
    private ref CasinoJackpot casinoJackpot;
    private int minJackpotLuckyWheel;

    void Jackpot(int minJackpotLuckyWheelExt) {
        casinoJackpot = new CasinoJackpot;
        minJackpotLuckyWheel = minJackpotLuckyWheelExt;
        if (FileExist(CASINO_JACK_POT_PATH)) {
            DebugMessageCasino("try load jackpot");
            JsonFileLoader<CasinoJackpot>.JsonLoadFile(CASINO_JACK_POT_PATH, casinoJackpot);
        }

        if (casinoJackpot.currentJackpotLuckyWheel < minJackpotLuckyWheel) {
            casinoJackpot.currentJackpotLuckyWheel = minJackpotLuckyWheel;
        }

        JsonFileLoader<CasinoJackpot>.JsonSaveFile(CASINO_JACK_POT_PATH, casinoJackpot);
    }

    int GetJackpotLuckyWheel() {
        return casinoJackpot.currentJackpotLuckyWheel;
    }

    void UpdateLuckyWheelJackpot(int newJackpotLuckyWheel) {
        casinoJackpot.currentJackpotLuckyWheel = newJackpotLuckyWheel;

        if (casinoJackpot.currentJackpotLuckyWheel < minJackpotLuckyWheel) {
            casinoJackpot.currentJackpotLuckyWheel = minJackpotLuckyWheel;
        }

        if (FileExist(CASINO_JACK_POT_PATH)) {
            DebugMessageCasino("try load jackpot");
            JsonFileLoader<CasinoJackpot>.JsonSaveFile(CASINO_JACK_POT_PATH, casinoJackpot);
        }
    }
};