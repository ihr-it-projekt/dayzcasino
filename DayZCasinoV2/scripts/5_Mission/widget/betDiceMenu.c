class BetDiceMenu extends GameBetBaseMenu {

    private static int COUNT_SHUFFLE_BEFORE_SHOW_WIN_NUMBER = 12;

    private ButtonWidget shuffle;
    private ButtonWidget sub1Number;
    private ButtonWidget sub10Number;
    private ButtonWidget add1Number;
    private ButtonWidget add10Number;
    private ImageWidget diceImage1;
    private ImageWidget diceImage2;
    private TextWidget number;
    private int currentNumber = 2;
    private TextWidget winFactor;
    ref Param3<int, int, DayZPlayer> parameterShuffel
    private EffectSound effect_sound;
    private EffectSound lose_sound;
    private EffectSound win_sound;
    private ref Timer imageShuffleTimer;
    private int currentCountBeforeSendShuffle = 0;
    private int winFactorInt = 2;

    int winImageNumber1;
    int winImageNumber2;


    override Widget Init() {
        if(IsInitialized()) {
            DebugMessageCasino("Widget is all ready initialized");

            return layoutRoot;
        }

        widgetPath = "DayZCasinoV2/layouts/BetDice.layout";
        super.Init();

        shuffle = ButtonWidget.Cast(layoutRoot.FindAnyWidget("shuffle"));
        number = TextWidget.Cast(layoutRoot.FindAnyWidget("number"));
        number.SetText(currentNumber.ToString());

        sub1Number = ButtonWidget.Cast(layoutRoot.FindAnyWidget("sub1Number"));
        sub10Number = ButtonWidget.Cast(layoutRoot.FindAnyWidget("sub10Number"));
        add1Number = ButtonWidget.Cast(layoutRoot.FindAnyWidget("add1Number"));
        add10Number = ButtonWidget.Cast(layoutRoot.FindAnyWidget("add10Number"));


        winFactor = TextWidget.Cast(layoutRoot.FindAnyWidget("winFactor"));

        diceImage1 = ImageWidget.Cast(layoutRoot.FindAnyWidget("diceImage1"));
        diceImage1.LoadImageFile(0, "DayZCasinoV2/data/dice/dice1.edds");
        diceImage1.LoadImageFile(1, "DayZCasinoV2/data/dice/dice2.edds");
        diceImage1.LoadImageFile(2, "DayZCasinoV2/data/dice/dice3.edds");
        diceImage1.LoadImageFile(3, "DayZCasinoV2/data/dice/dice4.edds");
        diceImage1.LoadImageFile(4, "DayZCasinoV2/data/dice/dice5.edds");
        diceImage1.LoadImageFile(5, "DayZCasinoV2/data/dice/dice6.edds");

        diceImage2 = ImageWidget.Cast(layoutRoot.FindAnyWidget("diceImage2"));
        diceImage2.LoadImageFile(0, "DayZCasinoV2/data/dice/dice1.edds");
        diceImage2.LoadImageFile(1, "DayZCasinoV2/data/dice/dice2.edds");
        diceImage2.LoadImageFile(2, "DayZCasinoV2/data/dice/dice3.edds");
        diceImage2.LoadImageFile(3, "DayZCasinoV2/data/dice/dice4.edds");
        diceImage2.LoadImageFile(4, "DayZCasinoV2/data/dice/dice5.edds");
        diceImage2.LoadImageFile(5, "DayZCasinoV2/data/dice/dice6.edds");

        diceImage1.SetImage(0);
        diceImage2.SetImage(0);
        winFactor.SetText("2");

        maxChipsUse = casinoConfig.diceSettings.maxBet;
        minChipsUse = casinoConfig.diceSettings.minBet;

        effect_sound = SEffectManager.CreateSound("DayZCasino_CLACK_SoundSet", player.GetPosition());
        win_sound = SEffectManager.CreateSound("DayZCasino_WIN_SoundSet", player.GetPosition());
        lose_sound = SEffectManager.CreateSound("DayZCasino_LOSE_SoundSet", player.GetPosition());

        return layoutRoot;
    }

    override void OnShow() {
        if(isMenuOpen) {
            DebugMessageCasino("Menu is already open");
            return;
        }
        if(winFactorInt && winFactor) winFactor.SetText(winFactorInt.ToString());
        super.OnShow();
    }

    override bool OnClick(Widget w, int x, int y, int button)	{
        DebugMessageCasino("on click action super");
        bool actionRuns = super.OnClick(w, x, y, button);

        if(actionRuns) {
            return actionRuns;
        } else if(w == shuffle) {
            DebugMessageCasino("click shuffle");
            Play();
            return true;
        } else if(w == add1Number) {
            UpdateNumber(1);
            return true;
        } else if(w == add10Number) {
            UpdateNumber(10);
            return true;
        } else if(w == sub1Number) {
            UpdateNumber(-1);
            return true;
        } else if(w == sub10Number) {
            UpdateNumber(-10);
            return true;
        }

        return false;
    }

    private void UpdateNumber(int addNumber) {
        currentNumber += addNumber;

        if(currentNumber < 2) {
            currentNumber = 2;
        } else if(currentNumber > 12) {
            currentNumber = 12;
        }

        number.SetText(currentNumber.ToString());
    }


    void SetWinFactor(int winF) {
        winFactorInt = winF;
        DebugMessageCasino("winFactorInt " + winFactorInt.ToString());

        if(winFactor) winFactor.SetText(winFactorInt.ToString());
    }

    override void EndGame() {
        super.EndGame();
        imageShuffleTimer.Stop();
        shuffle.Show(true);
        add1Number.Show(true);
        add10Number.Show(true);
        sub1Number.Show(true);
        sub10Number.Show(true);
    }

    override protected void Play() {
        if(CanPlayGame()) {
            super.Play();
            shuffle.Show(false);
            add1Number.Show(false);
            add10Number.Show(false);
            sub1Number.Show(false);
            sub10Number.Show(false);

            parameterShuffel = new Param3<int, int, DayZPlayer>(chipsValue, currentNumber, player);
            DebugMessageCasino("create timer");
            currentCountBeforeSendShuffle = 0;
            imageShuffleTimer = new Timer();

            imageShuffleTimer.Run(0.25, this, "SwitchImage", null, true);

            DebugMessageCasino("chipsBet value is " + chipsValue);
            DebugMessageCasino("numberValue value is " + currentNumber);
        }
    }


    private void SwitchImage() {
        DebugMessageCasino("change image");

        if(currentCountBeforeSendShuffle == 0) {
            GetGame().RPCSingleParam(player, DAYZ_CASINO_SHUFFEL_BET_DICE, parameterShuffel, true);
            DebugMessageCasino("has send to server ");
        }

        if(winImageNumber1 != 10 && COUNT_SHUFFLE_BEFORE_SHOW_WIN_NUMBER <= currentCountBeforeSendShuffle) {
            if(lastWinChips > 0) {
                if(false == win_sound.SoundPlay()) {
                    DebugMessageCasino("win sound not loaded");
                }
            } else {
                if(false == lose_sound.SoundPlay()) {
                    DebugMessageCasino("lose sound not loaded");
                }
            }

            diceImage1.SetImage(winImageNumber1);
            diceImage2.SetImage(winImageNumber2);
            winImageNumber1 = 10;
            winImageNumber2 = 10;
            lastWin.SetText(lastWinChips.ToString());
            countChips.SetText(currentAmount.ToString());

            EndGame();
            return;
        }

        if(false == effect_sound.SoundPlay()) {
            DebugMessageCasino("sound not loaded");
        }

        diceImage1.SetImage(Math.RandomIntInclusive(0, 6));
        diceImage2.SetImage(Math.RandomIntInclusive(0, 6));

        if(30 == currentCountBeforeSendShuffle) {
            DebugMessageCasino("No response from Server");

        }

        ++currentCountBeforeSendShuffle;
    }
}
