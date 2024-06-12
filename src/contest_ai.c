#include "global.h"
#include "battle.h"
#include "contest.h"
#include "random.h"
#include "contest_ai.h"
#include "contest_effect.h"
#include "constants/moves.h"

#define AI_ACTION_DONE (1 << 0)

extern const u8 *gAIScriptPtr;
extern const u8 *gContestAI_ScriptsTable[];

static void ContestAICmd_score(void);
static void ContestAICmd_get_appeal_num(void);
static void ContestAICmd_if_appeal_num_less_than(void);
static void ContestAICmd_if_appeal_num_more_than(void);
static void ContestAICmd_if_appeal_num_eq(void);
static void ContestAICmd_if_appeal_num_not_eq(void);
static void ContestAICmd_get_excitement(void);
static void ContestAICmd_if_excitement_less_than(void);
static void ContestAICmd_if_excitement_more_than(void);
static void ContestAICmd_if_excitement_eq(void);
static void ContestAICmd_if_excitement_not_eq(void);
static void ContestAICmd_get_user_order(void);
static void ContestAICmd_if_user_order_less_than(void);
static void ContestAICmd_if_user_order_more_than(void);
static void ContestAICmd_if_user_order_eq(void);
static void ContestAICmd_if_user_order_not_eq(void);
static void ContestAICmd_get_user_condition(void);
static void ContestAICmd_if_user_condition_less_than(void);
static void ContestAICmd_if_user_condition_more_than(void);
static void ContestAICmd_if_user_condition_eq(void);
static void ContestAICmd_if_user_condition_not_eq(void);
static void ContestAICmd_get_points(void);
static void ContestAICmd_if_points_less_than(void);
static void ContestAICmd_if_points_more_than(void);
static void ContestAICmd_if_points_eq(void);
static void ContestAICmd_if_points_not_eq(void);
static void ContestAICmd_get_preliminary_points(void);
static void ContestAICmd_if_preliminary_points_less_than(void);
static void ContestAICmd_if_preliminary_points_more_than(void);
static void ContestAICmd_if_preliminary_points_eq(void);
static void ContestAICmd_if_preliminary_points_not_eq(void);
static void ContestAICmd_get_contest_type(void);
static void ContestAICmd_if_contest_type_eq(void);
static void ContestAICmd_if_contest_type_not_eq(void);
static void ContestAICmd_get_move_excitement(void);
static void ContestAICmd_if_move_excitement_less_than(void);
static void ContestAICmd_if_move_excitement_more_than(void);
static void ContestAICmd_if_move_excitement_eq(void);
static void ContestAICmd_if_move_excitement_not_eq(void);
static void ContestAICmd_get_move_effect(void);
static void ContestAICmd_if_move_effect_eq(void);
static void ContestAICmd_if_move_effect_not_eq(void);
static void ContestAICmd_get_move_effect_type(void);
static void ContestAICmd_if_move_effect_type_eq(void);
static void ContestAICmd_if_move_effect_type_not_eq(void);
static void ContestAICmd_check_most_appealing_move(void);
static void ContestAICmd_if_most_appealing_move(void);
static void ContestAICmd_check_most_jamming_move(void);
static void ContestAICmd_if_most_jamming_move(void);
static void ContestAICmd_get_num_move_hearts(void);
static void ContestAICmd_if_num_move_hearts_less_than(void);
static void ContestAICmd_if_num_move_hearts_more_than(void);
static void ContestAICmd_if_num_move_hearts_eq(void);
static void ContestAICmd_if_num_move_hearts_not_eq(void);
static void ContestAICmd_get_num_move_jam_hearts(void);
static void ContestAICmd_if_num_move_jam_hearts_less_than(void);
static void ContestAICmd_if_num_move_jam_hearts_more_than(void);
static void ContestAICmd_if_num_move_jam_hearts_eq(void);
static void ContestAICmd_if_num_move_jam_hearts_not_eq(void);
static void ContestAICmd_get_move_used_count(void);
static void ContestAICmd_if_most_used_count_less_than(void);
static void ContestAICmd_if_most_used_count_more_than(void);
static void ContestAICmd_if_most_used_count_eq(void);
static void ContestAICmd_if_most_used_count_not_eq(void);
static void ContestAICmd_check_combo_starter(void);
static void ContestAICmd_if_combo_starter(void);
static void ContestAICmd_if_not_combo_starter(void);
static void ContestAICmd_check_combo_finisher(void);
static void ContestAICmd_if_combo_finisher(void);
static void ContestAICmd_if_not_combo_finisher(void);
static void ContestAICmd_check_would_finish_combo(void);
static void ContestAICmd_if_would_finish_combo(void);
static void ContestAICmd_if_would_not_finish_combo(void);
static void ContestAICmd_get_condition(void);
static void ContestAICmd_if_condition_less_than(void);
static void ContestAICmd_if_condition_more_than(void);
static void ContestAICmd_if_condition_eq(void);
static void ContestAICmd_if_condition_not_eq(void);
static void ContestAICmd_get_used_combo_starter(void);
static void ContestAICmd_if_used_combo_starter_less_than(void);
static void ContestAICmd_if_used_combo_starter_more_than(void);
static void ContestAICmd_if_used_combo_starter_eq(void);
static void ContestAICmd_if_used_combo_starter_not_eq(void);
static void ContestAICmd_check_can_participate(void);
static void ContestAICmd_if_can_participate(void);
static void ContestAICmd_if_cannot_participate(void);
static void ContestAICmd_get_completed_combo(void);
static void ContestAICmd_if_completed_combo(void);
static void ContestAICmd_if_not_completed_combo(void);
static void ContestAICmd_get_points_diff(void);
static void ContestAICmd_if_points_more_than_mon(void);
static void ContestAICmd_if_points_less_than_mon(void);
static void ContestAICmd_if_points_eq_mon(void);
static void ContestAICmd_if_points_not_eq_mon(void);
static void ContestAICmd_get_preliminary_points_diff(void);
static void ContestAICmd_if_preliminary_points_more_than_mon(void);
static void ContestAICmd_if_preliminary_points_less_than_mon(void);
static void ContestAICmd_if_preliminary_points_eq_mon(void);
static void ContestAICmd_if_preliminary_points_not_eq_mon(void);
static void ContestAICmd_get_used_moves_effect(void);
static void ContestAICmd_if_used_moves_effect_less_than(void);
static void ContestAICmd_if_used_moves_effect_more_than(void);
static void ContestAICmd_if_used_moves_effect_eq(void);
static void ContestAICmd_if_used_moves_effect_not_eq(void);
static void ContestAICmd_get_used_moves_excitement(void);
static void ContestAICmd_if_used_moves_excitement_less_than(void);
static void ContestAICmd_if_used_moves_excitement_more_than(void);
static void ContestAICmd_if_used_moves_excitement_eq(void);
static void ContestAICmd_if_used_moves_excitement_not_eq(void);
static void ContestAICmd_get_used_moves_effect_type(void);
static void ContestAICmd_if_used_moves_effect_type_eq(void);
static void ContestAICmd_if_used_moves_effect_type_not_eq(void);
static void ContestAICmd_save_result(void);
static void ContestAICmd_setvar(void);
static void ContestAICmd_add(void);
static void ContestAICmd_addvar(void);
static void ContestAICmd_addvar_duplicate(void);
static void ContestAICmd_if_less_than(void);
static void ContestAICmd_if_greater_than(void);
static void ContestAICmd_if_eq(void);
static void ContestAICmd_if_not_eq(void);
static void ContestAICmd_if_less_than_var(void);
static void ContestAICmd_if_greater_than_var(void);
static void ContestAICmd_if_eq_var(void);
static void ContestAICmd_if_not_eq_var(void);
static void ContestAICmd_if_random_less_than(void);
static void ContestAICmd_if_random_greater_than(void);
static void ContestAICmd_goto(void);
static void ContestAICmd_call(void);
static void ContestAICmd_end(void);
static void ContestAICmd_check_user_has_exciting_move(void);
static void ContestAICmd_if_user_has_exciting_move(void);
static void ContestAICmd_if_user_doesnt_have_exciting_move(void);
static void ContestAICmd_check_user_has_move(void);
static void ContestAICmd_if_user_has_move(void);
static void ContestAICmd_if_user_doesnt_have_move(void);

