class CardCollection {

    private ref CasinoCard cardArray[52];

    void CardCollection() {
        cardArray[0] = new CasinoCard (2, "DayZCasinoV2/data/cards/herz_zwei.edds");
        cardArray[1] = new CasinoCard (3, "DayZCasinoV2/data/cards/herz_drei.edds");
        cardArray[2] = new CasinoCard (4, "DayZCasinoV2/data/cards/herz_vier.edds");
        cardArray[3] = new CasinoCard (5, "DayZCasinoV2/data/cards/herz_fuenf.edds");
        cardArray[4] = new CasinoCard (6, "DayZCasinoV2/data/cards/herz_sechs.edds");
        cardArray[5] = new CasinoCard (7, "DayZCasinoV2/data/cards/herz_sieben.edds");
        cardArray[6] = new CasinoCard (8, "DayZCasinoV2/data/cards/herz_acht.edds");
        cardArray[7] = new CasinoCard (9, "DayZCasinoV2/data/cards/herz_neun.edds");
        cardArray[8] = new CasinoCard (10, "DayZCasinoV2/data/cards/herz_zehn.edds");
        cardArray[9] = new CasinoCard (10, "DayZCasinoV2/data/cards/herz_bauer.edds");
        cardArray[10] = new CasinoCard (10, "DayZCasinoV2/data/cards/herz_dame.edds");
        cardArray[11] = new CasinoCard (10, "DayZCasinoV2/data/cards/herz_koenig.edds");
        cardArray[12] = new CasinoCard (11, "DayZCasinoV2/data/cards/herz_ass.edds", true);

        cardArray[14] = new CasinoCard (2, "DayZCasinoV2/data/cards/karo_zwei.edds");
        cardArray[15] = new CasinoCard (3, "DayZCasinoV2/data/cards/karo_drei.edds");
        cardArray[16] = new CasinoCard (4, "DayZCasinoV2/data/cards/karo_vier.edds");
        cardArray[17] = new CasinoCard (5, "DayZCasinoV2/data/cards/karo_fuenf.edds");
        cardArray[18] = new CasinoCard (6, "DayZCasinoV2/data/cards/karo_sechs.edds");
        cardArray[19] = new CasinoCard (7, "DayZCasinoV2/data/cards/karo_sieben.edds");
        cardArray[20] = new CasinoCard (8, "DayZCasinoV2/data/cards/karo_acht.edds");
        cardArray[21] = new CasinoCard (9, "DayZCasinoV2/data/cards/karo_neun.edds");
        cardArray[22] = new CasinoCard (10, "DayZCasinoV2/data/cards/karo_zehn.edds");
        cardArray[23] = new CasinoCard (10, "DayZCasinoV2/data/cards/karo_bauer.edds");
        cardArray[24] = new CasinoCard (10, "DayZCasinoV2/data/cards/karo_dame.edds");
        cardArray[25] = new CasinoCard (10, "DayZCasinoV2/data/cards/karo_koenig.edds");
        cardArray[26] = new CasinoCard (11, "DayZCasinoV2/data/cards/karo_ass.edds", true);

        cardArray[27] = new CasinoCard (2, "DayZCasinoV2/data/cards/kreuz_zwei.edds");
        cardArray[28] = new CasinoCard (3, "DayZCasinoV2/data/cards/kreuz_drei.edds");
        cardArray[29] = new CasinoCard (4, "DayZCasinoV2/data/cards/kreuz_vier.edds");
        cardArray[30] = new CasinoCard (5, "DayZCasinoV2/data/cards/kreuz_fuenf.edds");
        cardArray[31] = new CasinoCard (6, "DayZCasinoV2/data/cards/kreuz_sechs.edds");
        cardArray[32] = new CasinoCard (7, "DayZCasinoV2/data/cards/kreuz_sieben.edds");
        cardArray[33] = new CasinoCard (8, "DayZCasinoV2/data/cards/kreuz_acht.edds");
        cardArray[34] = new CasinoCard (9, "DayZCasinoV2/data/cards/kreuz_neun.edds");
        cardArray[35] = new CasinoCard (10, "DayZCasinoV2/data/cards/kreuz_zehn.edds");
        cardArray[36] = new CasinoCard (10, "DayZCasinoV2/data/cards/kreuz_bauer.edds");
        cardArray[37] = new CasinoCard (10, "DayZCasinoV2/data/cards/kreuz_dame.edds");
        cardArray[38] = new CasinoCard (10, "DayZCasinoV2/data/cards/kreuz_koenig.edds");
        cardArray[39] = new CasinoCard (11, "DayZCasinoV2/data/cards/kreuz_ass.edds", true);

        cardArray[40] = new CasinoCard (2, "DayZCasinoV2/data/cards/pik_zwei.edds");
        cardArray[41] = new CasinoCard (3, "DayZCasinoV2/data/cards/pik_drei.edds");
        cardArray[42] = new CasinoCard (4, "DayZCasinoV2/data/cards/pik_vier.edds");
        cardArray[43] = new CasinoCard (5, "DayZCasinoV2/data/cards/pik_fuenf.edds");
        cardArray[44] = new CasinoCard (6, "DayZCasinoV2/data/cards/pik_sechs.edds");
        cardArray[45] = new CasinoCard (7, "DayZCasinoV2/data/cards/pik_sieben.edds");
        cardArray[46] = new CasinoCard (8, "DayZCasinoV2/data/cards/pik_acht.edds");
        cardArray[47] = new CasinoCard (9, "DayZCasinoV2/data/cards/pik_neun.edds");
        cardArray[48] = new CasinoCard (10, "DayZCasinoV2/data/cards/pik_zehn.edds");
        cardArray[49] = new CasinoCard (10, "DayZCasinoV2/data/cards/pik_bauer.edds");
        cardArray[50] = new CasinoCard (10, "DayZCasinoV2/data/cards/pik_dame.edds");
        cardArray[51] = new CasinoCard (10, "DayZCasinoV2/data/cards/pik_koenig.edds");
        cardArray[13] = new CasinoCard (11, "DayZCasinoV2/data/cards/pik_ass.edds", true);
    }

    int GetRandomCardIndex(TIntArray cardAllreadyUsed) {
        int cardNumber = Math.RandomIntInclusive(0, 51);

        while(true) {
            bool hasNewCard = true;
            foreach(int index, int usedCardNumber: cardAllreadyUsed) {
                if(cardNumber != usedCardNumber) {
                    continue;
                }
                cardNumber = Math.RandomIntInclusive(0, 51);
                hasNewCard = false;
                break;
            }

            if(hasNewCard) {
                break;
            }
        }

        return cardNumber;
    }

    CasinoCard GetCardByIndex(int indexValue) {
        return cardArray[indexValue];
    }

}