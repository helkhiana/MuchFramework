class CfgPatches
{
	class MuchFramework
	{
		units[]={};
		weapons[]={};
		requiredVersion=0.1;
		requiredAddons[]=
		{
			"DZ_Data"
		};
	};
};

class CfgMods
{
    class MuchFramework
    {
        dir = "MuchFramework";
        picture = "";
        action = "";
        hideName = 1;
        hidePicture = 1;
        name = "MuchFramework";
        credits = "";
        author = "Helkhiana";
        authorID = "0"; 
        version = "1.0"; 
        extra = 0;
        type = "mod";
        dependencies[] = {"GameLib", "Game", "World", "Mission"};
        
        class defs
        {
			class gameScriptModule
            {
                value = "";
                files[] = {"MuchFramework/scripts/3_Game"};
			};

            class worldScriptModule
            {
                value = "";
                files[] = {"MuchFramework/scripts/4_World"};
			};

			class missionScriptModule
            {
                value = "";
                files[] = {"MuchFramework/scripts/5_Mission"};
			};
		};
    };
};

class CfgVehicles
{
	class Container_Base;
	class Msp_Item: Container_Base
	{
		scope=0;
		destroyOnEmpty=0;
		varQuantityDestroyOnMin=0;
		descriptionShort="This can be dismantled with a screwdriver, pliers or hammer.";
		quantityBar=1;
		carveNavmesh=1;
		bounding="BSphere";
		overrideDrawArea="3.0";
		visibilityModifier=0.94999999;
		canBeDigged=0;
		alignHologramToTerain=1;
		heavyItem=1;
		itemBehaviour=1;
		weight=10;
		itemSize[]={10,10};
		physLayer="item_large";
		simulation="inventoryItem";
		hiddenSelections[]=
		{
			"all"
		};			
		simpleHiddenSelections[]=
		{
			"proxy_weapons", "proxy_clothes", "proxy_other"
		};
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=100;
				};
			};
			class GlobalArmor
			{
				class Projectile
				{
					class Health
					{
						damage=0;
					};
					class Blood
					{
						damage=0;
					};
					class Shock
					{
						damage=0;
					};
				};
				class FragGrenade
				{
					class Health
					{
						damage=0;
					};
					class Blood
					{
						damage=0;
					};
					class Shock
					{
						damage=0;
					};
				};
			};
		};
	};

	class Msp_Kit: Container_Base
	{
		scope=0;
		displayName="Box Kit";
		descriptionShort="A cardboard box used to transport base or furniture items. Place to deploy item inside. The items can be dismantled with a screwdriver, pliers or hammer after deployment.";
		model="\MuchFramework\data\kitbox\kitbox.p3d";
		itemsCargoSize[]={0,0};
		itemSize[]={6,4};
		carveNavmesh=1;
		canBeDigged=0;
		simulation="inventoryItem";
		physLayer="item_small";
		rotationFlags=2;
		heavyItem=1;
		weight=3000;
		itemBehaviour=0;
		hiddenSelections[]=
		{
			"all"
		};
		hiddenSelectionsTextures[]=
		{
			"MuchFramework\data\kitbox\kitbox_co.paa"
		};		
		hiddenSelectionsMaterials[]=
		{
			"MuchFramework\data\kitbox\kitbox.rvmat"
		};	
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=100;
				};
			};
			class GlobalArmor
			{
				class Projectile
				{
					class Health
					{
						damage=0;
					};
					class Blood
					{
						damage=0;
					};
					class Shock
					{
						damage=0;
					};
				};
				class FragGrenade
				{
					class Health
					{
						damage=0;
					};
					class Blood
					{
						damage=0;
					};
					class Shock
					{
						damage=0;
					};
				};
			};
		};
	};

	class Msp_Storage_Base: Container_Base
	{
		scope=0;      
		itemSize[]={10,15};
		overrideDrawArea="8.0";
		physLayer="item_small";
		carveNavmesh=0;
		canBeDigged=0;
		weight=1000;
		itemBehaviour=1;
		itemsCargoSize[]={0,0};
		hiddenSelections[]=
		{
			"all"
		};			
		simpleHiddenSelections[]=
		{
			"proxy_weapons", "proxy_clothes", "proxy_other"
		};	
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=100;
				};
			};
			class GlobalArmor
			{
				class Projectile
				{
					class Health
					{
						damage=0;
					};
					class Blood
					{
						damage=0;
					};
					class Shock
					{
						damage=0;
					};
				};
				class FragGrenade
				{
					class Health
					{
						damage=0;
					};
					class Blood
					{
						damage=0;
					};
					class Shock
					{
						damage=0;
					};
				};
			};
		};
	};
	
	class Msp_InventoryStorage_Base : Container_Base 
	{
		scope=0;      
		itemSize[]={10,15};
		overrideDrawArea="8.0";
		physLayer="item_small";
		weight=1000;
		itemBehaviour=1;
		itemsCargoSize[]={0,0};
		allowOwnedCargoManipulation=1;
		repairableWithKits[]={2};
		repairCosts[]={25};
		hiddenSelections[]=
		{
			"all"
		};			
		simpleHiddenSelections[]=
		{
			"proxy_weapons", "proxy_clothes", "proxy_other"
		};		
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=80;
				};
			};
		};
		soundImpactType="textile";
		class AnimEvents
		{
			class SoundWeapon
			{
				class pickUpItem_Light
				{
					soundSet="pickUpCourierBag_Light_SoundSet";
					id=796;
				};
				class pickUpItem
				{
					soundSet="pickUpCourierBag_SoundSet";
					id=797;
				};
			};
		};
	};
	class Msp_AmmoStorage_Base : Msp_Storage_Base {};
	
	class Msp_Openable_Base: Msp_Item 
	{				
		class AnimationSources
		{
			class Doors1
			{
				source="user";
				initPhase=0;
				animPeriod=1;
			};
			class Doors2
			{
				source="user";
				initPhase=0;
				animPeriod=1;
			};
			class Doors3
			{
				source="user";
				initPhase=0;
				animPeriod=1;
			};
			class Doors4
			{
				source="user";
				initPhase=0;
				animPeriod=1;
			};
		};
	};

	class Msp_Openable_Placeable_Base: Msp_Storage_Base
	{
		class AnimationSources
		{
			class Doors1
			{
				source="user";
				initPhase=0;
				animPeriod=1;
			};
			class Doors2
			{
				source="user";
				initPhase=0;
				animPeriod=1;
			};
			class Doors3
			{
				source="user";
				initPhase=0;
				animPeriod=1;
			};
			class Doors4
			{
				source="user";
				initPhase=0;
				animPeriod=1;
			};
		};
	};

	class Msp_Fridge_Base : Msp_Item
	{
		hasCargoRestrictions=1;
		class EnergyManager
		{
			hasIcon=1;
			powerSocketsCount=1;
			energyUsagePerSecond=0.03;
			cordTextureFile="DZ\gear\camping\Data\plug_black_CO.paa";
			cordLength=5;
			plugType=2;
			updateInterval=5;
		};						
		class AnimationSources
		{
			class Doors1
			{
				source="user";
				initPhase=0;
				animPeriod=0.5;
			};
			class Doors2
			{
				source="user";
				initPhase=0;
				animPeriod=0.5;
			};
			class Doors3
			{
				source="user";
				initPhase=0;
				animPeriod=1;
			};
			class Doors4
			{
				source="user";
				initPhase=0;
				animPeriod=1;
			};
		};
	};
	
	class Msp_Foldable_Item: Container_Base
	{
		descriptionShort="Deploy to unfold. Then it can be folded with your hands.";
		itemSize[] = {3,4};
		rotationFlags=16;
		weight = 2000;
		absorbency = 0;
		visibilityModifier=0.94999999;
		canBeDigged=0;
		alignHologramToTerain=1;
		itemBehaviour=2;
		physLayer="item_large";
		simulation="inventoryItem";
		hiddenSelections[]=
		{
			"all"
		};	
		class AnimationSources
		{
			class Placing
			{
				source="user";
				animPeriod=0.0099999998;
				initPhase=1;
			};
			class Inventory
			{
				source="user";
				animPeriod=0.0099999998;
				initPhase=0;
			};
		};
	};
	
    class Msp_Lamp_Base: Msp_Item
	{
		scope=0;
		class EnergyManager
		{
			hasIcon=1;
			energyUsagePerSecond=0.07;
			cordTextureFile="DZ\gear\camping\Data\plug_yellow_CO.paa";
			cordLength=5;
			plugType=2;
			updateInterval=50;
		};
	};
};