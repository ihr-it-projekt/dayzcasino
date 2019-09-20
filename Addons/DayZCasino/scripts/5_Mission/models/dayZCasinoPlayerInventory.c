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


    int AddChipsToPlayer(DayZPlayer player, int chipsCount) {
        array<EntityAI> itemsArray = new array<EntityAI>;
        player.GetInventory().EnumerateInventory(InventoryTraversalType.PREORDER, itemsArray);

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
};