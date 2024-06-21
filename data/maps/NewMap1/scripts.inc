NewMap1_MapScripts::
	.byte 0

Map1_HealingMage::
	setrespawn HEAL_LOCATION_MAP1
	call Common_EventScript_MageHeal
	end