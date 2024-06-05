StartingCave_MapScripts::
	.byte 0


StartingCave_EventScript_Bag::
	lock
	faceplayer
	fadescreen FADE_TO_BLACK
	special ChooseStarter
	waitstate
	special HealPlayerParty
	release
	warp MAP_LITTLEROOT_TOWN_BRENDANS_HOUSE_2F, 6, 3
	end

