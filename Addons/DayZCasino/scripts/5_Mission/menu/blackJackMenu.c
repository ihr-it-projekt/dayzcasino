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
	private MultilineTextWidget pointPlayer;
	private MultilineTextWidget pointBank;

    ref TIntArray usedCards;
    int cardValuePlayer;
    int cardValueBank;

	override Widget Init()
	{
		if (IsInitialized()) {
			return widget;
		}
		
        widgetPath = "DayZCasino/layouts/BlackJack.layout";
		super.Init();

		holdCard = ButtonWidget.Cast( widget.FindAnyWidget( "holdCard" ));
        WidgetEventHandler.GetInstance().RegisterOnMouseButtonDown( holdCard,  this, "OnClick" );
        usedCards = new TIntArray;

        newGame = ButtonWidget.Cast( widget.FindAnyWidget( "newGame" ));
        WidgetEventHandler.GetInstance().RegisterOnMouseButtonDown( newGame,  this, "OnClick" );

        nextCard = ButtonWidget.Cast( widget.FindAnyWidget( "nextCard" ));
        WidgetEventHandler.GetInstance().RegisterOnMouseButtonDown( nextCard,  this, "OnClick" );

        cards = ImageWidget.Cast(widget.FindAnyWidget( "cards" ));
        cards.LoadImageFile(0, "DayZCasino/data/cards/rueckseite.edds");
        cards.SetImage(0);
		
		pointBank = MultilineTextWidget.Cast( widget.FindAnyWidget("pointBank"));
		pointPlayer = MultilineTextWidget.Cast(widget.FindAnyWidget("pointPlayer"));

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

		pointPlayer.SetText("0");
		pointBank.SetText("0");
		
		holdCard.Show(false);
		nextCard.Show(false);
		cancel.Show(true);
		newGame.Show(true);
		
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
            GiveNextCard();
            return true;
        }
        if (!holdCard && w == nextCard){
            DebugMessageCasino("click holdCard");
            HoldCardAction();
            return true;
        }

		return false;
	}

	void HideCards() {
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

    void Play(){
        if (player && isMenuOpen && chipsBet) {
            int chipsValue = GetCurrenBet();

            if (chipsValue > currentAmount) {
                countChips.SetText("" + currentAmount);
                message.SetText("#Not_enough_chips_available");
                message.Show(true);

                return;
            }
            HideCards();
            message.Show(false);
            cancel.Show(false);
            newGame.Show(false);

            Param2 <int, DayZPlayer> startGame = new Param2<int, DayZPlayer>(chipsValue, player);
            GetGame().RPCSingleParam(player, DAYZ_CASINO_BLACK_JACK_START_GAME, startGame, true);

        }
    }

    void SetStartCards(Card firstCardPlayer, Card secondCardPlayer, Card firstCardBank) {
        playerCard0.LoadImageFile(0, firstCardPlayer.GetImagePath());
        playerCard0.SetImage(0);
        playerCard0.Show(true);
        playerCard1.LoadImageFile(0, secondCardPlayer.GetImagePath());
        playerCard1.SetImage(0);
        playerCard1.Show(true);
        bankCard0.LoadImageFile(0, firstCardBank.GetImagePath());
        bankCard0.SetImage(0);
        bankCard0.Show(true);
        bankCard1.LoadImageFile(0, "DayZCasino/data/cards/rueckseite.edds");
        bankCard1.SetImage(0);
        bankCard1.Show(true);
	}

	void SetNextPlayerCard(int numberOfCard, Card nextPlayerCard) {
        switch(numberOfCard) {
            case 2:
                playerCard1.LoadImageFile(0, nextPlayerCard.GetImagePath());
                playerCard1.SetImage(0);
                playerCard1.Show(true);
                break;
            case 3:
                playerCard2.LoadImageFile(0, nextPlayerCard.GetImagePath());
                playerCard2.SetImage(0);
                playerCard2.Show(true);
                break;
            case 4:
                playerCard3.LoadImageFile(0, nextPlayerCard.GetImagePath());
                playerCard3.SetImage(0);
                playerCard3.Show(true);
                break;
            case 5:
                playerCard4.LoadImageFile(0, nextPlayerCard.GetImagePath());
                playerCard4.SetImage(0);
                playerCard4.Show(true);
                break;
            case 6:
                playerCard5.LoadImageFile(0, nextPlayerCard.GetImagePath());
                playerCard5.SetImage(0);
                playerCard5.Show(true);
                break;

            default:

                return;
        }
	}

    void LoseGame() {
        message.SetText("#you_lose");
        message.Show(true);
        countChips.SetText("" + currentAmount);

        EndGame();
    }

    void RefreshPoints(string playerPoints, string bankPoints) {
        pointPlayer.SetText(playerPoints);
        pointBank.SetText(bankPoints);
    }

    void EndGame() {
        holdCard.Show(false);
        nextCard.Show(false);
        cancel.Show(true);
        newGame.Show(true);
    }

    void HidePlayButtons() {
        nextCard.Show(true);
        holdCard.Show(true);
	}

    void ShowPlayButtons() {
        nextCard.Show(true);
        holdCard.Show(true);
	}

    void HoldCardAction() {
        GetGame().RPCSingleParam(player, DAYZ_CASINO_BLACK_JACK_START_NEXT_CARD_PLAYER, new Param2<ref TIntArray, DayZPlayer>(usedCards, player), true);
    }

	private void GiveNextCard() {
		if (cardValuePlayer > 21) {
			LoseGame();
		} else {
            HidePlayButtons();
			GetGame().RPCSingleParam(player, DAYZ_CASINO_BLACK_JACK_START_NEXT_CARD_PLAYER, new Param2<ref TIntArray, DayZPlayer>(usedCards, player), true);
		} 
	}



}