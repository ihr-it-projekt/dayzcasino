static int DAYZ_CASINO_SEND_MESSAGE_TO_PLAYER = 99995858587;
static int DAYZ_CASINO_SHUFFEL_BET_DICE = 99995858588;
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

	private ButtonWidget shuffel;
	private ButtonWidget cancel;
	private XComboBoxWidget number;
	private XComboBoxWidget rubel;

	
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
			rubel = XComboBoxWidget.Cast( widget.FindAnyWidget( "rubel" ));
			DebugMessageCasino("Has rubel loaded");
	
			widget.Show(false);
		}
		
		return widget;
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
		if (rpc_type == DAYZ_CASINO_SHUFFEL_BET_DICE) {
			Param3<int, int, DayZPlayer> parameter;
			if (ctx.Read(parameter)) {
				player = parameter.param3;
				DebugMessageCasino("Check Player has chips");
				if (PlayerHasEnoghChips(player, parameter.param1)){
					int luckNumber = Math.RandomInt(1, 6);
					
					if (DAYZ_CASINO_DEBUG) {
						luckNumber = 1;
					}
					
					if (parameter.param2 == luckNumber) {
						DebugMessageCasino("Win");
						AddChipsToPlayer(player, 6 * parameter.param1);
					} else {
						DebugMessageCasino("lose");
						AddChipsToPlayer(player, -1 * parameter.param1);
					}
				}
			}
		}
	}

	
	override vector GetPosition() {
		return "11810.3 4.25288 3415.5";
	}

	void play(){
		if (player && isMenuOpen && number && rubel) {
			int rubelValue = 0;
			int numberValue = number.GetCurrentItem() + 1;
			
			switch (rubel.GetCurrentItem())
			{
				case BET1:
					rubelValue = 1;
					break;
				case BET5:
					rubelValue = 5;
					break;
				case BET10:
					rubelValue = 10;
					break;
				case BET25:
					rubelValue = 25;
				case BET50:
					rubelValue = 50;
				case BET100:
					rubelValue = 100;
				case BET250:
					rubelValue = 250;
				case BET500:
					rubelValue = 500;
				case BET1000:
					rubelValue = 1000;
				
				default:
					break;
			}
			
			DebugMessageCasino("rubel value is " + rubelValue);
			DebugMessageCasino("numberValue value is " + numberValue);
			
			Param3<int, int, DayZPlayer> parameter = new Param3<int, int, DayZPlayer>(rubelValue, numberValue, player);
			GetGame().RPCSingleParam(player, DAYZ_CASINO_SHUFFEL_BET_DICE, parameter, true);
			DebugMessageCasino("has send to server ");
		}
	}
}