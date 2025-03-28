class LuckyWheelMenu extends BaseMenu {
    static int COUNT_SHUFFLE_BEFORE_SHOW_WIN_WHEEL = 360;
    private ButtonWidget rotate;
    private ImageWidget luckyWheel;
    private EffectSound effect_sound;
    private EffectSound lose_sound;
    private EffectSound win_sound;
    private EffectSound jackpot_sound;
    private ref Timer imageRotateTimer;
    private int currentCountBeforeGoToWin;
    private ref LuckyWheelMapping luckyWheelMapping;

    private MultilineTextWidget jackpotWidget;
    private MultilineTextWidget betPerRoll;
    private TextWidget winView;
    private int currentDegree;
    private int currentIntervalTime;

    int winDegree = 500;
    bool jackpotWin;
    int jackpot;

    override Widget Init() {
        if(IsInitialized()) {
            return layoutRoot;
        }

        widgetPath = "DayZCasinoV2/layouts/LuckyWheel.layout";
        super.Init();

        rotate = ButtonWidget.Cast(layoutRoot.FindAnyWidget("rotate"));

        jackpotWidget = MultilineTextWidget.Cast(layoutRoot.FindAnyWidget("jackpot"));
        betPerRoll = MultilineTextWidget.Cast(layoutRoot.FindAnyWidget("betPerRoll"));
        winView = TextWidget.Cast(layoutRoot.FindAnyWidget("winView"));
        luckyWheel = ImageWidget.Cast(layoutRoot.FindAnyWidget("luckyWheel"));
        luckyWheel.LoadImageFile(0, "DayZCasinoV2/data/luckywheel/tbmWheel.edds");

        return layoutRoot;
    }

    override void OnShow() {
        if(isMenuOpen) {
            return;
        }

        super.OnShow();

        betPerRoll.SetText(casinoConfig.luckyWheelSettings.chipsBet.ToString());
        luckyWheel.SetImage(0);
        effect_sound = SEffectManager.CreateSound("DayZCasino_FLAP_SoundSet", player.GetPosition());
        win_sound = SEffectManager.CreateSound("DayZCasino_WIN_SoundSet", player.GetPosition());
        jackpot_sound = SEffectManager.CreateSound("DayZCasino_JACKPOT_SoundSet", player.GetPosition());
        lose_sound = SEffectManager.CreateSound("DayZCasino_LOSE_SoundSet", player.GetPosition());
        GetGame().RPCSingleParam(player, DAYZ_CASINO_LUCKY_WHEEL_GET_JACKPOT, new Param1<DayZPlayer>(player), true);
    }

    override bool OnClick(Widget w, int x, int y, int button)	{
        bool actionRuns = super.OnClick(w, x, y, button);

        if(actionRuns) {
            return actionRuns;
        } else if(w == rotate) {
            Play();
            return true;
        }

        return false;
    }

    override void SetConfig(CasinoConfig casinoConfigExt) {
        super.SetConfig(casinoConfigExt);
        luckyWheelMapping = new LuckyWheelMapping(casinoConfig.luckyWheelSettings);
    }

    override void EndGame() {
        imageRotateTimer.Stop();
        rotate.Show(true);
    }

    void UpdateJackpot(int jackpotExt) {
        jackpot = jackpotExt;
        jackpotWidget.SetText("" + jackpot);
    }

    override void Play() {
        if(CanPlayGame()) {
            int currentAmountLocal = inventory.GetPlayerChipsAmount(GetGame().GetPlayer());
            if(casinoConfig.luckyWheelSettings.chipsBet > currentAmountLocal) {
                countChips.SetText(currentAmountLocal.ToString());
                message.SetText("#Not_enough_chips_available");
                message.Show(true);

                return;
            }
            jackpotWin = false;
            currentCountBeforeGoToWin = 0;
            message.Show(false);

            cancel.Show(false);
            rotate.Show(false);

            Param1<DayZPlayer> parameterRotate = new Param1<DayZPlayer>(player);
            GetGame().RPCSingleParam(player, DAYZ_CASINO_LUCKY_WHEEL_START, parameterRotate, true);
            imageRotateTimer = new Timer();

            imageRotateTimer.Run(0.00001, this, "RotateImage", null, true);
        }
    }

    private void RotateImage() {
        if(winDegree != 500 && COUNT_SHUFFLE_BEFORE_SHOW_WIN_WHEEL <= currentCountBeforeGoToWin && winDegree == currentDegree) {
            if(lastWinChips > 0 && jackpotWin) {
                jackpot_sound.SoundPlay();
            } else if(lastWinChips > 0 && !jackpotWin) {
                win_sound.SoundPlay();
            } else {
                lose_sound.SoundPlay();
            }
            winDegree = 500;
            lastWin.SetText("" + lastWinChips);
            countChips.SetText("" + currentAmount);
            imageRotateTimer.Stop();
            jackpotWin = false;
            jackpotWidget.SetText("" + jackpot);
            cancel.Show(true);
            rotate.Show(true);
            return;
        }

        currentDegree++;

        if(currentDegree == 360) {
            currentDegree = 0;
        }

        if((currentDegree % 10) == 0) {
            effect_sound.SoundPlay();
            int index = currentDegree / 10;

            LuckyWheelWin currentSelected = luckyWheelMapping.GetLuckyWheelWinByIndex(index);
            string selectedWinAmount = "" + currentSelected.GetWinAmmount() + " Chips";

            if(currentSelected.GetLuckyDegree() == DAYZ_CASINO_LUCKY_WHEEL_JACKPOT_DEGREE) {
                selectedWinAmount = "#jackpot";
            }

            winView.SetText(selectedWinAmount);
        }

        luckyWheel.SetRotation(0, 0, currentDegree);

        if(360 == currentCountBeforeGoToWin && winDegree == 500) {
            imageRotateTimer.Stop();
            cancel.Show(true);
            rotate.Show(true);
        }

        ++currentCountBeforeGoToWin;
    }
}