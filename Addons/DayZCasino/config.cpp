class CfgPatches
{
	class DayZCasino
	{
		units[]={"CasinoChips",};
        weapons[]={};
        requiredVersion=1.0;
        requiredAddons[]={"DZ_Data"};
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
		inputs = "DayZCasino\inputs.xml";
		dir = "DayZCasino";
		picture = "";
		action = "";
		hideName = 1;
		hidePicture = 1;
		name = "DayZCasino";
		credits = "TheBuster";
		author = "TheBuster";
		authorID = "0"; 
		version = "0.1"; 
		extra = 0;
		type = "mod";
		
		dependencies[] = { "Mission"};
		
		class worldScriptModule
			{
				value="";
				files[]=
				{
					"DayZCasino/scripts/4_World"
				};
			};
		
		class defs
		{
			class missionScriptModule
			{
				value = "";
				files[] = {"DayZCasino/scripts/5_Mission"};
			};
		}
		
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
};
class cfgSoundShaders
{
	class DayZCasino_CLACK_SoundShader
	{
		samples[]=
		{
			
			{
				"DayZCasino\data\sounds\clack",
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
				"DayZCasino\data\sounds\flipcard",
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
				"DayZCasino\data\sounds\win",
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
				"DayZCasino\data\sounds\lose",
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
		model="DayZCasino\CasinoChips.p3d";
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