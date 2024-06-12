#ifndef GUARD_CONTEST_H
#define GUARD_CONTEST_H

#include "palette.h"
#include "constants/contest.h"
#include "random.h" // for rng_value_t



extern u16 gSpecialVar_ContestCategory;
extern u16 gSpecialVar_ContestRank;

// contest.c
void ResetLinkContestBoolean(void);
void LoadContestBgAfterMoveAnim(void);
void CB2_StartContest(void);
void CreateContestMonFromParty(u8 partyIndex);
void SetContestants(u8 contestType, u8 rank);
void SetLinkAIContestants(u8 contestType, u8 rank, bool32 isPostgame);
u8 GetContestEntryEligibility(struct Pokemon *pkmn);
void CalculateRound1Points(u8 contestCategory);
bool8 IsSpeciesNotUnown(u16 species);
bool8 Contest_IsMonsTurnDisabled(u8 contestant);
void SaveLinkContestResults(void);
void SortContestants(bool8 useRanking);
void SetContestantEffectStringID(u8 contestant, u8 effectStringId);
void SetContestantEffectStringID2(u8 contestant, u8 effectStringId);
void SetStartledString(u8 contestant, u8 jam);
void MakeContestantNervous(u8 p);
s8 Contest_GetMoveExcitement(u16 move);
bool8 IsContestantAllowedToCombo(u8 contestant);
void Contest_PrintTextToBg0WindowAt(u32 windowId, u8 *currChar, s32 x, s32 y, s32 fontId);
void ResetContestLinkResults(void);
bool8 SaveContestWinner(u8 rank);
u8 GetContestWinnerSaveIdx(u8 rank, bool8 shift);
void ClearContestWinnerPicsInContestHall(void);
void StripPlayerAndMonNamesForLinkContest( s32 language);

#endif //GUARD_CONTEST_H
