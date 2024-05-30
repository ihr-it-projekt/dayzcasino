class RatRaceMenu extends GameBetBaseMenu {

    private static int COUNT_BEFORE_START_RACE = 3;

    private ButtonWidget startRace;
    private ButtonWidget newRace;
    private ButtonWidget sub1Number;
    private ButtonWidget sub10Number;
    private ButtonWidget add1Number;
    private ButtonWidget add10Number;
    private int currentNumber = 1;
    private ref array<ImageWidget> ratImages;
    private ref array<TextWidget> ratQuats;
    private TextWidget ratNumber;
    private TextWidget goalTextWidget;
    private float initialPositionX;
    private float initialPositionY;
    private float goalPositionX;
    private float goalPositionY;
    private EffectSound background_sound;
    private EffectSound lose_sound;
    private EffectSound win_sound;
    private EffectSound countdown_1_sound;
    private EffectSound countdown_2_sound;
    private EffectSound countdown_3_sound;
    private EffectSound shoot_sound;
    private MultilineTextWidget countDownWidget;
    private ref Timer startRaceTimer;
    private int currentAnimationStep = 0;
    private int currentCountdown = 0;
    private int timoutRaceTimer = 0;
    private bool raceAnimated = false;
    private ref Timer animationTimer;

    private ref Race race;

    override Widget Init() {
        if(IsInitialized()) {
            return layoutRoot;
        }

        widgetPath = "DayZCasinoV2/layouts/RatRace.layout";
        super.Init();

        ratImages = new array<ImageWidget>;
        ratQuats = new array<TextWidget>;

        goalTextWidget = TextWidget.Cast(layoutRoot.FindAnyWidget("goal1"));

        goalTextWidget.GetPos(goalPositionX, goalPositionY);

        for(int n = 0; n < DAYZ_CASINO_RAT_RACE_COUNT_RAT; n++) {
            int imageNumber = n + 1;
            ImageWidget ratImage = ImageWidget.Cast(layoutRoot.FindAnyWidget("ratImage" + imageNumber.ToString()));
            ratImage.LoadImageFile(0, "DayZCasinoV2/data/ratrace/rat.edds");
            ratImage.SetImage(0);
            ratImage.GetPos(initialPositionX, initialPositionY);
            ratImages.Insert(ratImage);

            TextWidget ratQuata = TextWidget.Cast(layoutRoot.FindAnyWidget("quota" + imageNumber.ToString()));
            ratQuats.Insert(ratQuata);
        }

        startRace = ButtonWidget.Cast(layoutRoot.FindAnyWidget("startRace"));
        newRace = ButtonWidget.Cast(layoutRoot.FindAnyWidget("newRace"));

        ratNumber = TextWidget.Cast(layoutRoot.FindAnyWidget("ratNumber"));
        ratNumber.SetText(currentNumber.ToString());

        countDownWidget = MultilineTextWidget.Cast(layoutRoot.FindAnyWidget("countDownWidget"));
        countDownWidget.Show(false);

        sub1Number = ButtonWidget.Cast(layoutRoot.FindAnyWidget("sub1Number"));
        sub10Number = ButtonWidget.Cast(layoutRoot.FindAnyWidget("sub10Number"));
        add1Number = ButtonWidget.Cast(layoutRoot.FindAnyWidget("add1Number"));
        add10Number = ButtonWidget.Cast(layoutRoot.FindAnyWidget("add10Number"));

        background_sound = SEffectManager.CreateSound("DayZCasino_RACE_BACKGROUND_SoundSet", player.GetPosition());
        countdown_1_sound = SEffectManager.CreateSound("DayZCasino_COUNTDOWN_1_SoundSet", player.GetPosition());
        countdown_2_sound = SEffectManager.CreateSound("DayZCasino_COUNTDOWN_2_SoundSet", player.GetPosition());
        countdown_3_sound = SEffectManager.CreateSound("DayZCasino_COUNTDOWN_3_SoundSet", player.GetPosition());
        shoot_sound = SEffectManager.CreateSound("DayZCasino_SHOOT_SoundSet", player.GetPosition());
        win_sound = SEffectManager.CreateSound("DayZCasino_WIN_SoundSet", player.GetPosition());
        lose_sound = SEffectManager.CreateSound("DayZCasino_LOSE_SoundSet", player.GetPosition());

        maxChipsUse = casinoConfig.ratRaceSettings.maxBet;
        minChipsUse = casinoConfig.ratRaceSettings.minBet;

        return layoutRoot;
    }

    override void OnShow() {
        if(isMenuOpen) {
            return;
        }

        super.OnShow();

        GetGame().RPCSingleParam(player, DAYZ_CASINO_NEW_RAT_RACE, new Param3<DayZPlayer, float, float>(GetGame().GetPlayer(), initialPositionX, goalPositionX), true);
        newRace.Show(false);
        startRace.Show(false);
        countDownWidget.Show(false);
    }

    override bool OnClick(Widget w, int x, int y, int button)	{
        bool actionRuns = super.OnClick(w, x, y, button);

        if(actionRuns) {
            return actionRuns;
        } else if(w == startRace) {
            Play();
            return true;
        } else if(w == newRace) {
            GetGame().RPCSingleParam(player, DAYZ_CASINO_NEW_RAT_RACE, new Param3<DayZPlayer, float, float>(GetGame().GetPlayer(), initialPositionX, goalPositionX), true);
            newRace.Show(false);
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

    void UpdateNumber(int addNumber) {
        currentNumber += addNumber;

        if(currentNumber < 1) {
            currentNumber = 1;
        } else if(currentNumber > DAYZ_CASINO_RAT_RACE_COUNT_RAT) {
            currentNumber = DAYZ_CASINO_RAT_RACE_COUNT_RAT;
        }

        ratNumber.SetText(currentNumber.ToString());
    }

    void ResetGame(Race raceFromEvent) {
        ResetRats();
        startRace.Show(true);
        message.Show(false);
        race = raceFromEvent;
        SetQouta();
        raceAnimated = false;
    }

    override void Play() {
        if(CanPlayGame()) {
            super.Play();

            add1Number.Show(false);
            add10Number.Show(false);
            sub1Number.Show(false);
            sub10Number.Show(false);
            startRace.Show(false);
            message.Show(false);

            GetGame().RPCSingleParam(player, DAYZ_CASINO_START_RAT_RACE, new Param3<int, int, DayZPlayer>(chipsValue, currentNumber, player), true);
            currentCountdown = 3;

            countDownWidget.SetText(currentCountdown.ToString());
            timoutRaceTimer = 0;
            startRaceTimer = new Timer();

            startRaceTimer.Run(1, this, "RunRace", null, true);
        }
    }

    override void EndGame() {
        super.EndGame();
        countDownWidget.Show(false);
        startRaceTimer.Stop();
        animationTimer.Stop();
        add1Number.Show(true);
        add10Number.Show(true);
        sub1Number.Show(true);
        sub10Number.Show(true);
        newRace.Show(true);
    }

    void AnimateRace(Race raceFromExtern) {
        race = raceFromExtern;
        race.SetImages(ratImages);
        animationTimer = new Timer();

        int countSteps = race.winRat.positions.Count();

        float stepTime = (DAYZ_CASINO_LENGTH_SOUND_RACE - 2) / countSteps;

        countDownWidget.Show(true);
        countdown_3_sound.SoundPlay();

        animationTimer.Run(stepTime, this, "AnimateStep", null, true);

        currentAnimationStep = 0;
    }

    void AnimateStep() {
        if(raceAnimated || currentCountdown > 0) {
            return;
        }
        race.AnimateStep(currentAnimationStep);
        currentAnimationStep++;

        raceAnimated = race.isAnimationFinished;

        if(race.winRat.hasPassGoal && !message.IsVisible()) {
            message.SetText("#rat_win " + race.winRat.number);
            message.Show(true);
            if(lastWinChips > 0) {
                win_sound.SoundPlay();
            } else {
                lose_sound.SoundPlay();
            }
            lastWin.SetText(lastWinChips.ToString());
            countChips.SetText(currentAmount.ToString());
        }
    }

    private void ResetRats() {
        foreach(ImageWidget ratImage: ratImages) {
            ratImage.SetPos(initialPositionX, initialPositionY);
        }
    }

    private void SetQouta() {
        foreach(int number, TextWidget ratQuat: ratQuats) {
            ratQuat.SetText(race.rats.Get(number).quote.ToString());
        }
    }

    private void RunRace() {
        if(race && race.winRat && -1 < currentCountdown) {
            currentCountdown--;
            countDownWidget.SetText(currentCountdown.ToString());

            if(2 == currentCountdown) {
                countdown_2_sound.SoundPlay();
            } else if(1 == currentCountdown) {
                countdown_1_sound.SoundPlay();
            } else if(0 == currentCountdown) {
                shoot_sound.SoundPlay();
                background_sound.SoundPlay();
                countDownWidget.Show(false);
            }
        } else if(race && race.winRat && raceAnimated) {
            EndGame();
        } else if((!race || !race.winRat) && 10 == timoutRaceTimer) {
            EndGame();
        }

        timoutRaceTimer ++;
    }
}