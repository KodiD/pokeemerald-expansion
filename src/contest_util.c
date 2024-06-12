#include "global.h"
#include "malloc.h"
#include "battle.h"
#include "battle_gfx_sfx_util.h"
#include "bg.h"
#include "contest.h"
#include "contest_util.h"
#include "contest_link.h"
#include "contest_painting.h"
#include "data.h"
#include "decompress.h"
#include "dma3.h"
#include "event_data.h"
#include "event_object_movement.h"
#include "field_specials.h"
#include "gpu_regs.h"
#include "graphics.h"
#include "international_string_util.h"
#include "link.h"
#include "link_rfu.h"
#include "load_save.h"
#include "main.h"
#include "overworld.h"
#include "palette.h"
#include "pokedex.h"
#include "pokemon.h"
#include "pokemon_icon.h"
#include "random.h"
#include "save.h"
#include "scanline_effect.h"
#include "script.h"
#include "script_menu.h"
#include "sound.h"
#include "string_util.h"
#include "strings.h"
#include "task.h"
#include "text.h"
#include "trig.h"
#include "tv.h"
#include "util.h"
#include "window.h"
#include "constants/event_objects.h"
#include "constants/field_specials.h"
#include "constants/game_stat.h"
#include "constants/rgb.h"
#include "constants/songs.h"
#include "contest.h"


static void LoadAllContestMonIconPalettes(void);
static void LoadContestResultsTitleBarTilemaps(void);
static u8 GetNumPreliminaryPoints(u8, bool8);
static s8 GetNumRound2Points(u8, bool8);
static void AddContestTextPrinter(int, u8 *, int);
static void AllocContestResults(void);
static void FreeContestResults(void);
static void LoadAllContestMonIcons(u8, u8);
static void CreateResultsTextWindowSprites(void);
static void TryCreateWirelessSprites(void);
static void Task_StartShowContestResults(u8 taskId);
static void CB2_StartShowContestResults(void);
static void Task_ShowContestResults(u8);
static void CB2_ShowContestResults(void);
static void VBlankCB_ShowContestResults(void);
static void Task_SlideContestResultsBg(u8);
static void Task_WaitForLinkPartnersBeforeResults(u8);
static void Task_CommunicateMonIdxsForResults(u8);
static void Task_WaitForLinkPartnerMonIdxs(u8);
static void Task_AnnouncePreliminaryResults(u8);
static void Task_FlashStarsAndHearts(u8);
static void Task_ShowPreliminaryResults(u8);
static void Task_AnnounceRound2Results(u8);
static void Task_ShowRound2Results(u8);
static void Task_AnnounceWinner(u8);
static void Task_DrawFinalStandingNumber(u8);
static void Task_StartHighlightWinnersBox(u8);
static void Task_HighlightWinnersBox(u8);
static void Task_ShowWinnerMonBanner(u8);
static void Task_SetSeenWinnerMon(u8);
static void Task_TryDisconnectLinkPartners(u8);
static void Task_WaitForLinkPartnersDisconnect(u8);
static void Task_TrySetContestInterviewData(u8);
static void Task_EndShowContestResults(u8);
static void CalculateContestantsResultData(void);
static void ShowLinkResultsTextBox(const u8 *);
static void HideLinkResultsTextBox(void);
static s32 DrawResultsTextWindow(const u8 *, u8);
static void StartTextBoxSlideIn(s16, u16, u16, u16);
static void UpdateContestResultBars(bool8, u8);
static void Task_UpdateContestResultBar(u8);
static void StartTextBoxSlideOut(u16);
static void BounceMonIconInBox(u8, u8);
static void Task_BounceMonIconInBox(u8);
static void SpriteCB_WinnerMonSlideIn(struct Sprite *);
static void SpriteCB_WinnerMonSlideOut(struct Sprite *);
static void Task_CreateConfetti(u8);
static void SpriteCB_TextBoxSlideIn(struct Sprite *);
static void SpriteCB_TextBoxSlideOut(struct Sprite *);
static void SpriteCB_EndTextBoxSlideIn(struct Sprite *);
static void Task_StartCommunication(u8);
static void Task_StartCommunicateRngRS(u8);
static void Task_StartCommunicateLeaderIdsRS(u8);
static void Task_StartCommunicateCategoryRS(u8);
static void Task_LinkContest_SetUpContestRS(u8);
static void Task_LinkContest_CalculateTurnOrderRS(u8);
static void Task_LinkContest_Disconnect(u8);
static void Task_LinkContest_WaitDisconnect(u8);
static void SpriteCB_Confetti(struct Sprite *sprite);
static void Task_ShowContestEntryMonPic(u8 taskId);
static void Task_LinkContestWaitForConnection(u8 taskId);

