class CfgPatches {
    class TBCV2 {
        units[] = {};
        weapons[] = {};
        requiredVersion = 0.1;
        requiredAddons[] = {"DZ_Data"};
    };
};
class CfgVehicles {
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
};
