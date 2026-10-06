#include <pspkernel.h>
#include <psprtc.h>
#include <pspdisplay.h>

#include "system.h"

volatile bool sys_is_running = false;

static int exit_callback(int arg1, int arg2, void *common);
static int callback_thread(SceSize args, void *argp);
static void setup_callbacks(void);

static int exit_callback(int arg1, int arg2, void *common) {
  sys_is_running = false;
  return 0;
}

static int callback_thread(SceSize args, void *argp) {
  int cbid = sceKernelCreateCallback("exit", exit_callback, NULL);
  sceKernelRegisterExitCallback(cbid);
  sceKernelSleepThreadCB();
  return 0;
}

static void setup_callbacks(void) {
  int thid = sceKernelCreateThread("cb", callback_thread, 0x11, 0xFA0, 0, NULL);
  if (thid >= 0) sceKernelStartThread(thid, 0, NULL);
}

void sys_init(void) {
  sys_is_running = true;
  setup_callbacks();
}

void sys_exit_game() {
  sceKernelExitGame();
}