class CfgPatches
{
	class MF_Proxies
	{
		units[]={};
		weapons[]={};
		requiredVersion=0.1;
		requiredAddons[] = 
		{
			"DZ_Scripts",
			"DZ_Gear_Cooking",
			"DZ_Weapons_Melee_Blade",
			"DZ_Gear_Tools",
			"DZ_Weapons_Melee",
			"DZ_Gear_Crafting",
			"DZ_Gear_Books",
			"DZ_Gear_Containers",
			"Mass_Textures",
			"Munghardsgunwall",
			"Skyline_Furniture_Base",
			"MassBuildings"
		};
	};
};

class CfgWeapons
{
	class RifleCore;
	class Rifle_Base: RifleCore
	{
		inventorySlot[] +=
		{
			"Shoulder",
			"Melee",
			"Shoulder1",
			"Shoulder2",
			"Shoulder3",
			"Shoulder4",
			"Shoulder5",
			"Shoulder6",
			"Shoulder7",
			"Shoulder8",
			"Shoulder9",
			"Shoulder10",
			"Shoulder11",
			"Shoulder12",
			"Shoulder13",
			"Shoulder14",
			"Shoulder15",
			"Shoulder16",
			"Shoulder17",
			"Shoulder18",
			"Shoulder19",
			"Shoulder20",
			"Shoulder21",
			"Shoulder22",
			"Shoulder23",
			"Shoulder24",
			"Shoulder25",
			"Shoulder26",
			"Shoulder27",
			"Shoulder28",
			"Shoulder29",
			"Shoulder30"
		};
	};
	class PistolCore;
	class Pistol_Base: PistolCore
	{
		inventorySlot[] +=
		{
			"Pistol",
			"Pistol1",
			"Pistol2",
			"Pistol3",
			"Pistol4"
		};
	};
	class Archery_Base: RifleCore
	{
		inventorySlot[] +=
		{
			"Shoulder",
			"Melee",
			"Shoulder1",
			"Shoulder2",
			"Shoulder3",
			"Shoulder4",
			"Shoulder5",
			"Shoulder6",
			"Shoulder7",
			"Shoulder8",
			"Shoulder9",
			"Shoulder10",
			"Shoulder11",
			"Shoulder12",
			"Shoulder13",
			"Shoulder14",
			"Shoulder15",
			"Shoulder16",
			"Shoulder17",
			"Shoulder18",
			"Shoulder19",
			"Shoulder20",
			"Shoulder21",
			"Shoulder22",
			"Shoulder23",
			"Shoulder24",
			"Shoulder25",
			"Shoulder26",
			"Shoulder27",
			"Shoulder28",
			"Shoulder29",
			"Shoulder30"
		};
	};
};

