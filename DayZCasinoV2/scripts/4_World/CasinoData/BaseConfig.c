class BaseConfig {
    protected void Load(string filename) {
        if(IsServerAndMultiplayerCasino() && FileExist(CONFIGSFOLDER + filename)) {
            DebugMessageCasino("load file");
            DoLoad();
        }
    }

    protected void Save(string filename) {
        if(IsServerAndMultiplayerCasino()) {
            if(!FileExist(CONFIGSFOLDER)) {
                MakeDirectory(CONFIGSFOLDER);
                DebugMessageCasino("create folder");
            }
            DebugMessageCasino("save file");
            DoSave();
        }
    }


    protected void DoLoad() {}
    protected void DoSave() {}
};