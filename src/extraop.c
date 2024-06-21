#include "global.h"
#include "battle_pike.h"
#include "battle_pyramid.h"
#include "battle_pyramid_bag.h"
#include "bg.h"
#include "debug.h"
#include "event_data.h"
#include "extraop.h"
#include "event_object_movement.h"
#include "event_object_lock.h"
#include "event_scripts.h"
#include "fieldmap.h"
#include "field_effect.h"
#include "field_player_avatar.h"
#include "field_specials.h"
#include "field_weather.h"
#include "field_screen_effect.h"
#include "frontier_pass.h"
#include "frontier_util.h"
#include "gpu_regs.h"
#include "international_string_util.h"
#include "item_menu.h"
#include "link.h"
#include "load_save.h"
#include "main.h"
#include "menu.h"
#include "new_game.h"
#include "option_menu.h"
#include "overworld.h"
#include "palette.h"
#include "party_menu.h"
#include "pokedex.h"
#include "pokenav.h"
#include "safari_zone.h"
#include "save.h"
#include "scanline_effect.h"
#include "script_pokemon_util.h"
#include "script.h"
#include "sound.h"
#include "start_menu.h"
#include "strings.h"
#include "string_util.h"
#include "task.h"
#include "text.h"
#include "text_window.h"
#include "trainer_card.h"
#include "window.h"
#include "union_room.h"
#include "constants/battle_frontier.h"
#include "constants/rgb.h"
#include "constants/songs.h"

// Menu actions
enum
{
    MENU_ACTION_HEAL,
    MENU_ACTION_REPEL,
    MENU_ACTION_WAIT,
    MENU_ACTION_EXIT,
};


// IWRAM common
bool8 (*gMenuCallbackE)(void);

// EWRAM
EWRAM_DATA static u8 sStartMenuCursorPos = 0;
EWRAM_DATA static u8 sNumStartMenuActions = 0;
EWRAM_DATA static u8 sCurrentStartMenuActions[9] = {0};
EWRAM_DATA static s8 sInitStartMenuData[2] = {0};
EWRAM_DATA static u32 sExtraWindowId = 0;

// Menu action callbacks
static bool8 ExtraMenuHealCallback(void);
static bool8 ExtraMenuRepelCallback(void);
static bool8 ExtraMenuWaitCallback(void);
static bool8 ExtraMenuExitCallback(void);

// Menu callbacks
static bool8 HandleStartMenuInput(void);

// Task callbacks
static void StartMenuTask(u8 taskId);
static bool8 FieldCB_ReturnToFieldStartMenu(void);

static const struct WindowTemplate sExtraMenuWindowTemp = {
    .bg = 0,
    .tilemapLeft = 1,
    .tilemapTop = 1,
    .width = 13,
    .height = 9,
    .paletteNum = 15,
    .baseBlock = 0x8
};

extern const u8 ExtraOp_EventScript_HealingStone[];
extern const u8 ExtraOp_EventScript_HealingNoCharge[];
extern const u8 ExtraOp_EventScript_RepelOff[];
extern const u8 ExtraOp_EventScript_RepelOn[];
extern const u8 PlayersHouse_2F_EventScript_SetWallClock[];
static const u8 gExtraOpText_HealingStone[] =   _("Use Healing Stone");
static const u8 gExtraOpText_RepelCharm[] =     _("Toggle Repel Charm");
static const u8 gExtraOpText_Wait[] =           _("Wait");
static const u8 gExtraOpText_Exit[] =           _("Exit");


static const struct MenuAction sStartMenuItems[] =
{
    [MENU_ACTION_HEAL]              = {gExtraOpText_HealingStone,     {.u8_void = ExtraMenuHealCallback}},
    [MENU_ACTION_REPEL]             = {gExtraOpText_RepelCharm,       {.u8_void = ExtraMenuRepelCallback}},
    [MENU_ACTION_WAIT]              = {gExtraOpText_Wait,             {.u8_void = ExtraMenuWaitCallback}},
    [MENU_ACTION_EXIT]              = {gExtraOpText_Exit,             {.u8_void = ExtraMenuExitCallback}},
};


