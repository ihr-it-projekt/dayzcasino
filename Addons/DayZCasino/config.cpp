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

class CfgVehicles
{
	class Inventory_Base;
	class CasinoChips: Inventory_Base
	{
		scope=2;
		displayName="1 Casino Chip";
		descriptionShort="With this chip you can play at casino games";
		model="DayZCasino\chip.p3d";
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
		hiddenSelections[]=
		{
			"WholeObject"
		};
		hiddenSelectionsTextures[]=
		{
			"DayZCasino\data\chip_co.paa"
		};
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=100;
					healthLevels[]=
					{
						
						{
							1,
							
							{
								"DayZCasino\data\chip.rvmat"
							}
						},
						
						{
							0.69999999,
							
							{
								"DayZCasino\data\chip.rvmat"
							}
						},
						
						{
							0.5,
							
							{
								"DayZCasino\data\chip_damage.rvmat"
							}
						},
						
						{
							0.30000001,
							
							{
								"DayZCasino\data\chip_damage.rvmat"
							}
						},
						
						{
							0,
							
							{
								"DayZCasino\data\chip_destruct.rvmat"
							}
						}
					};
				};
			};
		};
	};
};