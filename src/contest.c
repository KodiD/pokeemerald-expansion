#include "global.h"
#include "gpu_regs.h"
#include "bg.h"
#include "malloc.h"
#include "battle.h"
#include "battle_anim.h"
#include "contest.h"
#include "contest_link.h"
#include "data.h"
#include "decompress.h"
#include "graphics.h"
#include "link.h"
#include "m4a.h"
#include "main.h"
#include "menu.h"
#include "overworld.h"
#include "palette.h"
#include "random.h"
#include "new_game.h"
#include "script.h"
#include "sound.h"
#include "sprite.h"
#include "string_util.h"
#include "task.h"
#include "text.h"
#include "tv.h"
#include "scanline_effect.h"
#include "util.h"
#include "contest_util.h"
#include "dma3.h"
#include "battle_message.h"
#include "event_scripts.h"
#include "event_data.h"
#include "strings.h"
#include "contest_effect.h"
#include "contest_link.h"
#include "international_string_util.h"
#include "data.h"
#include "contest_ai.h"
#include "constants/event_objects.h"
#include "constants/items.h"
#include "constants/moves.h"
#include "constants/rgb.h"
#include "constants/songs.h"

// This file's functions.
static void LoadContestPalettes(void);
static void Task_StartContestWaitFade(u8 taskId);
static void Task_TryStartLinkContest(u8 taskId);
static void Task_CommunicateMonIdxs(u8 taskId);
static void Task_EndCommunicateMonIdxs(u8 taskId);
static void Task_ReadyStartLinkContest(u8 taskId);
static bool8 SetupContestGraphics(u8 *stateVar);
static void Task_WaitToRaiseCurtainAtStart(u8 taskId);
static void Task_RaiseCurtainAtStart(u8 taskId);
static void VBlankCB_Contest(void);
static void CB2_ContestMain(void);
static void Task_DisplayAppealNumberText(u8 taskId);
static void Task_TryShowMoveSelectScreen(u8 taskId);
static void Task_ShowMoveSelectScreen(u8 taskId);
static void Task_HandleMoveSelectInput(u8 taskId);
static void DrawMoveSelectArrow(s8);
static void EraseMoveSelectArrow(s8);
static void Task_SelectedMove(u8 taskId);
static void Task_EndCommunicateMoveSelections(u8 taskId);
static void Task_HideMoveSelectScreen(u8 taskId);
static void Task_HideApplauseMeterForAppealStart(u8 taskId);
static void Task_WaitHideApplauseMeterForAppealStart(u8 taskId);
static void Task_AppealSetup(u8 taskId);
static void Task_DoAppeals(u8 taskId);
static void Task_EndWaitForLink(u8);
static void SpriteCB_MonSlideIn(struct Sprite *);
static void SpriteCB_MonSlideOut(struct Sprite *);
static void Task_FinishRoundOfAppeals(u8);
static void Task_ReadyUpdateHeartSliders(u8);
static void Task_UpdateHeartSliders(u8);
static void Task_WaitForHeartSliders(u8);
static void Task_RestorePlttBufferUnfaded(u8);
static void Task_WaitPrintRoundResult(u8);
static void Task_PrintRoundResultText(u8);
static void Task_ReUpdateHeartSliders(u8);
static void Task_WaitForHeartSlidersAgain(u8);
static void Task_DropCurtainAtRoundEnd(u8);
static void Task_TryStartNextRoundOfAppeals(u8);
static void Task_StartNewRoundOfAppeals(u8);
static void Task_EndAppeals(u8);
static void Task_WaitForOutOfTimeMsg(u8);
static void Task_DropCurtainAtAppealsEnd(u8);
static void Task_TryCommunicateFinalStandings(u8);
static void Task_CommunicateFinalStandings(u8);
static void Task_EndCommunicateFinalStandings(u8);
static void Task_ContestReturnToField(u8);
static void FieldCB_ContestReturnToField(void);
static bool8 IsPlayerLinkLeader(void);
static void PrintContestantTrainerName(u8);
static void PrintContestantTrainerNameWithColor(u8, u8);
static void PrintContestantMonName(u8);
static void PrintContestantMonNameWithColor(u8, u8);
static u8 CreateJudgeSprite(void);
static u8 CreateJudgeSpeechBubbleSprite(void);
static u8 CreateContestantSprite(u16, bool8, u32, u32);
static void PrintContestMoveDescription(u16);
static u16 SanitizeSpecies(u16);
static void ContestClearGeneralTextWindow(void);
static u16 GetChosenMove(u8);
static void GetAllChosenMoves(void);
static void ContestPrintLinkStandby(void);
static void FillContestantWindowBgs(void);
static void CreateSliderHeartSprites(void);
static void SetBottomSliderHeartsInvisibility(bool8);
static void CreateNextTurnSprites(void);
static void CreateApplauseMeterSprite(void);
static void CreateJudgeAttentionEyeTask(void);
static void CreateUnusedBlendTask(void);
static void ContestDebugDoPrint(void);
static void DrawContestantWindows(void);
static void ApplyNextTurnOrder(void);
static void SlideApplauseMeterIn(void);
static void SlideApplauseMeterOut(void);
static void SetBgForCurtainDrop(void);
static void UpdateContestantBoxOrder(void);
static void Task_StartDropCurtainAtRoundEnd(u8);
static void AnimateSliderHearts(u8);
static void CreateInvisibleBattleTargetSprite(void);
static void Contest_StartTextPrinter(const u8 *, u32);
static void ContestBG_FillBoxWithIncrementingTile(u8, u16, u8, u8, u8, u8, u8, s16);
static bool32 Contest_RunTextPrinters(void);
static void Contest_SetBgCopyFlags(u32 flagIndex);
static void CalculateFinalScores(void);
static void CalculateAppealMoveImpact(u8);
static void SetMoveAnimAttackerData(u8);
static void BlinkContestantBox(u8, u8);
static u8 CreateContestantBoxBlinkSprites(u8);
static u16 SanitizeMove(u16);
static void SetMoveSpecificAnimData(u8);
static void SetMoveTargetPosition(u16);
static void ClearMoveAnimData(u8);
static void StopFlashJudgeAttentionEye(u8);
static void DrawUnnervedSymbols(void);
static void PrintAppealMoveResultText(u8, u8);
static void DoJudgeSpeechBubble(u8);
static void ShowHideNextTurnGfx(bool8);
static u8 UpdateAppealHearts(s16, s16, u8);
static bool8 UpdateConditionStars(u8, u8);
static bool8 DrawStatusSymbol(u8);
static void DrawStatusSymbols(void);
static void StartStopFlashJudgeAttentionEye(u8);
static void BlendAudienceBackground(s8, s8);
static void ShowAndUpdateApplauseMeter(s8 unused);
static void AnimateAudience(void);
static void UpdateApplauseMeter(void);
static void RankContestants(void);
static void SetAttentionLevels(void);
static void UpdateHeartSliders(void);
static bool8 SlidersDoneUpdating(void);
static void ContestBG_FillBoxWithTile(u8, u16, u8, u8, u8, u8, u8);
static void Contest_PrintTextToBg0WindowStd(u32, const u8 *);
static s16 GetContestantRound2Points(u8);
static void DetermineFinalStandings(void);
static bool8 DidContestantPlaceHigher(s32, s32);
static void Task_UpdateAppealHearts(u8);
static void SpriteCB_UpdateHeartSlider(struct Sprite *);
static void Task_FlashJudgeAttentionEye(u8);
static void Task_StopFlashJudgeAttentionEye(u8);
static void Task_UnusedBlend(u8);
static void InitUnusedBlendTaskData(u8);
static void UpdateBlendTaskContestantData(u8);
static void SpriteCB_BlinkContestantBox(struct Sprite *);
static void SpriteCB_EndBlinkContestantBox(struct Sprite *sprite);
static u8 StartApplauseOverflowAnimation(void);
static void Task_ApplauseOverflowAnimation(u8);
static void Task_SlideApplauseMeterIn(u8);
static void Task_SlideApplauseMeterOut(u8);
static void Task_ShowAndUpdateApplauseMeter(u8);
static void Task_AnimateAudience(u8);
static void Task_BlendAudienceBackground(u8);
static void GetTurnOrderNumberGfx(u8);
static void Task_UpdateCurtainDropAtRoundEnd(u8);
static void Task_ResetForNextRound(u8);
static void Task_WaitRaiseCurtainAtRoundEnd(u8);
static void Task_StartRaiseCurtainAtRoundEnd(u8);
static void Task_WaitForSliderHeartAnim(u8);
static void SetBattleTargetSpritePosition(void);
static void CalculateContestLiveUpdateData(void);
static void SetConestLiveUpdateTVData(void);
static void SetContestLiveUpdateFlags(u8);
static void ContestDebugPrintBitStrings(void);
static void StripPlayerNameForLinkContest(u8 *);
static void StripMonNameForLinkContest(u8 *, s32);
static void SwapMoveDescAndContestTilemaps(void);

