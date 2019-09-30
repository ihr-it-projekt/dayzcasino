class LuckyWheelMenu extends BaseMenu
{
    static int COUNT_SHUFFLE_BEFORE_SHOW_WIN_WHEEL = 360;
	private ButtonWidget rotate;
	private ImageWidget luckyWheel;
	private ImageWidget arrow;
	private EffectSound effect_sound;
	private EffectSound lose_sound;
	private EffectSound win_sound;
	private EffectSound jackpot_sound;
    private ref Timer imageRotateTimer;
    private CasinoConfig casinoConfig;
    private int currentCountBeforeGoToWin;
    private ref LuckyWheelMapping luckyWheelMapping;

    private MultilineTextWidget jackpotWidget;
    private TextWidget winView;
    private int currentDegree;

    int winDegree = 500;
    bool jackpotWin;
    int jackpot;

	override Widget Init()
	{
		if (IsInitialized()) {
			DebugMessageCasino("Widget is all ready initialized");
			
			return widget;
		}

        widgetPath = "DayZCasino/layouts/LuckyWheel.layout";
		super.Init();

        rotate = ButtonWidget.Cast(widget.FindAnyWidget( "rotate" ));
        WidgetEventHandler.GetInstance().RegisterOnMouseButtonDown(rotate,  this, "OnClick");

        jackpotWidget = MultilineTextWidget.Cast(widget.FindAnyWidget( "jackpot" ));
        winView = TextWidget.Cast(widget.FindAnyWidget( "winView" ));
        arrow = ImageWidget.Cast(widget.FindAnyWidget( "arrow" ));
        arrow.LoadImageFile(0, "DayZCasino/data/luckywheel/arrow.edds");
        luckyWheel = ImageWidget.Cast(widget.FindAnyWidget( "luckyWheel" ));
        luckyWheel.LoadImageFile(0, "DayZCasino/data/luckywheel/luckywheel.edds");

		return widget;
	}
	
	override void OnShow()
	{
		if (isMenuOpen) {
			DebugMessageCasino("Menu is already open");
			return;
		}
		
		super.OnShow();

        arrow.SetImage(0);
        luckyWheel.SetImage(0);
		effect_sound = SEffectManager.CreateSound("DayZCasino_FLAP_SoundSet", player.GetPosition());
		win_sound = SEffectManager.CreateSound("DayZCasino_WIN_SoundSet", player.GetPosition());
		jackpot_sound = SEffectManager.CreateSound("DayZCasino_JACKPOT_SoundSet", player.GetPosition());
		lose_sound = SEffectManager.CreateSound("DayZCasino_LOSE_SoundSet", player.GetPosition())
        GetGame().RPCSingleParam(player, DAYZ_CASINO_LUCKY_WHEEL_GET_JACKPOT,  new Param1<DayZPlayer>(player), true);
	}

	override bool OnClick( Widget w, int x, int y, int button )	{
		DebugMessageCasino("on click action super");
		bool actionRuns = super.OnClick(w, x, y, button);

        if (!actionRuns && w == rotate){
            DebugMessageCasino("click shuffle");
            Play();
            return true;
        }

		return false;
	}

	void SetConfig(CasinoConfig casinoConfigExt) {
        casinoConfig = casinoConfigExt;
        luckyWheelMapping = new LuckyWheelMapping(casinoConfig);
	}

    void EndGame() {
    imageRotateTimer.Stop();
        cancel.Show(true);
        rotate.Show(true);
    }

    void UpdateJackpot(int jackpotExt) {
        jackpot = jackpotExt;
        jackpotWidget.SetText("" + jackpot);
	}
	
	private void Play(){
		if (player && isMenuOpen) {
			int currentAmount = inventory.GetPlayerChipsAmount(GetGame().GetPlayer());
			if (casinoConfig.chipsValueLuckyWheel > currentAmount) {
				countChips.SetText("" + currentAmount);
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
			DebugMessageCasino("create timer");
            imageRotateTimer = new Timer();

            imageRotateTimer.Run(0.00001, this, "RotateImage", null, true);
		}
	}

	private void RotateImage() {
		if (winDegree != 500 && COUNT_SHUFFLE_BEFORE_SHOW_WIN_WHEEL <= currentCountBeforeGoToWin && winDegree == currentDegree) {
            if (lastWinChips > 0 && jackpotWin){
                if (false == jackpot_sound.SoundPlay()) {
                    DebugMessageCasino("win sound not loaded");
                }
            } else if (lastWinChips > 0 && !jackpotWin){
                if (false == win_sound.SoundPlay()) {
                    DebugMessageCasino("win sound not loaded");
                }
            } else {
                if (false == lose_sound.SoundPlay()) {
                    DebugMessageCasino("lose sound not loaded");
                }
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

        if (currentDegree == 360) {
            currentDegree = 0;
        }

		if ((currentDegree % 10) == 0) {
			effect_sound.SoundPlay();
			int index = currentDegree / 10;

            LuckyWheelWin currentSelected = luckyWheelMapping.GetLuckyWheelWinByIndex(index);
            string selectedWinAmount = "" + currentSelected.GetWinAmmount() + "x";

            if (currentSelected.GetLuckyDegree() == DAYZ_CASINO_LUCKY_WHEEL_JACKPOT_DEGREE) {
                selectedWinAmount = "#jackpot";
            }

            winView.SetText(selectedWinAmount);
		}

        luckyWheel.SetRotation(0,0,currentDegree);

		if (360 == currentCountBeforeGoToWin && winDegree == 500) {
			DebugMessageCasino("No response from Server");
            imageRotateTimer.Stop();
			cancel.Show(true);
            rotate.Show(true);
		}
		
		++currentCountBeforeGoToWin;
	}
}