class CfgSlots
{
	class Slot_Att_CodeLock
	{
		name="Att_CodeLock";
		displayName="Code Lock";
		selection="att_codeLock";
		ghostIcon="set:dayz_inventory image:combolock";
	};
	class Slot_Flashlight
	{
		name="Flashlight";
		displayName="$STR_CfgVehicles_Flashlight0";
		selection="Flashlight";
		ghostIcon="set:dayz_inventory image:weaponflashlight";
	};
	class Slot_fishingrod1
	{
		name="fishingrod1";
		displayName="Fishing Rod";
		selection="fishingrod1";
		ghostIcon="set:dayz_inventory image:shoulderleft";
	};
	class Slot_fishingrod2
	{
		name="fishingrod2";
		displayName="Fishing Rod";
		selection="fishingrod2";
		ghostIcon="set:dayz_inventory image:shoulderleft";
	};
	class Slot_fishingrod3
	{
		name="fishingrod3";
		displayName="Fishing Rod";
		selection="fishingrod3";
		ghostIcon="set:dayz_inventory image:shoulderleft";
	};
	class Slot_fishingrod4
	{
		name="fishingrod4";
		displayName="Fishing Rod";
		selection="fishingrod4";
		ghostIcon="set:dayz_inventory image:shoulderleft";
	};
	class Slot_fishingrod5
	{
		name="fishingrod5";
		displayName="Fishing Rod";
		selection="fishingrod5";
		ghostIcon="set:dayz_inventory image:shoulderleft";
	};
	class Slot_fishingrod6
	{
		name="fishingrod6";
		displayName="Fishing Rod";
		selection="fishingrod6";
		ghostIcon="set:dayz_inventory image:shoulderleft";
	};
	class Slot_fishingrod7
	{
		name="fishingrod7";
		displayName="Fishing Rod";
		selection="fishingrod7";
		ghostIcon="set:dayz_inventory image:shoulderleft";
	};
	class Slot_fishingrod8
	{
		name="fishingrod8";
		displayName="Fishing Rod";
		selection="fishingrod8";
		ghostIcon="set:dayz_inventory image:shoulderleft";
	};
	class Slot_fishingrod9
	{
		name="fishingrod9";
		displayName="Fishing Rod";
		selection="fishingrod9";
		ghostIcon="set:dayz_inventory image:shoulderleft";
	};
	class Slot_fishingrod10
	{
		name="fishingrod10";
		displayName="Fishing Rod";
		selection="fishingrod10";
		ghostIcon="set:dayz_inventory image:shoulderleft";
	};
	class Slot_Axe1
	{
		name="Axe1";
		displayName="Axe";
		ghostIcon="set:dayz_inventory image:shoulderleft";
	};
	class Slot_Hatchet
	{
		name="Hatchet";
		displayName="Hatchet";
		ghostIcon="set:dayz_inventory image:shoulderleft";
	};
	class Slot_Hatchet1
	{
		name="Hatchet1";
		displayName="Hatchet";
		ghostIcon="set:dayz_inventory image:shoulderleft";
	};
	class Slot_Hatchet2
	{
		name="Hatchet2";
		displayName="Hatchet";
		ghostIcon="set:dayz_inventory image:shoulderleft";
	};
	class Slot_Hatchet3
	{
		name="Hatchet3";
		displayName="Hatchet";
		ghostIcon="set:dayz_inventory image:shoulderleft";
	};
	class Slot_Hatchet4
	{
		name="Hatchet4";
		displayName="Hatchet";
		ghostIcon="set:dayz_inventory image:shoulderleft";
	};
	class Slot_Pickaxe1
	{
		name="Pickaxe1";
		displayName="Pickaxe";
		ghostIcon="set:dayz_inventory image:shoulderleft";
	};
	class Slot_Pliers1
	{
		name="Pliers1";
		displayName="Pliers";
		ghostIcon="set:dayz_inventory image:cat_common_cargo";
	};
	class Slot_Screwdriver1
	{
		name="Screwdriver1";
		displayName="Screwdriver";
		ghostIcon="set:dayz_inventory image:cat_common_cargo";
	};
	class Slot_Screwdriver2
	{
		name="Screwdriver2";
		displayName="Screwdriver";
		ghostIcon="set:dayz_inventory image:cat_common_cargo";
	};
	class Slot_Shovel1
	{
		name="Shovel1";
		displayName="Shovel";
		ghostIcon="set:dayz_inventory image:shoulderleft";
	};
	class Slot_Hammer1
	{
		name="Hammer1";
		displayName="Hammer";
		ghostIcon="set:dayz_inventory image:cat_common_cargo";
	};
	class Slot_Hammer2
	{
		name="Hammer2";
		displayName="Hammer";
		ghostIcon="set:dayz_inventory image:cat_common_cargo";
	};
	class Slot_Hammer3
	{
		name="Hammer3";
		displayName="Hammer";
		ghostIcon="set:dayz_inventory image:cat_common_cargo";
	};
	class Slot_Saw1
	{
		name="Saw1";
		displayName="Saw";
		ghostIcon="set:dayz_inventory image:cat_common_cargo";
	};
	class Slot_Saw2
	{
		name="Saw2";
		displayName="Saw";
		ghostIcon="set:dayz_inventory image:cat_common_cargo";
	};
	class Slot_Saw3
	{
		name="Saw3";
		displayName="Saw";
		ghostIcon="set:dayz_inventory image:cat_common_cargo";
	};
	class Slot_Wire1
	{
		name="Wire1";
		displayName="Wire";
		ghostIcon="set:dayz_inventory image:metalwire";
	};
	class Slot_Wire2
	{
		name="Wire2";
		displayName="Wire";
		ghostIcon="set:dayz_inventory image:metalwire";
	};
	class Slot_Wire3
	{
		name="Wire3";
		displayName="Wire";
		ghostIcon="set:dayz_inventory image:metalwire";
	};
	class Slot_Pistol1
	{
		name="Pistol1";
		displayName="Pistol";
		ghostIcon="set:dayz_inventory image:pistol";
	};
	class Slot_Pistol2
	{
		name="Pistol2";
		displayName="Pistol";
		ghostIcon="set:dayz_inventory image:pistol";
	};
	class Slot_Pistol3
	{
		name="Pistol3";
		displayName="Pistol";
		ghostIcon="set:dayz_inventory image:pistol";
	};
	class Slot_Pistol4
	{
		name="Pistol4";
		displayName="Pistol";
		ghostIcon="set:dayz_inventory image:pistol";
	};
	class Slot_FirstAid
	{
		name = "FirstAid";
		displayName = "First Aid Kit";
		ghostIcon="set:dayz_inventory image:medicalbandage";
	};
	class Slot_FirstAidKit1
	{
		name = "FirstAidKit1";
		displayName = "First Aid Kit";
		ghostIcon="set:dayz_inventory image:medicalbandage";
	};
	class Slot_FirstAidKit2
	{
		name = "FirstAidKit2";
		displayName = "First Aid Kit";
		ghostIcon="set:dayz_inventory image:medicalbandage";
	};
	class Slot_FirstAidKit3
	{
		name = "FirstAidKit3";
		displayName = "First Aid Kit";
		ghostIcon="set:dayz_inventory image:medicalbandage";
	};
	class Slot_FirstAidKit4
	{
		name = "FirstAidKit4";
		displayName = "First Aid Kit";
		ghostIcon="set:dayz_inventory image:medicalbandage";
	};
	class Slot_protectorcase
	{
		name = "protectorcase";
		displayName = "Protector Case";
		ghostIcon = "set:dayz_inventory image:pouches";
	};
	class Slot_AmmoBox1
	{
		name="AmmoBox1";
		displayName="Ammo Box";
		ghostIcon="set:dayz_inventory image:cat_common_cargo";
	};
	class Slot_AmmoBox2
	{
		name="AmmoBox2";
		displayName="Ammo Box";
		ghostIcon="set:dayz_inventory image:cat_common_cargo";
	};
	class Slot_AmmoBox3
	{
		name="AmmoBox3";
		displayName="Ammo Box";
		ghostIcon="set:dayz_inventory image:cat_common_cargo";
	};
	class Slot_GasLamp
	{
		name="GasLamp";
		displayName="Gas Lamp";
		ghostIcon="set:dayz_inventory image:cookingequipment";
	};
	class Slot_FGrenade1
	{
		name="FGrenade1";
		displayName="Grenade";
		ghostIcon="set:dayz_inventory image:grenade";
	};
	class Slot_FGrenade2
	{
		name="FGrenade2";
		displayName="Grenade";
		ghostIcon="set:dayz_inventory image:grenade";
	};
	class Slot_FGrenade3
	{
		name="FGrenade3";
		displayName="Grenade";
		ghostIcon="set:dayz_inventory image:grenade";
	};
	class Slot_FGrenade4
	{
		name="FGrenade4";
		displayName="Grenade";
		ghostIcon="set:dayz_inventory image:grenade";
	};
	class Slot_FGrenade5
	{
		name="FGrenade5";
		displayName="Grenade";
		ghostIcon="set:dayz_inventory image:grenade";
	};
	class Slot_FGrenade6
	{
		name="FGrenade6";
		displayName="Grenade";
		ghostIcon="set:dayz_inventory image:grenade";
	};
	class Slot_FGrenade7
	{
		name="FGrenade7";
		displayName="Grenade";
		ghostIcon="set:dayz_inventory image:grenade";
	};
	class Slot_FGrenade8
	{
		name="FGrenade8";
		displayName="Grenade";
		ghostIcon="set:dayz_inventory image:grenade";
	};
	class Slot_FGrenade9
	{
		name="FGrenade9";
		displayName="Grenade";
		ghostIcon="set:dayz_inventory image:grenade";
	};
	class Slot_FGrenade10
	{
		name="FGrenade10";
		displayName="Grenade";
		ghostIcon="set:dayz_inventory image:grenade";
	};
	class Slot_Shoulder1
	{
		name="Shoulder1";
		displayName="$STR_CfgShoulder0";
		ghostIcon="set:dayz_inventory image:shoulderleft";
	};
	class Slot_Shoulder2
	{
		name="Shoulder2";
		displayName="$STR_CfgShoulder0";
		ghostIcon="set:dayz_inventory image:shoulderleft";
	};
	class Slot_Shoulder3
	{
		name="Shoulder3";
		displayName="$STR_CfgShoulder0";
		ghostIcon="set:dayz_inventory image:shoulderleft";
	};
	class Slot_Shoulder4
	{
		name="Shoulder4";
		displayName="$STR_CfgShoulder0";
		ghostIcon="set:dayz_inventory image:shoulderleft";
	};
	class Slot_Shoulder5
	{
		name="Shoulder5";
		displayName="$STR_CfgShoulder0";
		ghostIcon="set:dayz_inventory image:shoulderleft";
	};
	class Slot_Shoulder6
	{
		name="Shoulder6";
		displayName="$STR_CfgShoulder0";
		ghostIcon="set:dayz_inventory image:shoulderleft";
	};
	class Slot_Shoulder7
	{
		name="Shoulder7";
		displayName="$STR_CfgShoulder0";
		ghostIcon="set:dayz_inventory image:shoulderleft";
	};
	class Slot_Shoulder8
	{
		name="Shoulder8";
		displayName="$STR_CfgShoulder0";
		ghostIcon="set:dayz_inventory image:shoulderleft";
	};	
	class Slot_Shoulder9
	{
		name="Shoulder9";
		displayName="$STR_CfgShoulder0";
		ghostIcon="set:dayz_inventory image:shoulderleft";
	};
	class Slot_Shoulder10
	{
		name="Shoulder10";
		displayName="$STR_CfgShoulder0";
		ghostIcon="set:dayz_inventory image:shoulderleft";
	};
	class Slot_Shoulder11
	{
		name="Shoulder11";
		displayName="$STR_CfgShoulder0";
		ghostIcon="set:dayz_inventory image:shoulderleft";
	};
	class Slot_Shoulder12
	{
		name="Shoulder12";
		displayName="$STR_CfgShoulder0";
		ghostIcon="set:dayz_inventory image:shoulderleft";
	};
	class Slot_Shoulder13
	{
		name="Shoulder13";
		displayName="$STR_CfgShoulder0";
		ghostIcon="set:dayz_inventory image:shoulderleft";
	};
	class Slot_Shoulder14
	{
		name="Shoulder14";
		displayName="$STR_CfgShoulder0";
		ghostIcon="set:dayz_inventory image:shoulderleft";
	};
	class Slot_Shoulder15
	{
		name="Shoulder15";
		displayName="$STR_CfgShoulder0";
		ghostIcon="set:dayz_inventory image:shoulderleft";
	};
	class Slot_Shoulder16
	{
		name="Shoulder16";
		displayName="$STR_CfgShoulder0";
		ghostIcon="set:dayz_inventory image:shoulderleft";
	};
	class Slot_Shoulder17
	{
		name="Shoulder17";
		displayName="$STR_CfgShoulder0";
		ghostIcon="set:dayz_inventory image:shoulderleft";
	};
	class Slot_Shoulder18
	{
		name="Shoulder18";
		displayName="$STR_CfgShoulder0";
		ghostIcon="set:dayz_inventory image:shoulderleft";
	};
	class Slot_Shoulder19
	{
		name="Shoulder19";
		displayName="$STR_CfgShoulder0";
		ghostIcon="set:dayz_inventory image:shoulderleft";
	};
	class Slot_Shoulder20
	{
		name="Shoulder20";
		displayName="$STR_CfgShoulder0";
		ghostIcon="set:dayz_inventory image:shoulderleft";
	};
	class Slot_Sword1
	{
		name="Sword1";
		displayName="Sword1";
		ghostIcon="set:dayz_inventory image:shoulderleft";
	};
	class Slot_Sword2
	{
		name="Sword2";
		displayName="Sword2";
		ghostIcon="set:dayz_inventory image:shoulderleft";
	};
	class Slot_Sword3
	{
		name="Sword3";
		displayName="Sword3";
		ghostIcon="set:dayz_inventory image:shoulderleft";
	};	
	class Slot_Book1
	{
		name="Book1";
		displayname="Book";
		ghostIcon="set:dayz_inventory image:book";
	};
	class Slot_Book2
	{
		name="Book2";
		displayname="Book";
		ghostIcon="set:dayz_inventory image:book";
	};
	class Slot_Book3
	{
		name="Book3";
		displayname="Book";
		ghostIcon="set:dayz_inventory image:book";
	};
	class Slot_Book4
	{
		name="Book4";
		displayname="Book";
		ghostIcon="set:dayz_inventory image:book";
	};
	class Slot_Book5
	{
		name="Book5";
		displayname="Book";
		ghostIcon="set:dayz_inventory image:book";
	};
	class Slot_Book6
	{
		name="Book6";
		displayname="Book";
		ghostIcon="set:dayz_inventory image:book";
	};
	class Slot_Book7
	{
		name="Book7";
		displayname="Book";
		ghostIcon="set:dayz_inventory image:book";
	};
	class Slot_Book8
	{
		name="Book8";
		displayname="Book";
		ghostIcon="set:dayz_inventory image:book";
	};
	class Slot_Book9
	{
		name="Book9";
		displayname="Book";
		ghostIcon="set:dayz_inventory image:book";
	};
	class Slot_Book10
	{
		name="Book10";
		displayname="Book";
		ghostIcon="set:dayz_inventory image:book";
	};
	class Slot_Book11
	{
		name="Book11";
		displayname="Book";
		ghostIcon="set:dayz_inventory image:book";
	};
	class Slot_Book12
	{
		name="Book12";
		displayname="Book";
		ghostIcon="set:dayz_inventory image:book";
	};
	class Slot_Book13
	{
		name="Book13";
		displayname="Book";
		ghostIcon="set:dayz_inventory image:book";
	};
	class Slot_Book14
	{
		name="Book14";
		displayname="Book";
		ghostIcon="set:dayz_inventory image:book";
	};
	class Slot_Book15
	{
		name="Book15";
		displayname="Book";
		ghostIcon="set:dayz_inventory image:book";
	};
	class Slot_Book16
	{
		name="Book16";
		displayname="Book";
		ghostIcon="set:dayz_inventory image:book";
	};
	class Slot_Book17
	{
		name="Book17";
		displayname="Book";
		ghostIcon="set:dayz_inventory image:book";
	};
	class Slot_Book18
	{
		name="Book18";
		displayname="Book";
		ghostIcon="set:dayz_inventory image:book";
	};
	class Slot_Book19
	{
		name="Book19";
		displayname="Book";
		ghostIcon="set:dayz_inventory image:book";
	};
	class Slot_Book20
	{
		name="Book20";
		displayname="Book";
		ghostIcon="set:dayz_inventory image:book";
	};
	class Slot_Book21
	{
		name="Book21";
		displayname="Book";
		ghostIcon="set:dayz_inventory image:book";
	};
	class Slot_Book22
	{
		name="Book22";
		displayname="Book";
		ghostIcon="set:dayz_inventory image:book";
	};
	class Slot_Book23
	{
		name="Book23";
		displayname="Book";
		ghostIcon="set:dayz_inventory image:book";
	};
	class Slot_Book24
	{
		name="Book24";
		displayname="Book";
		ghostIcon="set:dayz_inventory image:book";
	};
	class Slot_Book25
	{
		name="Book25";
		displayname="Book";
		ghostIcon="set:dayz_inventory image:book";
	};
	class Slot_Book26
	{
		name="Book26";
		displayname="Book";
		ghostIcon="set:dayz_inventory image:book";
	};
	class Slot_Book27
	{
		name="Book27";
		displayname="Book";
		ghostIcon="set:dayz_inventory image:book";
	};
	class Slot_Book28
	{
		name="Book28";
		displayname="Book";
		ghostIcon="set:dayz_inventory image:book";
	};
	class Slot_Book29
	{
		name="Book29";
		displayname="Book";
		ghostIcon="set:dayz_inventory image:book";
	};
	class Slot_Book30
	{
		name="Book30";
		displayname="Book";
		ghostIcon="set:dayz_inventory image:book";
	};
	class Slot_Book31
	{
		name="Book31";
		displayname="Book";
		ghostIcon="set:dayz_inventory image:book";
	};
	class Slot_Book32
	{
		name="Book32";
		displayname="Book";
		ghostIcon="set:dayz_inventory image:book";
	};
	class Slot_Book33
	{
		name="Book33";
		displayname="Book";
		ghostIcon="set:dayz_inventory image:book";
	};
	class Slot_Book34
	{
		name="Book34";
		displayname="Book";
		ghostIcon="set:dayz_inventory image:book";
	};
	class Slot_Book35
	{
		name="Book35";
		displayname="Book";
		ghostIcon="set:dayz_inventory image:book";
	};
	class Slot_Book36
	{
		name="Book36";
		displayname="Book";
		ghostIcon="set:dayz_inventory image:book";
	};
	class Slot_Book37
	{
		name="Book37";
		displayname="Book";
		ghostIcon="set:dayz_inventory image:book";
	};
	class Slot_Book38
	{
		name="Book38";
		displayname="Book";
		ghostIcon="set:dayz_inventory image:book";
	};
	class Slot_Book39
	{
		name="Book39";
		displayname="Book";
		ghostIcon="set:dayz_inventory image:book";
	};
	class Slot_Book40
	{
		name="Book40";
		displayname="Book";
		ghostIcon="set:dayz_inventory image:book";
	};
	class Slot_Book41
	{
		name="Book41";
		displayname="Book";
		ghostIcon="set:dayz_inventory image:book";
	};
	class Slot_Book42
	{
		name="Book42";
		displayname="Book";
		ghostIcon="set:dayz_inventory image:book";
	};
	class Slot_Book43
	{
		name="Book43";
		displayname="Book";
		ghostIcon="set:dayz_inventory image:book";
	};
	class Slot_Book44
	{
		name="Book44";
		displayname="Book";
		ghostIcon="set:dayz_inventory image:book";
	};
	class Slot_Book45
	{
		name="Book45";
		displayname="Book";
		ghostIcon="set:dayz_inventory image:book";
	};
	class Slot_Book46
	{
		name="Book46";
		displayname="Book";
		ghostIcon="set:dayz_inventory image:book";
	};
	class Slot_Book47
	{
		name="Book47";
		displayname="Book";
		ghostIcon="set:dayz_inventory image:book";
	};
	class Slot_Book48
	{
		name="Book48";
		displayname="Book";
		ghostIcon="set:dayz_inventory image:book";
	};
	class Slot_Book49
	{
		name="Book49";
		displayname="Book";
		ghostIcon="set:dayz_inventory image:book";
	};
	class Slot_Book50
	{
		name="Book50";
		displayname="Book";
		ghostIcon="set:dayz_inventory image:book";
	};
};

