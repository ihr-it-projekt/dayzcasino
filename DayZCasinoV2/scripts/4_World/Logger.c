static void LogPlay(DayZPlayer player, int winAmmount, string gameName) {
    static int hour;
    static int minute;
    static int second;
    GetHourMinuteSecondUTC(hour, minute, second);

    static int year;
    static int month;
    static int day;

    GetYearMonthDay(year, month, day);

    string time = "" + hour + ":" + minute + ":" + second + " ";
    string date = "" + year + "-" + month + "-" + day;


    if(!FileExist(CONFIGSFOLDER)) {
        MakeDirectory(CONFIGSFOLDER);
        DebugMessageCasino("create folder");
    }

    FileHandle handle;

    if(!FileExist(CONFIGSFOLDER + date + "_play.csv")) {
        handle = OpenFile(CONFIGSFOLDER + date + "_play.csv", FileMode.APPEND);
        if(handle == 0)
            return;

        FPrintln(handle, "time;game;playerid;win/lose;");
    }

    if(handle == 0) {
        handle = OpenFile(CONFIGSFOLDER + date + "_play.csv", FileMode.APPEND);
    }

    if(handle == 0)
        return;

    FPrintln(handle, time + ";" + gameName + ";" + player.GetIdentity().GetPlainId() + ";" + winAmmount.ToString() + ";");

    CloseFile(handle);
}