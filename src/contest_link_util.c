#include "global.h"
#include "contest.h"
#include "contest_link.h"
#include "event_data.h"
#include "link.h"
#include "random.h"
#include "task.h"

/*
    The functions in this file handle preliminary communication
    for Emerald-only link contests. If the link contest has an RS
    player linked, none of these functions are used.

    The equivalent functions for RS-linked contests are spread
    between contest_link.c and contest_util.c, and are suffixed RS
    instead of Em
*/

static void Task_LinkContest_CommunicateMonsEm(u8);
static void Task_LinkContest_StartCommunicateRngEm(u8);
static void Task_LinkContest_CommunicateRngEm(u8);
static void Task_LinkContest_StartCommunicateLeaderIdsEm(u8);
static void Task_LinkContest_CommunicateLeaderIdsEm(u8);
static void Task_LinkContest_StartCommunicateCategoryEm(u8);
static void Task_LinkContest_CommunicateCategoryEm(u8);
static void Task_LinkContest_SetUpContestEm(u8);
static void Task_LinkContest_CommunicateAIMonsEm(u8);
static void Task_LinkContest_CalculateRound1Em(u8);
static void Task_LinkContest_CalculateTurnOrderEm(u8);


void Task_LinkContest_StartCommunicationEm(u8 taskId)
{
    
}

static void Task_LinkContest_StartCommunicateRngEm(u8 taskId)
{
}

static void Task_LinkContest_StartCommunicateLeaderIdsEm(u8 taskId)
{
}

static void Task_LinkContest_StartCommunicateCategoryEm(u8 taskId)
{
}

static void Task_LinkContest_SetUpContestEm(u8 taskId)
{
}

static void Task_LinkContest_CalculateRound1Em(u8 taskId)
{
}

static void Task_LinkContest_CalculateTurnOrderEm(u8 taskId)
{
}

static void Task_LinkContest_CommunicateMonsEm(u8 taskId)
{

}

static void Task_LinkContest_CommunicateRngEm(u8 taskId)
{

}

static void Task_LinkContest_CommunicateLeaderIdsEm(u8 taskId)
{
}

static void Task_LinkContest_CommunicateCategoryEm(u8 taskId)
{

}

static void Task_LinkContest_CommunicateAIMonsEm(u8 taskId)
{
}