class CfgVehicles
{
	class Inventory_Base;
    class Container_Base;

	class PortableGasLamp: Inventory_Base
	{
        inventorySlot[] +=
		{
			"GasLamp"
		};
    };

	class Grenade_Base: Inventory_Base
	{
		inventorySlot[] +=
		{
			"VestGrenadeA",
			"VestGrenadeB",
			"VestGrenadeC",
			"VestGrenadeD",
			"tripWireAttachment",
			"FGrenade1",
			"FGrenade2",
			"FGrenade3",
			"FGrenade4",	
			"FGrenade5",
			"FGrenade6",
			"FGrenade7",
			"FGrenade8",
			"FGrenade9",
			"FGrenade10"
		};
	};
	class Sword: Inventory_Base
	{
		inventorySlot[] +=
		{
			"Shoulder",
			"Melee",
			"Sword1",
			"Sword2",
			"Sword3"
		};
	};
	class WoodAxe: Inventory_Base
	{
		inventorySlot[] +=
		{
			"Shoulder",
			"Melee",
			"Axe1"
		};
	};
	class FirefighterAxe: Inventory_Base
	{
		inventorySlot[] +=
		{
			"Shoulder",
			"Melee",
			"Axe1"
		};
	};
	class Pickaxe: Inventory_Base
	{
		inventorySlot[] +=
		{
			"Shoulder",
			"Melee",
			"Pickaxe1"
		};
	};
	class Hatchet: Inventory_Base
	{
		inventorySlot[] +=
		{
			"MassTool",
			"Hatchet",
			"Hatchet1",
			"Hatchet2",
			"Hatchet3",
			"Hatchet4"
		};
	};
	class Hammer: Inventory_Base
	{
		inventorySlot[] +=
		{
			"Hammer",
			"MassHammer",
			"Hammer1",
			"Hammer2",
			"Hammer3"
		};
	};
	class Shovel: Inventory_Base
	{
		inventorySlot[] +=
		{
			"Shoulder",
			"Melee",
			"Shovel1"
		};
	};
	class Pliers: Inventory_Base
	{
		inventorySlot[] +=
		{
			"Pliers",
			"Pliers1"
		};
	};
	class HandSaw: Inventory_Base
	{
		inventorySlot[] +=
		{
			"HandSaw",
			"Saw",
			"Saw1",
			"Saw2",
			"Saw3"
		};
	};
	class Hacksaw: Inventory_Base
	{
		inventorySlot[] +=
		{
			"Hacksaw",
			"Saw",
			"Saw1",
			"Saw2",
			"Saw3"
		};
	};
	class Screwdriver: Inventory_Base
	{
		inventorySlot[] +=
		{
			"Screwdriver",
			"MassScrewDriver",
			"Screwdriver1",
			"Screwdriver2"
		};
	};
	class MetalWire: Inventory_Base
	{
		inventorySlot[] +=
		{
			"MetalWire",
			"Material_MetalWire",
			"Material_FPole_MetalWire",
			"Wire1",
			"Wire2",
			"Wire3"
		};
	};
	class Book_Base: Inventory_Base
	{
		inventorySlot[] +=
		{
			"Book",
			"Book1","Book2","Book3","Book4","Book5",
			"Book6","Book7","Book8","Book9","Book10",
			"Book11","Book12","Book13","Book14","Book15",
			"Book16","Book17","Book18","Book19","Book20",
			"Book21","Book22","Book23","Book24","Book25",
			"Book26","Book27","Book28","Book29","Book30",
			"Book31","Book32","Book33","Book34","Book35",
			"Book36","Book37","Book38","Book39","Book40",
			"Book41","Book42","Book43","Book44","Book45",
			"Book46","Book47","Book48","Book49","Book50"
		};		
	};	
	class ItemBook;
	class BookBible: ItemBook
	{
		displayName="The Bible";
		descriptionShort="The Bible";
	};

