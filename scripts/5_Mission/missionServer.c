modded class MissionServer {

	private ref CasinoConfig casinoConfig;
	private ref BlackJackServerEventHandler blackJackServerEventHandler;
	private ref RatRaceServerEventHandler ratRaceServerEventHandler;
	private ref BetDiceServerEventHandler betDiceServerEventHandler;
	private ref LuckyWheelServerEventHandler luckyWheelServerEventHandler;
	private ref Jackpot jackpot;

	void MissionServer()
	{
		casinoConfig = GetCasinoConfig();

        if (casinoConfig.enabledDice) {
            PlaceGame(casinoConfig.positionDice, casinoConfig.orientationDice, casinoConfig.gameObjectDice);
            betDiceServerEventHandler = BetDiceServerEventHandler();
			betDiceServerEventHandler.SetConfig(casinoConfig);
        }
        if (casinoConfig.enabledBlackJack) {
            PlaceGame(casinoConfig.positionBlackJack, casinoConfig.orientationBlackJack, casinoConfig.gameObjectBlackJack);
            blackJackServerEventHandler = BlackJackServerEventHandler();
        }
        if (casinoConfig.enabledRatRace) {
            PlaceGame(casinoConfig.positionRatRace, casinoConfig.orientationRatRace, casinoConfig.gameObjectRatRace);
            ratRaceServerEventHandler = RatRaceServerEventHandler();
        }
        if (casinoConfig.enabledLuckyWheel) {
            PlaceGame(casinoConfig.positionLuckyWheel, casinoConfig.orientationLuckyWheel, casinoConfig.gameObjectLuckyWheel);
            luckyWheelServerEventHandler = LuckyWheelServerEventHandler();
            luckyWheelServerEventHandler.SetConfig(casinoConfig);
            jackpot = Jackpot(casinoConfig.minJackpotLuckyWheel);
            luckyWheelServerEventHandler.SetJackpot(jackpot);
        }

        GetDayZGame().Event_OnRPC.Insert(HandleEvents);
		DebugMessageCasino("loaded");
	}

	void ~MissionServer() {
		GetDayZGame().Event_OnRPC.Remove(HandleEvents);
	}
	
	void HandleEvents(PlayerIdentity sender, Object target, int rpc_type, ParamsReadContext ctx) {
		if (rpc_type == DAYZ_CASINO_SEND_MESSAGE_TO_PLAYER) {
			autoptr Param2<PlayerBase, string> paramMessage;
			if (ctx.Read(paramMessage))
			{
				DayZPlayer senderPlayerMessage = paramMessage.param1;
				string message = paramMessage.param2;
				DebugMessageCasino("server get message event");
		    	
		    	if (senderPlayerMessage) {
					SendMessageToPlayerCasino(message, senderPlayerMessage);
				}
			}
		}
		
		if (rpc_type == DAYZ_CASINO_GET_CASINO_CONFIG) {
			DebugMessageCasino("receive get config");
			autoptr Param1<PlayerBase> paramGetConfig;
			if (ctx.Read(paramGetConfig)){

                paramGetConfig.param1.GetInventory().CreateInInventory("CasinoChips");
	        	GetGame().RPCSingleParam(paramGetConfig.param1, DAYZ_CASINO_GET_CASINO_CONFIG_RESPONSE, new Param1<ref CasinoConfig>(casinoConfig), true, sender);
			}
		}
	}

    private void PlaceGame(vector pos, vector orientation, string gameObjectName) {
        DebugMessageCasino("create object " + gameObjectName);
        House game_obj = Building.Cast(GetGame().CreateObject(gameObjectName, pos));
        game_obj.SetPosition( pos );
        game_obj.SetOrientation( orientation );
        game_obj.SetOrientation( game_obj.GetOrientation() ); //Collision fix
        game_obj.Update();
        game_obj.SetAffectPathgraph( true, false );
        if( game_obj.CanAffectPathgraph() ) {
            GetGame().GetCallQueue( CALL_CATEGORY_SYSTEM ).CallLater( GetGame().UpdatePathgraphRegionByObject, 100, false, game_obj );
        }
    }
};