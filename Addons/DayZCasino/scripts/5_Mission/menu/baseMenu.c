class BaseMenu extends UIScriptedMenu
{
	bool isMenuOpen = false;
	protected bool isDebug = true;
	protected Widget widget;
	protected DayZPlayer player;
	
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
		return "4680.468750 340.209229 10311.168945";
	}
	
		
	protected bool PlayerHasEnoghChips(DayZPlayer player, int betSumme) {
		int amount = GetPlayerChipsAmount(player);
		DebugMessageCasino("Has amunt of " + amount);
		
		return betSumme <= amount;
	}

	protected int GetPlayerChipsAmount(DayZPlayer m_Player) 
	{
		DebugMessageCasino("GetPlayerChipsAmount");
		int currencyAmount = 0;
		
		array<EntityAI> itemsArray = new array<EntityAI>;
		m_Player.GetInventory().EnumerateInventory(InventoryTraversalType.PREORDER, itemsArray);

		ItemBase item;
		
		for (int i = 0; i < itemsArray.Count(); i++)
		{
			Class.CastTo(item, itemsArray.Get(i));
			DebugMessageCasino("has item " + item.GetType());
			if(item && item.GetType() == "CasinoChips") {
				DebugMessageCasino("Find chips ");
				currencyAmount += item.GetQuantity();
			}
		}
		
		return currencyAmount;
	}
	
	protected void AddChipsToPlayer(DayZPlayer m_Player, int chipsCount) {
		array<EntityAI> itemsArray = new array<EntityAI>;
		m_Player.GetInventory().EnumerateInventory(InventoryTraversalType.PREORDER, itemsArray);

		ItemBase item;
		
		for (int i = 0; i < itemsArray.Count(); i++)
		{
			Class.CastTo(item, itemsArray.Get(i));
			DebugMessageCasino("has item " + item.GetType());
			if(item && item.GetType() == "CasinoChips") {
				DebugMessageCasino("Find chips ");
				int currencyAmount = item.GetQuantity() + chipsCount;
				item.SetQuantity(currencyAmount);
			}
		}
	}
	
}