class BaseMenu extends UIScriptedMenu {
    protected bool isDebug = DAYZ_CASINO_DEBUG;
    protected ButtonWidget info;
    protected ButtonWidget steam;
    protected ButtonWidget discord;
    protected ButtonWidget donate;
    protected ButtonWidget closeInfo;
    protected Widget infoWidget;
    protected DayZPlayer player;
    protected ButtonWidget cancel;
    protected MultilineTextWidget lastWin;
    protected MultilineTextWidget message;
    protected MultilineTextWidget countChips;
    protected CasinoConfig casinoConfig;
    protected bool canClose = true;
    bool isMenuOpen = false;
    protected map<string, int> currencyValues;
    ref protected DayZCasinoPlayerInventory inventory;
    int lastWinChips;
    int currentAmount;
    protected string widgetPath;

    void SetConfig(CasinoConfig casinoConfigExt) {
        casinoConfig = casinoConfigExt;
        inventory = new DayZCasinoPlayerInventory(casinoConfig.currencyValues);
    }

    override Widget Init() {
        if(IsServerCasino()) {
            return null;
        }

        if(IsInitialized()) {
            return layoutRoot;
        }

        super.Init();


        player = GetGame().GetPlayer();

        layoutRoot = GetGame().GetWorkspace().CreateWidgets(widgetPath);

        cancel = ButtonWidget.Cast(layoutRoot.FindAnyWidget("cancel"));
        discord = ButtonWidget.Cast(layoutRoot.FindAnyWidget("discord"));

        countChips = MultilineTextWidget.Cast(layoutRoot.FindAnyWidget("countChips"));
        lastWin = MultilineTextWidget.Cast(layoutRoot.FindAnyWidget("lastWin"));
        message = MultilineTextWidget.Cast(layoutRoot.FindAnyWidget("message"));

        layoutRoot.Show(false);

        info = ButtonWidget.Cast(layoutRoot.FindAnyWidget("info"));

        infoWidget = GetGame().GetWorkspace().CreateWidgets("DayZCasinoV2/layouts/Info.layout");
        infoWidget.Show(false);

        closeInfo = ButtonWidget.Cast(infoWidget.FindAnyWidget("closeInfo"));
        steam = ButtonWidget.Cast(infoWidget.FindAnyWidget("steam"));
        donate = ButtonWidget.Cast(infoWidget.FindAnyWidget("donate"));
        layoutRoot.AddChild(infoWidget);

        return layoutRoot;
    }

    override bool OnClick(Widget w, int x, int y, int button)	{
        bool actionRuns = super.OnClick(w, x, y, button);

        if(actionRuns) {
            return actionRuns;
        }

        if(w == cancel) {
            CloseMenu();
            return true;
        } else if(w == info) {
            infoWidget.Show(true);
            return true;
        } else if(w == closeInfo) {
            infoWidget.Show(false);
            return true;
        } else if(w == donate) {
            GetGame().OpenURL("https://www.paypal.com/donate/?hosted_button_id=8UASRGVP88YE4");
            return true;
        } else if(w == steam) {
            GetGame().OpenURL("https://steamcommunity.com/profiles/76561198196317725/myworkshopfiles/");
            return true;
        } else if(w == discord) {
            GetGame().OpenURL("https://discord.gg/3maa9Q9rHB");
            return true;
        }

        return false;
    }

    override void OnHide() {
        super.OnHide();

        PPEffects.SetBlurMenu(0);

        GetGame().GetUIManager().ShowCursor(false);
        GetGame().GetUIManager().ShowUICursor(false);
        GetGame().GetInput().ResetGameFocus();
        GetGame().GetMission().PlayerControlEnable(true);
        GetGame().GetUIManager().Back();
        GetGame().GetMission().GetHud().Show(true);

        isMenuOpen = false;
    }


    override void OnShow() {
        if(isMenuOpen) {
            return;
        }
        super.OnShow();

        PPEffects.SetBlurMenu(0.5);

        SetFocus(layoutRoot);
        layoutRoot.Show(true);

        GetGame().GetMission().PlayerControlDisable(INPUT_EXCLUDE_INVENTORY);
        GetGame().GetUIManager().ShowUICursor(true);
        GetGame().GetUIManager().ShowCursor(true);
        GetGame().GetInput().ChangeGameFocus(1);
        GetGame().GetMission().GetHud().Show(false);
        isMenuOpen = true;
        currentAmount = inventory.GetPlayerChipsAmount(player);
        countChips.SetText(currentAmount.ToString());
        lastWin.SetText("0");
    }

    void Play() {
        cancel.Show(false);
        message.Show(false);
        canClose = false;
    }

    void EndGame() {
        cancel.Show(true);
        canClose = true;
    }

    bool CanCloseGameMenu() {
        return canClose && isMenuOpen;
    }

    protected bool CanPlayGame() {
        return player && isMenuOpen;
    }

    void CloseMenu() {
        GetGame().GetUIManager().HideScriptedMenu(this);
    }

    bool IsInitialized() {
        return !!layoutRoot;
    }

    override void Update(float timeslice) {
        super.Update(timeslice);
        if(CanCloseGameMenu() && GetUApi() && GetUApi().GetInputByName("UAUIBack").LocalPress()) {
            GetGame().GetUIManager().HideScriptedMenu(this);
        }
    }

}
