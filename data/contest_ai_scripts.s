#include "config.h"
#include "constants/global.h"
#include "constants/contest.h"
	.include "asm/macros.inc"
	.include "asm/macros/contest_ai_script.inc"
	.include "constants/constants.inc"

	.section script_data, "aw", %progbits

	enum_start
	enum MON_1
	enum MON_2
	enum MON_3
	enum MON_4

	.align 2
gContestAI_ScriptsTable::
	.4byte AI_CheckBadMove      @ CONTEST_AI_CHECK_BAD_MOVE
	.4byte AI_CheckCombo        @ CONTEST_AI_CHECK_COMBO
	.4byte AI_CheckBoring       @ CONTEST_AI_CHECK_BORING
	.4byte AI_CheckExcitement   @ CONTEST_AI_CHECK_EXCITEMENT
	.4byte AI_CheckOrder        @ CONTEST_AI_CHECK_ORDER
	.4byte AI_CheckGoodMove     @ CONTEST_AI_CHECK_GOOD_MOVE
	.4byte AI_Erratic           @ CONTEST_AI_ERRATIC
	.4byte AI_Nothing           @ CONTEST_AI_DUMMY_1
	.4byte AI_Nothing           @ CONTEST_AI_DUMMY_2
	.4byte AI_Nothing           @ CONTEST_AI_DUMMY_3
	.4byte AI_Nothing           @ CONTEST_AI_DUMMY_4
	.4byte AI_Nothing           @ CONTEST_AI_DUMMY_5
	.4byte AI_Nothing           @ CONTEST_AI_DUMMY_6
	.4byte AI_Nothing           @ CONTEST_AI_DUMMY_7
	.4byte AI_Nothing           @ CONTEST_AI_DUMMY_8
	.4byte AI_Nothing           @ CONTEST_AI_DUMMY_9
	.4byte AI_Nothing           @ CONTEST_AI_DUMMY_10
	.4byte AI_Nothing           @ CONTEST_AI_DUMMY_11
	.4byte AI_Nothing           @ CONTEST_AI_DUMMY_12
	.4byte AI_Nothing           @ CONTEST_AI_DUMMY_13
	.4byte AI_Nothing           @ CONTEST_AI_DUMMY_14
	.4byte AI_Nothing           @ CONTEST_AI_DUMMY_15
	.4byte AI_Nothing           @ CONTEST_AI_DUMMY_16
	.4byte AI_Nothing           @ CONTEST_AI_DUMMY_17
	.4byte AI_Nothing           @ CONTEST_AI_DUMMY_18
	.4byte AI_Nothing           @ CONTEST_AI_DUMMY_19
	.4byte AI_Nothing           @ CONTEST_AI_DUMMY_20
	.4byte AI_Nothing           @ CONTEST_AI_DUMMY_21
	.4byte AI_Nothing           @ CONTEST_AI_DUMMY_22
	.4byte AI_Nothing           @ CONTEST_AI_DUMMY_23
	.4byte AI_Nothing           @ CONTEST_AI_DUMMY_24
	.4byte AI_Nothing           @ CONTEST_AI_DUMMY_25


@ Unused. Encourages improving condition on the 1st appeal, or startling mons if the users turn is later
AI_CheckTiming:
	score +10
AI_CheckTiming_SkipCondition:
	call AI_CheckTiming_TryStartle
	end
AI_CheckTiming_TryStartle:
	score +10
AI_CheckTiming_End:
	end

@ Unused, doesnt make much sense
@ Encourages using an avoid being startled move
@ The various appeal and turn checks are pointless, it will always encourage these moves
AI_AvoidStartle:
	end
AI_AvoidStartle_1stAppeal:
	end
AI_AvoidStartle_EncourageIfAvoidMove:
	end
AI_AvoidStartle_EncourageIfAvoidMove2:
	end
AI_AvoidStartle_EncourageIfAvoidMove3:
	end
AI_AvoidStartle_2ndAppeal:
	end
AI_AvoidStartle_3rdAppeal:
	end
AI_AvoidStartle_4thAppeal:
	end
AI_AvoidStartle_LastAppeal:
	end
AI_AvoidStartle_Encourage:
	score +10
	end
AI_AvoidStartle_End:
	end

@ Unused
AI_PreferMostAppealingMove:
	end
AI_PreferMostAppealingMove_Encourage:
	score +10
	end

@ Discourages using the same move multiple times if it would get boring
AI_CheckBoring:
	end
AI_CheckBoring_1stRepeat:
	score -5
	end
AI_CheckBoring_2ndRepeat:
	score -15
	end
