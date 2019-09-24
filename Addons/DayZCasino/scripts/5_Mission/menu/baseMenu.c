class BaseMenu extends UIScriptedMenu
{
    protected static int BET1 = 0;
    protected static int BET5 = 1;
    protected static int BET10 = 2;
    protected static int BET25 = 3;
    protected static int BET50 = 4;
    protected static int BET100 = 5;
    protected static int BET250 = 6;
    protected static int BET500 = 7;
    protected static int BET1000 = 8;

	bool isMenuOpen = false;
	protected bool isDebug = true;
	protected Widget widget;
	protected DayZPlayer player;
	protected vector position;
    protected ButtonWidget cancel;
    protected XComboBoxWidget chipsBet;
    protected MultilineTextWidget lastWin;
    protected MultilineTextWidget message;
    protected MultilineTextWidget countChips;
    ref protected DayZCasinoPlayerInventory inventory;
    int lastWinChips;
    int currentAmount;
    protected string widgetPath;

    void BaseMenu(vector pos) {
		BaseConstrctor(pos);
	}
	
	protected void BaseConstrctor(vector pos) {
		position = pos;
        inventory = new DayZCasinoPlayerInventory;
		DebugMessageCasino("base menu is created");
	}

    override Widget Init()
    {
        if (IsServerCasino()){
            DebugMessageCasino("can not init, is server");
            return null;
        }

        if (IsInitialized()) {
            return widget;
        }

        super.Init();

        widget = GetGame().GetWorkspace().CreateWidgets(widgetPath);

        cancel = ButtonWidget.Cast( widget.FindAnyWidget( "cancel" ));
        WidgetEventHandler.GetInstance().RegisterOnMouseButtonDown( cancel,  this, "OnClick" );

        chipsBet = XComboBoxWidget.Cast( widget.FindAnyWidget( "chipsBet" ));
        countChips = MultilineTextWidget.Cast( widget.FindAnyWidget( "countChips" ));
        lastWin = MultilineTextWidget.Cast( widget.FindAnyWidget( "lastWin" ));
        message = MultilineTextWidget.Cast( widget.FindAnyWidget( "message" ));

        widget.Show(false);

        return widget;
    }

    override bool OnClick( Widget w, int x, int y, int button )	{
        super.OnClick(w, x, y, button);

        if (w == cancel){
            DebugMessageCasino("click cancel");
            CloseMenu();
            return true;
        }

        return false;
    }
	
	override void OnHide()
	{
		if (!isMenuOpen) {
			return;
		}
		
		DebugMessageCasino("hide action");
		super.OnHide();

		PPEffects.SetBlurMenu(0);

		GetGame().GetUIManager().ShowCursor(false);
		GetGame().GetUIManager().ShowUICursor(false);
		GetGame().GetInput().ResetGameFocus();
		GetGame().GetMission().PlayerControlEnable();
		GetGame().GetUIManager().Back();
		GetGame().GetMission().GetHud().Show( true );

		Close();
		isMenuOpen = false;
	}
	
		
	override void OnShow()
	{
		if (isMenuOpen) {
			DebugMessageCasino("Menue is already open");
			return;
		}
		
		super.OnShow();
				
		DebugMessageCasino("show action");
		
		PPEffects.SetBlurMenu(0.5);

		SetFocus( widget );
		widget.Show(true);

		GetGame().GetMission().PlayerControlDisable(INPUT_EXCLUDE_INVENTORY);
		GetGame().GetUIManager().ShowUICursor(true);
		GetGame().GetUIManager().ShowCursor(true);
		GetGame().GetInput().ChangeGameFocus( 1 );
		GetGame().GetMission().GetHud().Show( false );
		player = GetGame().GetPlayer();
		isMenuOpen = true;
        currentAmount =  inventory.GetPlayerChipsAmount(GetGame().GetPlayer());
        countChips.SetText("" + currentAmount);
        lastWin.SetText("0");
	}
	
	void CloseMenu(){
		DebugMessageCasino("check is open");
		if(isMenuOpen){
			DebugMessageCasino("try close menue");
			SetFocus(NULL);
			OnHide();
			widget.Show(false);
			isMenuOpen = false;
		}	
	}
	
	bool IsInitialized() {
		return !!widget;
	}
	
	vector GetPosition() {
		DebugMessageCasino("position is " + position.ToString());
		return position;
	}

	int GetCurrenBet() {
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