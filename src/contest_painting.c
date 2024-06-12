#include "global.h"
#include "malloc.h"
#include "battle.h"
#include "battle_gfx_sfx_util.h"
#include "bg.h"
#include "contest.h"
#include "contest_painting.h"
#include "data.h"
#include "decompress.h"
#include "gpu_regs.h"
#include "image_processing_effects.h"
#include "international_string_util.h"
#include "main.h"
#include "lilycove_lady.h"
#include "palette.h"
#include "random.h"
#include "scanline_effect.h"
#include "string_util.h"
#include "strings.h"
#include "text.h"
#include "window.h"
#include "constants/rgb.h"



static void ShowContestPainting(void);
static void HoldContestPainting(void);
static void InitContestPaintingWindow(void);
static void InitContestPaintingBg(void);
static void InitContestPaintingVars(bool8);
static void CreateContestPaintingPicture(u8, u8);
static void PrintContestPaintingCaption(u8, u8);
static void VBlankCB_ContestPainting(void);
static void _InitContestMonPixels(u8 *spriteGfx, u16 *palette, u16 (*destPixels)[64][64]);


void SetContestWinnerForPainting(int contestWinnerId)
{

}

void CB2_ContestPainting(void)
{
}

static void CB2_HoldContestPainting(void)
{
}

static void CB2_QuitContestPainting(void)
{
}

static void ShowContestPainting(void)
{

}

static void HoldContestPainting(void)
{

}

static void InitContestPaintingWindow(void)
{

}

static void PrintContestPaintingCaption(u8 contestType, bool8 isForArtist)
{

}

static void InitContestPaintingBg(void)
{

}

static void InitContestPaintingVars(bool8 reset)
{
}

static void UpdateContestPaintingMosaicEffect(void)
{

}

static void VBlankCB_ContestPainting(void)
{

}

static void InitContestMonPixels(u16 species, bool8 backPic)
{

}

static void _InitContestMonPixels(u8 *spriteGfx, u16 *palette, u16 (*destPixels)[64][64])
{
}

static void LoadContestPaintingFrame(u8 contestWinnerId, bool8 isForArtist)
{
}

static void InitPaintingMonOamData(u8 contestWinnerId)
{
}

static u8 GetImageEffectForContestWinner(u8 contestWinnerId)
{

    return 0;
}

static void AllocPaintingResources(void)
{
}

static void DoContestPaintingImageProcessing(u8 imageEffect)
{
}

static void CreateContestPaintingPicture(u8 contestWinnerId, bool8 isForArtist)
{
}

