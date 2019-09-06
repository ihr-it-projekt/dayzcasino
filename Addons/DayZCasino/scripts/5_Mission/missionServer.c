modded class MissionServer {

	ref GameMenues m_gameMenues;
	
	void MissionServer()
	{
		DebugMessageCasino("loaded");
		GetDayZGame().Event_OnRPC.Insert(OnRPC);
		
		m_gameMenues = new GameMenues;
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
		
		m_gameMenues.HandleEvents(sender, target, rpc_type, ctx);
	}

	

};