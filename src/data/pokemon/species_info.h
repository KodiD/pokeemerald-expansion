#include "constants/abilities.h"

#include "species_info/shared_dex_text.h"
#include "pokemon.h"

// Macros for ease of use.

#define EVOLUTION(...) (const struct Evolution[]) { __VA_ARGS__, { EVOLUTIONS_END }, }

#if P_FOOTPRINTS
#define FOOTPRINT(sprite) .footprint = gMonFootprint_## sprite,
#else
#define FOOTPRINT(sprite)
#endif

// Maximum value for a female Pokémon is 254 (MON_FEMALE) which is 100% female.
// 255 (MON_GENDERLESS) is reserved for genderless Pokémon.
#define PERCENT_FEMALE(percent) min(254, ((percent * 255) / 100))

#define MON_TYPES(type1, ...) { type1, DEFAULT(type1, __VA_ARGS__) }
#define MON_EGG_GROUPS(group1, ...) { group1, DEFAULT(group1, __VA_ARGS__) }

#define FLIP    0
#define NO_FLIP 1

const struct SpeciesInfo gSpeciesInfo[] =
{
    [SPECIES_NONE] =
    {
        .speciesName = _("??????????"),
        .cryId = CRY_NONE,
        .natDexNum = NATIONAL_DEX_NONE,
        .categoryName = _("Unknown"),
        .height = 0,
        .weight = 0,
        .description = COMPOUND_STRING(
            "This is a newly discovered Pokémon.\n"
            "It is currently under investigation.\n"
            "No detailed information is available\n"
            "at this time."),
        .pokemonScale = 256,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_CircledQuestionMark,
        .frontPicSize = MON_COORDS_SIZE(40, 40),
        .frontPicYOffset = 12,
        .frontAnimFrames = sAnims_None,
        .frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_CircledQuestionMark,
        .backPicSize = MON_COORDS_SIZE(40, 40),
        .backPicYOffset = 12,
        .backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_CircledQuestionMark,
        .shinyPalette = gMonShinyPalette_CircledQuestionMark,
        .iconSprite = gMonIcon_QuestionMark,
        .iconPalIndex = 0,
        FOOTPRINT(QuestionMark)
        .levelUpLearnset = sNoneLevelUpLearnset,
        .teachableLearnset = sNoneTeachableLearnset,
    },

    #include "species_info/gen_1_families.h"
    #include "species_info/gen_2_families.h"
    #include "species_info/gen_3_families.h"
    #include "species_info/gen_4_families.h"
    #include "species_info/gen_5_families.h"
    #include "species_info/gen_6_families.h"
    #include "species_info/gen_7_families.h"
    #include "species_info/gen_8_families.h"
    #include "species_info/gen_9_families.h"

    [SPECIES_MARSHSTOMP_XFORM] =
    { 
        .baseHP        = 70,
        .baseAttack    = 85,
        .baseDefense   = 70,
        .baseSpeed     = 50,
        .baseSpAttack  = 60,
        .baseSpDefense = 70,
        .types = { TYPE_WATER, TYPE_ELECTRIC },
        .catchRate = 45,
        .expYield = (P_UPDATED_EXP_YIELDS >= GEN_5) ? 142 : 143,
        .evYield_Attack = 2,
        .genderRatio = PERCENT_FEMALE(12.5),
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_MONSTER, EGG_GROUP_WATER_1),
        .abilities = { ABILITY_TORRENT, ABILITY_NONE, ABILITY_VOLT_ABSORB },
        .bodyColor = BODY_COLOR_BLUE,
        .speciesName = _("Marshtomp"),
        .cryId = CRY_MARSHTOMP,
        .natDexNum = NATIONAL_DEX_MARSHTOMP,
        .categoryName = _("Mud Fish"),
        .height = 7,
        .weight = 280,
        .description = COMPOUND_STRING(
            "Its toughened hind legs enable it to stand\n"
            "upright. Because it weakens if its skin\n"
            "dries out, it replenishes fluids by playing\n"
            "in mud."),
        .pokemonScale = 340,
        .pokemonOffset = 7,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Marshtomp_Xform,
        .frontPicSize = MON_COORDS_SIZE(48, 56),
        .frontPicYOffset = 7,
        .frontAnimFrames = sAnims_Marshtomp,
        .frontAnimId = ANIM_V_STRETCH,
        .backPic = gMonBackPic_Marshtomp_Xform,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 3,
        .backAnimId = BACK_ANIM_CONCAVE_ARC_SMALL,
        .palette = gMonPalette_Marshtomp_Xform,
        .shinyPalette = gMonShinyPalette_Marshtomp_Xform,
        .iconSprite = gMonIcon_Marshtomp_Xform,
        .iconPalIndex = 0,
        FOOTPRINT(Marshtomp)
        .levelUpLearnset = sMarshtompXformLevelUpLearnset,
        .teachableLearnset = sMarshtompXformTeachableLearnset,
        .evolutions = EVOLUTION({EVO_LEVEL, 36, SPECIES_SWAMPERT_XFORM}),
    },

    [SPECIES_SWAMPERT_XFORM] =
    { 
       .catchRate = 45,
    #if P_UPDATED_EXP_YIELDS >= GEN_8
        .expYield = 268,
    #elif P_UPDATED_EXP_YIELDS >= GEN_5
        .expYield = 241,
    #else
        .expYield = 210,
    #endif
        .evYield_Attack = 3,
        .genderRatio = PERCENT_FEMALE(12.5),
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_MONSTER, EGG_GROUP_WATER_1),
        .abilities = { ABILITY_TORRENT, ABILITY_NONE, ABILITY_VOLT_ABSORB},
        .bodyColor = BODY_COLOR_BLUE,
        .speciesName = _("Swampert"),
        .cryId = CRY_SWAMPERT,
        .natDexNum = NATIONAL_DEX_SWAMPERT,
        .categoryName = _("Mud Fish"),
        .height = 15,
        .weight = 819,
        .description = COMPOUND_STRING(
            "If it senses the approach of a storm and\n"
            "a tidal wave, it protects its seaside nest\n"
            "by piling up boulders. It swims as fast as\n"
            "a jet ski."),
        .pokemonScale = 256,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Swampert_Xform,
        .frontPicSize = MON_COORDS_SIZE(64, 56),
        .frontPicYOffset = 6,
        .frontAnimFrames = sAnims_Swampert,
        .frontAnimId = ANIM_H_SHAKE,
        .backPic = gMonBackPic_Swampert_Xform,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 6,
        .backAnimId = BACK_ANIM_SHAKE_GLOW_BLUE,
        .palette = gMonPalette_Swampert_Xform,
        .shinyPalette = gMonShinyPalette_Swampert_Xform,
        .iconSprite = gMonIcon_Swampert_Xform,
        .iconPalIndex = 0,
        FOOTPRINT(Swampert)
        .levelUpLearnset = sSwampertXformLevelUpLearnset,
        .teachableLearnset = sSwampertXformTeachableLearnset,
        .formSpeciesIdTable = sSwampertXformFormSpeciesIdTable,
        .formChangeTable = sSwampertXformFormChangeTable,
    },

    #if P_MEGA_EVOLUTIONS
    [SPECIES_SWAMPERT_XFORM_MEGA] =
    { 
       .baseHP        = 100,
        .baseAttack    = 150,
        .baseDefense   = 110,
        .baseSpeed     = 70,
        .baseSpAttack  = 95,
        .baseSpDefense = 110,
        .types = MON_TYPES(TYPE_WATER, TYPE_GROUND),
        .catchRate = 45,
        .expYield = (P_UPDATED_EXP_YIELDS >= GEN_8) ? 318 : 286,
        .evYield_Attack = 3,
        .genderRatio = PERCENT_FEMALE(12.5),
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_MONSTER, EGG_GROUP_WATER_1),
        .abilities = { ABILITY_MOLD_BREAKER, ABILITY_MOLD_BREAKER, ABILITY_MOLD_BREAKER },
        .bodyColor = BODY_COLOR_BLUE,
        .speciesName = _("Swampert"),
        .cryId = CRY_SWAMPERT_MEGA,
        .natDexNum = NATIONAL_DEX_SWAMPERT,
        .categoryName = _("Mud Fish"),
        .height = 19,
        .weight = 1020,
        .description = COMPOUND_STRING(
            "When it Mega Evolves, the strength that it\n"
            "needs to act in the water is increased.\n"
            "It can use its tenacious power\n"
            "both on land and in the water."),
        .pokemonScale = 256,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_SwampertMega_Xform,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 6,
        .frontAnimFrames = sAnims_SwampertMega,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_SwampertMega_Xform,
        .backPicSize = MON_COORDS_SIZE(64, 56),
        .backPicYOffset = 6,
        .backAnimId = BACK_ANIM_SHAKE_GLOW_BLUE,
        .palette = gMonPalette_SwampertMega_Xform,
        .shinyPalette = gMonShinyPalette_SwampertMega_Xform,
        .iconSprite = gMonIcon_SwampertMega_Xform,
        .iconPalIndex = 0,
        FOOTPRINT(Swampert)
        .isMegaEvolution = TRUE,
        .levelUpLearnset = sSwampertXformLevelUpLearnset,
        .teachableLearnset = sSwampertXformTeachableLearnset,
        .formSpeciesIdTable = sSwampertXformFormSpeciesIdTable,
        .formChangeTable = sSwampertXformFormChangeTable,
    },
    #endif //P_MEGA_EVOLUTIONS

    [SPECIES_EGG] =
    {
        .frontPic = gMonFrontPic_Egg,
        .frontPicSize = MON_COORDS_SIZE(24, 24),
        .frontPicYOffset = 20,
        .backPic = gMonFrontPic_Egg,
        .backPicSize = MON_COORDS_SIZE(24, 24),
        .backPicYOffset = 20,
        .palette = gMonPalette_Egg,
        .shinyPalette = gMonPalette_Egg,
        .iconSprite = gMonIcon_Egg,
        .iconPalIndex = 1,
    },

    /* You may add any custom species below this point based on the following structure: */

    /*
    [SPECIES_NONE] =
    {
        .baseHP        = 1,
        .baseAttack    = 1,
        .baseDefense   = 1,
        .baseSpeed     = 1,
        .baseSpAttack  = 1,
        .baseSpDefense = 1,
        .types = MON_TYPES(TYPE_MYSTERY),
        .catchRate = 255,
        .expYield = 67,
        .evYield_HP = 1,
        .evYield_Defense = 1,
        .evYield_SpDefense = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_NO_EGGS_DISCOVERED),
        .abilities = { ABILITY_NONE, ABILITY_CURSED_BODY, ABILITY_DAMP },
        .bodyColor = BODY_COLOR_BLACK,
        .speciesName = _("??????????"),
        .cryId = CRY_NONE,
        .natDexNum = NATIONAL_DEX_NONE,
        .categoryName = _("Unknown"),
        .height = 0,
        .weight = 0,
        .description = COMPOUND_STRING(
            "This is a newly discovered Pokémon.\n"
            "It is currently under investigation.\n"
            "No detailed information is available\n"
            "at this time."),
        .pokemonScale = 256,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_CircledQuestionMark,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        //.frontPicFemale = gMonFrontPic_CircledQuestionMark,
        //.frontPicSizeFemale = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
        .frontAnimFrames = sAnims_None,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_CircledQuestionMark,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        //.backPicFemale = gMonBackPic_CircledQuestionMarkF,
        //.backPicSizeFemale = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 7,
        .backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_CircledQuestionMark,
        .shinyPalette = gMonShinyPalette_CircledQuestionMark,
        //.paletteFemale = gMonPalette_CircledQuestionMarkF,
        .shinyPaletteFemale = gMonShinyPalette_CircledQuestionMarkF,
        .iconSprite = gMonIcon_QuestionMark,
        .iconPalIndex = 0,
        //.iconSpriteFemale = gMonIcon_QuestionMarkF,
        //.iconPalIndexFemale = 1,
        FOOTPRINT(QuestionMark)
        .levelUpLearnset = sNoneLevelUpLearnset,
        .teachableLearnset = sNoneTeachableLearnset,
        .evolutions = EVOLUTION({EVO_LEVEL, 100, SPECIES_NONE},
                                {EVO_ITEM, ITEM_MOOMOO_MILK, SPECIES_NONE}),
        //.formSpeciesIdTable = sNoneFormSpeciesIdTable,
        //.formChangeTable = sNoneFormChangeTable,
        .allPerfectIVs = TRUE,
    },
    */
};

