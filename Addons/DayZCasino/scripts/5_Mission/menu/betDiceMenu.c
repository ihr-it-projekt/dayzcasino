

class BetDiceMenue extends BaseMenu
{
	private static int BET1 = 0;
	private static int BET5 = 1;
	private static int BET10 = 2;
	private static int BET25 = 3;
	private static int BET50 = 4;
	private static int BET100 = 5;
	private static int BET250 = 6;
	private static int BET500 = 7;
	private static int BET1000 = 8;
	private static int COUNT_SHUFFLE_BEFOR_SHOW_WIN_NUMBER = 12;

	private ButtonWidget shuffle;
	private ImageWidget diceImage;
	private ref Timer imageShufelTimer;
	private int currentCountBeforSendShufel = 0;
	private int winImageNumber;
	ref Param3<int, int, DayZPlayer> parameterShuffel
	private EffectSound effect_sound;
	private EffectSound lose_sound;
	private EffectSound win_sound;

		
	override Widget Init()
	{
		if (IsInitialized()) {
			DebugMessageCasino("Widget is all ready initialized");
			
			return widget;
		}

        widgetPath = "DayZCasino/layouts/BetDice.layout";
		super.Init();

		if(!widget){
			shuffle = ButtonWidget.Cast( widget.FindAnyWidget( "shuffle" ));
			WidgetEventHandler.GetInstance().RegisterOnMouseButtonDown( shuffle,  this, "OnClick" );

			diceImage = ImageWidget.Cast( widget.FindAnyWidget( "diceImage" ));
            diceImage.LoadImageFile(0, "{79BC5FA94F25EF0B}DayZCasino/data/dice/dice1.edds");
            diceImage.LoadImageFile(1, "{275476EAF0A86104}DayZCasino/data/dice/dice2.edds");
            diceImage.LoadImageFile(2, "{D35C3172FD750970}DayZCasino/data/dice/dice3.edds");
            diceImage.LoadImageFile(3, "{9A84246D8FB37D1A}DayZCasino/data/dice/dice4.edds");
            diceImage.LoadImageFile(4, "{6E8C63F5826E156E}DayZCasino/data/dice/dice5.edds");
            diceImage.LoadImageFile(5, "{30644AB63DE39B61}DayZCasino/data/dice/dice6.edds");
		}
		
		return widget;
	}
	
	override void OnShow()
	{
		if (isMenuOpen) {
			DebugMessageCasino("Menue is already open");
			return;
		}
		
		super.OnShow();
		currentAmmount = GetPlayerChipsAmount(GetGame().GetPlayer());
		countChips.SetText("" + currentAmmount);
		lastWin.SetText("0");
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
            play();
            return true
        }

		return false;
	}
	
	override void HandleEvents(PlayerIdentity sender, Object target, int rpc_type, ParamsReadContext ctx) {
		if (rpc_type == DAYZ_CASINO_SHUFFEL_BET_DICE && IsServerCasino()) {
			Param3<int, int, DayZPlayer> parameterShuffel;
			if (ctx.Read(parameterShuffel)) {
				player = parameterShuffel.param3;
				DebugMessageCasino("Check Player has chips");
				if (PlayerHasEnoghChips(player, parameterShuffel.param1)){
					int luckNumber = Math.RandomInt(1, 6);
					
					if (DAYZ_CASINO_DEBUG) {
						luckNumber = 1;
					}
					
					int winSum = 0;
					
					if (parameterShuffel.param2 == luckNumber) {
						DebugMessageCasino("Win");
						winSum = 3 * parameterShuffel.param1;
						
					} else {
						DebugMessageCasino("lose");
						winSum = -1 * parameterShuffel.param1;
					}
					
					AddChipsToPlayer(player, winSum);
					int currentChips = GetPlayerChipsAmount(player);
					DebugMessageCasino("server: player has " + currentAmmount);
					Param3<int, int, int> parameterResponse = new Param3<int, int, int>(luckNumber, winSum, currentChips);
					
					GetGame().RPCSingleParam(player, DAYZ_CASINO_RESPONSE_SHUFFEL_BET_DICE, parameterResponse, true, player.GetIdentity());
					DebugMessageCasino("has message send to player");
				} else {
					GetGame().RPCSingleParam(player, DAYZ_CASINO_RESPONSE_SHUFFEL_BET_DICE_NOT_ENOUGH_BALANCE, new Param1<bool>(true), true,  player.GetIdentity());
				}
			}
		}
		if (rpc_type == DAYZ_CASINO_RESPONSE_SHUFFEL_BET_DICE && false == IsServerCasino()) {
			DebugMessageCasino("recive response shuffle");
			Param3<int, int, int> parameterShuffelResponse;
			if (ctx.Read(parameterShuffelResponse)) {
				DebugMessageCasino("has recive response for bet dice");
				winImageNumber = parameterShuffelResponse.param1 - 1;
				lastWinChips = parameterShuffelResponse.param2;
				currentAmmount += parameterShuffelResponse.param2;
				DebugMessageCasino("new ammount is " + currentAmmount);

			}
		}
		if (rpc_type == DAYZ_CASINO_RESPONSE_SHUFFEL_BET_DICE_NOT_ENOUGH_BALANCE && false == IsServerCasino()) {
			DebugMessageCasino("recive not enough ballance");
			imageShufelTimer.Stop();
			cancel.Show(true);
			shuffle.Show(true);
		}
	}


	void play(){
		if (player && isMenuOpen && number && chipsBet) {
			int chipsValue = GetCurrenBet();
			int numberValue = number.GetCurrentItem() + 1;
			
			if (chipsValue > currentAmmount) {
				DebugMessageCasino("chipsVaue" + chipsValue);
				DebugMessageCasino("currentAmmount" + currentAmmount);
				countChips.SetText("" + currentAmmount);
				message.SetText("#Not_enough_chips_available");
				message.Show(true);
				
				return;
			}
			message.Show(false);
			
			cancel.Show(false);
			shuffle.Show(false);
			
			parameterShuffel = new Param3<int, int, DayZPlayer>(chipsValue, numberValue, player);
			DebugMessageCasino("create timer");
			currentCountBeforSendShufel = 0;
			imageShufelTimer = new Timer();
			
			imageShufelTimer.Run(0.25, this, "SwitchImage", null, true);
		
			
			DebugMessageCasino("chipsBet value is " + chipsValue);
			DebugMessageCasino("numberValue value is " + numberValue);
		}
	}
	
	void SwitchImage() {
		DebugMessageCasino("change image");

		if (currentCountBeforSendShufel == 0) {
			GetGame().RPCSingleParam(player, DAYZ_CASINO_SHUFFEL_BET_DICE, parameterShuffel, true);
			DebugMessageCasino("has send to server ");
		}
				
		if (winImageNumber != 10 && COUNT_SHUFFLE_BEFOR_SHOW_WIN_NUMBER == currentCountBeforSendShufel) {
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
			countChips.SetText("" + currentAmmount);
			imageShufelTimer.Stop();
			cancel.Show(true);
			shuffle.Show(true);
			return;
		}
		
		if (false == effect_sound.SoundPlay()) {
			DebugMessageCasino("sound not loaded");
		}
		
		diceImage.SetImage(Math.RandomInt(0, 5));
		
		if (20 == currentCountBeforSendShufel) {
			DebugMessageCasino("No respons from Server");
			imageShufelTimer.Stop();
			cancel.Show(true);
			shuffle.Show(true);
		}
		
		++currentCountBeforSendShufel;
	}
}