typedef void (* ContestAICmdFunc)(void);

static const ContestAICmdFunc sContestAICmdTable[] =
{
    ContestAICmd_score,                               // 0x00
    ContestAICmd_get_appeal_num,                      // 0x01
    ContestAICmd_if_appeal_num_less_than,             // 0x02
    ContestAICmd_if_appeal_num_more_than,             // 0x03
    ContestAICmd_if_appeal_num_eq,                    // 0x04
    ContestAICmd_if_appeal_num_not_eq,                // 0x05
    ContestAICmd_get_excitement,                      // 0x06
    ContestAICmd_if_excitement_less_than,             // 0x07
    ContestAICmd_if_excitement_more_than,             // 0x08
    ContestAICmd_if_excitement_eq,                    // 0x09
    ContestAICmd_if_excitement_not_eq,                // 0x0A
    ContestAICmd_get_user_order,                      // 0x0B
    ContestAICmd_if_user_order_less_than,             // 0x0C
    ContestAICmd_if_user_order_more_than,             // 0x0D
    ContestAICmd_if_user_order_eq,                    // 0x0E
    ContestAICmd_if_user_order_not_eq,                // 0x0F
    ContestAICmd_get_user_condition,                  // 0x10
    ContestAICmd_if_user_condition_less_than,         // 0x11
    ContestAICmd_if_user_condition_more_than,         // 0x12
    ContestAICmd_if_user_condition_eq,                // 0x13
    ContestAICmd_if_user_condition_not_eq,            // 0x14
    ContestAICmd_get_points,                          // 0x15
    ContestAICmd_if_points_less_than,                 // 0x16
    ContestAICmd_if_points_more_than,                 // 0x17
    ContestAICmd_if_points_eq,                        // 0x18
    ContestAICmd_if_points_not_eq,                    // 0x19
    ContestAICmd_get_preliminary_points,              // 0x1A
    ContestAICmd_if_preliminary_points_less_than,     // 0x1B
    ContestAICmd_if_preliminary_points_more_than,     // 0x1C
    ContestAICmd_if_preliminary_points_eq,            // 0x1D
    ContestAICmd_if_preliminary_points_not_eq,        // 0x1E
    ContestAICmd_get_contest_type,                    // 0x1F
    ContestAICmd_if_contest_type_eq,                  // 0x20
    ContestAICmd_if_contest_type_not_eq,              // 0x21
    ContestAICmd_get_move_excitement,                 // 0x22
    ContestAICmd_if_move_excitement_less_than,        // 0x23
    ContestAICmd_if_move_excitement_more_than,        // 0x24
    ContestAICmd_if_move_excitement_eq,               // 0x25
    ContestAICmd_if_move_excitement_not_eq,           // 0x26
    ContestAICmd_get_move_effect,                     // 0x27
    ContestAICmd_if_move_effect_eq,                   // 0x28
    ContestAICmd_if_move_effect_not_eq,               // 0x29
    ContestAICmd_get_move_effect_type,                // 0x2A
    ContestAICmd_if_move_effect_type_eq,              // 0x2B
    ContestAICmd_if_move_effect_type_not_eq,          // 0x2C
    ContestAICmd_check_most_appealing_move,           // 0x2D
    ContestAICmd_if_most_appealing_move,              // 0x2E
    ContestAICmd_check_most_jamming_move,             // 0x2F
    ContestAICmd_if_most_jamming_move,                // 0x30
    ContestAICmd_get_num_move_hearts,                 // 0x31
    ContestAICmd_if_num_move_hearts_less_than,        // 0x32
    ContestAICmd_if_num_move_hearts_more_than,        // 0x33
    ContestAICmd_if_num_move_hearts_eq,               // 0x34
    ContestAICmd_if_num_move_hearts_not_eq,           // 0x35
    ContestAICmd_get_num_move_jam_hearts,             // 0x36
    ContestAICmd_if_num_move_jam_hearts_less_than,    // 0x37
    ContestAICmd_if_num_move_jam_hearts_more_than,    // 0x38
    ContestAICmd_if_num_move_jam_hearts_eq,           // 0x39
    ContestAICmd_if_num_move_jam_hearts_not_eq,       // 0x3A
    ContestAICmd_get_move_used_count,                 // 0x3B
    ContestAICmd_if_most_used_count_less_than,        // 0x3C
    ContestAICmd_if_most_used_count_more_than,        // 0x3D
    ContestAICmd_if_most_used_count_eq,               // 0x3E
    ContestAICmd_if_most_used_count_not_eq,           // 0x3F
    ContestAICmd_check_combo_starter,                 // 0x40
    ContestAICmd_if_combo_starter,                    // 0x41
    ContestAICmd_if_not_combo_starter,                // 0x42
    ContestAICmd_check_combo_finisher,                // 0x43
    ContestAICmd_if_combo_finisher,                   // 0x44
    ContestAICmd_if_not_combo_finisher,               // 0x45
    ContestAICmd_check_would_finish_combo,            // 0x46
    ContestAICmd_if_would_finish_combo,               // 0x47
    ContestAICmd_if_would_not_finish_combo,           // 0x48
    ContestAICmd_get_condition,                       // 0x49
    ContestAICmd_if_condition_less_than,              // 0x4A
    ContestAICmd_if_condition_more_than,              // 0x4B
    ContestAICmd_if_condition_eq,                     // 0x4C
    ContestAICmd_if_condition_not_eq,                 // 0x4D
    ContestAICmd_get_used_combo_starter,              // 0x4E
    ContestAICmd_if_used_combo_starter_less_than,     // 0x4F
    ContestAICmd_if_used_combo_starter_more_than,     // 0x50
    ContestAICmd_if_used_combo_starter_eq,            // 0x51
    ContestAICmd_if_used_combo_starter_not_eq,        // 0x52
    ContestAICmd_check_can_participate,               // 0x53
    ContestAICmd_if_can_participate,                  // 0x54
    ContestAICmd_if_cannot_participate,               // 0x55
    ContestAICmd_get_completed_combo,                 // 0x56
    ContestAICmd_if_completed_combo,                  // 0x57
    ContestAICmd_if_not_completed_combo,              // 0x58
    ContestAICmd_get_points_diff,                     // 0x59
    ContestAICmd_if_points_more_than_mon,             // 0x5A
    ContestAICmd_if_points_less_than_mon,             // 0x5B
    ContestAICmd_if_points_eq_mon,                    // 0x5C
    ContestAICmd_if_points_not_eq_mon,                // 0x5D
    ContestAICmd_get_preliminary_points_diff,         // 0x5E
    ContestAICmd_if_preliminary_points_more_than_mon, // 0x5F
    ContestAICmd_if_preliminary_points_less_than_mon, // 0x60
    ContestAICmd_if_preliminary_points_eq_mon,        // 0x61
    ContestAICmd_if_preliminary_points_not_eq_mon,    // 0x62
    ContestAICmd_get_used_moves_effect,               // 0x63
    ContestAICmd_if_used_moves_effect_less_than,      // 0x64
    ContestAICmd_if_used_moves_effect_more_than,      // 0x65
    ContestAICmd_if_used_moves_effect_eq,             // 0x66
    ContestAICmd_if_used_moves_effect_not_eq,         // 0x67
    ContestAICmd_get_used_moves_excitement,           // 0x68
    ContestAICmd_if_used_moves_excitement_less_than,  // 0x69
    ContestAICmd_if_used_moves_excitement_more_than,  // 0x6A
    ContestAICmd_if_used_moves_excitement_eq,         // 0x6B
    ContestAICmd_if_used_moves_excitement_not_eq,     // 0x6C
    ContestAICmd_get_used_moves_effect_type,          // 0x6D
    ContestAICmd_if_used_moves_effect_type_eq,        // 0x6E
    ContestAICmd_if_used_moves_effect_type_not_eq,    // 0x6F
    ContestAICmd_save_result,                         // 0x70
    ContestAICmd_setvar,                              // 0x71
    ContestAICmd_add,                                 // 0x72
    ContestAICmd_addvar,                              // 0x73
    ContestAICmd_addvar_duplicate,                    // 0x74
    ContestAICmd_if_less_than,                        // 0x75
    ContestAICmd_if_greater_than,                     // 0x76
    ContestAICmd_if_eq,                               // 0x77
    ContestAICmd_if_not_eq,                           // 0x78
    ContestAICmd_if_less_than_var,                    // 0x79
    ContestAICmd_if_greater_than_var,                 // 0x7A
    ContestAICmd_if_eq_var,                           // 0x7B
    ContestAICmd_if_not_eq_var,                       // 0x7C
    ContestAICmd_if_random_less_than,                 // 0x7D
    ContestAICmd_if_random_greater_than,              // 0x7E
    ContestAICmd_goto,                                // 0x7F
    ContestAICmd_call,                                // 0x80
    ContestAICmd_end,                                 // 0x81
    ContestAICmd_check_user_has_exciting_move,        // 0x82
    ContestAICmd_if_user_has_exciting_move,           // 0x83
    ContestAICmd_if_user_doesnt_have_exciting_move,   // 0x84
    ContestAICmd_check_user_has_move,                 // 0x85
    ContestAICmd_if_user_has_move,                    // 0x86
    ContestAICmd_if_user_doesnt_have_move,            // 0x87
};