// An index into a palette where the text color for each contestant is stored.
// Contestant 0 will use palette color 10, contestant 1 will use color 11, etc.

EWRAM_DATA u16 gSpecialVar_ContestCategory = 0;
EWRAM_DATA u16 gSpecialVar_ContestRank = 0;


static void TaskDummy1(u8 taskId)
{
}

void ResetLinkContestBoolean(void)
{
}

static void SetupContestGpuRegs(void)
{
   
}

void LoadContestBgAfterMoveAnim(void)
{
}

static void InitContestInfoBgs(void)
{
}

static void InitContestWindows(void)
{
}

static void LoadContestPalettes(void)
{
}

static void InitContestResources(void)
{
}

static void AllocContestResources(void)
{
}

static void FreeContestResources(void)
{
}

void CB2_StartContest(void)
{
}

static void Task_StartContestWaitFade(u8 taskId)
{

}

// If this is a link contest try to start appeals communication
// Otherwise skip ahead
static void Task_TryStartLinkContest(u8 taskId)
{
}

static void Task_CommunicateMonIdxs(u8 taskId)
{
}

static void Task_EndCommunicateMonIdxs(u8 taskId)
{
}

static void Task_ReadyStartLinkContest(u8 taskId)
{
}

static bool8 SetupContestGraphics(u8 *stateVar)
{
    return FALSE;
}

