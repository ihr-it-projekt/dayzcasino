class DayZCasinoPlayerInventory {
    private map<string, int> currencyValues;

    void DayZCasinoPlayerInventory(map<string, int> _currencyValues) {
        this.currencyValues = _currencyValues;
    }

    bool PlayerHasEnoughChips(DayZPlayer player, int betSumme) {
        int amount = GetPlayerChipsAmount(player);
        return betSumme <= amount;
    }

    int GetPlayerChipsAmount(DayZPlayer player) {
        if(!player) {
            return 0;
        }

        int currencyAmount = 0;

        array<EntityAI> itemsArray = new array<EntityAI>;
        player.GetInventory().EnumerateInventory(InventoryTraversalType.PREORDER, itemsArray);

        ItemBase item;
        for(int i = 0; i < itemsArray.Count(); i++) {
            Class.CastTo(item, itemsArray.Get(i));

            if(item && item.GetType()) {
                int value = currencyValues.Get(item.GetType());
                if(value) {
                    currencyAmount += value * item.GetQuantity();
                }
            }
        }

        return currencyAmount;
    }

    int AddChipsToPlayer(DayZPlayer player, float chipsCount) {
        array<EntityAI> itemsArray = new array<EntityAI>;
        player.GetInventory().EnumerateInventory(InventoryTraversalType.PREORDER, itemsArray);

        ItemBase item;
        int currencyAmount = 0;
        for(int i = 0; i < itemsArray.Count(); i++) {
            Class.CastTo(item, itemsArray.Get(i));

            if(item && item.GetType()) {
                int value = currencyValues.Get(item.GetType());
                if(value) {
                    currencyAmount += value * item.GetQuantity();
                    GetGame().ObjectDelete(item);
                }
            }
        }

        currencyAmount = currencyAmount + chipsCount;

        if(currencyAmount > 0) {
            currencyAmount = AddNewChipsItemToInventory(player, currencyAmount);
        }

        return currencyAmount;
    }

    private int AddNewChipsItemToInventory(DayZPlayer player, float chipsCount) {
        InventoryLocation inventoryLocation = new InventoryLocation;

        int selectedValue = 0;
        string selectedType = "";
        foreach(string type, int value: currencyValues) {
            if(chipsCount >= value && selectedValue < value) {
                selectedValue = value;
                selectedType = type;
            }
        }

        if(selectedValue == 0) {
            return 0;
        }

        EntityAI chipsEntity;
        if(player.GetInventory().FindFirstFreeLocationForNewEntity(selectedType, FindInventoryLocationType.ANY, inventoryLocation)) {
            chipsEntity = player.GetHumanInventory().CreateInInventory(selectedType);
        }

        if(!chipsEntity && !player.GetHumanInventory().GetEntityInHands()) {
            chipsEntity = player.GetHumanInventory().CreateInHands(selectedType);
        }

        if(!chipsEntity) {
            chipsEntity = player.SpawnEntityOnGroundPos(selectedType, player.GetPosition());
        }

        if(!chipsEntity) {
            Print("[DayZCasino] Chips entity from type: " + selectedType + " can not created, can not spawn");
            GetGame().AdminLog("[DayZCasino] Chips entity from type: " + selectedType + " can not created, can not spawn");
            return 0;
        }

        chipsCount = AddChips(selectedValue, chipsCount, chipsEntity);

        if(chipsCount) {
            chipsCount = AddNewChipsItemToInventory(player, chipsCount);
        }

        return chipsCount;
    }

    private int AddChips(int factor, float chipsToAdd, EntityAI entity) {


        ItemBase item;
        ItemBase.CastTo(item, entity);

        int maxAmount = item.GetQuantityMax();

        int countAddFromType = Math.Floor(chipsToAdd / factor);

        if(countAddFromType > maxAmount) {
            chipsToAdd -= maxAmount * factor;
            item.SetQuantity(maxAmount);
        } else {
            item.SetQuantity(countAddFromType);
            chipsToAdd -= countAddFromType * factor;
        }

        if(chipsToAdd < 1) {
            chipsToAdd = 0;
        }

        return chipsToAdd;
    }
};