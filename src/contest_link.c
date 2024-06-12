#include "global.h"
#include "contest.h"
#include "decompress.h"
#include "event_data.h"
#include "link.h"
#include "pokemon.h"
#include "random.h"
#include "task.h"
#include "contest_link.h"

static void Task_LinkContest_StartInitFlags(u8);
static void Task_LinkContest_InitFlags(u8);


bool32 LinkContest_SendBlock(void *src, u16 size)
{
        return FALSE;
}

bool8 LinkContest_GetBlockReceived(u8 flag)
{
        return TRUE;
}

bool8 LinkContest_GetBlockReceivedFromAllPlayers(void)
{
        return FALSE;
}

void Task_LinkContest_Init(u8 taskId)
{
}

static void Task_LinkContest_StartInitFlags(u8 taskId)
{
}

static void Task_LinkContest_InitFlags(u8 taskId)
{
}

bool32 LinkContest_TryLinkStandby(s16 *state)
{
            return TRUE;
}

void Task_LinkContest_CommunicateMonsRS(u8 taskId)
{
}

void Task_LinkContest_CommunicateRngRS(u8 taskId)
{
}

void Task_LinkContest_CommunicateCategoryRS(u8 taskId)
{
}

void Task_LinkContest_CommunicateMonIdxs(u8 taskId)
{
}

void Task_LinkContest_CommunicateMoveSelections(u8 taskId)
{
}

void Task_LinkContest_CommunicateFinalStandings(u8 taskId)
{
}

void Task_LinkContest_CommunicateAppealsState(u8 taskId)
{
}

void Task_LinkContest_CommunicateLeaderIdsRS(u8 taskId)
{
}

void Task_LinkContest_CommunicateRound1Points(u8 taskId)
{
}

void Task_LinkContest_CommunicateTurnOrder(u8 taskId)
{
}