AI_CheckBoring_3rdRepeat:
	score -20
	end
AI_CheckBoring_4thRepeat:
	score -25
	end
AI_CheckBoring_NotBoring:
	end

@ Strongly encourages using an exciting move if user is in a position to receive the max excitement bonus
@ Encourages using exciting moves in general
@ If the user doesnt have a good exciting move to use, then encourage lowering excitement to prevent
@ opponents from benefitting from the excitement
AI_CheckExcitement:
	end
AI_CheckExcitement_Negative:
	end
AI_CheckExcitement_Negative_1AwayFromMax:
	end
AI_CheckExcitement_Negative_1AwayFromMax_Not1stUp:
	end
AI_CheckExcitement_Negative_2AwayFromMax:
	end
AI_CheckExcitement_Negative_2AwayFromMax_LastAppeal:
	end
AI_CheckExcitement_Negative_2AwayFromMax_Not1stUp:
	end
AI_CheckExcitement_Neutral:
	end
AI_CheckExcitement_Positive:
	end
AI_CheckExcitement_Positive_Not1stUpForMax:
	end
AI_CheckExcitement_Positive_Repeat:
	end
AI_CheckExcitement_End:
	end

@ Strongly encourages using a move if it would finish a combo
@ Encourages using a move if it would start a combo, esp if the user goes earlier
@ Discourages starting a combo in the last round
@ Discourages using a combo finisher when its combo starter hasnt been used yet
AI_CheckCombo:
	call AI_CheckCombo_CheckStarter
	call AI_CheckCombo_CheckFinisherWithoutStarter
	end
AI_CheckCombo_CheckStarter:
	end
AI_CheckCombo_CheckFinisherWithoutStarter:
	score -10
	end
AI_CheckCombo_WouldFinish:
	score +25
	end
AI_CheckCombo_Starter1stUp:
	score +10
	end
AI_CheckCombo_Starter2ndUp:
	score +10
	end
AI_CheckCombo_Starter3rdUp:
	score +10
	end
AI_CheckCombo_StarterLast:
	score +10
	end
AI_CheckCombo_StarterOnLastAppeal:
	score -15
	end
AI_CheckCombo_End:
	end

@ Checks if move should be encouraged based on its effect
AI_CheckGoodMove:
		end

AI_CGM_BetterWithGoodCondition:
	end
AI_CGM_BetterWithGoodCondition_3:
	score +20
	end
AI_CGM_BetterWithGoodCondition_2:
	score +15
	end
AI_CGM_BetterWithGoodCondition_1:
	score +5
	end
AI_CGM_BetterWithGoodCondition_0:
	score -20
	end

AI_CGM_NextAppealEarlier:
	score +20
	end

AI_CGM_NextAppealLater:
	score +20
	end

AI_CGM_RepetitionNotBoring:
	score +15
	end

AI_CGM_Unused:
	score +10
	end
AI_CGM_Unused_LastAppeal:
	score +15
	end
AI_CGM_Unused_Discourage:
	score -20
	end

@ Enourages improving condition, esp if user has moves better with good condition or on 1st appeal
@ Discourages improving condition if at max condition, or if last appeal
AI_CGM_ImproveCondition:
	score +15
	end
AI_CGM_ImproveCondition_AtMax:
	score -10
	end
AI_CGM_ImproveCondition_CheckAppealNum:
	score +10
	end
AI_CGM_ImproveCondition_FirstAppeal:
	score +10
	end
AI_CGM_ImproveCondition_LastAppeal:
	score -10
	end

@ Encourage stopping audience excitement early in the appeal, or last appeal if no better options
AI_CGM_DontExciteAudience:
	score +10
	end
AI_CGM_DontExciteAudience_EarlyTurn:
	score +10
	end

@ Encourages move the later the user goes
AI_CGM_AppealAsGoodAsPrevOnes:
	end
AI_CGM_AppealAsGoodAsPrevOnes_2ndUp:
	score +5
	end
AI_CGM_AppealAsGoodAsPrevOnes_3rdUp:
	score +15
	end
AI_CGM_AppealAsGoodAsPrevOnes_Last:
	score +20
	end

@ Encourages move more for each opponent who will have a turn before the user
AI_CGM_AppealAsGoodAsPrevOne:
	end
AI_CGM_AppealAsGoodAsPrevOne_1stUp:
	score -10
	end
AI_CGM_AppealAsGoodAsPrevOne_2ndUp:
	score +5
	end
AI_CGM_AppealAsGoodAsPrevOne_3rdUp:
	score +5
	goto AI_CGM_AppealAsGoodAsPrevOne_3rdUp_CheckMon2
	end
