static void DebugMessageCasino(string message) {
    if (DAYZ_CASINO_DEBUG) {
        Print("[DayZCasino] " + message);
        GetGame().AdminLog("[DayZCasino] " + message);
    }
}

static bool IsServerCasino()
{
    return GetGame().IsServer();
}
static bool IsMultiplayerCasino()
{
    return GetGame().IsMultiplayer();
}

static bool IsServerAndMultiplayerCasino()
{
    return IsMultiplayerCasino() && IsServerCasino();
}
static bool IsClientOrNotMultiplayerCasino()
{
    return !IsMultiplayerCasino() || GetGame().IsClient();
}

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


    if (!FileExist(CONFIGSFOLDER)) {
        MakeDirectory(CONFIGSFOLDER);
        DebugMessageCasino("create folder");
    }

    FileHandle handle = OpenFile(CONFIGSFOLDER + date +"_play.csv" , FileMode.APPEND);
    if ( handle == 0 )
        return;

    FPrintln( handle, time + ";" + gameName + ";Player: " + owner.GetIdentity().GetPlainId() + ";win/lose:" +  winAmmount.ToString() +";");

    CloseFile( handle );
}