#include "global.h"
#include "random.h"
#include "constants/moves.h"
#include "contest.h"
#include "contest_effect.h"

static void ContestEffect_HighlyAppealing(void);
static void ContestEffect_UserMoreEasilyStartled(void);
static void ContestEffect_GreatAppealButNoMoreMoves(void);
static void ContestEffect_RepetitionNotBoring(void);
static void ContestEffect_AvoidStartleOnce(void);
static void ContestEffect_AvoidStartle(void);
static void ContestEffect_AvoidStartleSlightly(void);
static void ContestEffect_UserLessEasilyStartled(void);
static void ContestEffect_StartleFrontMon(void);
static void ContestEffect_StartlePrevMons(void);
static void ContestEffect_StartlePrevMon2(void);
static void ContestEffect_StartlePrevMons2(void);
static void ContestEffect_ShiftJudgeAttention(void);
static void ContestEffect_StartleMonWithJudgesAttention(void);
static void ContestEffect_JamsOthersButMissOneTurn(void);
static void ContestEffect_StartleMonsSameTypeAppeal(void);
static void ContestEffect_StartleMonsCoolAppeal(void);
static void ContestEffect_StartleMonsBeautyAppeal(void);
static void ContestEffect_StartleMonsCuteAppeal(void);
static void ContestEffect_StartleMonsSmartAppeal(void);
static void ContestEffect_StartleMonsToughAppeal(void);
static void ContestEffect_MakeFollowingMonNervous(void);
static void ContestEffect_MakeFollowingMonsNervous(void);
static void ContestEffect_WorsenConditionOfPrevMons(void);
static void ContestEffect_BadlyStartlesMonsInGoodCondition(void);
static void ContestEffect_BetterIfFirst(void);
static void ContestEffect_BetterIfLast(void);
static void ContestEffect_AppealAsGoodAsPrevOnes(void);
static void ContestEffect_AppealAsGoodAsPrevOne(void);
static void ContestEffect_BetterWhenLater(void);
static void ContestEffect_QualityDependsOnTiming(void);
static void ContestEffect_BetterIfSameType(void);
static void ContestEffect_BetterIfDiffType(void);
static void ContestEffect_AffectedByPrevAppeal(void);
static void ContestEffect_ImproveConditionPreventNervousness(void);
static void ContestEffect_BetterWithGoodCondition(void);
static void ContestEffect_NextAppealEarlier(void);
static void ContestEffect_NextAppealLater(void);
static void ContestEffect_MakeScramblingTurnOrderEasier(void);
static void ContestEffect_ScrambleNextTurnOrder(void);
static void ContestEffect_ExciteAudienceInAnyContest(void);
static void ContestEffect_BadlyStartleMonsWithGoodAppeals(void);
static void ContestEffect_BetterWhenAudienceExcited(void);
static void ContestEffect_DontExciteAudience(void);
static void JamByMoveCategory(u8);
static bool8 CanUnnerveContestant(u8);
static u8 WasAtLeastOneOpponentJammed(void);
static void JamContestant(u8, u8);
static s16 RoundTowardsZero(s16);
static s16 RoundUp(s16);


bool8 AreMovesContestCombo(u16 lastMove, u16 nextMove)
{
        return FALSE;
}

// A highly appealing move.
static void ContestEffect_HighlyAppealing(void)
{
}

// After this move, the user is more easily startled.
static void ContestEffect_UserMoreEasilyStartled(void)
{
}

// Makes a great appeal, but allows no more to the end.
static void ContestEffect_GreatAppealButNoMoreMoves(void)
{
}

// Can be used repeatedly without boring the JUDGE.
static void ContestEffect_RepetitionNotBoring(void)
{
}

// Can avoid being startled by others once.
static void ContestEffect_AvoidStartleOnce(void)
{
}

// Can avoid being startled by others.
static void ContestEffect_AvoidStartle(void)
{
}

// Can avoid being startled by others a little.
static void ContestEffect_AvoidStartleSlightly(void)
{
}

// After this move, the user is less likely to be startled.
static void ContestEffect_UserLessEasilyStartled(void)
{
}

// Slightly startles the POK�MON in front.
static void ContestEffect_StartleFrontMon(void)
{
}

// Slightly startles those that have made appeals.
static void ContestEffect_StartlePrevMons(void)
{
}

// Startles the POK�MON that appealed before the user.
static void ContestEffect_StartlePrevMon2(void)
{
}

