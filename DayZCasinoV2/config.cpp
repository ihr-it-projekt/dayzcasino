class CfgPatches {
    class DayZCasino {
        units[] = {"CasinoChips",};
        weapons[] = {};
        requiredVersion = 1.0;
        requiredAddons[] = {
            "DZ_Data",
            "DZ_Scripts",
            "JM_CF_Scripts"
        };
    };
};

class CfgAddons {
    //access = 1;
    class PreloadBanks {};
    class PreloadAddons {
        class dayz {
            list[] = {};
        };
    };
};

class CfgMods {
    class DayZCasino {
        inputs = "DayZCasinoV2\inputs.xml";
        dir = "DayZCasino";
        name = "DayZCasino";
        credits = "TheBuster";
        author = "TheBuster";
        authorID = "0";
        version = "0.1";
        extra = 0;
        type = "mod";

        dependencies[] = {"Game", "World", "Mission"};

        class defs {
            class gameScriptModule {
                value = "";
                files[] = {
                    "DayZCasinoV2/scripts/3_Game"
                };
            };

            class worldScriptModule {
                value = "";
                files[] = {
                    "DayZCasinoV2/scripts/4_World"
                };
            };
            class missionScriptModule {
                value = "";
                files[] = {
                    "DayZCasinoV2/scripts/5_Mission"
                };
            };
        };
    };
};

class cfgSoundSets {
    class DayZCasino_FLIPCARD_SoundSet {
        soundShaders[] = {
            "DayZCasino_FLIPCARD_SoundShader"
        };
        sound3DProcessingType = "character3DProcessingType";
        volumeCurve = "characterAttenuationCurve";
        spatial = 1;
        doppler = 0;
        loop = 0;
    };
    class DayZCasino_CLACK_SoundSet {
        soundShaders[] = {
            "DayZCasino_CLACK_SoundShader"
        };
        sound3DProcessingType = "character3DProcessingType";
        volumeCurve = "characterAttenuationCurve";
        spatial = 1;
        doppler = 0;
        loop = 0;
    };
    class DayZCasino_WIN_SoundSet {
        soundShaders[] = {
            "DayZCasino_WIN_SoundShader"
        };
        sound3DProcessingType = "character3DProcessingType";
        volumeCurve = "characterAttenuationCurve";
        spatial = 1;
        doppler = 0;
        loop = 0;
    };
    class DayZCasino_LOSE_SoundSet {
        soundShaders[] = {
            "DayZCasino_LOSE_SoundShader"
        };
        sound3DProcessingType = "character3DProcessingType";
        volumeCurve = "characterAttenuationCurve";
        spatial = 1;
        doppler = 0;
        loop = 0;
    };
    class DayZCasino_JACKPOT_SoundSet {
        soundShaders[] = {
            "DayZCasino_JACKPOT_SoundShader"
        };
        sound3DProcessingType = "character3DProcessingType";
        volumeCurve = "characterAttenuationCurve";
        spatial = 1;
        doppler = 0;
        loop = 0;
    };
    class DayZCasino_FLAP_SoundSet {
        soundShaders[] = {
            "DayZCasino_FLAP_SoundShader"
        };
        sound3DProcessingType = "character3DProcessingType";
        volumeCurve = "characterAttenuationCurve";
        spatial = 1;
        doppler = 0;
        loop = 0;
    };
    class DayZCasino_RACE_BACKGROUND_SoundSet {
        soundShaders[] = {
            "DayZCasino_RACE_BACKGROUND_SoundShader"
        };
        sound3DProcessingType = "character3DProcessingType";
        volumeCurve = "characterAttenuationCurve";
        spatial = 1;
        doppler = 0;
        loop = 0;
    };
    class DayZCasino_COUNTDOWN_1_SoundSet {
        soundShaders[] = {
            "DayZCasino_COUNTDOWN_1_SoundShader"
        };
        sound3DProcessingType = "character3DProcessingType";
        volumeCurve = "characterAttenuationCurve";
        spatial = 1;
        doppler = 0;
        loop = 0;
    };
    class DayZCasino_COUNTDOWN_2_SoundSet {
        soundShaders[] = {
            "DayZCasino_COUNTDOWN_2_SoundShader"
        };
        sound3DProcessingType = "character3DProcessingType";
        volumeCurve = "characterAttenuationCurve";
        spatial = 1;
        doppler = 0;
        loop = 0;
    };
    class DayZCasino_COUNTDOWN_3_SoundSet {
        soundShaders[] = {
            "DayZCasino_COUNTDOWN_3_SoundShader"
        };
        sound3DProcessingType = "character3DProcessingType";
        volumeCurve = "characterAttenuationCurve";
        spatial = 1;
        doppler = 0;
        loop = 0;
    };
    class DayZCasino_SHOOT_SoundSet {
        soundShaders[] = {
            "DayZCasino_SHOOT_SoundShader"
        };
        sound3DProcessingType = "character3DProcessingType";
        volumeCurve = "characterAttenuationCurve";
        spatial = 1;
        doppler = 0;
        loop = 0;
    };
};
class cfgSoundShaders {
    class DayZCasino_CLACK_SoundShader {
        samples[] = {
            {
                "DayZCasinoV2\data\sounds\clack",
                1
            }
        };
        volume = 1;
        range = 10;
        limitation = 0;
    };
    class DayZCasino_FLIPCARD_SoundShader {
        samples[] = {
            {
                "DayZCasinoV2\data\sounds\flipcard",
                1
            }
        };
        volume = 1;
        range = 10;
        limitation = 0;
    };
    class DayZCasino_WIN_SoundShader {
        samples[] = {
            {
                "DayZCasinoV2\data\sounds\win",
                1
            }
        };
        volume = 1;
        range = 10;
        limitation = 0;
    };
    class DayZCasino_LOSE_SoundShader {
        samples[] = {

            {
                "DayZCasinoV2\data\sounds\lose",
                1
            }
        };
        volume = 1;
        range = 10;
        limitation = 0;
    };
    class DayZCasino_FLAP_SoundShader {
        samples[] = {

            {
                "DayZCasinoV2\data\sounds\flap",
                1
            }
        };
        volume = 1;
        range = 10;
        limitation = 0;
    };
    class DayZCasino_JACKPOT_SoundShader {
        samples[] = {

            {
                "DayZCasinoV2\data\sounds\jackpot",
                1
            }
        };
        volume = 1;
        range = 10;
        limitation = 0;
    };
    class DayZCasino_RACE_BACKGROUND_SoundShader {
        samples[] = {

            {
                "DayZCasinoV2\data\sounds\race_background",
                1
            }
        };
        volume = 1;
        range = 10;
        limitation = 0;
    };
    class DayZCasino_COUNTDOWN_1_SoundShader {
        samples[] = {

            {
                "DayZCasinoV2\data\sounds\one",
                1
            }
        };
        volume = 1;
        range = 10;
        limitation = 0;
    };
    class DayZCasino_COUNTDOWN_2_SoundShader {
        samples[] = {

            {
                "DayZCasinoV2\data\sounds\tow",
                1
            }
        };
        volume = 1;
        range = 10;
        limitation = 0;
    };
    class DayZCasino_COUNTDOWN_3_SoundShader {
        samples[] = {

            {
                "DayZCasinoV2\data\sounds\three",
                1
            }
        };
        volume = 1;
        range = 10;
        limitation = 0;
    };
    class DayZCasino_SHOOT_SoundShader {
        samples[] = {

            {
                "DayZCasinoV2\data\sounds\pistol-shot",
                1
            }
        };
        volume = 1;
        range = 10;
        limitation = 0;
    };
};

