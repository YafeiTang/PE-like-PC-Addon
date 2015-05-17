#include <jni.h>
#include <dlfcn.h>
#include <android/log.h>
#include <time.h>
#include <string>

#include "Substrate.h"
#include "mcpe.h"
#include "shared.h"
#include "mcpe/gui/screen/StartMenuScreen.h"
#include "mcpelauncher.h"

void exampleScreen() {
	// 버튼을 추가하기 위해 init, setupPositions, buttonClicked 세개를 Hook 합니다.
	// You should hook these functions to create button in the start menu: init(), setupPositions(), buttonClicked().
	mcpelauncher_hook((void *) &Touch::StartMenuScreen::init,		(void *) &Touch::StartMenuScreen::init_hook,			(void **) &Touch::StartMenuScreen::init_real);
	mcpelauncher_hook((void *) &Touch::StartMenuScreen::setupPositions,	(void *) &Touch::StartMenuScreen::setupPositions_hook,		(void **) &Touch::StartMenuScreen::setupPositions_real);
	mcpelauncher_hook((void *) &Touch::StartMenuScreen::buttonClicked,	(void *) &Touch::StartMenuScreen::buttonClicked_hook,		(void **) &Touch::StartMenuScreen::buttonClicked_real);
}

const std::string PElikePCVERSION = "1.0.B1";

static std::string (*getGameVersionString_real)();

static std::string getGameVersionString_hook() {
	return "§a§lPE like PC V" + PElikePCVERSION ;
}

static char** gSplashes;

static void (*Touch$StartMenuScreen$chooseRandomSplash_real)(Touch::StartMenuScreen*);
static void Touch$StartMenuScreen$chooseRandomSplash_hook(Touch::StartMenuScreen* screen) {
	gSplashes[0] = "§0§lSpoilers!";
	gSplashes[1] = "§1§lOriginal Renderers?!";
	gSplashes[2] = "§2§lMade by Xriomedabeast!";
	gSplashes[3] = "§3§lTileTessellator? What is that?";
	gSplashes[4] = "§4§lMade by RedstoneGunMade!";
	gSplashes[5] = "§5§lSome of the code by Byteandahalf!";
	gSplashes[6] = "§6§lThanks for zhuoweizhang for develop BL!";
	gSplashes[7] = "§7§l@AgameR_Modder (peacestorm) is awesome!";
	gSplashes[8] = "§8§lICustom splashes and game version!";
    gSplashes[9] = "§9§lIn the future... MinePocket Launcher!";
	gSplashes[10] = "§a§lMade by John Dan!";
	gSplashes[11] = "§b§lAlso join MinePocket Server!";
	gSplashes[12] = "§c§lThanks to MOJANG for this awesome game!";
	gSplashes[13] = "§d§lWe maybe implement... Pink Blocks ;)!";
	gSplashes[14] = "§e§lPlay MCPE, Watch Top Gear, get Pig!";
	gSplashes[15] = "§f§lWorks in Local World Multiplayer!";
	gSplashes[16] = "§1§lC§2O§3L§4O§5R§6M§7A§8T§9I§a§0_§bT§cI§dM§eE§f!";
	gSplashes[17] = "§o";
	screen->currentSplash = rand() % 18;
}

JNIEXPORT jint JNI_OnLoad(JavaVM* vm, void* reserved) {
    void* handle = dlopen("libminecraftpe.so", RTLD_LAZY);

	gSplashes = (char**) dlsym(handle, "gSplashes");
	
	MSHookFunction((void*) &Touch::StartMenuScreen::chooseRandomSplash, (void*) &Touch$StartMenuScreen$chooseRandomSplash_hook, (void**) &Touch$StartMenuScreen$chooseRandomSplash_real);
	
	srand(time(0));

void* getGameVersionString = dlsym(RTLD_DEFAULT, "_ZN6Common20getGameVersionStringEv");

	MSHookFunction(getGameVersionString, (void*)&getGameVersionString_hook, (void**)&getGameVersionString_real);
	return JNI_VERSION_1_2;
}