	class FishingRod_Base;
	class FishingRod_Base_New: FishingRod_Base
	{
		inventorySlot[] +=
		{
			"fishingpole",
			"fishingrod1",
			"fishingrod2",
			"fishingrod3",
			"fishingrod4",
			"fishingrod5",
			"fishingrod6",
			"fishingrod7",
			"fishingrod8",
			"fishingrod9",
			"fishingrod10"
		};
	};
	class FishingRod: FishingRod_Base_New
	{
		inventorySlot[] +=
		{
			"fishingpole",
			"fishingrod1",
			"fishingrod2",
			"fishingrod3",
			"fishingrod4",
			"fishingrod5",
			"fishingrod6",
			"fishingrod7",
			"fishingrod8",
			"fishingrod9",
			"fishingrod10"
		};
	};
	class ImprovisedFishingRod: FishingRod_Base_New
	{
		inventorySlot[] +=
		{
			"fishingpole",
			"fishingrod1",
			"fishingrod2",
			"fishingrod3",
			"fishingrod4",
			"fishingrod5",
			"fishingrod6",
			"fishingrod7",
			"fishingrod8",
			"fishingrod9",
			"fishingrod10"
		};
	};
	class FirstAidKit: Container_Base
	{
		inventorySlot[] += {"FirstAid","FirstAidKit1","FirstAidKit2","FirstAidKit3","FirstAidKit4"};
	};
	class SmallProtectorCase: Container_Base
	{
		inventorySlot[] += {"protectorcase"};
	};
	class AmmoBox: Container_Base
	{
		inventorySlot[] += {"300RoundBox","AmmoBox1","AmmoBox2","AmmoBox3"};
	};

