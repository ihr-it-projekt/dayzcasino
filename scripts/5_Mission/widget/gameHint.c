class GameHint extends UIScriptedMenu
{
    private Widget widget;
    private bool isOpen  = false;
    private MultilineTextWidget message;

    override Widget Init()
    {
        if (IsServerCasino()){
            DebugMessageCasino("can not init, is server");
            return null;
        }

        if (IsInitialized()) {
            return widget;
        }

        super.Init();

        widget = GetGame().GetWorkspace().CreateWidgets("DayZCasino/layouts/GameHint");
        message = MultilineTextWidget.Cast( widget.FindAnyWidget( "message" ));


        isOpen = false;
        widget.Show(isOpen);
        message.Show(isOpen);

        return widget;
    }

    override void OnHide()
    {
        if (!isOpen) {
            return;
        }

        super.OnHide();

        isOpen = false;
        widget.Show(isOpen);
        message.Show(isOpen);
    }


    override void OnShow()
    {
        if (isOpen) {
            DebugMessageCasino("Menu is already open");
            return;
        }

        super.OnShow();

        DebugMessageCasino("show game hint");

        isOpen = true;
        widget.Show(isOpen);
        message.Show(isOpen);
    }


    bool IsInitialized() {
        return !!widget;
    }
};