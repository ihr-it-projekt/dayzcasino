

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

	private ButtonWidget shuffel;
	private ButtonWidget cancel;
	private XComboBoxWidget number;
	private XComboBoxWidget chipsBet;
	private MultilineTextWidget countChips;
	private MultilineTextWidget lastWin;
	private MultilineTextWidget message;
	private ImageWidget diceImage;
	private ref Timer imageShufelTimer;
	private int currentCountBeforSendShufel = 0;
	private int winImageNumber;
	private int lastWinChips;
	private int currentAmmount;
	ref Param3<int, int, DayZPlayer> parameterShuffel
	private EffectSound effect_sound;

		
	override Widget Init()
	{
		if (IsInitialized()) {
			DebugMessageCasino("Widget is allreadyiIs initialized");
			
			return widget;
		}
		
		super.Init();
		
		
		DebugMessageCasino("init widget bet dice");
		
		if (IsServerCasino()){
			DebugMessageCasino("can not init bet dice, is server");
			return null;
		}
		
		if(!widget){
			DebugMessageCasino("Load UI");
			
			DebugMessageCasino("Try create widget");
			widget = GetGame().GetWorkspace().CreateWidgets("DayZCasino/layouts/BetDice.layout");
			
			if (!widget){
				DebugMessageCasino("could not create widget");
			}
			DebugMessageCasino("Has widget loaded");
			shuffel = ButtonWidget.Cast( widget.FindAnyWidget( "shuffel" ));
			DebugMessageCasino("Has shuffel loaded");
			WidgetEventHandler.GetInstance().RegisterOnMouseButtonDown( shuffel,  this, "OnClick" );
			cancel = ButtonWidget.Cast( widget.FindAnyWidget( "cancel" ));
			DebugMessageCasino("Has cancel loaded");
			WidgetEventHandler.GetInstance().RegisterOnMouseButtonDown( cancel,  this, "OnClick" );
			number = XComboBoxWidget.Cast( widget.FindAnyWidget( "number" ));
			DebugMessageCasino("Has number loaded");
			chipsBet = XComboBoxWidget.Cast( widget.FindAnyWidget( "chipsBet" ));
			DebugMessageCasino("Has chipsBet loaded");
			countChips = MultilineTextWidget.Cast( widget.FindAnyWidget( "countChips" ));
			DebugMessageCasino("Has countChips loaded");
			lastWin = MultilineTextWidget.Cast( widget.FindAnyWidget( "lastWin" ));
			DebugMessageCasino("Has lastWin loaded");
			message = MultilineTextWidget.Cast( widget.FindAnyWidget( "message" ));
			DebugMessageCasino("Has message loaded");
			diceImage = ImageWidget.Cast( widget.FindAnyWidget( "diceImage" ));
			DebugMessageCasino("Has diceImage loaded");
			
			widget.Show(false);
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
		diceImage.LoadImageFile(0, "{79BC5FA94F25EF0B}DayZCasino/data/dice/dice1.edds");
		diceImage.LoadImageFile(1, "{275476EAF0A86104}DayZCasino/data/dice/dice2.edds");
		diceImage.LoadImageFile(2, "{D35C3172FD750970}DayZCasino/data/dice/dice3.edds");
		diceImage.LoadImageFile(3, "{9A84246D8FB37D1A}DayZCasino/data/dice/dice4.edds");
		diceImage.LoadImageFile(4, "{6E8C63F5826E156E}DayZCasino/data/dice/dice5.edds");
		diceImage.LoadImageFile(5, "{30644AB63DE39B61}DayZCasino/data/dice/dice6.edds");
		diceImage.SetImage(0);
		effect_sound = SEffectManager.CreateSound("DayZCasino_CLACK_SoundSet", player.GetPosition());
	}

	override bool OnClick( Widget w, int x, int y, int button )	{
		DebugMessageCasino("on click action super");
		super.OnClick(w, x, y, button);
		
		DebugMessageCasino("on click action");

		if (w == cancel){
			DebugMessageCasino("click cancel");
			CloseMenu();
		}
		
		if (w == shuffel){
			DebugMessageCasino("click shuffel");
			play();
		}	
		
		return true;
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
						winSum = 6 * parameterShuffel.param1;
						
					} else {
						DebugMessageCasino("lose");
						winSum = -1 * parameterShuffel.param1;
					}
					
					AddChipsToPlayer(player, winSum);
					int currentChips = GetPlayerChipsAmount(player);
					Param3<int, int, int> parameterResponse = new Param3<int, int, int>(luckNumber, winSum, currentChips);
					
					GetGame().RPCSingleParam(player, DAYZ_CASINO_RESPONSE_SHUFFEL_BET_DICE, parameterResponse, true);
					DebugMessageCasino("has message send to player");
				} else {
					GetGame().RPCSingleParam(player, DAYZ_CASINO_RESPONSE_SHUFFEL_BET_DICE_NOT_ENOUGH_BALANCE, new Param1<bool>(true), true);
				}
			}
		}
		if (rpc_type == DAYZ_CASINO_RESPONSE_SHUFFEL_BET_DICE && false == IsServerCasino()) {
			DebugMessageCasino("recive response shuffel");
			Param3<int, int, int> parameterShuffelResponse;
			if (ctx.Read(parameterShuffelResponse)) {
				DebugMessageCasino("has recive response for bet dice");
				winImageNumber = parameterShuffelResponse.param1 - 1;
				lastWinChips = parameterShuffelResponse.param2;
				currentAmmount = parameterShuffelResponse.param3;

			}
		}
		if (rpc_type == DAYZ_CASINO_RESPONSE_SHUFFEL_BET_DICE_NOT_ENOUGH_BALANCE && false == IsServerCasino()) {
			DebugMessageCasino("recive not enough ballance");
			imageShufelTimer.Stop();
			cancel.Show(true);
			shuffel.Show(true);
		}
	}


	void play(){
		if (player && isMenuOpen && number && chipsBet) {
			int chipsValue = GetCurrenBet();
			int numberValue = number.GetCurrentItem() + 1;
			
			if (chipsValue > currentAmmount) {
				DebugMessageCasino("chipsVaue" + chipsValue);
				DebugMessageCasino("currentAmmount" + currentAmmount);
				message.SetText("Nicht genug Chips vorhanden");
				message.Show(true);
				return;
			}
			message.Show(false);
			
			cancel.Show(false);
			shuffel.Show(false);
			
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
		if (false == effect_sound.SoundPlay()) {
			DebugMessageCasino("sound not loaded");
		} else {
			DebugMessageCasino("sound has played");
		}
		
		if (currentCountBeforSendShufel == 0) {
			GetGame().RPCSingleParam(player, DAYZ_CASINO_SHUFFEL_BET_DICE, parameterShuffel, true);
			DebugMessageCasino("has send to server ");
		}
				
		
		if (winImageNumber != 10 && COUNT_SHUFFLE_BEFOR_SHOW_WIN_NUMBER == currentCountBeforSendShufel) {
			diceImage.SetImage(winImageNumber);
			winImageNumber = 10;
			lastWin.SetText("" + lastWinChips);
			countChips.SetText("" + currentAmmount);
			imageShufelTimer.Stop();
			cancel.Show(true);
			shuffel.Show(true);
			return;
		}
		
		diceImage.SetImage(Math.RandomInt(0, 5));
		
		if (20 == currentCountBeforSendShufel) {
			DebugMessageCasino("No respons from Server");
			imageShufelTimer.Stop();
			cancel.Show(true);
			shuffel.Show(true);
		}
		
		++currentCountBeforSendShufel;
	}
	
	private int GetCurrenBet() {
		int chipsValue = 0;
		DebugMessageCasino("" + chipsBet.GetCurrentItem());
		switch (chipsBet.GetCurrentItem()){
			case BET1:
				chipsValue = 1;
				break;
			case BET5:
				chipsValue = 5;
				break;
			case BET10:
				chipsValue = 10;
				break;
			case BET25:
				chipsValue = 25;
				break;
			case BET50:
				chipsValue = 50;
				break;
			case BET100:
				chipsValue = 100;
				break;
			case BET250:
				chipsValue = 250;
				break;
			case BET500:
				chipsValue = 500;
				break;
			case BET1000:
				chipsValue = 1000;
				break;
			
			default:
				break;
		}
		return chipsValue;
	}
	
}