	class Flashlight: Inventory_Base
	{
		inventorySlot[] += {"Flashlight","Flashlight1","Flashlight2","Flashlight3"};
	};
};

class CfgNonAIVehicles
{
	class ProxyAttachment;
	class ProxyFirstAidKit: ProxyAttachment
	{
		scope = 2;
		inventorySlot[] = {"FirstAid"};
		model = "DZ\gear\containers\FirstAidKit.p3d";
	};
	class Proxyflashlight: ProxyAttachment
	{
		scope = 2;
		inventorySlot[] = {"Flashlight"};
		model = "\DZ\gear\tools\flashlight.p3d";
	};
	class Proxyprotector_case: ProxyAttachment
	{
		scope = 2;
		inventorySlot[] = {"protectorcase"};
		model = "\dz\gear\containers\protector_case.p3d";
	};
	class Proxypistol1: ProxyAttachment
	{
		scope=2;
		inventorySlot[]={"Pistol1"};
		model="\MuchFramework\proxies\pistol1.p3d";
	};
	class Proxypistol2: ProxyAttachment
	{
		scope=2;
		inventorySlot[]={"Pistol2"};
		model="\MuchFramework\proxies\pistol2.p3d";
	};
	class Proxypistol3: ProxyAttachment
	{
		scope=2;
		inventorySlot[]={"Pistol3"};
		model="\MuchFramework\proxies\pistol3.p3d";
	};
	class Proxypistol4: ProxyAttachment
	{
		scope=2;
		inventorySlot[]={"Pistol4"};
		model="\MuchFramework\proxies\pistol4.p3d";
	};
	class Proxyfishing_rod1: ProxyAttachment
	{
		scope=2;
		inventorySlot[] = {	"fishingrod1" };
		model="MuchFramework\proxies\fishingrods\fishing_rod1.p3d";
	};
	class Proxyfishing_rod2: ProxyAttachment
	{
		scope=2;
		inventorySlot[] = {	"fishingrod2" };
		model="MuchFramework\proxies\fishingrods\fishing_rod2.p3d";
	};
	class Proxyfishing_rod3: ProxyAttachment
	{
		scope=2;
		inventorySlot[] = {	"fishingrod3" };
		model="MuchFramework\proxies\fishingrods\fishing_rod3.p3d";
	};
	class Proxyfishing_rod4: ProxyAttachment
	{
		scope=2;
		inventorySlot[] = {	"fishingrod4" };
		model="MuchFramework\proxies\fishingrods\fishing_rod4.p3d";
	};
	class Proxyfishing_rod5: ProxyAttachment
	{
		scope=2;
		inventorySlot[] = {	"fishingrod5" };
		model="MuchFramework\proxies\fishingrods\fishing_rod5.p3d";
	};
	class Proxyfishing_rod6: ProxyAttachment
	{
		scope=2;
		inventorySlot[] = {	"fishingrod6" };
		model="MuchFramework\proxies\fishingrods\fishing_rod6.p3d";
	};
	class Proxyfishing_rod7: ProxyAttachment
	{
		scope=2;
		inventorySlot[] = {	"fishingrod7" };
		model="MuchFramework\proxies\fishingrods\fishing_rod7.p3d";
	};
	class Proxyfishing_rod8: ProxyAttachment
	{
		scope=2;
		inventorySlot[] = {	"fishingrod8" };
		model="MuchFramework\proxies\fishingrods\fishing_rod8.p3d";
	};
	class Proxyfishing_rod9: ProxyAttachment
	{
		scope=2;
		inventorySlot[] = {	"fishingrod9" };
		model="MuchFramework\proxies\fishingrods\fishing_rod9.p3d";
	};
	class Proxyfishing_rod10: ProxyAttachment
	{
		scope=2;
		inventorySlot[] = {	"fishingrod10" };
		model="MuchFramework\proxies\fishingrods\fishing_rod10.p3d";
	};
	class Proxygaslight: ProxyAttachment
	{
		scope=2;
		inventorySlot[] = { "GasLamp" };
		model="\dz\gear\cooking\GasLight.p3d";
	};
	class Proxyaxe1: ProxyAttachment
	{
		scope=2;
		inventorySlot[] = { "Axe1" };
		model="\MuchFramework\proxies\tools\axe1.p3d";
	};
	class Proxypickaxe1: ProxyAttachment
	{
		scope=2;
		inventorySlot[] = { "Pickaxe1" };
		model="\MuchFramework\proxies\tools\pickaxe1.p3d";
	};
	class Proxypliers1: ProxyAttachment
	{
		scope=2;
		inventorySlot[] = { "Pliers1" };
		model="\MuchFramework\proxies\tools\pliers1.p3d";
	};
	class Proxyhatchet1: ProxyAttachment
	{
		scope=2;
		inventorySlot[] = { "Hatchet1" };
		model="\MuchFramework\proxies\tools\hatchet1.p3d";
	};
	class Proxyhatchet2: ProxyAttachment
	{
		scope=2;
		inventorySlot[] = { "Hatchet2" };
		model="\MuchFramework\proxies\tools\hatchet2.p3d";
	};
	class Proxyhatchet3: ProxyAttachment
	{
		scope=2;
		inventorySlot[] = { "Hatchet3" };
		model="\MuchFramework\proxies\tools\hatchet3.p3d";
	};
	class Proxyhatchet4: ProxyAttachment
	{
		scope=2;
		inventorySlot[] = { "Hatchet4" };
		model="\MuchFramework\proxies\tools\hatchet4.p3d";
	};
	class Proxyhatchet5: ProxyAttachment
	{
		scope=2;
		inventorySlot[] = { "Hatchet" };
		model="\MuchFramework\proxies\tools\hatchet5.p3d";
	};
	class Proxyscrewdriver1: ProxyAttachment
	{
		scope=2;
		inventorySlot[] = { "Screwdriver1" };
		model="\MuchFramework\proxies\tools\screwdriver1.p3d";
	};
	class Proxyscrewdriver2: ProxyAttachment
	{
		scope=2;
		inventorySlot[] = { "Screwdriver2" };
		model="\MuchFramework\proxies\tools\screwdriver2.p3d";
	};
	class Proxyshovel1: ProxyAttachment
	{
		scope=2;
		inventorySlot[] = { "Shovel1" };
		model="\MuchFramework\proxies\tools\shovel1.p3d";
	};
	