static void ContestAI_DoAIProcessing(void);
static bool8 GetContestantIdByTurn(u8);
static void AIStackPushVar(const u8 *);
static u8 AIStackPop(void);

void ContestAI_ResetAI(u8 contestantAI)
{
   
}

u8 ContestAI_GetActionToUse(void)
{
    return -1;
}

static void ContestAI_DoAIProcessing(void)
{
   
}

static u8 GetContestantIdByTurn(u8 turn)
{
  return -1;
}

static void ContestAICmd_score(void)
{
    
}

static void ContestAICmd_get_appeal_num(void)
{
    
}

static void ContestAICmd_if_appeal_num_less_than(void)
{
   
}

static void ContestAICmd_if_appeal_num_more_than(void)
{
    
}

static void ContestAICmd_if_appeal_num_eq(void)
{
    
}

static void ContestAICmd_if_appeal_num_not_eq(void)
{
    
}

static void ContestAICmd_get_excitement(void)
{
    
}

static void ContestAICmd_if_excitement_less_than(void)
{
    
}

static void ContestAICmd_if_excitement_more_than(void)
{
    
}

static void ContestAICmd_if_excitement_eq(void)
{
    
}

static void ContestAICmd_if_excitement_not_eq(void)
{
    
}

static void ContestAICmd_get_user_order(void)
{
   
}