// Local functions
static void BuildStartMenuActions(void);
static void AddStartMenuAction(u8 action);
static void BuildNormalStartMenu(void);
static bool32 PrintStartMenuActions(s8 *pIndex, u32 count);
static bool32 InitStartMenuStep(void);
static void InitStartMenu(void);
static void CreateStartMenuTask(TaskFunc followupFunc);
static void HideStartMenuWindow(void);

static void BuildStartMenuActions(void)
{
    sNumStartMenuActions = 0;
            BuildNormalStartMenu();
}

static void AddStartMenuAction(u8 action)
{
    AppendToListE(sCurrentStartMenuActions, &sNumStartMenuActions, action);
}

static void BuildNormalStartMenu(void)
{

    if (FlagGet(FLAG_SYS_HEALSTONE_GET) == TRUE)
    {
        AddStartMenuAction(MENU_ACTION_HEAL);
    }
    if (FlagGet(FLAG_SYS_REPELCHARM_GET) == TRUE)
    {
        AddStartMenuAction(MENU_ACTION_REPEL);
    }
    AddStartMenuAction(MENU_ACTION_WAIT);
    AddStartMenuAction(MENU_ACTION_EXIT);
}

static bool32 PrintStartMenuActions(s8 *pIndex, u32 count)
{
    s8 index = *pIndex;

    do
    {
            StringExpandPlaceholders(gStringVar4, sStartMenuItems[sCurrentStartMenuActions[index]].text);
            AddTextPrinterParameterized(sExtraWindowId, FONT_NORMAL, gStringVar4, 8, (index << 4) + 3, TEXT_SKIP_DRAW, NULL);

        index++;
        if (index >= sNumStartMenuActions)
        {
            *pIndex = index;
            return TRUE;
        }

        count--;
    }
    while (count != 0);

    *pIndex = index;
    return FALSE;
}

static bool32 InitStartMenuStep(void)
{
    s8 state = sInitStartMenuData[0];

    switch (state)
    {
    case 0:
        sInitStartMenuData[0]++;
        break;
    case 1:
        BuildStartMenuActions();
        sInitStartMenuData[0]++;
        break;
    case 2:
        LoadMessageBoxAndBorderGfx();

        sExtraWindowId = AddWindow(&sExtraMenuWindowTemp);
        DrawStdWindowFrame(sExtraWindowId, FALSE);
        sInitStartMenuData[1] = 0;
        sInitStartMenuData[0]++;
        break;
    case 3:
        sInitStartMenuData[0]++;
        break;
    case 4:
        if (PrintStartMenuActions(&sInitStartMenuData[1], 2))
            sInitStartMenuData[0]++;
        break;
    case 5:
        sStartMenuCursorPos = InitMenuNormal(sExtraWindowId, FONT_NORMAL, 0, 4, 16, sNumStartMenuActions, sStartMenuCursorPos);
        CopyWindowToVram(sExtraWindowId, COPYWIN_MAP);
        return TRUE;
    }

    return FALSE;
}

static void InitStartMenu(void)
{
    sInitStartMenuData[0] = 0;
    sInitStartMenuData[1] = 0;
    while (!InitStartMenuStep())
        ;
}

static void StartMenuTask(u8 taskId)
{
    if (InitStartMenuStep() == TRUE)
        SwitchTaskToFollowupFunc(taskId);
}

static void CreateStartMenuTask(TaskFunc followupFunc)
{
    u8 taskId;

    sInitStartMenuData[0] = 0;
    sInitStartMenuData[1] = 0;
    taskId = CreateTask(StartMenuTask, 0x50);
    SetTaskFuncWithFollowupFunc(taskId, StartMenuTask, followupFunc);
}