class CfgVehicles {
    class Inventory_Base;
    class HouseNoDestruct;
    class Casino_Pacman: HouseNoDestruct {
        scope = 2;
        model = "DayZCasinoV2\Models\Pacman.p3d";
        hiddenSelections[] = {
            "ghost1",
            "ghost2",
            "ghost3",
            "ghost4",
            "mouth bott",
            "mouth top",
            "pacman machine",
            "pacman"
        };
        hiddenSelectionsTextures[] = {
            "DayZCasinoV2\Models\Data\Pacman\Pacman_Ghost.paa",
            "DayZCasinoV2\Models\Data\Pacman\Pacman_Ghost.paa",
            "DayZCasinoV2\Models\Data\Pacman\Pacman_Ghost.paa",
            "DayZCasinoV2\Models\Data\Pacman\Pacman_Ghost.paa",
            "DayZCasinoV2\Models\Data\Pacman\Pacman.paa",
            "DayZCasinoV2\Models\Data\Pacman\Pacman.paa",
            "DayZCasinoV2\Models\Data\Pacman\Pacman.paa",
            "DayZCasinoV2\Models\Data\Pacman\Pacman_Ghost.paa"
        };
    };
    class CasinoChips_Base: Inventory_Base {
        scope = 2;
        displayName = "#Casino_Chip";
        descriptionShort = "#With_this_chip_you_can_play_at_casino_games";
        model = "DayZCasinoV2\Models\CasinoChips.p3d";
        animClass = "NoFireClass";
        weight = 1;
        itemSize[] = {1, 1};
        canBeSplit = 1;
        varQuantityInit = 10000;
        varQuantityMin = 0;
        varQuantityMax = 10000;
        varQuantityDestroyOnMin = 1;
        varStackMax = 10000;
        hiddenSelections[] = {
            "chipColor"
        };
    };
    class CasinoChip: CasinoChips_Base {
        hiddenSelectionsTextures[] = {
            "#(argb,8,8,3)color(0.0,0.0,0.0,1.0,co)"
        };
    };
    class CasinoChip_Red: CasinoChips_Base {
        hiddenSelectionsTextures[] = {
            "#(argb,8,8,3)color(1.0,0.0,0.0,1.0,co)"
        };
    };
    class CasinoChip_Green: CasinoChips_Base {
        hiddenSelectionsTextures[] = {
            "#(argb,8,8,3)color(0.0,0.5,0.0,1.0,co)"
        };
    };
    class CasinoChip_Blue: CasinoChips_Base {
        hiddenSelectionsTextures[] = {
            "#(argb,8,8,3)color(0.0,0.0,1.0,1.0,co)"
        };
    };
    class CasinoChip_Yellow: CasinoChips_Base {
        hiddenSelectionsTextures[] = {
            "#(argb,8,8,3)color(1.0,1.0,0.0,1.0,co)"
        };
    };
};