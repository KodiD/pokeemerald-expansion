.set LOCALID_BAG, 1
StartingCave_MapScripts::
	.byte 0


StartingCave_EventScript_Bag::
	lockall
	faceplayer
	fadescreen FADE_TO_BLACK
	special ChooseStarter
	removeobject LOCALID_BAG
	setflag FLAG_SYS_POKEMON_GET
	fadescreen FADE_TO_BLACK
	setflag FLAG_ADVENTURE_STARTED
	setflag FLAG_HIDE_ROUTE_101_BIRCH_STARTERS_BAG
	setflag FLAG_SYS_NATIONAL_DEX
	special EnableNationalPokedex
	setflag FLAG_RECEIVED_RUNNING_SHOES
	setflag FLAG_SYS_B_DASH
	waitstate
	special HealPlayerParty
	release
	warp MAP_NEW_MAP0, 25, 11
	end