static void ContestAICmd_if_user_order_less_than(void)
{
    
}

static void ContestAICmd_if_user_order_more_than(void)
{
    
}

static void ContestAICmd_if_user_order_eq(void)
{
    
}

static void ContestAICmd_if_user_order_not_eq(void)
{
    
}

static void ContestAICmd_get_user_condition(void)
{
    
}

static void ContestAICmd_if_user_condition_less_than(void)
{
    
}

static void ContestAICmd_if_user_condition_more_than(void)
{
    
}

static void ContestAICmd_if_user_condition_eq(void)
{
    
}

static void ContestAICmd_if_user_condition_not_eq(void)
{
    
}

static void ContestAICmd_get_points(void)
{
    
}

static void ContestAICmd_if_points_less_than(void)
{
    
}

static void ContestAICmd_if_points_more_than(void)
{
    
}

static void ContestAICmd_if_points_eq(void)
{
    
}

static void ContestAICmd_if_points_not_eq(void)
{
    
}

static void ContestAICmd_get_preliminary_points(void)
{
    
}

static void ContestAICmd_if_preliminary_points_less_than(void)
{
    
}

static void ContestAICmd_if_preliminary_points_more_than(void)
{
    
}

static void ContestAICmd_if_preliminary_points_eq(void)
{
    
}