static void Task_WaitToRaiseCurtainAtStart(u8 taskId)
{
}

static void Task_RaiseCurtainAtStart(u8 taskId)
{
}

static void CB2_ContestMain(void)
{
}

static void VBlankCB_Contest(void)
{
}

static void Task_DisplayAppealNumberText(u8 taskId)
{
}

static void Task_TryShowMoveSelectScreen(u8 taskId)
{
}

static void Task_ShowMoveSelectScreen(u8 taskId)
{
}

static void Task_HandleMoveSelectInput(u8 taskId)
{
}

static void DrawMoveSelectArrow(s8 moveIndex)
{
}

static void EraseMoveSelectArrow(s8 moveIndex)
{
}

static void Task_SelectedMove(u8 taskId)
{
}

static void Task_EndCommunicateMoveSelections(u8 taskId)
{
}

static void Task_HideMoveSelectScreen(u8 taskId)
{
}

static void Task_HideApplauseMeterForAppealStart(u8 taskId)
{
}

static void Task_WaitHideApplauseMeterForAppealStart(u8 taskId)
{
}


static void Task_AppealSetup(u8 taskId)
{
}

static void Task_DoAppeals(u8 taskId)
{
}

static void Task_EndWaitForLink(u8 taskId)
{
}

static void SpriteCB_MonSlideIn(struct Sprite *sprite)
{
}

static void SpriteCB_MonSlideOut(struct Sprite *sprite)
{
}

static void Task_FinishRoundOfAppeals(u8 taskId)
{
}

static void Task_ReadyUpdateHeartSliders(u8 taskId)
{
}

static void Task_UpdateHeartSliders(u8 taskId)
{
}

static void Task_WaitForHeartSliders(u8 taskId)
{
}

static void Task_RestorePlttBufferUnfaded(u8 taskId)
{
}

static void Task_WaitPrintRoundResult(u8 taskId)
{
}

static void Task_PrintRoundResultText(u8 taskId)
{
}

static void Task_ReUpdateHeartSliders(u8 taskId)
{
}

static void Task_WaitForHeartSlidersAgain(u8 taskId)
{
}

static void Task_DropCurtainAtRoundEnd(u8 taskId)
{
}

static void Task_UpdateContestantBoxOrder(u8 taskId)
{
}

static void Task_TryStartNextRoundOfAppeals(u8 taskId)
{
}

static void Task_StartNewRoundOfAppeals(u8 taskId)
{
}

static void Task_EndAppeals(u8 taskId)
{
}

static void Task_WaitForOutOfTimeMsg(u8 taskId)
{
}

static void Task_DropCurtainAtAppealsEnd(u8 taskId)
{
}

static void Task_TryCommunicateFinalStandings(u8 taskId)
{
}

