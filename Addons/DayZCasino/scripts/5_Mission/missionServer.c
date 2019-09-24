modded class MissionServer {

	private ref CasinoConfig casinoConfig;
	private ref BlackJackServerEventHandler blackJackServerEventHandler;
	private ref BetDiceServerEventHandler betDiceServerEventHandler;

	void MissionServer()
	{
		casinoConfig = GetCasinoConfig();
        PlaceGame(casinoConfig.positionDice, casinoConfig.orientationDice);
        PlaceGame(casinoConfig.positionBlackJack, casinoConfig.orientationBlackJack);
        blackJackServerEventHandler = BlackJackServerEventHandler();
        betDiceServerEventHandler = BetDiceServerEventHandler();
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
			DebugMessageCasino("recive get config");
			autoptr Param1<PlayerBase> paramGetConfig;
			if (ctx.Read(paramGetConfig)){
	        	GetGame().RPCSingleParam(paramGetConfig.param1, DAYZ_CASINO_GET_CASINO_CONFIG_RESPONSE, new Param1<ref CasinoConfig>(casinoConfig), true, sender);
			}
		}
	}

    private void PlaceGame(vector pos, vector orientation) {
        House game_obj = GetGame().CreateObject("Nehr_Gaming_01", pos);
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