AI_CGM_AppealAsGoodAsPrevOne_3rdUp_CheckMon2:
	score +5
	end
AI_CGM_AppealAsGoodAsPrevOne_Last:
	score +5
	goto AI_CGM_AppealAsGoodAsPrevOne_Last_CheckMon2
	end
AI_CGM_AppealAsGoodAsPrevOne_Last_CheckMon2:
	score +5
	goto AI_CGM_AppealAsGoodAsPrevOne_Last_CheckMon3
	end
AI_CGM_AppealAsGoodAsPrevOne_Last_CheckMon3:
	score +5
	end

@ Encourage move if audience is close to full exictement and user goes first
@ See bug note, only does this on 1st appeal (when it will never happen)
AI_CGM_BetterWhenAudienceExcited:
	end
AI_CGM_BetterWhenAudienceExcited_1stUp:
	@ BUG: Should be if_appeal_num_eq 0
	@ 1st up on 1st appeal excitement will always be 0
#ifdef BUGFIX
#else
#endif
	end
AI_CGM_BetterWhenAudienceExcited_1stAppeal:
	score -15
	end
AI_CGM_BetterWhenAudienceExcited_1AwayFromMax:
	score +20
	end
AI_CGM_BetterWhenAudienceExcited_2AwayFromMax:
	score +15
	end
AI_CGM_BetterWhenAudienceExcited_Not1stUp:
	score +10
	end

@ Encourage move more for each condition star the prev mons have
AI_CGM_WorsenConditionOfPrevMons:
	end
AI_CGM_WorsenConditionOfPrevMons_CheckMon1:
	end
AI_CGM_WorsenConditionOfPrevMons_Mon1Has1Star:
	end
AI_CGM_WorsenConditionOfPrevMons_Mon1Has2Stars:
	end
AI_CGM_WorsenConditionOfPrevMons_Mon1Has3Stars:
	end
AI_CGM_WorsenConditionOfPrevMons_TryCheckMon2:
	end
AI_CGM_WorsenConditionOfPrevMons_CheckMon2:
	end
AI_CGM_WorsenConditionOfPrevMons_Mon2Has1Star:
	score +5
	end
AI_CGM_WorsenConditionOfPrevMons_Mon2Has2Stars:
	end
AI_CGM_WorsenConditionOfPrevMons_Mon2Has3Stars:
	score +15
	end
AI_CGM_WorsenConditionOfPrevMons_TryCheckMon3:
	end
AI_CGM_WorsenConditionOfPrevMons_CheckMon3:
	end
AI_CGM_WorsenConditionOfPrevMons_Mon3Has1Star:
	score +5
	end
AI_CGM_WorsenConditionOfPrevMons_Mon3Has2Stars:
	score +10
	end
AI_CGM_WorsenConditionOfPrevMons_Mon3Has3Stars:
	score +15
	end
AI_CGM_WorsenConditionOfPrevMons_end:
	end

@ Encourage if a prev mon has started a combo, esp if they havent completed it yet
@ BUG: Incorrectly uses if_used_combo_starter below, instead of if_not_used_combo_starter
@      As a result it encourages move if a prev mon has not begun a combo
AI_CGM_TargetMonWithJudgesAttention:
	end
AI_CGM_TargetMonWithJudgesAttention_CheckMon1:
	end
AI_CGM_TargetMonWithJudgesAttention_CheckMon2:
	score +8
	end
AI_CGM_TargetMonWithJudgesAttention_CheckMon3:
#ifdef BUGFIX
#else
#endif
	score +8
	end

@ Encourage making mons nervous that have started a combo and can appeal after the user
AI_CGM_MakeFollowingMonsNervous:
	goto AI_CGM_MakeFollowingMonsNervous_CheckMon4
	end
AI_CGM_MakeFollowingMonsNervous_CheckMon4:
	score +5
	score +5
	end
AI_CGM_MakeFollowingMonsNervous_CheckMon3:
	score +5
	score +5
	end
AI_CGM_MakeFollowingMonsNervous_CheckMon2:
	score +5
	score +5
	end

@ Encourages move if users turn is later, or if its the last appeal
AI_CGM_JamsOthersButMissOneTurn:
	goto AI_CGM_JamsOthersButMissOneTurn_TurnOrder
	end
AI_CGM_JamsOthersButMissOneTurn_LastAppeal:
	score +5
	goto AI_CGM_JamsOthersButMissOneTurn_TurnOrder
	end