static bool8 FieldCB_ReturnToFieldStartMenu(void)
{
    if (InitStartMenuStep() == FALSE)
    {
        return FALSE;
    }

    ReturnToFieldOpenStartMenu();
    return TRUE;
}

void ShowReturnToFieldStartMenuE(void)
{
    sInitStartMenuData[0] = 0;
    sInitStartMenuData[1] = 0;
    gFieldCallback2 = FieldCB_ReturnToFieldStartMenu;
}

void Task_ShowExtraMenu(u8 taskId)
{
    struct Task *task = &gTasks[taskId];

    switch(task->data[0])
    {
    case 0:
        gMenuCallbackE = HandleStartMenuInput;
        task->data[0]++;
        break;
    case 1:
        if (gMenuCallbackE() == TRUE)
            DestroyTask(taskId);
        break;
    }
}

void ShowExtraMenu(void)
{
    FreezeObjectEvents();
    PlayerFreeze();
    StopPlayerAvatar();
    CreateStartMenuTask(Task_ShowExtraMenu);
    LockPlayerFieldControls();
}

static bool8 HandleStartMenuInput(void)
{
    if (JOY_NEW(DPAD_UP))
    {
        PlaySE(SE_SELECT);
        sStartMenuCursorPos = Menu_MoveCursor(-1);
    }

    if (JOY_NEW(DPAD_DOWN))
    {
        PlaySE(SE_SELECT);
        sStartMenuCursorPos = Menu_MoveCursor(1);
    }

    if (JOY_NEW(A_BUTTON))
    {
        PlaySE(SE_SELECT);

        gMenuCallbackE = sStartMenuItems[sCurrentStartMenuActions[sStartMenuCursorPos]].func.u8_void;

        return FALSE;
    }

    if (JOY_NEW(L_BUTTON | B_BUTTON))
    {
        HideStartMenuE();
        return TRUE;
    }

    return FALSE;
}

static bool8 ExtraMenuHealCallback(void)
{
    PlaySE(SE_USE_ITEM);

    if (VarGet(VAR_HEALINGCHARGE_0x40F7)>0){
        VarSet(VAR_HEALINGCHARGE_0x40F7,VarGet(VAR_HEALINGCHARGE_0x40F7)-1);
        HealPlayerParty();
        ScriptContext_SetupScript(ExtraOp_EventScript_HealingStone);
    }else{
        ScriptContext_SetupScript(ExtraOp_EventScript_HealingNoCharge);
    }

    HideStartMenuE(); // Hide start menu
    return TRUE;
}


static bool8 ExtraMenuRepelCallback(void)
{
    bool8 repelCharmOn = FlagGet(FLAG_REPEL_0x020);
    FlagToggle(FLAG_REPEL_0x020);
    if(repelCharmOn)
    {
        PlaySE(SE_REPEL);
        ScriptContext_SetupScript(ExtraOp_EventScript_RepelOff);
    }
    else
    {
        PlaySE(SE_PC_OFF);
        ScriptContext_SetupScript(ExtraOp_EventScript_RepelOn);
    }
       

    HideStartMenuE(); // Hide start menu
    return TRUE;
}

static bool8 ExtraMenuWaitCallback(void)
{
    ScriptContext_SetupScript(PlayersHouse_2F_EventScript_SetWallClock);
    HideStartMenuE(); // Hide start menu
    return TRUE;
}

static bool8 ExtraMenuExitCallback(void)
{
    HideStartMenuE(); // Hide start menu

    return TRUE;
}

static void HideStartMenuWindow(void)
{
    ClearStdWindowAndFrame(sExtraWindowId, TRUE);
    RemoveWindow(sExtraWindowId);
    ScriptUnfreezeObjectEvents();
    UnlockPlayerFieldControls();
}

void HideStartMenuE(void)
{
    PlaySE(SE_SELECT);
    HideStartMenuWindow();
}

void AppendToListE(u8 *list, u8 *pos, u8 newEntry)
{
    list[*pos] = newEntry;
    (*pos)++;
}