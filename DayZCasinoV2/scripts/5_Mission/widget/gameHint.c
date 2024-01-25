class GameHint {
    private ref Widget hintWidget;
    private ref MultilineTextWidget message;

    void ~GameHint() {
        if(hintWidget) hintWidget.Show(false);
    }

    void GameHint() {
        hintWidget = GetGame().GetWorkspace().CreateWidgets("DayZCasinoV2/layouts/GameHint.layout");
        message = MultilineTextWidget.Cast(hintWidget.FindAnyWidget("message"));
        message.SetText("#hint_can_open_game");
    }

    void OnHide() {
        hintWidget.Show(false);
    }


    void OnShow() {
        hintWidget.Show(true);
    }
};