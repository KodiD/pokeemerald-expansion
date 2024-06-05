#include "global.h"
#include "list_menu.h"
#include "main.h"
#include "overworld.h"
#include "map_name_popup.h"
#include "menu.h"
#include "script.h"
#include "event_data.h"
#include "sound.h"
#include "strings.h"
#include "task.h"
#include "constants/songs.h"
#include "script_pokemon_util.h"
#include "ui_stat_editor.h"

#define EXTRAOP_MAIN_MENU_HEIGHT 7
#define EXTRAOP_MAIN_MENU_WIDTH 13

extern const u8 ExtraOp_EventScript_EXP_On[];
extern const u8 ExtraOp_EventScript_EXP_Off[];
extern const u8 ExtraOp_EventScript_HealingStone[];
extern const u8 ExtraOp_EventScript_HealingNoCharge[];

void ExtraOp_ShowMainMenu(void);
static void ExtraOp_DestroyMainMenu(u8);
static void ExtraOpAction_Cancel(u8);
static void ExtraOpAction_ExpGain(u8);
static void ExtraOpAction_Healing_Stone(u8);
static void ExtraOpAction_RespecEV(u8);
static void ExtraOpAction_RespecIV(u8);
static void ExtraOpTask_HandleMainMenuInput(u8);

enum {
    EXTRAOP_MENU_ITEM_EXPGAIN,
    EXTRAOP_MENU_ITEM_HEALINGSTONE,
    EXTRAOP_MENU_ITEM_RESPECEV,
    EXTRAOP_MENU_ITEM_RESPECIV,
    EXTRAOP_MENU_ITEM_CANCEL,
};

static const u8 gExtraOpText_ExpGain[] = _("Toggle Exp. Gain");
static const u8 gExtraOpText_HealingStone[] = _("Use Healing Stone");
static const u8 gExtraOpText_RespecEV[] = _("Respec Mon EV");
static const u8 gExtraOpText_RespecIV[] = _("Respec Mon IV");
static const u8 gExtraOpText_Cancel[] = _("Cancel");

static const struct ListMenuItem sExtraOpMenuItems[] =
{
    [EXTRAOP_MENU_ITEM_EXPGAIN] = {gExtraOpText_ExpGain, EXTRAOP_MENU_ITEM_EXPGAIN},
    [EXTRAOP_MENU_ITEM_HEALINGSTONE] = {gExtraOpText_HealingStone, EXTRAOP_MENU_ITEM_HEALINGSTONE},
    [EXTRAOP_MENU_ITEM_RESPECEV] = {gExtraOpText_RespecEV, EXTRAOP_MENU_ITEM_RESPECEV},
    [EXTRAOP_MENU_ITEM_RESPECIV] = {gExtraOpText_RespecIV, EXTRAOP_MENU_ITEM_RESPECIV},
    [EXTRAOP_MENU_ITEM_CANCEL] = {gExtraOpText_Cancel, EXTRAOP_MENU_ITEM_CANCEL},
};

static void (*const sExtraOpMenuActions[])(u8) =
{
    [EXTRAOP_MENU_ITEM_EXPGAIN] = ExtraOpAction_ExpGain,
    [EXTRAOP_MENU_ITEM_HEALINGSTONE] = ExtraOpAction_Healing_Stone,
    [EXTRAOP_MENU_ITEM_RESPECEV] = ExtraOpAction_RespecEV,
    [EXTRAOP_MENU_ITEM_RESPECIV] = ExtraOpAction_RespecIV,
    [EXTRAOP_MENU_ITEM_CANCEL] = ExtraOpAction_Cancel,
};

static const struct WindowTemplate sExtraOpMenuWindowTemplate =
{
    .bg = 0,
    .tilemapLeft = 1,
    .tilemapTop = 1,
    .width = EXTRAOP_MAIN_MENU_WIDTH,
    .height = 2 * EXTRAOP_MAIN_MENU_HEIGHT,
    .paletteNum = 15,
    .baseBlock = 1,
};

static const struct ListMenuTemplate sExtraOpMenuListTemplate =
{
    .items = sExtraOpMenuItems,
    .moveCursorFunc = ListMenuDefaultCursorMoveFunc,
    .totalItems = ARRAY_COUNT(sExtraOpMenuItems),
    .maxShowed = EXTRAOP_MAIN_MENU_HEIGHT,
    .windowId = 0,
    .header_X = 0,
    .item_X = 8,
    .cursor_X = 0,
    .upText_Y = 1,
    .cursorPal = 2,
    .fillValue = 1,
    .cursorShadowPal = 3,
    .lettersSpacing = 1,
    .itemVerticalPadding = 0,
    .scrollMultiple = LIST_NO_MULTIPLE_SCROLL,
    .fontId = 1,
    .cursorKind = 0
};