static void ContestAICmd_if_preliminary_points_not_eq(void)
{
    
}

static void ContestAICmd_get_contest_type(void)
{
    
}

static void ContestAICmd_if_contest_type_eq(void)
{
    
}

static void ContestAICmd_if_contest_type_not_eq(void)
{
    
}

static void ContestAICmd_get_move_excitement(void)
{
    
}

static void ContestAICmd_if_move_excitement_less_than(void)
{
    
}

static void ContestAICmd_if_move_excitement_more_than(void)
{
    
}

static void ContestAICmd_if_move_excitement_eq(void)
{
    
}

static void ContestAICmd_if_move_excitement_not_eq(void)
{
    
}

static void ContestAICmd_get_move_effect(void)
{
    
}

static void ContestAICmd_if_move_effect_eq(void)
{
    
}

static void ContestAICmd_if_move_effect_not_eq(void)
{
    
}

static void ContestAICmd_get_move_effect_type(void)
{
    
}

static void ContestAICmd_if_move_effect_type_eq(void)
{
    
}

static void ContestAICmd_if_move_effect_type_not_eq(void)
{
    
}

static void ContestAICmd_check_most_appealing_move(void)
{
    
}

static void ContestAICmd_if_most_appealing_move(void)
{
    
}

static void ContestAICmd_check_most_jamming_move(void)
{
    
}

