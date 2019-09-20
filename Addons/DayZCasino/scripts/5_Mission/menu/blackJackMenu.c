class BlackJackMenu extends BaseMenu
{
	private ButtonWidget holdCard;
	private ButtonWidget newGame;
	private ButtonWidget nextCard;
	private ImageWidget cards;
	private ImageWidget playerCard0;
	private ImageWidget playerCard1;
	private ImageWidget playerCard2;
	private ImageWidget playerCard3;
	private ImageWidget playerCard4;
	private ImageWidget playerCard5;
	private ImageWidget bankCard0;
	private ImageWidget bankCard1;
	private ImageWidget bankCard2;
	private ImageWidget bankCard3;
	private ImageWidget bankCard4;
	private ImageWidget bankCard5;
	private TClassArray currentCardsPlayer;
	private TClassArray currentCardsBank;
	private TIntArray cardAllreadyUsed;
	private ref CardCollection cardCollection;

	override Widget Init()
	{
		if (IsInitialized()) {
			DebugMessageCasino("Widget is all ready initialized");
			
			return widget;
		}
		
		

        widgetPath = "DayZCasino/layouts/BlackJack.layout";
		super.Init();

        cardCollection = new CardCollection();
			
        holdCard = ButtonWidget.Cast( widget.FindAnyWidget( "holdCard" ));
        WidgetEventHandler.GetInstance().RegisterOnMouseButtonDown( holdCard,  this, "OnClick" );

        newGame = ButtonWidget.Cast( widget.FindAnyWidget( "newGame" ));
        WidgetEventHandler.GetInstance().RegisterOnMouseButtonDown( newGame,  this, "OnClick" );

        nextCard = ButtonWidget.Cast( widget.FindAnyWidget( "nextCard" ));
        WidgetEventHandler.GetInstance().RegisterOnMouseButtonDown( newGame,  this, "OnClick" );

        cards = ImageWidget.Cast(widget.FindAnyWidget( "cards" ));
        cards.LoadImageFile(0, "DayZCasino/data/cards/blank_a.edds");
        cards.SetImage(0);

        bankCard0 = ImageWidget.Cast(widget.FindAnyWidget( "bankCard0" ));
        bankCard1 = ImageWidget.Cast(widget.FindAnyWidget( "bankCard1" ));
        bankCard2 = ImageWidget.Cast(widget.FindAnyWidget( "bankCard2" ));
        bankCard3 = ImageWidget.Cast(widget.FindAnyWidget( "bankCard3" ));
        bankCard4 = ImageWidget.Cast(widget.FindAnyWidget( "bankCard4" ));
        bankCard5 = ImageWidget.Cast(widget.FindAnyWidget( "bankCard5" ));
        playerCard0 = ImageWidget.Cast(widget.FindAnyWidget( "playerCard0" ));
        playerCard1 = ImageWidget.Cast(widget.FindAnyWidget( "playerCard1" ));
        playerCard2 = ImageWidget.Cast(widget.FindAnyWidget( "playerCard2" ));
        playerCard3 = ImageWidget.Cast(widget.FindAnyWidget( "playerCard3" ));
        playerCard4 = ImageWidget.Cast(widget.FindAnyWidget( "playerCard4" ));
        playerCard5 = ImageWidget.Cast(widget.FindAnyWidget( "playerCard5" ));

		return widget;
	}
	
	override void OnShow()
	{
		if (isMenuOpen) {
			DebugMessageCasino("Menu is already open");
			return;
		}
		
		super.OnShow();
		currentAmmount = GetPlayerChipsAmount(GetGame().GetPlayer());
		countChips.SetText("" + currentAmmount);
		lastWin.SetText("0");

        HideCards();
	}

	override bool OnClick( Widget w, int x, int y, int button )	{
		DebugMessageCasino("on click action super");
		bool actionRuns = super.OnClick(w, x, y, button);

        if (!actionRuns && w == newGame){
            DebugMessageCasino("click newGame");
            Play();
            return true;
        }
        if (!actionRuns && w == nextCard){
            DebugMessageCasino("click nextCard");
            NextCard();
            return true;
        }

		return false;
	}
	
	override void HandleEvents(PlayerIdentity sender, Object target, int rpc_type, ParamsReadContext ctx) {
		if (rpc_type == DAYZ_CASINO_BLACK_JACK_START_GAME && IsServerCasino()) {
			Param2 <int, DayZPlayer> startGame;
			if (ctx.Read(startGame)) {
				player = startGame.param2;
				if (PlayerHasEnoghChips(player, startGame.param1)){
					cardAllreadyUsed.Clear();
					int firstCardPlayerServer = cardCollection.GetRandomCardIndex(cardAllreadyUsed);
					int secondCardPlayerServer = cardCollection.GetRandomCardIndex(cardAllreadyUsed);
					int firstCardBankServer = cardCollection.GetRandomCardIndex(cardAllreadyUsed);
					
					DebugMessageCasino("client first card is " + firstCardPlayerServer);
				
					GetGame().RPCSingleParam(player, DAYZ_CASINO_BLACK_JACK_START_GAME_RESPONSE, new Param3<int, int, int>(firstCardPlayerServer, secondCardPlayerServer, firstCardBankServer), true,  player.GetIdentity());
				} else {
					GetGame().RPCSingleParam(player, DAYZ_CASINO_BLACK_JACK_NOT_ENOUGH_CHIPS, new Param1<bool>(true), true,  player.GetIdentity());
				}
			}
			
		}
		if (rpc_type == DAYZ_CASINO_BLACK_JACK_START_GAME_RESPONSE && !IsServerCasino()) {
			Param3 <int, int, int> responseStartGame;
			if (ctx.Read(responseStartGame)) {
				int firstCardPlayer = responseStartGame.param1;
				int secondCardPlayer = responseStartGame.param2;
				int firstCardBank = responseStartGame.param3;
				
				DebugMessageCasino("client first card is " + firstCardPlayer);
				
				Card firstCard = cardCollection.GetCardByIndex(firstCardPlayer);
				Card secondCard = cardCollection.GetCardByIndex(secondCardPlayer);
				Card firstCardB = cardCollection.GetCardByIndex(firstCardBank);
				
				cardAllreadyUsed.Clear();
				cardAllreadyUsed.Insert(firstCardPlayer);
				cardAllreadyUsed.Insert(secondCardPlayer);
				cardAllreadyUsed.Insert(firstCardBank);

                playerCard0.LoadImageFile(0, firstCard.GetImagePath());
                playerCard0.SetImage(0);
				playerCard0.Show(true);
                playerCard1.LoadImageFile(0, secondCard.GetImagePath());
                playerCard1.SetImage(0);
				playerCard1.Show(true);
                bankCard0.LoadImageFile(0, firstCardB.GetImagePath());
                bankCard0.SetImage(0);
				bankCard0.Show(true);
				
				currentCardsPlayer.Insert(firstCard);
				currentCardsPlayer.Insert(secondCard);
				currentCardsBank.Insert(firstCardB);
				nextCard.Show(true);
			}
		}
		
		if (rpc_type == DAYZ_CASINO_BLACK_JACK_NOT_ENOUGH_CHIPS && false == IsServerCasino()) {
			DebugMessageCasino("recive not enough ballance");
			cancel.Show(true);
			newGame.Show(true);
		}
		
		
	}

	private void HideCards() {
        holdCard.Show(false);

        playerCard0.Show(false);
        playerCard1.Show(false);
        playerCard2.Show(false);
        playerCard3.Show(false);
        playerCard4.Show(false);
        playerCard5.Show(false);

        bankCard0.Show(false);
        bankCard1.Show(false);
        bankCard2.Show(false);
        bankCard3.Show(false);
        bankCard4.Show(false);
        bankCard5.Show(false);
	}
	
	private void NextCard() {
		Param2 <int, DayZPlayer> nextCardParam = new Param2<int, DayZPlayer>(1, player);
		
		GetGame().RPCSingleParam(player, DAYZ_CASINO_BLACK_JACK_START_NEXT_CARD_PLAYER, nextCardParam, true);
	}


	void Play(){
		if (player && isMenuOpen && chipsBet) {
			int chipsValue = GetCurrenBet();
			
			if (chipsValue > currentAmmount) {
				countChips.SetText("" + currentAmmount);
				message.SetText("#Not_enough_chips_available");
				message.Show(true);
				
				return;
			}
			message.Show(false);
			cancel.Show(false);
			newGame.Show(false);
			
			Param2 <int, DayZPlayer> startGame = new Param2<int, DayZPlayer>(chipsValue, player);
			GetGame().RPCSingleParam(player, DAYZ_CASINO_BLACK_JACK_START_GAME, startGame, true);
		
		}
	}
}