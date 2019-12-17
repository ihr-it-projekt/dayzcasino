class RatRaceMenu extends GameBetBaseMenu
{

    private static int COUNT_BEFORE_START_RACE = 3;

	private ButtonWidget startRace;
	private ButtonWidget newRace;
	private ImageWidget ratImage1;
	private ImageWidget ratImage2;
	private XComboBoxWidget ratNumber;
	private EffectSound background_sound;
	private EffectSound lose_sound;
	private EffectSound win_sound;
    protected MultilineTextWidget countDownWidget;
    private ref Timer startRaceTimer;
    private int currentAnimationStep = 0;
    private int currentCountdown = 0;
	private bool raceAnimated = false;
	private ref Timer animationTimer;

	private Race race;

	override Widget Init()
	{
		if (IsInitialized()) {
			DebugMessageCasino("Widget is all ready initialized");
			
			return layoutRoot;
		}

        widgetPath = "DayZCasino/layouts/RatRace.layout";
		super.Init();

		startRace = ButtonWidget.Cast(layoutRoot.FindAnyWidget("startRace" ));
		newRace = ButtonWidget.Cast(layoutRoot.FindAnyWidget( "newRace" ));
        WidgetEventHandler.GetInstance().RegisterOnMouseButtonDown(startRace,  this, "OnClick" );
        WidgetEventHandler.GetInstance().RegisterOnMouseButtonDown(newRace,  this, "OnClick" );
		ratNumber = XComboBoxWidget.Cast( layoutRoot.FindAnyWidget( "ratNumber" ));
		countDownWidget = MultilineTextWidget.Cast( layoutRoot.FindAnyWidget( "countDownWidget" ));
		countDownWidget.Show(false);

        ratImage1 = ImageWidget.Cast(layoutRoot.FindAnyWidget( "ratImage1" ));
        ratImage1.LoadImageFile(0, "DayZCasino/data/ratrace/rat.edds");
        ratImage2 = ImageWidget.Cast(layoutRoot.FindAnyWidget( "ratImage2" ));
        ratImage2.LoadImageFile(0, "DayZCasino/data/ratrace/rat.edds");
		
		ratImage1.SetImage(0);
		ratImage2.SetImage(0);
		background_sound = SEffectManager.CreateSound("DayZCasino_RACE_BACKGROUND_SoundSet", player.GetPosition());
		win_sound = SEffectManager.CreateSound("DayZCasino_WIN_SoundSet", player.GetPosition());
		lose_sound = SEffectManager.CreateSound("DayZCasino_LOSE_SoundSet", player.GetPosition());
		
		maxChipsUse = casinoConfig.ratRaceMaxChipsUse;

		return layoutRoot;
	}
	
	override void OnShow()
	{
		if (isMenuOpen) {
			DebugMessageCasino("Menu is already open");
			return;
		}
		
		super.OnShow();
		
		GetGame().RPCSingleParam(player, DAYZ_CASINO_NEW_RAT_RACE, new Param1<DayZPlayer>(GetGame().GetPlayer()), true);
		newRace.Show(false);
		startRace.Show(false);
		countDownWidget.Show(false);
	}

	override bool OnClick( Widget w, int x, int y, int button )	{
		DebugMessageCasino("on click action super");
		bool actionRuns = super.OnClick(w, x, y, button);

        if (actionRuns) {
            return actionRuns;
        } else if (w == startRace){
            DebugMessageCasino("click startRace");
            Play();
            return true;
        } else if (w == newRace){
            DebugMessageCasino("click newRace");
            GetGame().RPCSingleParam(player, DAYZ_CASINO_NEW_RAT_RACE, new Param1<DayZPlayer>(GetGame().GetPlayer()), true);;
			newRace.Show(false);
            return true;
        }

		return false;
	}
	
	void ResetGame(Race raceFromEvent) {
		startRace.Show(true);
		race = raceFromEvent;
		DebugMessageCasino("has race object " + race.isAnimationFinished.ToString());
		raceAnimated = false;
	}

    override void Play(){
        if (CanPlayGame()) {
            super.Play();
			int numberValue = ratNumber.GetCurrentItem() + 1;

			startRace.Show(false);
			
			GetGame().RPCSingleParam(player, DAYZ_CASINO_RESPONSE_SHUFFEL_START_RATE_RACE, new Param3<int, int, DayZPlayer>(chipsValue, numberValue, player), true);
			DebugMessageCasino("create timer");
			currentCountdown = 3;
			countDownWidget.Show(true);
			countDownWidget.SetText(currentCountdown.ToString());
			startRaceTimer = new Timer();
			
			startRaceTimer.Run(1, this, "RunRace", null, true);
            

			DebugMessageCasino("chipsBet value is " + chipsValue);
			DebugMessageCasino("numberValue value is " + numberValue);
		}
	}
	
	override void EndGame() {
        super.EndGame();
		countDownWidget.Show(false);
		startRaceTimer.Stop();
		animationTimer.Stop();
		newRace.Show(true);
	}
	
	void AnimateRace(Race raceFromExtern) {
		race = raceFromExtern;
		animationTimer = new Timer();
		animationTimer.Run(0.00001, this, "AnimateStep", null, true);
		currentAnimationStep = 0;
	}
	
	void AnimateStep() {
		if (raceAnimated) {
			return;
		}
		race.AnimateRace(currentAnimationStep);
		currentAnimationStep++;
		
		raceAnimated = race.isAnimationFinished;
	}
	
	private void RunRace() {
		if (race && race.winRat && 0 > currentCountdown) {
			countDownWidget.SetText(currentCountdown.ToString());
			
			if (0 == currentCountdown) {
				if (false == background_sound.SoundPlay()) {
	                DebugMessageCasino("sound not loaded");
	            }
			}
			
			currentCountdown--;
		} else if (race && race.winRat && raceAnimated) {
			if (lastWinChips > 0){
				if (false == win_sound.SoundPlay()) {
					DebugMessageCasino("win sound not loaded");
				}
			} else {
				if (false == lose_sound.SoundPlay()) {
					DebugMessageCasino("lose sound not loaded");
				}
			}
			
			lastWin.SetText(lastWinChips.ToString());
			countChips.SetText(currentAmount.ToString());
			
			currentCountdown--;
			EndGame();
		} else if (-10 == currentCountdown) {
			DebugMessageCasino("No response from Server");
			EndGame();
		}
		
	}
}