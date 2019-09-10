static bool DAYZ_CASINO_DEBUG = true;

class BaseMenu extends UIScriptedMenu
{
	bool isMenuOpen = false;
	protected bool isDebug = true;
	protected Widget widget;
	protected DayZPlayer player;
	protected vector position;
	
	void BaseMenu(vector pos) {
		position = pos;
		GetDayZGame().Event_OnRPC.Insert(HandleEvents);
	}
	
	void ~BaseMenu() {
		GetDayZGame().Event_OnRPC.Remove(HandleEvents);
	}
	
	void HandleEvents(PlayerIdentity sender, Object target, int rpc_type, ParamsReadContext ctx) {
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
		DebugMessageCasino("position is " + position.ToString);
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
			DebugMessageCasino("has item " + item.GetType());
			if(item && item.GetType() == "CasinoChips") {
				DebugMessageCasino("has found chips ");
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
			DebugMessageCasino("has item " + item.GetType());
			if (item && item.GetType() == "CasinoChips") {
				DebugMessageCasino("has found chips ");
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
	
	private int AddNewChipsItemToInevntory(int chipsCount) {
		InventoryLocation inventoryLocation = new InventoryLocation;	
		EntityAI entityInHands = this.GetHumanInventory().GetEntityInHands();	
		if (player.GetInventory().FindFirstFreeLocationForNewEntity("CasinoChips", FindInventoryLocationType.ANY, inventoryLocation)) {
			EntityAI entity = player.GetHumanInventory().CreateInInventory("CasinoChips");
			chipsCount = AddChips(chipsCount, item);
		} else if (!entityInHands) {
			EntityAI entityInHands = this.GetHumanInventory().CreateInHands("CasinoChips");
			chipsCount = AddChips(chipsCount, entityInHands);
		} else {
			EntityAI entity = player.SpawnEntityOnGroundPos("CasinoChips", player.GetPosition());
			chipsCount = AddChips(chipsCount, entityInHands);
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
		}
		
		return chipsToAdd;
	}
	
}