class RatRaceServerEventHandler
{
    ref DayZCasinoPlayerInventory inventory;
	ref RaceCollection raceCollection;

    void RatRaceServerEventHandler() {
        inventory = new DayZCasinoPlayerInventory;
		raceCollection = new RaceCollection;
        DebugMessageCasino("Register RRSEH");
        GetDayZGame().Event_OnRPC.Insert(HandleEvents);
    }

    void ~RatRaceServerEventHandler() {
        GetDayZGame().Event_OnRPC.Remove(HandleEvents);
    }

    void HandleEvents(PlayerIdentity sender, Object target, int rpc_type, ParamsReadContext ctx) {
        if (!IsServerCasino()) {
            return;
        } else if (rpc_type == DAYZ_CASINO_NEW_RAT_RACE) {
			Param1<DayZPlayer> parameterNewRace;
	        if (ctx.Read(parameterNewRace)) {
                DayZPlayer playerNewRace = parameterNewRace.param1;
				Race newRace = raceCollection.FindRace(playerNewRace.GetIdentity());
				if(DAYZ_CASINO_DEBUG_CHIPS) {
                    playerNewRace.GetInventory().CreateInInventory("CasinoChips");
                }
				
				if (null == newRace) {
					newRace = new Race(DAYZ_CASINO_RAT_RACE_COUNT_RAT);
				}
				
				raceCollection.AddRace(playerNewRace.GetIdentity(), newRace);
				
				DebugMessageCasino("Has create a new race");
				
				GetGame().RPCSingleParam(playerNewRace, DAYZ_CASINO_RESPONSE_NEW_RAT_RACE, new Param1<ref Race>(newRace), true,  playerNewRace.GetIdentity());
			}
        } else if (rpc_type == DAYZ_CASINO_START_RAT_RACE) {
            Param3<int, int, DayZPlayer> parameterStartRace;
            if (ctx.Read(parameterStartRace)) {
                DayZPlayer player = parameterStartRace.param3;
                DebugMessageCasino("Check Player has chips");
                if (inventory.PlayerHasEnoughChips(player, parameterStartRace.param1)){
					Race race = raceCollection.FindRace(player.GetIdentity());
					race.CreateRaceResults();
					
					Rat winRat = race.winRat;
					
					int winSum = 0;
    
                    if (parameterStartRace.param2 == winRat.number) {
                        DebugMessageCasino("Win");
                        winSum = winRat.quote * parameterStartRace.param1;
    
                    } else {
                        DebugMessageCasino("lose");
                        winSum = -1 * parameterStartRace.param1;
                    }

                    inventory.AddChipsToPlayer(player, winSum);
                    int currentChips = inventory.GetPlayerChipsAmount(player);
                    DebugMessageCasino("server: player has " + currentChips);
    
                    GetGame().RPCSingleParam(player, DAYZ_CASINO_RESPONSE_START_RAT_RACE, new Param3<int, int, ref Race>(winSum, currentChips, race), true, player.GetIdentity());
                    DebugMessageCasino("has message send to player");
                    raceCollection.RemoveRace(player.GetIdentity());
                } else {
                    GetGame().RPCSingleParam(player, DAYZ_CASINO_RESPONSE_RAT_RACE_NOT_ENOUGH_BALANCE, new Param1<bool>(true), true,  player.GetIdentity());
                }
            }
        }
    }

};