static void Task_CommunicateFinalStandings(u8 taskId)
{
}

static void Task_EndCommunicateFinalStandings(u8 taskId)
{
}

static void Task_ContestReturnToField(u8 taskId)
{
}

static void FieldCB_ContestReturnToField(void)
{
}

static void TryPutPlayerLast(void)
{
}

static bool8 IsPlayerLinkLeader(void)
{
    return TRUE;
}

void CreateContestMonFromParty(u8 partyIndex)
{
}

void SetContestants(u8 contestType, u8 rank)
{
}

void SetLinkAIContestants(u8 contestType, u8 rank, bool32 isPostgame)
{
}

u8 GetContestEntryEligibility(struct Pokemon *pkmn)
{
    return 0;
}

static void DrawContestantWindowText(void)
{
}

static u8 *Contest_CopyStringWithColor(const u8 *string, u8 color)
{
    return 0;
}

static void PrintContestantTrainerName(u8 contestant)
{
}

static void PrintContestantTrainerNameWithColor(u8 contestant, u8 color)
{
}

static void PrintContestantMonName(u8 contestant)
{
}

static void PrintContestantMonNameWithColor(u8 contestant, u8 color)
{
}

static u16 CalculateContestantRound1Points(u8 who, u8 contestCategory)
{
    return 0;
}

void CalculateRound1Points(u8 contestCategory)
{
}

static u8 CreateJudgeSprite(void)
{
    return 0;
}

static u8 CreateJudgeSpeechBubbleSprite(void)
{
    return 0;
}

static u8 CreateContestantSprite(u16 species, bool8 isShiny, u32 personality, u32 index)
{
    return 0;
}

bool8 IsSpeciesNotUnown(u16 species)
{
    return TRUE;
}

// The contestant info windows and general-purpose text box are drawn on one half, while
// the moves and move description windows are drawn on another screen. Only the first 32 * 20
// tiles are actually drawn on screen.
static void SwapMoveDescAndContestTilemaps(void)
{
}

// Functionally unused
static u16 GetMoveEffectSymbolTileOffset(u16 move, u8 contestant)
{
    return 0;
}

static void PrintContestMoveDescription(u16 move)
{
}

static void DrawMoveEffectSymbol(u16 move, u8 contestant)
{
}

static void UNUSED DrawMoveEffectSymbols(void)
{
}

static u16 GetStarTileOffset(void)
{
    return 0x2034;
}

static bool8 UpdateConditionStars(u8 contestantIdx, bool8 resetMod)
{
    return TRUE;
}

static void DrawConditionStars(void)
{
}

static u16 GetStatusSymbolTileOffset(u8 status)
{
    return 0;
}

static bool8 DrawStatusSymbol(u8 contestant)
{
    return 0;
}

static void DrawStatusSymbols(void)
{
}

static void ContestClearGeneralTextWindow(void)
{
}

static u16 GetChosenMove(u8 contestant)
{
    return 0;
}

static void GetAllChosenMoves(void)
{
}

static void RankContestants(void)
{
}

static void SetAttentionLevels(void)
{
}

static bool8 ContestantCanUseTurn(u8 contestant)
{
        return TRUE;
}

static void SetContestantStatusesForNextRound(void)
{
    
}

bool8 Contest_IsMonsTurnDisabled(u8 contestant)
{
        return FALSE;
}

static void CalculateTotalPointsForContestant(u8 contestant)
{
}

static void CalculateFinalScores(void)
{
}

static s16 GetContestantRound2Points(u8 contestant)
{
    return 0;
}

static void DetermineFinalStandings(void)
{
}

void SaveLinkContestResults(void)
{
}

static bool8 DidContestantPlaceHigher(s32 a, s32 b)
{
    return TRUE;
}

static void ContestPrintLinkStandby(void)
{
}

static void FillContestantWindowBgs(void)
{
}

static u16 GetAppealHeartTileOffset(u8 contestant)
{
    return 0;
}

static s8 GetNumHeartsFromAppealPoints(s16 appeal)
{
    return 0;
}

static u8 UpdateAppealHearts(s16 startAppeal, s16 appealDelta, u8 contestant)
{
    return 0;
}

static void Task_UpdateAppealHearts(u8 taskId)
{
}

static void CreateSliderHeartSprites(void)
{
}


static void UpdateHeartSlider(u8 contestant)
{
}

static void UpdateHeartSliders(void)
{
}

static bool8 SlidersDoneUpdating(void)
{
    return FALSE;
}

