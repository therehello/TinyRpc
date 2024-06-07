#include "common/util.h"
#include <pthread.h>
#include <sched.h>
#include <sys/syscall.h>
#include <unistd.h>
#include <ctime>

namespace tinyrpc {
static pid_t pid = 0;
static thread_local pthread_t thread_id = 0;
auto GetPid() -> pid_t {
  if (pid == 0) {
    pid = getpid();
  }
  return pid;
}
auto GetThreadId() -> pthread_t {
  if (thread_id == 0) {
    thread_id = syscall(SYS_gettid);
  }
  return thread_id;
}
}  // namespace tinyrpc
