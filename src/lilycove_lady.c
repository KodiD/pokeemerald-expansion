#include "global.h"
#include "main.h"
#include "overworld.h"
#include "fldeff.h"
#include "field_specials.h"
#include "pokeblock.h"
#include "event_data.h"
#include "script.h"
#include "random.h"
#include "string_util.h"
#include "item.h"
#include "constants/items.h"
#include "item_menu.h"
#include "text.h"
#include "easy_chat.h"
#include "lilycove_lady.h"
#include "contest.h"
#include "strings.h"
#include "constants/lilycove_lady.h"

#include "data/lilycove_lady.h"

static void InitLilycoveQuizLady(void);
static void InitLilycoveFavorLady(void);
static void ResetQuizLadyForRecordMix(void);
static void ResetFavorLadyForRecordMix(void);
static u8 BufferQuizAuthorName(void);
static bool8 IsQuizTrainerIdNotPlayer(void);
static u8 GetPlayerNameLength(const u8 *);

static EWRAM_DATA struct LilycoveLadyFavor *sFavorLadyPtr = NULL;
static EWRAM_DATA struct LilycoveLadyQuiz *sQuizLadyPtr = NULL;
static EWRAM_DATA struct LilycoveLadyContest *sContestLadyPtr = NULL;

extern EWRAM_DATA u16 gSpecialVar_ItemId;

u8 GetLilycoveLadyId(void)
{
    return 0;
}

void SetLilycoveLadyGfx(void)
{
}

void InitLilycoveLady(void)
{

}

void ResetLilycoveLadyForRecordMix(void)
{
}

// Unused
void InitLilycoveLadyRandomly(void)
{

}

void Script_GetLilycoveLadyId(void)
{
}

static u8 GetNumAcceptedItems(const u16 *itemsArray)
{
    return 0;
}

static void FavorLadyPickFavorAndBestItem(void)
{
}

static void InitLilycoveFavorLady(void)
{
}

static void ResetFavorLadyForRecordMix(void)
{
}

u8 GetFavorLadyState(void)
{
        return 0;
}

static const u8 *GetFavorLadyRequest(u8 idx)
{
    return 0;
}

void BufferFavorLadyRequest(void)
{
}

bool8 HasAnotherPlayerGivenFavorLadyItem(void)
{
    return FALSE;
}

static void BufferItemName(u8 *dest, u16 itemId)
{
}

void BufferFavorLadyItemName(void)
{
}

static void SetFavorLadyPlayerName(const u8 *src, u8 *dest)
{
}

void BufferFavorLadyPlayerName(void)
{
}

// Only used to determine if a record-mixed player had given her an item she liked
bool8 DidFavorLadyLikeItem(void)
{
    return TRUE;
}

void Script_FavorLadyOpenBagMenu(void)
{
}

static bool8 DoesFavorLadyLikeItem(u16 itemId)
{
    return TRUE;
}

bool8 Script_DoesFavorLadyLikeItem(void)
{
    return TRUE;
}

bool8 IsFavorLadyThresholdMet(void)
{

    return TRUE;
}

static void FavorLadyBufferPrizeName(u16 prize)
{
}

u16 FavorLadyGetPrize(void)
{
    return 0;
}

void SetFavorLadyState_Complete(void)
{
}

void FieldCallback_FavorLadyEnableScriptContexts(void)
{
}

static void QuizLadyPickQuestion(void)
{
}

static void InitLilycoveQuizLady(void)
{
}

static void ResetQuizLadyForRecordMix(void)
{
}

u8 GetQuizLadyState(void)
{
        return 0;
}

u8 GetQuizAuthor(void)
{
        return 0;
}

static u8 BufferQuizAuthorName(void)
{

    return 0;
}

static bool8 IsQuizTrainerIdNotPlayer(void)
{
    return TRUE;
}

static u8 GetPlayerNameLength(const u8 *playerName)
{
    return 0;
}

void BufferQuizPrizeName(void)
{
}

bool8 BufferQuizAuthorNameAndCheckIfLady(void)
{
    return TRUE;
}

bool8 IsQuizLadyWaitingForChallenger(void)
{
    return TRUE;
}

void QuizLadyGetPlayerAnswer(void)
{

}

bool8 IsQuizAnswerCorrect(void)
{
    return TRUE;
}

void BufferQuizPrizeItem(void)
{
}

void SetQuizLadyState_Complete(void)
{
}

void SetQuizLadyState_GivePrize(void)
{
}

void ClearQuizLadyPlayerAnswer(void)
{
}

void Script_QuizLadyOpenBagMenu(void)
{
}

void QuizLadyPickNewQuestion(void)
{
}

void ClearQuizLadyQuestionAndAnswer(void)
{
}

void QuizLadySetCustomQuestion(void)
{
}

void QuizLadyTakePrizeForCustomQuiz(void)
{
}

void QuizLadyRecordCustomQuizData(void)
{
}

void QuizLadySetWaitingForChallenger(void)
{
}

void BufferQuizCorrectAnswer(void)
{
}


void FieldCallback_QuizLadyEnableScriptContexts(void)
{
}

void QuizLadyClearQuestionForRecordMix(const LilycoveLady *lilycoveLady)
{
}

static void ResetContestLadyContestData(void)
{
}

static void InitLilycoveContestLady(void)
{
}

static void ResetContestLadyForRecordMix(void)
{
}

static void ContestLadySavePlayerNameIfHighSheen(u8 sheen)
{
}

bool8 GivePokeblockToContestLady(struct Pokeblock *pokeblock)
{

    return TRUE;
}

static void BufferContestLadyCategoryAndMonName(u8 *category, u8 *nickname)
{
}

void BufferContestLadyMonName(u8 *category, u8 *nickname)
{
}

void BufferContestLadyPlayerName(u8 *dest)
{
}

void BufferContestLadyLanguage(u8 *dest)
{
}

void BufferContestName(u8 *dest, u8 category)
{
}

// Used by the Contest Lady's TV show to determine how well she performed
u8 GetContestLadyPokeblockState(void)
{
    
        return 0;
}


bool8 HasPlayerGivenContestLadyPokeblock(void)
{

    return FALSE;
}

bool8 ShouldContestLadyShowGoOnAir(void)
{
    return TRUE;
}

void Script_BufferContestLadyCategoryAndMonName(void)
{
}

void OpenPokeblockCaseForContestLady(void)
{
}

void SetContestLadyGivenPokeblock(void)
{
}

void GetContestLadyMonSpecies(void)
{
}

u8 GetContestLadyCategory(void)
{
    return 0;
}
