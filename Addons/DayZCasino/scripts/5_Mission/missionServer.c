modded class MissionServer {

	ref GameMenues m_gameMenues;
	private ref CasinoConfig casinoConfig;
	
	void MissionServer()
	{
		casinoConfig = GetCasinoConfig();
		m_gameMenues = new GameMenues(casinoConfig);
		GetDayZGame().Event_OnRPC.Insert(OnRPC);
		DebugMessageCasino("loaded");
	}

	void ~MissionServer() {
		GetDayZGame().Event_OnRPC.Remove(OnRPC);
	}
	
	void OnRPC(PlayerIdentity sender, Object target, int rpc_type, ParamsReadContext ctx) {
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
		
		m_gameMenues.HandleEvents(sender, target, rpc_type, ctx);
	}
};