static void SpriteCB_UpdateHeartSlider(struct Sprite *sprite)
{
}


// Y positions change as the contestants change order
static void UpdateSliderHeartSpriteYPositions(void)
{
}

// Used to hide (or subsequently reshow) the bottom two slider hearts that get hidden by text windows by moving them offscreen
static void SetBottomSliderHeartsInvisibility(bool8 invisible)
{
}

static void CreateNextTurnSprites(void)
{
}

static void CreateApplauseMeterSprite(void)
{
}

static void CreateJudgeAttentionEyeTask(void)
{
}

static void StartFlashJudgeAttentionEye(u8 contestant)
{
}

static void StopFlashJudgeAttentionEye(u8 contestant)
{
}

static void Task_StopFlashJudgeAttentionEye(u8 taskId)
{
}

static void Task_FlashJudgeAttentionEye(u8 taskId)
{
}

// Note: While the below task is run for the entire Appeals portion of the contest,
//       because data[i * 4] is always 0xFF it never does anything
//       If turned on by setting that data between 0 and 16, it blends
//       an odd selection of palette colors (e.g. the text box, the appeal hearts
//       for only one contestant, the heart outlines in the move selection box, etc)
//       Given the similarities, it's possible this was an incorrect attempt
//       at something similar to what CreateJudgeAttentionEyeTask does
static void CreateUnusedBlendTask(void)
{
}

static void InitUnusedBlendTaskData(u8 contestant)
{
}

static void UpdateBlendTaskContestantsData(void)
{
}

static void UpdateBlendTaskContestantData(u8 contestant)
{
}

// See comments on CreateUnusedBlendTask
static void Task_UnusedBlend(u8 taskId)
{
}

static void StartStopFlashJudgeAttentionEye(u8 contestant)
{
}

static u8 CreateContestantBoxBlinkSprites(u8 contestant)
{
    return 0;
}

static void DestroyContestantBoxBlinkSprites(u8 spriteId)
{
}

static void SetBlendForContestantBoxBlink(void)
{
}

static void ResetBlendForContestantBoxBlink(void)
{
}

// To indicate whose turn is up
static void BlinkContestantBox(u8 spriteId, bool8 b)
{
}

static void SpriteCB_BlinkContestantBox(struct Sprite *sprite)
{
}

static void SpriteCB_EndBlinkContestantBox(struct Sprite *sprite)
{
}

static void UNUSED ContestDebugTogglePointTotal(void)
{
}

static void ContestDebugDoPrint(void)
{
}

void SortContestants(bool8 useRanking)
{
}

static void DrawContestantWindows(void)
{
}

static void CalculateAppealMoveImpact(u8 contestant)
{
}

void SetContestantEffectStringID(u8 contestant, u8 effectStringId)
{
}

void SetContestantEffectStringID2(u8 contestant, u8 effectStringId)
{
}

void SetStartledString(u8 contestant, u8 jam)
{
}

static void PrintAppealMoveResultText(u8 contestant, u8 stringId)
{
}

void MakeContestantNervous(u8 p)
{
}

// This function calculates the new turn order for the next round. The
// algorithm first checks for explicit turn assignments in the
// ContestantStatus::nextTurnOrder field of each contestant. The remaining
// turns are assigned such that the turn order will reverse.
//
// For example, if no Pokémon have a defined nextTurnOrder, then the 4th
// will become 1st, the 3rd will become 2nd, etc.
//
// Note: This function assumes that multiple Pokémon cannot have the same
// nextTurnOrder value.
static void ApplyNextTurnOrder(void)
{
    
}

static void SpriteCB_JudgeSpeechBubble(struct Sprite *sprite)
{

}

static void DoJudgeSpeechBubble(u8 symbolId)
{
    
}

static void UpdateApplauseMeter(void)
{
  
}

s8 Contest_GetMoveExcitement(u16 move)
{
    return-1;
}

static u8 StartApplauseOverflowAnimation(void)
{
    return -1;
}

static void Task_ApplauseOverflowAnimation(u8 taskId)
{

}

static void SlideApplauseMeterIn(void)
{

}

static void Task_SlideApplauseMeterIn(u8 taskId)
{

}

static void SlideApplauseMeterOut(void)
{

}

static void Task_SlideApplauseMeterOut(u8 taskId)
{

}

static void ShowAndUpdateApplauseMeter(s8 unused)
{

}

