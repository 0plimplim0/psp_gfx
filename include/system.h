#ifndef SYSTEM_H
#define SYSTEM_H

extern volatile bool sys_is_running;

void sys_init(void);
void sys_exit_game();

#endif