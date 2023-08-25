#include <vitasdk.h>
#include <vitaGL.h>

static char comm_id[12] = {0};
static const char signature[160] = {0xb9,0xdd,0xe1,0x3b,0x01,0x00};

static int trp_ctx;
static int plat_id = -1;

typedef struct {
	int sdkVersion;
	SceCommonDialogParam commonParam;
	int context;
	int options;
	uint8_t reserved[128];
} SceNpTrophySetupDialogParam;

int sceNpTrophyInit(void *unk);
int sceNpTrophyCreateContext(int *context, char *commId, char *commSign, uint64_t options);
int sceNpTrophySetupDialogInit(SceNpTrophySetupDialogParam *param);
SceCommonDialogStatus sceNpTrophySetupDialogGetStatus();
int sceNpTrophySetupDialogTerm();
int sceNpTrophyCreateHandle(int *handle);
int sceNpTrophyDestroyHandle(int handle);
int sceNpTrophyUnlockTrophy(int ctx, int handle, int id, int *plat_id);
int trophies_available = 0;

volatile int trp_id;
SceUID trp_request_mutex;
int trophies_unlocker(SceSize args, void *argp) {
	for (;;) {
		sceKernelWaitSema(trp_request_mutex, 1, NULL);
		int trp_handle;
		sceNpTrophyCreateHandle(&trp_handle);
		sceNpTrophyUnlockTrophy(trp_ctx, trp_handle, trp_id, &plat_id);
		sceNpTrophyDestroyHandle(trp_handle);
	}
}

int trophies_init() {
	sceAppMgrAppParamGetString(0, 12, comm_id, 256);
	sceSysmoduleLoadModule(SCE_SYSMODULE_NP_TROPHY);
	sceNpTrophyInit(NULL);
	int res = sceNpTrophyCreateContext(&trp_ctx, comm_id, signature, 0);
	if (res < 0)
		return res;
	SceNpTrophySetupDialogParam setupParam;
	sceClibMemset(&setupParam, 0, sizeof(SceNpTrophySetupDialogParam));
	_sceCommonDialogSetMagicNumber(&setupParam.commonParam);
	setupParam.sdkVersion = PSP2_SDK_VERSION;
	setupParam.options = 0;
	setupParam.context = trp_ctx;
	sceNpTrophySetupDialogInit(&setupParam);
	
	static int trophy_setup = SCE_COMMON_DIALOG_STATUS_RUNNING;
	while (trophy_setup == SCE_COMMON_DIALOG_STATUS_RUNNING) {
		trophy_setup = sceNpTrophySetupDialogGetStatus();
		vglSwapBuffers(GL_TRUE);
	}
	sceNpTrophySetupDialogTerm();
	
	trp_request_mutex = sceKernelCreateSema("trps request", 0, 0, 1, NULL);
	SceUID tropies_unlocker_thd = sceKernelCreateThread("trophies unlocker", &trophies_unlocker, 0x10000100, 0x10000, 0, 0, NULL);
	sceKernelStartThread(tropies_unlocker_thd, 0, NULL);
	
	trophies_available = 1;
	return res;
}

void trophies_unlock(int id) {
	if (trophies_available) {
		trp_id = id;
		sceKernelSignalSema(trp_request_mutex, 1);
	}
}