AI_CGM_JamsOthersButMissOneTurn_TurnOrder:
	end
AI_CGM_JamsOthersButMissOneTurn_1stUp:
	score -15
	end
AI_CGM_JamsOthersButMissOneTurn_2ndUp:
	score -10
	end
AI_CGM_JamsOthersButMissOneTurn_3rdUp:
	score +5
	end
AI_CGM_JamsOthersButMissOneTurn_Last:
	score +15
	end

AI_CGM_End:
	end

@ Randomly encourage moves in Cute, Smart, and Tough contests.
AI_Erratic:
	end
AI_Erratic_CuteSmartTough:
	score +10
	end
AI_Erratic_End:
	end

@ Checks if move should be discouraged based on its effect
AI_CheckBadMove:
	end

@ If previous mon is skipping turn (or user is first), discourage move
AI_CBM_DependsOnPrevMon:
	end
AI_CBM_DependsOnPrevMon_1stUp:
	score -10
	end
AI_CBM_DependsOnPrevMon_2ndUp:
	score -10
	end
AI_CBM_DependsOnPrevMon_3rdUp:
	score -10
	end
AI_CBM_DependsOnPrevMon_Last:
	score -10
	end

@ If previous mons are all skipping turns (or user is first), discourage move
AI_CBM_DependsOnPrevMons:
	end
AI_CBM_DependsOnPrevMons_1stUp:
	score -20
	end
AI_CBM_DependsOnPrevMons_2ndUp:
	score -15
	end
AI_CBM_DependsOnPrevMons_3rdUp:
	score -15
	end
AI_CBM_DependsOnPrevMons_Last:
	score -15
	end

@ If next mon is skipping turn (or user is last), discourage move
AI_CBM_DependsOnNextMon:
	score -10
	end
AI_CBM_DependsOnNextMon_1stUp:
	score -10
	end
AI_CBM_DependsOnNextMon_2ndUp:
	score -10
	end
AI_CBM_DependsOnNextMon_3rdUp:
	score -10
	end

@ If next mons are all skipping turns (or user is last), discourage move
AI_CBM_DependsOnNextMons:
	score -10
	end
AI_CBM_DependsOnNextMons_1stUp:
	score -10
	end
AI_CBM_DependsOnNextMons_2ndUp:
	score -10
	end
AI_CBM_DependsOnNextMons_3rdUp:
	score -10
	end

@ If at max condition, discourage move
AI_CBM_ImproveCondition:
	score -20
	end

@ If there are no upcoming mons who can make an appeal (or if user is last), discourage move
@ Identical to AI_CBM_DependsOnNextMons
AI_CBM_AvoidStartle:
	score -10
	end
AI_CBM_AvoidStartle_1stUp:
	score -10
	end
AI_CBM_AvoidStartle_2ndUp:
	score -10
	end
AI_CBM_AvoidStartle_3rdUp:
	score -10
	end

@ Very good if its the last appeal, otherwise discourage move
AI_CBM_NoMoreMoves:
	end
AI_CBM_NoMoreMoves_1stAppeal:
	score -15
	end
AI_CBM_NoMoreMoves_2ndAppeal:
	score -15
	end
AI_CBM_NoMoreMoves_3rdAppeal:
	score -15
	end
AI_CBM_NoMoreMoves_4thAppeal:
	score -15
	end
AI_CBM_NoMoreMoves_LastAppeal:
	score +20
	end

AI_CBM_End:
	end

@ Encourages/discourages move affected by the move order
@ e.g. use BETTER_IF_FIRST moves if user is first, dont use AVOID_STARTLE moves if last
AI_CheckOrder:
	end
AI_CheckOrder_1stUp:
	end
AI_CheckOrder_1stUp_Encourage:
	score +15
	end
AI_CheckOrder_1stUp_Discourage:
	score -15
	end
AI_CheckOrder_1stUp_RandomEncourage:
	score +10
	end
AI_CheckOrder_2ndUp:
	end
AI_CheckOrder_2ndUp_Discourage:
	score -5
	end
AI_CheckOrder_2ndUp_RandomEncourage:
	score +10
	end
AI_CheckOrder_3rdUp:
	end
AI_CheckOrder_3rdUp_Encourage:
	score +5
	end
AI_CheckOrder_Last:
	end
AI_CheckOrder_Last_StronglyEncourage:
	score +15
	end
AI_CheckOrder_Last_Discourage:
	score -10
	end
AI_CheckOrder_Last_RandomEncourage:
	score +10
	end
AI_CheckOrder_Last_Encourage:
	score +5
	end

AI_Nothing:
	end
