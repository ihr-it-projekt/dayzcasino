class DayZCasinoPlayerInventory
{
    bool PlayerHasEnoughChips(DayZPlayer player, int betSumme) {
        int amount = GetPlayerChipsAmount(player);
        DebugMessageCasino("Has amount of " + amount);

        return betSumme <= amount;
    }

    int GetPlayerChipsAmount(DayZPlayer player)
    {
        if (!player) {
            DebugMessageCasino("can not get chips, no player set");
            return 0;
        }

        DebugMessageCasino("GetPlayerChipsAmount");
        int currencyAmount = 0;

        array<EntityAI> itemsArray = new array<EntityAI>;
        player.GetInventory().EnumerateInventory(InventoryTraversalType.PREORDER, itemsArray);

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


    int AddChipsToPlayer(DayZPlayer player, float chipsCount) {
        array<EntityAI> itemsArray = new array<EntityAI>;
        player.GetInventory().EnumerateInventory(InventoryTraversalType.PREORDER, itemsArray);

        ItemBase item;
        for (int i = 0; i < itemsArray.Count(); i++)
        {
            Class.CastTo(item, itemsArray.Get(i));
            if (item && item.GetType() == "CasinoChips") {
                if (chipsCount > 0) {
                    chipsCount = AddChips(chipsCount, item);
                } else if(chipsCount < 0) {
                    DebugMessageCasino("try remove chips");
                    chipsCount = RemoveChips(chipsCount, item);
                }
                if (chipsCount == 0) {
                    DebugMessageCasino("no chips to add");
                    break;
                }
            }
        }

        if (chipsCount > 0) {
            chipsCount = AddNewChipsItemToInventory(player, chipsCount);
        }

        return chipsCount;
    }

    private int AddNewChipsItemToInventory(DayZPlayer player, int chipsCount) {
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
            chipsCount = AddNewChipsItemToInventory(player, chipsCount);
        }

        return chipsCount;
    }

    private int AddChips(float chipsToAdd, EntityAI entity) {
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

    private int RemoveChips(float chipsToRemove, EntityAI entity) {
        ItemBase item;
        ItemBase.CastTo(item, entity);

        int canRemoveChipsCount = item.GetQuantity();

        DebugMessageCasino("has quantity " + canRemoveChipsCount);
        DebugMessageCasino("chips should remove " + chipsToRemove);

        if (canRemoveChipsCount > chipsToRemove) {
            GetGame().ObjectDelete(item);
            DebugMessageCasino("destroy item " + chipsToRemove);
            chipsToRemove += canRemoveChipsCount;
        } else {
			DebugMessageCasino("down count Quantity ");
            item.SetQuantity(canRemoveChipsCount + chipsToRemove);
            chipsToRemove = 0;
        }

        return chipsToRemove;
    }
};