void ExtraOp_ShowMainMenu(void) {
    struct ListMenuTemplate menuTemplate;
    u8 windowId;
    u8 menuTaskId;
    u8 inputTaskId;

    // create window
    HideMapNamePopUpWindow();
    LoadMessageBoxAndBorderGfx();
    windowId = AddWindow(&sExtraOpMenuWindowTemplate);
    DrawStdWindowFrame(windowId, FALSE);

    // create list menu
    menuTemplate = sExtraOpMenuListTemplate;
    menuTemplate.windowId = windowId;
    menuTaskId = ListMenuInit(&menuTemplate, 0, 0);

    // draw everything
    CopyWindowToVram(windowId, 3);

    // create input handler task
    inputTaskId = CreateTask(ExtraOpTask_HandleMainMenuInput, 3);
    gTasks[inputTaskId].data[0] = menuTaskId;
    gTasks[inputTaskId].data[1] = windowId;
}

static void ExtraOp_DestroyMainMenu(u8 taskId)
{
    DestroyListMenuTask(gTasks[taskId].data[0], NULL, NULL);
    ClearStdWindowAndFrame(gTasks[taskId].data[1], TRUE);
    RemoveWindow(gTasks[taskId].data[1]);
    DestroyTask(taskId);
}

static void ExtraOpTask_HandleMainMenuInput(u8 taskId)
{
    void (*func)(u8);
    u32 input = ListMenu_ProcessInput(gTasks[taskId].data[0]);

    if (JOY_NEW(A_BUTTON))
    {
        PlaySE(SE_SELECT);
        if ((func = sExtraOpMenuActions[input]) != NULL)
            func(taskId);
    }
    else if (JOY_NEW(B_BUTTON))
    {
        PlaySE(SE_SELECT);
        ExtraOp_DestroyMainMenu(taskId);
        ScriptContext_Enable();
    }
}

static void ExtraOpAction_Cancel(u8 taskId)
{
    ExtraOp_DestroyMainMenu(taskId);
    ScriptContext_Enable();
}

// static void ExtraOp_DestroyMenu_Full_Script(u8 taskId, const u8 *script)
// {
//     ScriptContext_SetupScript(script);
// }

static void ExtraOpAction_ExpGain(u8 taskId)
{
    PlaySE(SE_USE_ITEM);
    FlagToggle(FLAG_XP_Gain_0x021);
    ExtraOp_DestroyMainMenu(taskId);

    if(FlagGet(FLAG_XP_Gain_0x021)){
        //ExtraOp_DestroyMenu_Full_Script(taskId,ExtraOp_EventScript_EXP_Off);
        ScriptContext_SetupScript(ExtraOp_EventScript_EXP_Off);
    }else{
        //ExtraOp_DestroyMenu_Full_Script(taskId,ExtraOp_EventScript_EXP_On);
        ScriptContext_SetupScript(ExtraOp_EventScript_EXP_On);
    }
    ScriptContext_Enable();
}

static void ExtraOpAction_Healing_Stone(u8 taskId)
{
    if (VarGet(VAR_HEALINGCHARGE_0x40F7)>0){
        VarSet(VAR_HEALINGCHARGE_0x40F7,VarGet(VAR_HEALINGCHARGE_0x40F7)-1);
        HealPlayerParty();
        ScriptContext_SetupScript(ExtraOp_EventScript_HealingStone);
    }else{
        ScriptContext_SetupScript(ExtraOp_EventScript_HealingNoCharge);
    }

    ExtraOp_DestroyMainMenu(taskId);
    ScriptContext_Enable();
}

// static void ExtraOpAction_Respec(u8 taskId)
// {
//     PlaySE(SE_SELECT);
//     CreateTask(Task_OpenStatEditorFromStartMenu, 0);
// }

static void ExtraOpAction_RespecEV(u8 taskId)
{
    PlaySE(SE_SELECT);
    gSpecialVar_0x8004 = 0;
    CreateTask(Task_OpenToEditEV, 0);
}

static void ExtraOpAction_RespecIV(u8 taskId)
{
    PlaySE(SE_SELECT);
    gSpecialVar_0x8004 = 0;
    CreateTask(Task_OpenToEditIV, 0);
}
