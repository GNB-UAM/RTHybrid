#include "clamplauncher.h"

ClampLauncher::ClampLauncher(clamp_args args)
{
    this->args = args;
    this->pid = getpid();
}

pid_t ClampLauncher::getPid() {
    return this->pid;
}