static void ContestAICmd_if_most_jamming_move(void)
{
    
}

static void ContestAICmd_get_num_move_hearts(void)
{
    
}

static void ContestAICmd_if_num_move_hearts_less_than(void)
{
    
}

static void ContestAICmd_if_num_move_hearts_more_than(void)
{
    
}

static void ContestAICmd_if_num_move_hearts_eq(void)
{
    
}

static void ContestAICmd_if_num_move_hearts_not_eq(void)
{
    
}

static void ContestAICmd_get_num_move_jam_hearts(void)
{
    
}

static void ContestAICmd_if_num_move_jam_hearts_less_than(void)
{
    
}

static void ContestAICmd_if_num_move_jam_hearts_more_than(void)
{
    
}

static void ContestAICmd_if_num_move_jam_hearts_eq(void)
{
    
}

static void ContestAICmd_if_num_move_jam_hearts_not_eq(void)
{
    
}

static void ContestAICmd_get_move_used_count(void)
{
    
}

static void ContestAICmd_if_most_used_count_less_than(void)
{
    
}

static void ContestAICmd_if_most_used_count_more_than(void)
{
    
}

static void ContestAICmd_if_most_used_count_eq(void)
{
    
}

static void ContestAICmd_if_most_used_count_not_eq(void)
{
    
}

static void ContestAICmd_check_combo_starter(void)
{
    
}

static void ContestAICmd_if_combo_starter(void)
{
    
}

static void ContestAICmd_if_not_combo_starter(void)
{
    
}

static void ContestAICmd_check_combo_finisher(void)
{
    
}

static void ContestAICmd_if_combo_finisher(void)
{
    
}

static void ContestAICmd_if_not_combo_finisher(void)
{
    
}

static void ContestAICmd_check_would_finish_combo(void)
{
    
}

static void ContestAICmd_if_would_finish_combo(void)
{
    
}

static void ContestAICmd_if_would_not_finish_combo(void)
{
    
}

static void ContestAICmd_get_condition(void)
{
    
}

static void ContestAICmd_if_condition_less_than(void)
{
    
}

static void ContestAICmd_if_condition_more_than(void)
{
    
}

static void ContestAICmd_if_condition_eq(void)
{
    
}

static void ContestAICmd_if_condition_not_eq(void)
{
    
}

static void ContestAICmd_get_used_combo_starter(void)
{
    
}

static void ContestAICmd_if_used_combo_starter_less_than(void)
{
    
}

static void ContestAICmd_if_used_combo_starter_more_than(void)
{
    
}

static void ContestAICmd_if_used_combo_starter_eq(void)
{
    
}

static void ContestAICmd_if_used_combo_starter_not_eq(void)
{
    
}

static void ContestAICmd_check_can_participate(void)
{
    
}

static void ContestAICmd_if_can_participate(void)
{
    
}

static void ContestAICmd_if_cannot_participate(void)
{
    
}

static void ContestAICmd_get_completed_combo(void)
{
    
}

static void ContestAICmd_if_completed_combo(void)
{
    
}

static void ContestAICmd_if_not_completed_combo(void)
{
    
}