// Startles all POK�MON that appealed before the user.
static void ContestEffect_StartlePrevMons2(void)
{
}

// Shifts the JUDGE's attention from others.
static void ContestEffect_ShiftJudgeAttention(void)
{
}

// Startles the POK�MON that has the JUDGE's attention.
static void ContestEffect_StartleMonWithJudgesAttention(void)
{
}

// Jams the others, and misses one turn of appeals.
static void ContestEffect_JamsOthersButMissOneTurn(void)
{
}

// Startles POK�MON that made a same-type appeal.
static void ContestEffect_StartleMonsSameTypeAppeal(void)
{
}

// Badly startles POK�MON that made COOL appeals.
static void ContestEffect_StartleMonsCoolAppeal(void)
{
}

// Badly startles POK�MON that made BEAUTY appeals.
static void ContestEffect_StartleMonsBeautyAppeal(void)
{
}

// Badly startles POK�MON that made CUTE appeals.
static void ContestEffect_StartleMonsCuteAppeal(void)
{
}

// Badly startles POK�MON that made SMART appeals.
static void ContestEffect_StartleMonsSmartAppeal(void)
{
}

// Badly startles POK�MON that made TOUGH appeals.
static void ContestEffect_StartleMonsToughAppeal(void)
{
}

// Makes one POK�MON after the user nervous.
static void ContestEffect_MakeFollowingMonNervous(void)
{
}

// Makes all POK�MON after the user nervous.
static void ContestEffect_MakeFollowingMonsNervous(void)
{
}

// Worsens the condition of those that made appeals.
static void ContestEffect_WorsenConditionOfPrevMons(void)
{
}

// Badly startles POK�MON in good condition.
static void ContestEffect_BadlyStartlesMonsInGoodCondition(void)
{
}

// The appeal works great if performed first.
static void ContestEffect_BetterIfFirst(void)
{
}

// The appeal works great if performed last.
static void ContestEffect_BetterIfLast(void)
{
}

// Makes the appeal as good as those before it.
static void ContestEffect_AppealAsGoodAsPrevOnes(void)
{
}

// Makes the appeal as good as the one before it.
static void ContestEffect_AppealAsGoodAsPrevOne(void)
{
}

// The appeal works better the later it is performed.
static void ContestEffect_BetterWhenLater(void)
{
}

// The appeal's quality varies depending on its timing.
static void ContestEffect_QualityDependsOnTiming(void)
{
}

static void ContestEffect_BetterIfSameType(void)
{
}

// Works well if different in type than the one before.
static void ContestEffect_BetterIfDiffType(void)
{
}

// Affected by how well the appeal in front goes.
static void ContestEffect_AffectedByPrevAppeal(void)
{
}

// Ups the user's condition. Helps prevent nervousness.
static void ContestEffect_ImproveConditionPreventNervousness(void)
{
}

// The appeal works well if the user's condition is good.
static void ContestEffect_BetterWithGoodCondition(void)
{
}

// The next appeal can be made earlier next turn.
static void ContestEffect_NextAppealEarlier(void)
{
}

// The next appeal can be made later next turn.
static void ContestEffect_NextAppealLater(void)
{
}

// Makes the next turn's order more easily scrambled.
static void ContestEffect_MakeScramblingTurnOrderEasier(void)
{
    // dummied out?
}

// Scrambles the order of appeals on the next turn.
static void ContestEffect_ScrambleNextTurnOrder(void)
{
}

// An appeal that excites the audience in any CONTEST.
static void ContestEffect_ExciteAudienceInAnyContest(void)
{
}

// Badly startles all POK�MON that made good appeals.
static void ContestEffect_BadlyStartleMonsWithGoodAppeals(void)
{
}

// The appeal works best the more the crowd is excited.
static void ContestEffect_BetterWhenAudienceExcited(void)
{
}

// Temporarily stops the crowd from growing excited.
static void ContestEffect_DontExciteAudience(void)
{
}

static void JamByMoveCategory(u8 category)
{
}

static bool8 CanUnnerveContestant(u8 i)
{
        return FALSE;
}

static bool8 WasAtLeastOneOpponentJammed(void)
{
    return FALSE;
}

static void JamContestant(u8 i, u8 jam)
{
}

static s16 RoundTowardsZero(s16 score)
{

    return 0;
}

static s16 RoundUp(s16 score)
{

    return 0;
}