/* 
const struct AbilityList gAbilityList[] =
{
    [ABILITYLIST_ALL] =
    {
        .abilities =
        {
            ABILITY_NONE   
            ,ABILITY_STENCH   
            ,ABILITY_DRIZZLE   
            ,ABILITY_SPEED_BOOST   
            ,ABILITY_BATTLE_ARMOR   
            ,ABILITY_STURDY   
            ,ABILITY_DAMP   
            ,ABILITY_LIMBER   
            ,ABILITY_SAND_VEIL   
            ,ABILITY_STATIC   
            ,ABILITY_VOLT_ABSORB     
            ,ABILITY_WATER_ABSORB     
            ,ABILITY_OBLIVIOUS     
            ,ABILITY_CLOUD_NINE     
            ,ABILITY_COMPOUND_EYES     
            ,ABILITY_INSOMNIA     
            ,ABILITY_COLOR_CHANGE     
            ,ABILITY_IMMUNITY     
            ,ABILITY_FLASH_FIRE     
            ,ABILITY_SHIELD_DUST     
            ,ABILITY_OWN_TEMPO     
            ,ABILITY_SUCTION_CUPS     
            ,ABILITY_INTIMIDATE     
            ,ABILITY_SHADOW_TAG     
            ,ABILITY_ROUGH_SKIN     
            ,ABILITY_WONDER_GUARD     
            ,ABILITY_LEVITATE     
            ,ABILITY_EFFECT_SPORE     
            ,ABILITY_SYNCHRONIZE     
            ,ABILITY_CLEAR_BODY     
            ,ABILITY_NATURAL_CURE     
            ,ABILITY_LIGHTNING_ROD     
            ,ABILITY_SERENE_GRACE     
            ,ABILITY_SWIFT_SWIM     
            ,ABILITY_CHLOROPHYLL     
            ,ABILITY_ILLUMINATE     
            ,ABILITY_TRACE     
            ,ABILITY_HUGE_POWER     
            ,ABILITY_POISON_POINT     
            ,ABILITY_INNER_FOCUS     
            ,ABILITY_MAGMA_ARMOR     
            ,ABILITY_WATER_VEIL     
            ,ABILITY_MAGNET_PULL     
            ,ABILITY_SOUNDPROOF     
            ,ABILITY_RAIN_DISH     
            ,ABILITY_SAND_STREAM     
            ,ABILITY_PRESSURE     
            ,ABILITY_THICK_FAT     
            ,ABILITY_EARLY_BIRD     
            ,ABILITY_FLAME_BODY     
            ,ABILITY_RUN_AWAY     
            ,ABILITY_KEEN_EYE     
            ,ABILITY_HYPER_CUTTER     
            ,ABILITY_PICKUP     
            ,ABILITY_TRUANT     
            ,ABILITY_HUSTLE     
            ,ABILITY_CUTE_CHARM     
            ,ABILITY_PLUS     
            ,ABILITY_MINUS     
            ,ABILITY_FORECAST     
            ,ABILITY_STICKY_HOLD     
            ,ABILITY_SHED_SKIN     
            ,ABILITY_GUTS     
            ,ABILITY_MARVEL_SCALE     
            ,ABILITY_LIQUID_OOZE     
            ,ABILITY_OVERGROW     
            ,ABILITY_BLAZE     
            ,ABILITY_TORRENT     
            ,ABILITY_SWARM     
            ,ABILITY_ROCK_HEAD     
            ,ABILITY_DROUGHT     
            ,ABILITY_ARENA_TRAP     
            ,ABILITY_VITAL_SPIRIT     
            ,ABILITY_WHITE_SMOKE     
            ,ABILITY_PURE_POWER     
            ,ABILITY_SHELL_ARMOR     
            ,ABILITY_AIR_LOCK             
            ,ABILITY_TANGLED_FEET     
            ,ABILITY_MOTOR_DRIVE     
            ,ABILITY_RIVALRY     
            ,ABILITY_STEADFAST     
            ,ABILITY_SNOW_CLOAK     
            ,ABILITY_GLUTTONY     
            ,ABILITY_ANGER_POINT     
            ,ABILITY_UNBURDEN     
            ,ABILITY_HEATPROOF     
            ,ABILITY_SIMPLE     
            ,ABILITY_DRY_SKIN     
            ,ABILITY_DOWNLOAD     
            ,ABILITY_IRON_FIST     
            ,ABILITY_POISON_HEAL     
            ,ABILITY_ADAPTABILITY     
            ,ABILITY_SKILL_LINK     
            ,ABILITY_HYDRATION     
            ,ABILITY_SOLAR_POWER     
            ,ABILITY_QUICK_FEET     
            ,ABILITY_NORMALIZE     
            ,ABILITY_SNIPER     
            ,ABILITY_MAGIC_GUARD     
            ,ABILITY_NO_GUARD     
            ,ABILITY_STALL       
            ,ABILITY_TECHNICIAN       
            ,ABILITY_LEAF_GUARD       
            ,ABILITY_KLUTZ       
            ,ABILITY_MOLD_BREAKER       
            ,ABILITY_SUPER_LUCK       
            ,ABILITY_AFTERMATH       
            ,ABILITY_ANTICIPATION       
            ,ABILITY_FOREWARN       
            ,ABILITY_UNAWARE       
            ,ABILITY_TINTED_LENS       
            ,ABILITY_FILTER       
            ,ABILITY_SLOW_START       
            ,ABILITY_SCRAPPY       
            ,ABILITY_STORM_DRAIN       
            ,ABILITY_ICE_BODY       
            ,ABILITY_SOLID_ROCK       
            ,ABILITY_SNOW_WARNING       
            ,ABILITY_HONEY_GATHER       
            ,ABILITY_FRISK       
            ,ABILITY_RECKLESS       
            ,ABILITY_MULTITYPE       
            ,ABILITY_FLOWER_GIFT       
            ,ABILITY_BAD_DREAMS       
            ,ABILITY_PICKPOCKET       
            ,ABILITY_SHEER_FORCE       
            ,ABILITY_CONTRARY       
            ,ABILITY_UNNERVE       
            ,ABILITY_DEFIANT       
            ,ABILITY_DEFEATIST       
            ,ABILITY_CURSED_BODY       
            ,ABILITY_HEALER       
            ,ABILITY_FRIEND_GUARD       
            ,ABILITY_WEAK_ARMOR       
            ,ABILITY_HEAVY_METAL       
            ,ABILITY_LIGHT_METAL       
            ,ABILITY_MULTISCALE       
            ,ABILITY_TOXIC_BOOST       
            ,ABILITY_FLARE_BOOST       
            ,ABILITY_HARVEST       
            ,ABILITY_TELEPATHY       
            ,ABILITY_MOODY       
            ,ABILITY_OVERCOAT       
            ,ABILITY_POISON_TOUCH       
            ,ABILITY_REGENERATOR       
            ,ABILITY_BIG_PECKS       
            ,ABILITY_SAND_RUSH       
            ,ABILITY_WONDER_SKIN       
            ,ABILITY_ANALYTIC       
            ,ABILITY_ILLUSION       
            ,ABILITY_IMPOSTER       
            ,ABILITY_INFILTRATOR       
            ,ABILITY_MUMMY       
            ,ABILITY_MOXIE       
            ,ABILITY_JUSTIFIED       
            ,ABILITY_RATTLED       
            ,ABILITY_MAGIC_BOUNCE       
            ,ABILITY_SAP_SIPPER       
            ,ABILITY_PRANKSTER       
            ,ABILITY_SAND_FORCE       
            ,ABILITY_IRON_BARBS       
            ,ABILITY_ZEN_MODE       
            ,ABILITY_VICTORY_STAR       
            ,ABILITY_TURBOBLAZE       
            ,ABILITY_TERAVOLT          
            ,ABILITY_AROMA_VEIL       
            ,ABILITY_FLOWER_VEIL       
            ,ABILITY_CHEEK_POUCH       
            ,ABILITY_PROTEAN       
            ,ABILITY_FUR_COAT       
            ,ABILITY_MAGICIAN       
            ,ABILITY_BULLETPROOF       
            ,ABILITY_COMPETITIVE       
            ,ABILITY_STRONG_JAW       
            ,ABILITY_REFRIGERATE       
            ,ABILITY_SWEET_VEIL       
            ,ABILITY_STANCE_CHANGE       
            ,ABILITY_GALE_WINGS       
            ,ABILITY_MEGA_LAUNCHER       
            ,ABILITY_GRASS_PELT       
            ,ABILITY_SYMBIOSIS       
            ,ABILITY_TOUGH_CLAWS       
            ,ABILITY_PIXILATE       
            ,ABILITY_GOOEY       
            ,ABILITY_AERILATE       
            ,ABILITY_PARENTAL_BOND       
            ,ABILITY_DARK_AURA       
            ,ABILITY_FAIRY_AURA       
            ,ABILITY_AURA_BREAK       
            ,ABILITY_PRIMORDIAL_SEA       
            ,ABILITY_DESOLATE_LAND       
            ,ABILITY_DELTA_STREAM         
            ,ABILITY_STAMINA       
            ,ABILITY_WIMP_OUT       
            ,ABILITY_EMERGENCY_EXIT       
            ,ABILITY_WATER_COMPACTION       
            ,ABILITY_MERCILESS       
            ,ABILITY_SHIELDS_DOWN       
            ,ABILITY_STAKEOUT       
            ,ABILITY_WATER_BUBBLE       
            ,ABILITY_STEELWORKER       
            ,ABILITY_BERSERK       
            ,ABILITY_SLUSH_RUSH       
            ,ABILITY_LONG_REACH       
            ,ABILITY_LIQUID_VOICE       
            ,ABILITY_TRIAGE       
            ,ABILITY_GALVANIZE       
            ,ABILITY_SURGE_SURFER       
            ,ABILITY_SCHOOLING       
            ,ABILITY_DISGUISE       
            ,ABILITY_BATTLE_BOND       
            ,ABILITY_POWER_CONSTRUCT       
            ,ABILITY_CORROSION       
            ,ABILITY_COMATOSE       
            ,ABILITY_QUEENLY_MAJESTY       
            ,ABILITY_INNARDS_OUT       
            ,ABILITY_DANCER       
            ,ABILITY_BATTERY       
            ,ABILITY_FLUFFY       
            ,ABILITY_DAZZLING       
            ,ABILITY_SOUL_HEART       
            ,ABILITY_TANGLING_HAIR       
            ,ABILITY_RECEIVER       
            ,ABILITY_POWER_OF_ALCHEMY       
            ,ABILITY_BEAST_BOOST       
            ,ABILITY_RKS_SYSTEM       
            ,ABILITY_ELECTRIC_SURGE       
            ,ABILITY_PSYCHIC_SURGE       
            ,ABILITY_MISTY_SURGE       
            ,ABILITY_GRASSY_SURGE       
            ,ABILITY_FULL_METAL_BODY       
            ,ABILITY_SHADOW_SHIELD       
            ,ABILITY_PRISM_ARMOR       
            ,ABILITY_NEUROFORCE       
            ,ABILITY_INTREPID_SWORD       
            ,ABILITY_DAUNTLESS_SHIELD       
            ,ABILITY_LIBERO       
            ,ABILITY_BALL_FETCH       
            ,ABILITY_COTTON_DOWN       
            ,ABILITY_PROPELLER_TAIL       
            ,ABILITY_MIRROR_ARMOR       
            ,ABILITY_GULP_MISSILE       
            ,ABILITY_STALWART       
            ,ABILITY_STEAM_ENGINE       
            ,ABILITY_PUNK_ROCK       
            ,ABILITY_SAND_SPIT       
            ,ABILITY_ICE_SCALES       
            ,ABILITY_RIPEN       
            ,ABILITY_ICE_FACE       
            ,ABILITY_POWER_SPOT       
            ,ABILITY_MIMICRY       
            ,ABILITY_SCREEN_CLEANER       
            ,ABILITY_STEELY_SPIRIT       
            ,ABILITY_PERISH_BODY       
            ,ABILITY_WANDERING_SPIRIT       
            ,ABILITY_GORILLA_TACTICS       
            ,ABILITY_NEUTRALIZING_GAS       
            ,ABILITY_PASTEL_VEIL       
            ,ABILITY_HUNGER_SWITCH       
            ,ABILITY_QUICK_DRAW       
            ,ABILITY_UNSEEN_FIST       
            ,ABILITY_CURIOUS_MEDICINE       
            ,ABILITY_TRANSISTOR       
            ,ABILITY_DRAGONS_MAW       
            ,ABILITY_CHILLING_NEIGH       
            ,ABILITY_GRIM_NEIGH       
            ,ABILITY_AS_ONE_ICE_RIDER       
            ,ABILITY_AS_ONE_SHADOW_RIDER       
            ,ABILITY_LINGERING_AROMA       
            ,ABILITY_SEED_SOWER       
            ,ABILITY_THERMAL_EXCHANGE       
            ,ABILITY_ANGER_SHELL       
            ,ABILITY_PURIFYING_SALT       
            ,ABILITY_WELL_BAKED_BODY       
            ,ABILITY_WIND_RIDER       
            ,ABILITY_GUARD_DOG       
            ,ABILITY_ROCKY_PAYLOAD       
            ,ABILITY_WIND_POWER       
            ,ABILITY_ZERO_TO_HERO       
            ,ABILITY_COMMANDER       
            ,ABILITY_ELECTROMORPHOSIS       
            ,ABILITY_PROTOSYNTHESIS       
            ,ABILITY_QUARK_DRIVE       
            ,ABILITY_GOOD_AS_GOLD       
            ,ABILITY_VESSEL_OF_RUIN       
            ,ABILITY_SWORD_OF_RUIN       
            ,ABILITY_TABLETS_OF_RUIN       
            ,ABILITY_BEADS_OF_RUIN       
            ,ABILITY_ORICHALCUM_PULSE       
            ,ABILITY_HADRON_ENGINE       
            ,ABILITY_OPPORTUNIST       
            ,ABILITY_CUD_CHEW       
            ,ABILITY_SHARPNESS       
            ,ABILITY_SUPREME_OVERLORD       
            ,ABILITY_COSTAR       
            ,ABILITY_TOXIC_DEBRIS       
            ,ABILITY_ARMOR_TAIL       
            ,ABILITY_EARTH_EATER       
            ,ABILITY_MYCELIUM_MIGHT       
            ,ABILITY_HOSPITALITY       
            ,ABILITY_MINDS_EYE       
            ,ABILITY_EMBODY_ASPECT_TEAL_MASK       
            ,ABILITY_EMBODY_ASPECT_HEARTHFLAME_MASK       
            ,ABILITY_EMBODY_ASPECT_WELLSPRING_MASK       
            ,ABILITY_EMBODY_ASPECT_CORNERSTONE_MASK       
            ,ABILITY_TOXIC_CHAIN       
            ,ABILITY_SUPERSWEET_SYRUP       
            ,ABILITY_TERA_SHIFT       
            ,ABILITY_TERA_SHELL       
            ,ABILITY_TERAFORM_ZERO       
            ,ABILITY_POISON_PUPPETEER,
        }   
    },
}; */