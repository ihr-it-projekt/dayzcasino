class CfgPatches
{
	class DayZCasino
	{
		units[]={"CasinoChips",};
        weapons[]={};
        requiredVersion=1.0;
        requiredAddons[]={
            "DZ_Data",
            "DZ_Scripts",
            "JM_CF_Scripts"
        };
	};
};

class CfgAddons
{
	//access = 1;
	class PreloadBanks {};
	class PreloadAddons
	{
		class dayz
		{
			list[] ={};
		};
	};
};

class CfgMods
{
	class DayZCasino
	{
		inputs = "DayZCasinoV2\inputs.xml";
		dir = "DayZCasino";
		name = "DayZCasino";
		credits = "TheBuster";
		author = "TheBuster";
		authorID = "0";
		version = "0.1";
		extra = 0;
		type = "mod";
		
		dependencies[] = {"Game", "Mission"};

		class defs
		{
            class gameScriptModule
            {
                value="";
                files[]=
                {
                    "DayZCasinoV2/scripts/3_Game"
                };
            };
			class missionScriptModule
			{
				value = "";
				files[] = {
				        "DayZCasinoV2/scripts/5_Mission"
				};
			};
		};
	};
};

class cfgSoundSets
{
	class DayZCasino_FLIPCARD_SoundSet
	{
		soundShaders[]=
		{
			"DayZCasino_FLIPCARD_SoundShader"
		};
		sound3DProcessingType="character3DProcessingType";
		volumeCurve="characterAttenuationCurve";
		spatial=1;
		doppler=0;
		loop=0;
	};
	class DayZCasino_CLACK_SoundSet
	{
		soundShaders[]=
		{
			"DayZCasino_CLACK_SoundShader"
		};
		sound3DProcessingType="character3DProcessingType";
		volumeCurve="characterAttenuationCurve";
		spatial=1;
		doppler=0;
		loop=0;
	};
	class DayZCasino_WIN_SoundSet
	{
		soundShaders[]=
		{
			"DayZCasino_WIN_SoundShader"
		};
		sound3DProcessingType="character3DProcessingType";
		volumeCurve="characterAttenuationCurve";
		spatial=1;
		doppler=0;
		loop=0;
	};
	class DayZCasino_LOSE_SoundSet
	{
		soundShaders[]=
		{
			"DayZCasino_LOSE_SoundShader"
		};
		sound3DProcessingType="character3DProcessingType";
		volumeCurve="characterAttenuationCurve";
		spatial=1;
		doppler=0;
		loop=0;
	};
	class DayZCasino_JACKPOT_SoundSet
	{
		soundShaders[]=
		{
			"DayZCasino_JACKPOT_SoundShader"
		};
		sound3DProcessingType="character3DProcessingType";
		volumeCurve="characterAttenuationCurve";
		spatial=1;
		doppler=0;
		loop=0;
	};
	class DayZCasino_FLAP_SoundSet
	{
		soundShaders[]=
		{
			"DayZCasino_FLAP_SoundShader"
		};
		sound3DProcessingType="character3DProcessingType";
		volumeCurve="characterAttenuationCurve";
		spatial=1;
		doppler=0;
		loop=0;
	};
	class DayZCasino_RACE_BACKGROUND_SoundSet
	{
		soundShaders[]=
		{
			"DayZCasino_RACE_BACKGROUND_SoundShader"
		};
		sound3DProcessingType="character3DProcessingType";
		volumeCurve="characterAttenuationCurve";
		spatial=1;
		doppler=0;
		loop=0;
	};
	class DayZCasino_COUNTDOWN_1_SoundSet
	{
		soundShaders[]=
		{
			"DayZCasino_COUNTDOWN_1_SoundShader"
		};
		sound3DProcessingType="character3DProcessingType";
		volumeCurve="characterAttenuationCurve";
		spatial=1;
		doppler=0;
		loop=0;
	};
	class DayZCasino_COUNTDOWN_2_SoundSet
	{
		soundShaders[]=
		{
			"DayZCasino_COUNTDOWN_2_SoundShader"
		};
		sound3DProcessingType="character3DProcessingType";
		volumeCurve="characterAttenuationCurve";
		spatial=1;
		doppler=0;
		loop=0;
	};
	class DayZCasino_COUNTDOWN_3_SoundSet
	{
		soundShaders[]=
		{
			"DayZCasino_COUNTDOWN_3_SoundShader"
		};
		sound3DProcessingType="character3DProcessingType";
		volumeCurve="characterAttenuationCurve";
		spatial=1;
		doppler=0;
		loop=0;
	};
	class DayZCasino_SHOOT_SoundSet
	{
		soundShaders[]=
		{
			"DayZCasino_SHOOT_SoundShader"
		};
		sound3DProcessingType="character3DProcessingType";
		volumeCurve="characterAttenuationCurve";
		spatial=1;
		doppler=0;
		loop=0;
	};
};
class cfgSoundShaders
{
	class DayZCasino_CLACK_SoundShader
	{
		samples[]=
		{
			{
				"DayZCasinoV2\data\sounds\clack",
				1
			}
		};
		volume=1;
		range=10;
		limitation=0;
	};
	class DayZCasino_FLIPCARD_SoundShader
	{
		samples[]=
		{
			{
				"DayZCasinoV2\data\sounds\flipcard",
				1
			}
		};
		volume=1;
		range=10;
		limitation=0;
	};
	class DayZCasino_WIN_SoundShader
	{
		samples[]=
		{
			{
				"DayZCasinoV2\data\sounds\win",
				1
			}
		};
		volume=1;
		range=10;
		limitation=0;
	};
	class DayZCasino_LOSE_SoundShader
	{
		samples[]=
		{

			{
				"DayZCasinoV2\data\sounds\lose",
				1
			}
		};
		volume=1;
		range=10;
		limitation=0;
	};
	class DayZCasino_FLAP_SoundShader
	{
		samples[]=
		{

			{
				"DayZCasinoV2\data\sounds\flap",
				1
			}
		};
		volume=1;
		range=10;
		limitation=0;
	};
	class DayZCasino_JACKPOT_SoundShader
	{
		samples[]=
		{

			{
				"DayZCasinoV2\data\sounds\jackpot",
				1
			}
		};
		volume=1;
		range=10;
		limitation=0;
	};
	class DayZCasino_RACE_BACKGROUND_SoundShader
	{
		samples[]=
		{

			{
				"DayZCasinoV2\data\sounds\race_background",
				1
			}
		};
		volume=1;
		range=10;
		limitation=0;
	};
	class DayZCasino_COUNTDOWN_1_SoundShader
	{
		samples[]=
		{

			{
				"DayZCasinoV2\data\sounds\one",
				1
			}
		};
		volume=1;
		range=10;
		limitation=0;
	};
	class DayZCasino_COUNTDOWN_2_SoundShader
	{
		samples[]=
		{

			{
				"DayZCasinoV2\data\sounds\tow",
				1
			}
		};
		volume=1;
		range=10;
		limitation=0;
	};
	class DayZCasino_COUNTDOWN_3_SoundShader
	{
		samples[]=
		{

			{
				"DayZCasinoV2\data\sounds\three",
				1
			}
		};
		volume=1;
		range=10;
		limitation=0;
	};
	class DayZCasino_SHOOT_SoundShader
	{
		samples[]=
		{

			{
				"DayZCasinoV2\data\sounds\pistol-shot",
				1
			}
		};
		volume=1;
		range=10;
		limitation=0;
	};
};

class CfgVehicles
{
	class Inventory_Base;
	class CasinoChips: Inventory_Base
	{
		scope=2;
		displayName="Casino Chip";
		descriptionShort="With this chip you can play at casino games";
		model="DayZCasinoV2\CasinoChips.p3d";
		canBeSplit=1;
		rotationFlags=16;
		lootCategory="Materials";
		lootTag[]=
		{
			"Civilian",
			"Work"
		};
		itemSize[]={1};
		weight=1;
		varQuantityInit=1;
		varQuantityMin=0;
		varQuantityMax=10000;
		varQuantityDestroyOnMin=1;
		destroyOnEmpty=1;
		absorbency=1;
	};
};