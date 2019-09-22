class BetDiceMenu extends BaseMenu
{

    private static int COUNT_SHUFFLE_BEFORE_SHOW_WIN_NUMBER = 12;

	private ButtonWidget shuffle;
	private ImageWidget diceImage;
	private XComboBoxWidget number;
	ref Param3<int, int, DayZPlayer> parameterShuffel
	private EffectSound effect_sound;
	private EffectSound lose_sound;
	private EffectSound win_sound;
    private ref Timer imageShuffleTimer;
    private int currentCountBeforeSendShuffle = 0;

    int winImageNumber;


	override Widget Init()
	{
		if (IsInitialized()) {
			DebugMessageCasino("Widget is all ready initialized");
			
			return widget;
		}

        widgetPath = "DayZCasino/layouts/BetDice.layout";
		super.Init();

		shuffle = ButtonWidget.Cast(widget.FindAnyWidget( "shuffle" ));
        WidgetEventHandler.GetInstance().RegisterOnMouseButtonDown(shuffle,  this, "OnClick" );
		number = XComboBoxWidget.Cast( widget.FindAnyWidget( "number" ));

        diceImage = ImageWidget.Cast(widget.FindAnyWidget( "diceImage" ));
        diceImage.LoadImageFile(0, "{79BC5FA94F25EF0B}DayZCasino/data/dice/dice1.edds");
        diceImage.LoadImageFile(1, "{275476EAF0A86104}DayZCasino/data/dice/dice2.edds");
        diceImage.LoadImageFile(2, "{D35C3172FD750970}DayZCasino/data/dice/dice3.edds");
        diceImage.LoadImageFile(3, "{9A84246D8FB37D1A}DayZCasino/data/dice/dice4.edds");
        diceImage.LoadImageFile(4, "{6E8C63F5826E156E}DayZCasino/data/dice/dice5.edds");
        diceImage.LoadImageFile(5, "{30644AB63DE39B61}DayZCasino/data/dice/dice6.edds");

		return widget;
	}
	
	override void OnShow()
	{
		if (isMenuOpen) {
			DebugMessageCasino("Menu is already open");
			return;
		}
		
		super.OnShow();

		diceImage.SetImage(0);
		effect_sound = SEffectManager.CreateSound("DayZCasino_CLACK_SoundSet", player.GetPosition());
		win_sound = SEffectManager.CreateSound("DayZCasino_WIN_SoundSet", player.GetPosition());
		lose_sound = SEffectManager.CreateSound("DayZCasino_LOSE_SoundSet", player.GetPosition());
	}

	override bool OnClick( Widget w, int x, int y, int button )	{
		DebugMessageCasino("on click action super");
		bool actionRuns = super.OnClick(w, x, y, button);

        if (!actionRuns && w == shuffle){
            DebugMessageCasino("click shuffle");
            Play();
            return true;
        }

		return false;
	}

    void EndGame() {
        imageShuffleTimer.Stop();
        cancel.Show(true);
        shuffle.Show(true);
    }
	
	private void Play(){
		if (player && isMenuOpen && number && chipsBet) {
			int chipsValue = GetCurrenBet();
			int numberValue = number.GetCurrentItem() + 1;
			int currentAmount = inventory.GetPlayerChipsAmount(GetGame().GetPlayer());
			if (chipsValue > currentAmount) {
				countChips.SetText("" + currentAmount);
				message.SetText("#Not_enough_chips_available");
				message.Show(true);
				
				return;
			}
			message.Show(false);
			
			cancel.Show(false);
			shuffle.Show(false);
			
			parameterShuffel = new Param3<int, int, DayZPlayer>(chipsValue, numberValue, player);
			DebugMessageCasino("create timer");
			currentCountBeforeSendShuffle = 0;
			imageShuffleTimer = new Timer();
			
			imageShuffleTimer.Run(0.25, this, "SwitchImage", null, true);

			DebugMessageCasino("chipsBet value is " + chipsValue);
			DebugMessageCasino("numberValue value is " + numberValue);
		}
	}
	
	private void SwitchImage() {
		DebugMessageCasino("change image");

		if (currentCountBeforeSendShuffle == 0) {
			GetGame().RPCSingleParam(player, DAYZ_CASINO_SHUFFEL_BET_DICE, parameterShuffel, true);
			DebugMessageCasino("has send to server ");
		}
				
		if (winImageNumber != 10 && COUNT_SHUFFLE_BEFORE_SHOW_WIN_NUMBER == currentCountBeforeSendShuffle) {
			if (lastWinChips > 0){
				if (false == win_sound.SoundPlay()) {
					DebugMessageCasino("win sound not loaded");
				}
			} else {
				if (false == lose_sound.SoundPlay()) {
					DebugMessageCasino("lose sound not loaded");
				}
			}
			
			diceImage.SetImage(winImageNumber);
			winImageNumber = 10;
			lastWin.SetText("" + lastWinChips);
			countChips.SetText("" + currentAmount);
			imageShuffleTimer.Stop();
			cancel.Show(true);
			shuffle.Show(true);
			return;
		}
		
		if (false == effect_sound.SoundPlay()) {
			DebugMessageCasino("sound not loaded");
		}
		
		diceImage.SetImage(Math.RandomInt(0, 6));
		
		if (20 == currentCountBeforeSendShuffle) {
			DebugMessageCasino("No response from Server");
			imageShuffleTimer.Stop();
			cancel.Show(true);
			shuffle.Show(true);
		}
		
		++currentCountBeforeSendShuffle;
	}
}