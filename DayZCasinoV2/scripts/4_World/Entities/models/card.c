class CasinoCard {
    private int value;
    private string imagePath;
    private string name;
    private bool isAss

    void CasinoCard(int cardValue, string cardImagePath, bool cardIsAss = false) {
        value = cardValue;
        imagePath = cardImagePath;
        isAss = cardIsAss;

    }

    int GetValue() {
        return value;
    }

    string GetImagePath() {
        return imagePath;
    }

    bool IsAss() {
        return isAss;
    }

}