static void ContestAICmd_get_points_diff(void)
{
    
}

static void ContestAICmd_if_points_more_than_mon(void)
{
    
}

static void ContestAICmd_if_points_less_than_mon(void)
{
    
}

static void ContestAICmd_if_points_eq_mon(void)
{
    
}

static void ContestAICmd_if_points_not_eq_mon(void)
{
    
}

static void ContestAICmd_get_preliminary_points_diff(void)
{
    
}

static void ContestAICmd_if_preliminary_points_more_than_mon(void)
{
    
}

static void ContestAICmd_if_preliminary_points_less_than_mon(void)
{
    
}

static void ContestAICmd_if_preliminary_points_eq_mon(void)
{
    
}

static void ContestAICmd_if_preliminary_points_not_eq_mon(void)
{
    
}

static void ContestAICmd_get_used_moves_effect(void)
{
    
}

static void ContestAICmd_if_used_moves_effect_less_than(void)
{
    
}

static void ContestAICmd_if_used_moves_effect_more_than(void)
{
    
}

static void ContestAICmd_if_used_moves_effect_eq(void)
{
    
}

static void ContestAICmd_if_used_moves_effect_not_eq(void)
{
    
}

static void ContestAICmd_get_used_moves_excitement(void)
{
    
}

static void ContestAICmd_if_used_moves_excitement_less_than(void)
{
    
}

static void ContestAICmd_if_used_moves_excitement_more_than(void)
{
    
}

static void ContestAICmd_if_used_moves_excitement_eq(void)
{
    
}

static void ContestAICmd_if_used_moves_excitement_not_eq(void)
{
    
}

static void ContestAICmd_get_used_moves_effect_type(void)
{
    
}

static void ContestAICmd_if_used_moves_effect_type_eq(void)
{
    
}

static void ContestAICmd_if_used_moves_effect_type_not_eq(void)
{
    
}

static void ContestAICmd_save_result(void)
{
    
}

static void ContestAICmd_setvar(void)
{
    
}

static void ContestAICmd_add(void)
{
    
}

static void ContestAICmd_addvar(void)
{
    
}

static void ContestAICmd_addvar_duplicate(void)
{
    
}

static void ContestAICmd_if_less_than(void)
{
    
}

static void ContestAICmd_if_greater_than(void)
{
    
}

static void ContestAICmd_if_eq(void)
{
    
}

static void ContestAICmd_if_not_eq(void)
{
    
}

static void ContestAICmd_if_less_than_var(void)
{
    
}

static void ContestAICmd_if_greater_than_var(void)
{
    
}

static void ContestAICmd_if_eq_var(void)
{
    
}

static void ContestAICmd_if_not_eq_var(void)
{
    
}

// UB: Should just be comparing to gAIScriptPtr[1] in the functions below
// The values passed via gAIScriptPtr[1] range from 0-255
// and vars is an s16[3], so this goes way out of bounds
static void ContestAICmd_if_random_less_than(void)
{

}

static void ContestAICmd_if_random_greater_than(void)
{

}

static void ContestAICmd_goto(void)
{
    
}

static void ContestAICmd_call(void)
{
    
}

static void ContestAICmd_end(void)
{

}

static void AIStackPushVar(const u8 *ptr)
{

}

static bool8 AIStackPop(void)
{
    
        return FALSE;

}

static void ContestAICmd_check_user_has_exciting_move(void)
{
  
}

static void ContestAICmd_if_user_has_exciting_move(void)
{

}

static void ContestAICmd_if_user_doesnt_have_exciting_move(void)
{
    
}

// BUG: This is checking if the user has a specific move, but when it's used in the AI script
//      they're checking for an effect. Checking for a specific effect would make more sense,
//      but given that effects are normally read as a single byte and this reads 2 bytes, it
//      seems reading a move was intended and the AI script is using it incorrectly.
//      The fix below aligns the function with how it's used by the script, rather than the apparent
//      intention of its usage

static void ContestAICmd_check_user_has_move(void)
{
    
}

static void ContestAICmd_if_user_has_move(void)
{
 
}

static void ContestAICmd_if_user_doesnt_have_move(void)
{
    
}