static void InitContestResultsDisplay(void)
{
}

static void LoadContestResultsBgGfx(void)
{

}

static void LoadContestMonName(u8 monIndex)
{
}

static void LoadAllContestMonNames(void)
{
}

static void CB2_StartShowContestResults(void)
{
}

static void CB2_ShowContestResults(void)
{
}

static void VBlankCB_ShowContestResults(void)
{
}


static void Task_ShowContestResults(u8 taskId)
{
   
}

static void Task_WaitForLinkPartnersBeforeResults(u8 taskId)
{

}

static void Task_CommunicateMonIdxsForResults(u8 taskId)
{
}

static void Task_WaitForLinkPartnerMonIdxs(u8 taskId)
{
}

static void Task_AnnouncePreliminaryResults(u8 taskId)
{
}

static void Task_ShowPreliminaryResults(u8 taskId)
{
}

static void Task_AnnounceRound2Results(u8 taskId)
{
}

static void Task_ShowRound2Results(u8 taskId)
{
}

static void Task_AnnounceWinner(u8 taskId)
{

}

static void Task_ShowWinnerMonBanner(u8 taskId)
{
}

static void Task_SetSeenWinnerMon(u8 taskId)
{
}

static void Task_TryDisconnectLinkPartners(u8 taskId)
{
}

static void Task_WaitForLinkPartnersDisconnect(u8 taskId)
{
}

static void Task_TrySetContestInterviewData(u8 taskId)
{
}

static void Task_EndShowContestResults(u8 taskId)
{
}

static void Task_SlideContestResultsBg(u8 taskId)
{
}


static void Task_FlashStarsAndHearts(u8 taskId)
{
}

static void LoadContestMonIcon(u16 species, u8 monIndex, u8 srcOffset, u8 useDmaNow, u32 personality)
{
}

static void LoadAllContestMonIcons(u8 srcOffset, bool8 useDmaNow)
{
}

static void LoadAllContestMonIconPalettes(void)
{
}

static void TryCreateWirelessSprites(void)
{
}

static s32 DrawResultsTextWindow(const u8 *text, u8 spriteId)
{
    return 0;
}

static void CreateResultsTextWindowSprites(void)
{
}


// If slideOutTimer is -1, it will not automatically slide out
static void StartTextBoxSlideIn(s16 x, u16 y, u16 slideOutTimer, u16 slideIncrement)
{
}

static void StartTextBoxSlideOut(u16 slideIncrement)
{
}

static void EndTextBoxSlideOut(struct Sprite *sprite)
{
}

static void SpriteCB_TextBoxSlideIn(struct Sprite *sprite)
{
}

static void SpriteCB_EndTextBoxSlideIn(struct Sprite *sprite)
{
}

static void SpriteCB_TextBoxSlideOut(struct Sprite *sprite)
{
}

static void ShowLinkResultsTextBox(const u8 *text)
{
}

static void HideLinkResultsTextBox(void)
{
}

static void LoadContestResultsTitleBarTilemaps(void)
{
}

// Represented on results board as stars
static u8 GetNumPreliminaryPoints(u8 monIndex, bool8 capPoints)
{
    return 0;
}

// Represented on results board as hearts
static s8 GetNumRound2Points(u8 monIndex, bool8 capPoints)
{
    return 0;
}


static void Task_DrawFinalStandingNumber(u8 taskId)
{
}


static void Task_StartHighlightWinnersBox(u8 taskId)
{
}

static void Task_HighlightWinnersBox(u8 taskId)
{
}

static void SpriteCB_WinnerMonSlideIn(struct Sprite *sprite)
{
}

static void SpriteCB_WinnerMonSlideOut(struct Sprite *sprite)
{
}

