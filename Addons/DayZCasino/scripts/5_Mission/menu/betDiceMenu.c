static int DAYZ_CASINO_SEND_MESSAGE_TO_PLAYER = 99995858587;
static int DAYZ_CASINO_SHUFFEL_BET_DICE = 99995858588;
static int DAYZ_CASINO_RESPONSE_SHUFFEL_BET_DICE = 99995858589;
static bool DAYZ_CASINO_DEBUG = true;
static int DAYZ_CASINO_DISTANCE_TO_GAME = 1;

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
	private static int COUNT_SHUFFLE_BEFOR_SEND_TO_SERVER = 6;

	private ButtonWidget shuffel;
	private ButtonWidget cancel;
	private XComboBoxWidget number;
	private XComboBoxWidget chipsBet;
	private MultilineTextWidget countChips;
	private MultilineTextWidget lastWin;
	private ImageWidget diceImage;
	private ref Timer imageShufelTimer;
	private int currentCountBeforSendShufel = 0;
	ref Param3<int, int, DayZPlayer> parameterShuffel

	
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
			
			if (shuffel) {
				DebugMessageCasino("Has shuffel loaded");
				WidgetEventHandler.GetInstance().RegisterOnMouseButtonDown( shuffel,  this, "OnClick" );
			} else {
				DebugMessageCasino("Has shuffel NOT loaded");
			}
			
			
			cancel = ButtonWidget.Cast( widget.FindAnyWidget( "cancel" ));
			if (cancel) {
				DebugMessageCasino("Has cancel loaded");
				WidgetEventHandler.GetInstance().RegisterOnMouseButtonDown( cancel,  this, "OnClick" );
			} else {
				DebugMessageCasino("Has cancel NOT loaded");
			}
			
			number = XComboBoxWidget.Cast( widget.FindAnyWidget( "number" ));
			DebugMessageCasino("Has number loaded");
			chipsBet = XComboBoxWidget.Cast( widget.FindAnyWidget( "chipsBet" ));
			DebugMessageCasino("Has chipsBet loaded");
			countChips = MultilineTextWidget.Cast( widget.FindAnyWidget( "countChips" ));
			DebugMessageCasino("Has countChips loaded");
			lastWin = MultilineTextWidget.Cast( widget.FindAnyWidget( "lastWin" ));
			DebugMessageCasino("Has lastWin loaded");
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
		
		countChips.SetText("" + GetPlayerChipsAmount(GetGame().GetPlayer()));
		lastWin.SetText("0");
		diceImage.LoadImageFile(1, "DayZCasino\data\dice\dice1.edds");
		diceImage.LoadImageFile(2, "DayZCasino\data\dice\dice2.edds");
		diceImage.LoadImageFile(3, "DayZCasino\data\dice\dice3.edds");
		diceImage.LoadImageFile(4, "DayZCasino\data\dice\dice4.edds");
		diceImage.LoadImageFile(5, "DayZCasino\data\dice\dice5.edds");
		diceImage.LoadImageFile(6, "DayZCasino\data\dice\dice6.edds");
		diceImage.SetImage(1);
	}


	override bool OnClick( Widget w, int x, int y, int button )	{
		DebugMessageCasino("on click action super");
		super.OnClick(w, x, y, button);
		
		DebugMessageCasino("on click action");

		if (w == cancel){
			CloseMenu();
		}
		
		if (w == shuffel){
			play();
		}		
			
		return true;
	}
	
	void HandleEvents(PlayerIdentity sender, Object target, int rpc_type, ParamsReadContext ctx) {
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
					Param2<int, int> parameterResponse = new Param2<int, int>(luckNumber, winSum);
					
					GetGame().RPCSingleParam(player, DAYZ_CASINO_RESPONSE_SHUFFEL_BET_DICE, parameterResponse, true);
					DebugMessageCasino("has message send to player");
				}
			}
		}
		if (rpc_type == DAYZ_CASINO_RESPONSE_SHUFFEL_BET_DICE && false == IsServerCasino()) {
			DebugMessageCasino("recive response shuffel");
			Param2<int, int> parameterShuffelResponse;
			if (ctx.Read(parameterShuffelResponse)) {
				DebugMessageCasino("has recive response for bet dice");
				lastWin.SetText("" + parameterShuffelResponse.param2);
				imageShufelTimer.Stop();
				diceImage.SetImage(parameterShuffelResponse.param1);
				cancel.Show(true);
				shuffel.Show(true);
			}
		}
	}

	
	override vector GetPosition() {
		return "11810.3 4.25288 3415.5";
	}

	void play(){
		if (player && isMenuOpen && number && chipsBet) {
			cancel.Show(false);
			shuffel.Show(false);
			int chipsValue = 0;
			int numberValue = number.GetCurrentItem() + 1;
			
			
			switch (chipsBet.GetCurrentItem())
			{
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
				case BET50:
					chipsValue = 50;
				case BET100:
					chipsValue = 100;
				case BET250:
					chipsValue = 250;
				case BET500:
					chipsValue = 500;
				case BET1000:
					chipsValue = 1000;
				
				default:
					break;
			}
			parameterShuffel = new Param3<int, int, DayZPlayer>(chipsValue, numberValue, player);
			DebugMessageCasino("create timer");
			currentCountBeforSendShufel = 0;
			imageShufelTimer = new Timer();
			imageShufelTimer.Run(0.5, this, "SwitchImage", null, true);
			
			DebugMessageCasino("chipsBet value is " + chipsValue);
			DebugMessageCasino("numberValue value is " + numberValue);
		}
	}
	
	void SwitchImage() {
		DebugMessageCasino("change image");
		diceImage.SetImage(Math.RandomInt(1, 6));
		if (currentCountBeforSendShufel == COUNT_SHUFFLE_BEFOR_SEND_TO_SERVER) {
			GetGame().RPCSingleParam(player, DAYZ_CASINO_SHUFFEL_BET_DICE, parameterShuffel, true);
			DebugMessageCasino("has send to server ");
		}
		currentCountBeforSendShufel++;
	}
	
}