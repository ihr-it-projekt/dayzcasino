class BaseMenu extends UIScriptedMenu
{
    protected bool isDebug = DAYZ_CASINO_DEBUG;
	protected DayZPlayer player;
    protected ButtonWidget cancel;
    protected MultilineTextWidget lastWin;
    protected MultilineTextWidget message;
    protected MultilineTextWidget countChips;
	protected CasinoConfig casinoConfig;
	bool isMenuOpen = false;
    ref protected DayZCasinoPlayerInventory inventory;
    int lastWinChips;
    int currentAmount;
    protected string widgetPath;
	
	void SetConfig(CasinoConfig casinoConfigExt) {
        casinoConfig = casinoConfigExt;
	}

    override Widget Init()
    {
        if (IsServerCasino()){
            DebugMessageCasino("can not init, is server");
            return null;
        }

        if (IsInitialized()) {
            return layoutRoot;
        }

        super.Init();
		
        inventory = new DayZCasinoPlayerInventory;
		player = GetGame().GetPlayer();

        layoutRoot = GetGame().GetWorkspace().CreateWidgets(widgetPath);

        cancel = ButtonWidget.Cast( layoutRoot.FindAnyWidget( "cancel" ));
        WidgetEventHandler.GetInstance().RegisterOnMouseButtonDown(cancel,  this, "OnClick");

        countChips = MultilineTextWidget.Cast( layoutRoot.FindAnyWidget("countChips"));
        lastWin = MultilineTextWidget.Cast( layoutRoot.FindAnyWidget("lastWin"));
        message = MultilineTextWidget.Cast( layoutRoot.FindAnyWidget("message"));

        layoutRoot.Show(false);

        return layoutRoot;
    }

    override bool OnClick( Widget w, int x, int y, int button )	{
        bool actionRuns = super.OnClick(w, x, y, button);

        if (actionRuns) {
            return actionRuns;
        }

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
		GetGame().GetMission().PlayerControlEnable(true);
		GetGame().GetUIManager().Back();
		GetGame().GetMission().GetHud().Show( true );

		Close();
		isMenuOpen = false;
	}
	
		
	override void OnShow()
	{
		if (isMenuOpen) {
			DebugMessageCasino("Menu is already open");
			return;
		}
		
		super.OnShow();
				
		DebugMessageCasino("show action");
		
		PPEffects.SetBlurMenu(0.5);

		SetFocus( layoutRoot );
		layoutRoot.Show(true);

		GetGame().GetMission().PlayerControlDisable(INPUT_EXCLUDE_INVENTORY);
		GetGame().GetUIManager().ShowUICursor(true);
		GetGame().GetUIManager().ShowCursor(true);
		GetGame().GetInput().ChangeGameFocus( 1 );
		GetGame().GetMission().GetHud().Show( false );
        if(DAYZ_CASINO_DEBUG_CHIPS) {
            player.GetInventory().CreateInInventory("CasinoChips");
        }
		isMenuOpen = true;
        currentAmount =  inventory.GetPlayerChipsAmount(player);
        countChips.SetText(currentAmount.ToString());
        lastWin.SetText("0");
	}

    void Play() {
        cancel.Show(false);
    }

    void EndGame() {
        cancel.Show(true);
    }
	
	protected bool CanPlayGame() {
        return player && isMenuOpen;
    }
	
	void CloseMenu(){
		DebugMessageCasino("check is open");
		if(isMenuOpen){
			DebugMessageCasino("try close menu");
			SetFocus(NULL);
			OnHide();
			layoutRoot.Show(false);
			isMenuOpen = false;
		}	
	}
	
	bool IsInitialized() {
		return !!layoutRoot;
	}

}