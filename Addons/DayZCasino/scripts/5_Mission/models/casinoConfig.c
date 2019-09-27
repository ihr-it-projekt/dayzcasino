class CasinoConfig {
	vector positionDice;
	vector orientationDice;
    string gameObjectDice;
    bool enabledDice;
    vector positionBlackJack;
    vector orientationBlackJack;
    string gameObjectBlackJack;
    bool enabledBlackJack;
    vector positionLuckyWheel;
    vector orientationLuckyWheel;
    string gameObjectLuckyWheel;
    bool enabledLuckyWheel;
    int chipsValueLuckyWheel;
    int maxJackpotLuckyWheel = 1000000;
    int minJackpotLuckyWheel = 500;
}