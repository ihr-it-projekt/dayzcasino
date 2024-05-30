class BaseConfig {
    protected void Load(string filename) {
        if(IsServerAndMultiplayerCasino() && FileExist(CONFIGSFOLDER + filename)) {
            DoLoad();
        }
    }

    protected void Save(string filename) {
        if(IsServerAndMultiplayerCasino()) {
            if(!FileExist(CONFIGSFOLDER)) {
                MakeDirectory(CONFIGSFOLDER);
            }
            DoSave();
        }
    }


    protected void DoLoad() {}
    protected void DoSave() {}
};