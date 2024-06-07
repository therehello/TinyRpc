#ifndef TINYRPC_UTIL_H
#define TINYRPC_UTIL_H

#include <pthread.h>
#include <sched.h>
namespace tinyrpc {
auto GetPid() -> pid_t;
auto GetThreadId() -> pthread_t;
}  // namespace tinyrpc

#endif