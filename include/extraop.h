#ifndef GUARD_EXTRAOP_H
#define GUARD_EXTRAOP_H

extern bool8 (*gMenuCallbackE)(void);

void ShowReturnToFieldStartMenuE(void);
void Task_ShowExtraMenu(u8 taskId);
void ShowExtraMenu(void);
void HideStartMenuE(void);
void AppendToListE(u8 *list, u8 *pos, u8 newEntry);

// void ExtraOp_ShowMainMenu(void);

#endif