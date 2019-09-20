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
    protected int lastWinChips;
    protected int currentAmmount;
    protected string widgetPath;

    void BaseMenu(vector pos) {
		BaseConstrctor(pos);
	}
	
	protected void BaseConstrctor(vector pos) {
		position = pos;
		GetDayZGame().Event_OnRPC.Insert(HandleEvents);
		DebugMessageCasino("base menue is created");
	}
	
	void ~BaseMenu() {
		GetDayZGame().Event_OnRPC.Remove(HandleEvents);
	}
	
	void HandleEvents(PlayerIdentity sender, Object target, int rpc_type, ParamsReadContext ctx) {
	}

    override Widget Init()
    {
        if (IsInitialized()) {
            return widget;
        }

        super.Init();

        if (IsServerCasino()){
            DebugMessageCasino("can not init, is server");
            return null;
        }

        if(!widget){
            widget = GetGame().GetWorkspace().CreateWidgets(widgetPath);

            cancel = ButtonWidget.Cast( widget.FindAnyWidget( "cancel" ));
            WidgetEventHandler.GetInstance().RegisterOnMouseButtonDown( cancel,  this, "OnClick" );

            
            chipsBet = XComboBoxWidget.Cast( widget.FindAnyWidget( "chipsBet" ));
            countChips = MultilineTextWidget.Cast( widget.FindAnyWidget( "countChips" ));
            lastWin = MultilineTextWidget.Cast( widget.FindAnyWidget( "lastWin" ));
            message = MultilineTextWidget.Cast( widget.FindAnyWidget( "message" ));

            widget.Show(false);
        }

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
	
		
	protected bool PlayerHasEnoghChips(DayZPlayer player, int betSumme) {
		int amount = GetPlayerChipsAmount(player);
		DebugMessageCasino("Has amunt of " + amount);
		
		return betSumme <= amount;
	}

	protected int GetPlayerChipsAmount(DayZPlayer m_Player) 
	{
		if (!m_Player) {
			return 0;
		}
		
		DebugMessageCasino("GetPlayerChipsAmount");
		int currencyAmount = 0;
		
		array<EntityAI> itemsArray = new array<EntityAI>;
		m_Player.GetInventory().EnumerateInventory(InventoryTraversalType.PREORDER, itemsArray);

		ItemBase item;
		
		for (int i = 0; i < itemsArray.Count(); i++)
		{
			Class.CastTo(item, itemsArray.Get(i));
			if(item && item.GetType() == "CasinoChips") {
				currencyAmount += item.GetQuantity();
			}
		}
		
		return currencyAmount;
	}
	
	protected int AddChipsToPlayer(DayZPlayer m_Player, int chipsCount) {
		array<EntityAI> itemsArray = new array<EntityAI>;
		m_Player.GetInventory().EnumerateInventory(InventoryTraversalType.PREORDER, itemsArray);

		ItemBase item;
		
		bool hasAddedAllChips = false;
		
		for (int i = 0; i < itemsArray.Count(); i++)
		{
			Class.CastTo(item, itemsArray.Get(i));
			if (item && item.GetType() == "CasinoChips") {
				chipsCount = AddChips(chipsCount, item);
				if (chipsCount == 0) {
					break;
				}
			}
		}
		
		if (chipsCount) {
			chipsCount = AddNewChipsItemToInevntory(chipsCount);
		}
		
		return chipsCount;
	}

    protected int GetCurrenBet() {
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
	
	private int AddNewChipsItemToInevntory(int chipsCount) {
		InventoryLocation inventoryLocation = new InventoryLocation;	
		
		if (player.GetInventory().FindFirstFreeLocationForNewEntity("CasinoChips", FindInventoryLocationType.ANY, inventoryLocation)) {
			EntityAI entityInInventory = player.GetHumanInventory().CreateInInventory("CasinoChips");
			chipsCount = AddChips(chipsCount - 1, entityInInventory);
		} else if (!player.GetHumanInventory().GetEntityInHands()) {
			EntityAI entityInHands = player.GetHumanInventory().CreateInHands("CasinoChips");
			chipsCount = AddChips(chipsCount - 1, entityInHands);
		} else {
			EntityAI entityToGround = player.SpawnEntityOnGroundPos("CasinoChips", player.GetPosition());
			chipsCount = AddChips(chipsCount - 1, entityToGround);
		}
		
		if(chipsCount) {
			chipsCount = AddNewChipsItemToInevntory(chipsCount);
		}
		
		return chipsCount;
	}
	
	private int AddChips(int chipsToAdd, EntityAI entity) {
		ItemBase item;
		ItemBase.CastTo(item, entity);
		
		int currencyAmount = item.GetQuantity();
		int maxAmount = item.GetQuantityMax();
		
		int canAddedChipsCount = maxAmount - currencyAmount;
		
		if (canAddedChipsCount > 0) {
			if (chipsToAdd > canAddedChipsCount) {
				item.SetQuantity(maxAmount);
				chipsToAdd -= canAddedChipsCount;
				
			} else {
				item.SetQuantity(currencyAmount + chipsToAdd);
				chipsToAdd = 0;
			}
		} else {
			item.SetQuantity(0);
			chipsToAdd = currencyAmount + chipsToAdd;
		}
		
		return chipsToAdd;
	}
}