static void Task_ShowAndUpdateApplauseMeter(u8 taskId)
{

}

static void UNUSED HideApplauseMeterNoAnim(void)
{

}

static void UNUSED ShowApplauseMeterNoAnim(void)
{

}


static void AnimateAudience(void)
{
    
}

static void Task_AnimateAudience(u8 taskId)
{
    
}

static void BlendAudienceBackground(s8 excitementDir, s8 blendDir)
{

}

static void Task_BlendAudienceBackground(u8 taskId)
{
    
}

static void ShowHideNextTurnGfx(bool8 show)
{
    
}

static void GetTurnOrderNumberGfx(u8 contestant)
{

}

static void DrawUnnervedSymbols(void)
{
    
}

bool8 IsContestantAllowedToCombo(u8 contestant)
{
        return TRUE;
}

static void SetBgForCurtainDrop(void)
{
    
}

static void UpdateContestantBoxOrder(void)
{
   
}

static void Task_StartDropCurtainAtRoundEnd(u8 taskId)
{
    
}

static void Task_UpdateCurtainDropAtRoundEnd(u8 taskId)
{
    
}

static void Task_ResetForNextRound(u8 taskId)
{
    
}

static void Task_UpdateRaiseCurtainAtRoundEnd(u8 taskId)
{
    
}

static void Task_WaitRaiseCurtainAtRoundEnd(u8 taskId)
{
    
}

static void Task_StartRaiseCurtainAtRoundEnd(u8 taskId)
{
    
}


static void AnimateSliderHearts(u8 animId)
{
    
}

static void Task_WaitForSliderHeartAnim(u8 taskId)
{
    
}


static u16 SanitizeMove(u16 move)
{
    return-1;
}

static u16 SanitizeSpecies(u16 species)
{
    return-1;
}

static void SetMoveSpecificAnimData(u8 contestant)
{
   
}

static void ClearMoveAnimData(u8 contestant)
{
    
}

static void SetMoveAnimAttackerData(u8 contestant)
{
    
}

static void CreateInvisibleBattleTargetSprite(void)
{
    
}

static void SetBattleTargetSpritePosition(void)
{
    
}

static void SetMoveTargetPosition(u16 move)
{
    
}

static void Contest_PrintTextToBg0WindowStd(u32 windowId, const u8 *b)
{
    
}

void Contest_PrintTextToBg0WindowAt(u32 windowId, u8 *currChar, s32 x, s32 y, s32 fontId)
{
    
}

static void Contest_StartTextPrinter(const u8 *currChar, bool32 b)
{
    
}

static void ContestBG_FillBoxWithIncrementingTile(u8 bg, u16 firstTileNum, u8 x, u8 y, u8 width, u8 height, u8 paletteSlot, s16 tileNumData)
{

}

static void ContestBG_FillBoxWithTile(u8 bg, u16 firstTileNum, u8 x, u8 y, u8 width, u8 height, u8 paletteSlot)
{

}

static bool32 Contest_RunTextPrinters(void)
{

    return TRUE;
}

static void Contest_SetBgCopyFlags(u32 flagIndex)
{

}

void ResetContestLinkResults(void)
{
   
}

bool8 SaveContestWinner(u8 rank)
{
    return TRUE;
}

// Rank is either a regular contest rank (for saving winners to show in the Contest Hall)
// Or one of two special IDs listed below (for saving winners to show in Museum, or from the artist)
// If just retrieving the index where the winner *would* go, shift is FALSE
// If actually preparing to insert the winner into the saveblock, shift is TRUE
u8 GetContestWinnerSaveIdx(u8 rank, bool8 shift)
{
    return -1;
}

void ClearContestWinnerPicsInContestHall(void)
{
    
}

static void SetContestLiveUpdateFlags(u8 contestant)
{
    
}


static void CalculateContestLiveUpdateData(void)
{
    
}

static void SetConestLiveUpdateTVData(void)
{
    
}

// Unused
void ContestDebugToggleBitfields(bool8 loserFlags)
{
    
}

static void ContestDebugPrintBitStrings(void)
{
    
}

static u8 GetMonNicknameLanguage(u8 *nickname)
{
    return-1;
}

static void StripPlayerNameForLinkContest(u8 *playerName)
{
    
}

static void StripMonNameForLinkContest(u8 *monName, s32 language)
{
    
}

void StripPlayerAndMonNamesForLinkContest(s32 language)
{
    
}
