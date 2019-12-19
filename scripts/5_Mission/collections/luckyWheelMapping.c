class LuckyWheelMapping
{
    private ref LuckyWheelWin winArray[360];
    private int chipsValue;

    void LuckyWheelMapping(int chipsValueParam) {
        chipsValue = chipsValueParam;

        int i = 0;
        while (i < 36)
        {
            winArray[i] = new LuckyWheelWin(i, 0);
            i += 2;
        }

        i = 1;
        // 1,7,13,19,25
        while (i < 36)
        {
            winArray[i] = new LuckyWheelWin(i, chipsValue * 1.5);
            i += 6;
        }

        winArray[5] = new LuckyWheelWin(5, chipsValue * 5);
        winArray[23] = new LuckyWheelWin(23, chipsValue * 3);

        winArray[15] = new LuckyWheelWin(15, chipsValue * 0);
        winArray[33] = new LuckyWheelWin(33, 99);

        winArray[3] = new LuckyWheelWin(3, chipsValue * 0);
        winArray[9] = new LuckyWheelWin(9, chipsValue * 2);
        winArray[11] = new LuckyWheelWin(11, chipsValue * 0);
        winArray[17] = new LuckyWheelWin(17, chipsValue * 0);
        winArray[21] = new LuckyWheelWin(21, chipsValue * 2);
        winArray[27] = new LuckyWheelWin(27, chipsValue * 0);
        winArray[29] = new LuckyWheelWin(29, chipsValue * 2);
        winArray[31] = new LuckyWheelWin(31, chipsValue * 0);
        winArray[35] = new LuckyWheelWin(35, chipsValue * 2);
    }

    LuckyWheelWin GetLuckyWheelWin() {

        int luckNumber = Math.RandomIntInclusive(0, 35);

        if (DAYZ_CASINO_DEBUG_JACKPOT_WIN) {
            return winArray[DAYZ_CASINO_LUCKY_WHEEL_JACKPOT_DEGREE / 10];
        }

        return winArray[luckNumber];
    }

    LuckyWheelWin GetLuckyWheelWinByIndex(int index) {
        return winArray[index];
    }


};