	class Proxyhammer1: ProxyAttachment
	{
		scope=2;
		inventorySlot[] = { "Hammer1" };
		model="\MuchFramework\proxies\tools\hammer1.p3d";
	};
	class Proxyhammer2: ProxyAttachment
	{
		scope=2;
		inventorySlot[] = { "Hammer2" };
		model="\MuchFramework\proxies\tools\hammer2.p3d";
	};
	class Proxyhammer3: ProxyAttachment
	{
		scope=2;
		inventorySlot[] = { "Hammer3" };
		model="\MuchFramework\proxies\tools\hammer3.p3d";
	};
	class Proxysaw1: ProxyAttachment
	{
		scope=2;
		inventorySlot[] = { "Saw1" };
		model="\MuchFramework\proxies\tools\saw1.p3d";
	};
	class Proxysaw2: ProxyAttachment
	{
		scope=2;
		inventorySlot[] = { "Saw2" };
		model="\MuchFramework\proxies\tools\saw2.p3d";
	};
	class Proxysaw3: ProxyAttachment
	{
		scope=2;
		inventorySlot[] = { "Saw3" };
		model="\MuchFramework\proxies\tools\saw3.p3d";
	};
	class Proxywire1: ProxyAttachment
	{
		scope=2;
		inventorySlot[] = { "Wire1" };
		model="\MuchFramework\proxies\tools\wire1.p3d";
	};
	class Proxywire2: ProxyAttachment
	{
		scope=2;
		inventorySlot[] = { "Wire2" };
		model="\MuchFramework\proxies\tools\wire2.p3d";
	};
	class Proxywire3: ProxyAttachment
	{
		scope=2;
		inventorySlot[] = { "Wire3" };
		model="\MuchFramework\proxies\tools\wire3.p3d";
	};
	class ProxyAmmoBox1: ProxyAttachment
	{
		scope=2;
		inventorySlot[] = { "AmmoBox1" };
		model="\MuchFramework\proxies\AmmoBox1.p3d";
	};
	class ProxyAmmoBox2: ProxyAttachment
	{
		scope=2;
		inventorySlot[] = { "AmmoBox2" };
		model="\MuchFramework\proxies\AmmoBox2.p3d";
	};
	class ProxyAmmoBox3: ProxyAttachment
	{
		scope=2;
		inventorySlot[] = { "AmmoBox3" };
		model="\MuchFramework\proxies\AmmoBox3.p3d";
	};
	class Proxygrenade1: ProxyAttachment
	{
		scope=2;
		inventorySlot[] = { "FGrenade1" };
		model="\MuchFramework\proxies\grenade1.p3d";
	};
	class Proxygrenade2: ProxyAttachment
	{
		scope=2;
		inventorySlot[] = { "FGrenade2" };
		model="\MuchFramework\proxies\grenade2.p3d";
	};
	class Proxygrenade3: ProxyAttachment
	{
		scope=2;
		inventorySlot[] = { "FGrenade3" };
		model="\MuchFramework\proxies\grenade3.p3d";
	};
	class Proxygrenade4: ProxyAttachment
	{
		scope=2;
		inventorySlot[] = { "FGrenade4" };
		model="\MuchFramework\proxies\grenade4.p3d";
	};
	class Proxygrenade5: ProxyAttachment
	{
		scope=2;
		inventorySlot[] = { "FGrenade5" };
		model="\MuchFramework\proxies\grenade5.p3d";
	};
	class Proxygrenade6: ProxyAttachment
	{
		scope=2;
		inventorySlot[] = { "FGrenade6" };
		model="\MuchFramework\proxies\grenade6.p3d";
	};
	class Proxygrenade7: ProxyAttachment
	{
		scope=2;
		inventorySlot[] = { "FGrenade7" };
		model="\MuchFramework\proxies\grenade7.p3d";
	};
	class Proxygrenade8: ProxyAttachment
	{
		scope=2;
		inventorySlot[] = { "FGrenade8" };
		model="\MuchFramework\proxies\grenade8.p3d";
	};
	class Proxygrenade9: ProxyAttachment
	{
		scope=2;
		inventorySlot[] = { "FGrenade9" };
		model="\MuchFramework\proxies\grenade9.p3d";
	};
	class Proxygrenade10: ProxyAttachment
	{
		scope=2;
		inventorySlot[] = { "FGrenade10" };
		model="\MuchFramework\proxies\grenade10.p3d";
	};
	class Proxyshoulder1: ProxyAttachment
	{
		scope=2;
		inventorySlot[] = { "Shoulder1" };
		model="\MuchFramework\proxies\shoulder1.p3d";
	};
	class Proxyshoulder2: ProxyAttachment
	{
		scope=2;
		inventorySlot[] = { "Shoulder2" };
		model="\MuchFramework\proxies\shoulder2.p3d";
	};
	class Proxyshoulder3: ProxyAttachment
	{
		scope=2;
		inventorySlot[] = { "Shoulder3" };
		model="\MuchFramework\proxies\shoulder3.p3d";
	};
	class Proxyshoulder4: ProxyAttachment
	{
		scope=2;
		inventorySlot[] = { "Shoulder4" };
		model="\MuchFramework\proxies\shoulder4.p3d";
	};
	class Proxyshoulder5: ProxyAttachment
	{
		scope=2;
		inventorySlot[] = { "Shoulder5" };
		model="\MuchFramework\proxies\shoulder5.p3d";
	};
	class Proxyshoulder6: ProxyAttachment
	{
		scope=2;
		inventorySlot[] = { "Shoulder6" };
		model="\MuchFramework\proxies\shoulder6.p3d";
	};
	class Proxyshoulder7: ProxyAttachment
	{
		scope=2;
		inventorySlot[] = { "Shoulder7" };
		model="\MuchFramework\proxies\shoulder7.p3d";
	};
	class Proxyshoulder8: ProxyAttachment
	{
		scope=2;
		inventorySlot[] = { "Shoulder8" };
		model="\MuchFramework\proxies\shoulder8.p3d";
	};
	class Proxyshoulder9: ProxyAttachment
	{
		scope=2;
		inventorySlot[] = { "Shoulder9" };
		model="\MuchFramework\proxies\shoulder9.p3d";
	};
	class Proxyshoulder10: ProxyAttachment
	{
		scope=2;
		inventorySlot[] = { "Shoulder10" };
		model="\MuchFramework\proxies\shoulder10.p3d";
	};
	class Proxyshoulder11: ProxyAttachment
	{
		scope=2;
		inventorySlot[] = { "Shoulder11" };
		model="\MuchFramework\proxies\shoulder11.p3d";
	};
	class Proxyshoulder12: ProxyAttachment
	{
		scope=2;
		inventorySlot[] = { "Shoulder12" };
		model="\MuchFramework\proxies\shoulder12.p3d";
	};
	class Proxyshoulder13: ProxyAttachment
	{
		scope=2;
		inventorySlot[] = { "Shoulder13" };
		model="\MuchFramework\proxies\shoulder13.p3d";
	};
	class Proxyshoulder14: ProxyAttachment
	{
		scope=2;
		inventorySlot[] = { "Shoulder14" };
		model="\MuchFramework\proxies\shoulder14.p3d";
	};
	class Proxyshoulder15: ProxyAttachment
	{
		scope=2;
		inventorySlot[] = { "Shoulder15" };
		model="\MuchFramework\proxies\shoulder15.p3d";
	};
	class Proxyshoulder16: ProxyAttachment
	{
		scope=2;
		inventorySlot[] = { "Shoulder16" };
		model="\MuchFramework\proxies\shoulder16.p3d";
	};
	class Proxyshoulder17: ProxyAttachment
	{
		scope=2;
		inventorySlot[] = { "Shoulder17" };
		model="\MuchFramework\proxies\shoulder17.p3d";
	};
	class Proxyshoulder18: ProxyAttachment
	{
		scope=2;
		inventorySlot[] = { "Shoulder18" };
		model="\MuchFramework\proxies\shoulder18.p3d";
	};
	class Proxyshoulder19: ProxyAttachment
	{
		scope=2;
		inventorySlot[] = { "Shoulder19" };
		model="\MuchFramework\proxies\shoulder19.p3d";
	};
	class Proxyshoulder20: ProxyAttachment
	{
		scope=2;
		inventorySlot[] = { "Shoulder20" };
		model="\MuchFramework\proxies\shoulder20.p3d";
	};
	class ProxySword1: ProxyAttachment
	{
		scope=2;
		inventorySlot[] = { "Sword1" };
		model="\MuchFramework\proxies\Sword1.p3d";
	};
	class ProxySword2: ProxyAttachment
	{
		scope=2;
		inventorySlot[] = { "Sword2" };
		model="\MuchFramework\proxies\Sword2.p3d";
	};
	class ProxySword3: ProxyAttachment
	{
		scope=2;
		inventorySlot[] = { "Sword3" };
		model="\MuchFramework\proxies\Sword3.p3d";
	};
	
