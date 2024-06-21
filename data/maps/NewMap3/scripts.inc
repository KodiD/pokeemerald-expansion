NewMap3_MapScripts::
	.byte 0

Map3_GymLeaderDark::
	trainerbattle_double TRAINER_DARKGYM, GymLeaderNomralIntro, GymLeaderNomralOutro, GymLeaderNomralMon
	end

GymLeaderNomralIntro:
.string "You'll never beat me!$"

GymLeaderNomralOutro:
.string "I can't believe it!$"

GymLeaderNomralMon:
.string "You have to have more pokemon!$"

Map3_HealingMage::
	setrespawn HEAL_LOCATION_MAP3
	call Common_EventScript_MageHeal
	end