static void Task_CreateConfetti(u8 taskId)
{
}

static void SpriteCB_Confetti(struct Sprite *sprite)
{
}


static void BounceMonIconInBox(u8 monIndex, u8 numFrames)
{
}

static void Task_BounceMonIconInBox(u8 taskId)
{
}


static void CalculateContestantsResultData(void)
{
}


static void UpdateContestResultBars(bool8 isRound2, u8 numUpdates)
{
}

static void Task_UpdateContestResultBar(u8 taskId)
{
}


static void AllocContestResults(void)
{
}

static void FreeContestResults(void)
{
}

static void AddContestTextPrinter(int windowId, u8 *str, int x)
{
}

void TryEnterContestMon(void)
{
}

u16 HasMonWonThisContestBefore(void)
{

    return TRUE;
}

void GiveMonContestRibbon(void)
{
}

void BufferContestantTrainerName(void)
{
}

void BufferContestantMonNickname(void)
{
}

// Unused script special
void GetContestMonConditionRanking(void)
{
}

void GetContestMonCondition(void)
{
}

void GetContestWinnerId(void)
{
}

void BufferContestWinnerTrainerName(void)
{
}

void BufferContestWinnerMonName(void)
{
}

void CB2_SetStartContestCallback(void)
{
}

static void Task_StartContest(u8 taskId)
{
}

void StartContest(void)
{
}

void BufferContestantMonSpecies(void)
{
}

static void Task_StartShowContestResults(u8 taskId)
{
}

void ShowContestResults(void)
{
}

void GetContestPlayerId(void)
{
}

void ContestLinkTransfer(u8 category)
{
}

static void Task_StartCommunication(u8 taskId)
{
}

static void Task_StartCommunicateRngRS(u8 taskId)
{
}

static void Task_StartCommunicateLeaderIdsRS(u8 taskId)
{
}

static void Task_StartCommunicateCategoryRS(u8 taskId)
{
}

static void Task_LinkContest_SetUpContestRS(u8 taskId)
{
}

static void Task_LinkContest_CalculateTurnOrderRS(u8 taskId)
{
}

u8 LinkContest_GetLeaderIndex(u8 *ids)
{
    return 0;
}

void Task_LinkContest_FinalizeConnection(u8 taskId)
{
}

static void Task_LinkContest_Disconnect(u8 taskId)
{
}

static void Task_LinkContest_WaitDisconnect(u8 taskId)
{
}

/*
    A section of contest script functions starts here
*/

void SetContestTrainerGfxIds(void)
{
}

// Unused
void GetNpcContestantLocalId(void)
{
}

void BufferContestTrainerAndMonNames(void)
{
}

// Unused
void DoesContestCategoryHaveMuseumPainting(void)
{
}

void SaveMuseumContestPainting(void)
{
}

void ShouldReadyContestArtist(void)
{
}

u8 CountPlayerMuseumPaintings(void)
{
    return 0;
}

// Unused
void GetContestantNamesAtRank(void)
{
}

static void ExitContestPainting(void)
{
}

void ShowContestPainting(void)
{
}

void SetLinkContestPlayerGfx(void)
{
}

void LoadLinkContestPlayerPalettes(void)
{
}

bool8 GiveMonArtistRibbon(void)
{
    return TRUE;
}

bool8 IsContestDebugActive(void)
{
    return FALSE; // gUnknown_0203856C in pokeruby
}

void ShowContestEntryMonPic(void)
{
}

void HideContestEntryMonPic(void)
{
}

static void Task_ShowContestEntryMonPic(u8 taskId)
{
}

void GetContestMultiplayerId(void)
{
}

void GenerateContestRand(void)
{
}

u16 GetContestRand(void)
{
    return TRUE;
}

bool8 LinkContestWaitForConnection(void)
{
        return FALSE;
}

static void Task_LinkContestWaitForConnection(u8 taskId)
{
}

void LinkContestTryShowWirelessIndicator(void)
{
}

void LinkContestTryHideWirelessIndicator(void)
{
}

bool8 IsContestWithRSPlayer(void)
{
        return FALSE;
}

void ClearLinkContestFlags(void)
{
}

bool8 IsWirelessContest(void)
{
        return FALSE;
}