	class Proxymspbook1: ProxyAttachment
	{
		scope=2;
		inventorySlot[] = { "Book1" };
		model="\MuchFramework\proxies\books\mspbook1.p3d";
	};
	class Proxymspbook2: ProxyAttachment
	{
		scope=2;
		inventorySlot[] = { "Book2" };
		model="\MuchFramework\proxies\books\mspbook2.p3d";
	};
	class Proxymspbook3: ProxyAttachment
	{
		scope=2;
		inventorySlot[] = { "Book3" };
		model="\MuchFramework\proxies\books\mspbook3.p3d";
	};
	class Proxymspbook4: ProxyAttachment
	{
		scope=2;
		inventorySlot[] = { "Book4" };
		model="\MuchFramework\proxies\books\mspbook4.p3d";
	};
	class Proxymspbook5: ProxyAttachment
	{
		scope=2;
		inventorySlot[] = { "Book5" };
		model="\MuchFramework\proxies\books\mspbook5.p3d";
	};
	class Proxymspbook6: ProxyAttachment
	{
		scope=2;
		inventorySlot[] = { "Book6" };
		model="\MuchFramework\proxies\books\mspbook6.p3d";
	};
	class Proxymspbook7: ProxyAttachment
	{
		scope=2;
		inventorySlot[] = { "Book7" };
		model="\MuchFramework\proxies\books\mspbook7.p3d";
	};
	class Proxymspbook8: ProxyAttachment
	{
		scope=2;
		inventorySlot[] = { "Book8" };
		model="\MuchFramework\proxies\books\mspbook8.p3d";
	};
	class Proxymspbook9: ProxyAttachment
	{
		scope=2;
		inventorySlot[] = { "Book9" };
		model="\MuchFramework\proxies\books\mspbook9.p3d";
	};
	class Proxymspbook10: ProxyAttachment
	{
		scope=2;
		inventorySlot[] = { "Book10" };
		model="\MuchFramework\proxies\books\mspbook10.p3d";
	};
	class Proxymspbook11: ProxyAttachment
	{
		scope=2;
		inventorySlot[] = { "Book11" };
		model="\MuchFramework\proxies\books\mspbook11.p3d";
	};
	class Proxymspbook12: ProxyAttachment
	{
		scope=2;
		inventorySlot[] = { "Book12" };
		model="\MuchFramework\proxies\books\mspbook12.p3d";
	};
	class Proxymspbook13: ProxyAttachment
	{
		scope=2;
		inventorySlot[] = { "Book13" };
		model="\MuchFramework\proxies\books\mspbook13.p3d";
	};
	class Proxymspbook14: ProxyAttachment
	{
		scope=2;
		inventorySlot[] = { "Book14" };
		model="\MuchFramework\proxies\books\mspbook14.p3d";
	};
	class Proxymspbook15: ProxyAttachment
	{
		scope=2;
		inventorySlot[] = { "Book15" };
		model="\MuchFramework\proxies\books\mspbook15.p3d";
	};
	class Proxymspbook16: ProxyAttachment
	{
		scope=2;
		inventorySlot[] = { "Book16" };
		model="\MuchFramework\proxies\books\mspbook16.p3d";
	};
	class Proxymspbook17: ProxyAttachment
	{
		scope=2;
		inventorySlot[] = { "Book17" };
		model="\MuchFramework\proxies\books\mspbook17.p3d";
	};
	class Proxymspbook18: ProxyAttachment
	{
		scope=2;
		inventorySlot[] = { "Book18" };
		model="\MuchFramework\proxies\books\mspbook18.p3d";
	};
	class Proxymspbook19: ProxyAttachment
	{
		scope=2;
		inventorySlot[] = { "Book19" };
		model="\MuchFramework\proxies\books\mspbook19.p3d";
	};
	class Proxymspbook20: ProxyAttachment
	{
		scope=2;
		inventorySlot[] = { "Book20" };
		model="\MuchFramework\proxies\books\mspbook20.p3d";
	};
	class Proxymspbook21: ProxyAttachment
	{
		scope=2;
		inventorySlot[] = { "Book21" };
		model="\MuchFramework\proxies\books\mspbook21.p3d";
	};
	class Proxymspbook22: ProxyAttachment
	{
		scope=2;
		inventorySlot[] = { "Book22" };
		model="\MuchFramework\proxies\books\mspbook22.p3d";
	};
	class Proxymspbook23: ProxyAttachment
	{
		scope=2;
		inventorySlot[] = { "Book23" };
		model="\MuchFramework\proxies\books\mspbook23.p3d";
	};
	class Proxymspbook24: ProxyAttachment
	{
		scope=2;
		inventorySlot[] = { "Book24" };
		model="\MuchFramework\proxies\books\mspbook24.p3d";
	};
	class Proxymspbook25: ProxyAttachment
	{
		scope=2;
		inventorySlot[] = { "Book25" };
		model="\MuchFramework\proxies\books\mspbook25.p3d";
	};
	class Proxymspbook26: ProxyAttachment
	{
		scope=2;
		inventorySlot[] = { "Book26" };
		model="\MuchFramework\proxies\books\mspbook26.p3d";
	};
	class Proxymspbook27: ProxyAttachment
	{
		scope=2;
		inventorySlot[] = { "Book27" };
		model="\MuchFramework\proxies\books\mspbook27.p3d";
	};
	class Proxymspbook28: ProxyAttachment
	{
		scope=2;
		inventorySlot[] = { "Book28" };
		model="\MuchFramework\proxies\books\mspbook28.p3d";
	};
	class Proxymspbook29: ProxyAttachment
	{
		scope=2;
		inventorySlot[] = { "Book29" };
		model="\MuchFramework\proxies\books\mspbook29.p3d";
	};
	class Proxymspbook30: ProxyAttachment
	{
		scope=2;
		inventorySlot[] = { "Book30" };
		model="\MuchFramework\proxies\books\mspbook30.p3d";
	};
	class Proxymspbook31: ProxyAttachment
	{
		scope=2;
		inventorySlot[] = { "Book31" };
		model="\MuchFramework\proxies\books\mspbook31.p3d";
	};
	class Proxymspbook32: ProxyAttachment
	{
		scope=2;
		inventorySlot[] = { "Book32" };
		model="\MuchFramework\proxies\books\mspbook32.p3d";
	};
	class Proxymspbook33: ProxyAttachment
	{
		scope=2;
		inventorySlot[] = { "Book33" };
		model="\MuchFramework\proxies\books\mspbook33.p3d";
	};
	class Proxymspbook34: ProxyAttachment
	{
		scope=2;
		inventorySlot[] = { "Book34" };
		model="\MuchFramework\proxies\books\mspbook34.p3d";
	};
	class Proxymspbook35: ProxyAttachment
	{
		scope=2;
		inventorySlot[] = { "Book35" };
		model="\MuchFramework\proxies\books\mspbook35.p3d";
	};
	class Proxymspbook36: ProxyAttachment
	{
		scope=2;
		inventorySlot[] = { "Book36" };
		model="\MuchFramework\proxies\books\mspbook36.p3d";
	};
	class Proxymspbook37: ProxyAttachment
	{
		scope=2;
		inventorySlot[] = { "Book37" };
		model="\MuchFramework\proxies\books\mspbook37.p3d";
	};
	class Proxymspbook38: ProxyAttachment
	{
		scope=2;
		inventorySlot[] = { "Book38" };
		model="\MuchFramework\proxies\books\mspbook38.p3d";
	};
	class Proxymspbook39: ProxyAttachment
	{
		scope=2;
		inventorySlot[] = { "Book39" };
		model="\MuchFramework\proxies\books\mspbook39.p3d";
	};
	class Proxymspbook40: ProxyAttachment
	{
		scope=2;
		inventorySlot[] = { "Book40" };
		model="\MuchFramework\proxies\books\mspbook40.p3d";
	};
	class Proxymspbook41: ProxyAttachment
	{
		scope=2;
		inventorySlot[] = { "Book41" };
		model="\MuchFramework\proxies\books\mspbook41.p3d";
	};
	class Proxymspbook42: ProxyAttachment
	{
		scope=2;
		inventorySlot[] = { "Book42" };
		model="\MuchFramework\proxies\books\mspbook42.p3d";
	};
	class Proxymspbook43: ProxyAttachment
	{
		scope=2;
		inventorySlot[] = { "Book43" };
		model="\MuchFramework\proxies\books\mspbook43.p3d";
	};
	class Proxymspbook44: ProxyAttachment
	{
		scope=2;
		inventorySlot[] = { "Book44" };
		model="\MuchFramework\proxies\books\mspbook44.p3d";
	};
	class Proxymspbook45: ProxyAttachment
	{
		scope=2;
		inventorySlot[] = { "Book45" };
		model="\MuchFramework\proxies\books\mspbook45.p3d";
	};
	class Proxymspbook46: ProxyAttachment
	{
		scope=2;
		inventorySlot[] = { "Book46" };
		model="\MuchFramework\proxies\books\mspbook46.p3d";
	};
	class Proxymspbook47: ProxyAttachment
	{
		scope=2;
		inventorySlot[] = { "Book47" };
		model="\MuchFramework\proxies\books\mspbook47.p3d";
	};
	class Proxymspbook48: ProxyAttachment
	{
		scope=2;
		inventorySlot[] = { "Book48" };
		model="\MuchFramework\proxies\books\mspbook48.p3d";
	};
	class Proxymspbook49: ProxyAttachment
	{
		scope=2;
		inventorySlot[] = { "Book49" };
		model="\MuchFramework\proxies\books\mspbook49.p3d";
	};
	class Proxymspbook50: ProxyAttachment
	{
		scope=2;
		inventorySlot[] = { "Book50" };
		model="\MuchFramework\proxies\books\mspbook50.p3d";
	};
};
