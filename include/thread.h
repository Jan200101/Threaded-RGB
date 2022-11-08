#ifndef THREAD_H
#define THREAD_H

#include <stddef.h>

struct thread_t {
    size_t line;
};

typedef void (*thread_func)(struct thread_t*);
struct thread_info {
    thread_func func;
    thread_t* data;
};

extern struct thread_info threads[];
extern const size_t thread_count;

#define ARRAY_LEN(arr) sizeof(arr) / sizeof(arr[0]);

#define T_COROUTINE(func_name) \
    struct thread_t func_name##_thread; \
    void func_name(struct thread_t* thread)

#define T_INIT(func_name) func_name##_thread.line = 0
#define T_START() switch(thread->line) { case 0:
#define T_END() break; } thread->line = 0;

#define T_INFO(func_name) { .func = func_name, .data = &func_name##_thread }
#define T_CALL(info) \
    struct thread_info *_t_info = &(info); \
    _t_info->func(_t_info->data)


#define T_YIELD() thread->line = __LINE__; return; case __LINE__:

#define T_WAIT_WHILE(cond) \
    thread->line = __LINE__; case __LINE__: \
    if (cond) return;
#define T_WAIT_UNTIL(cond) T_WHILE_WAIT(!cond)

#endif // THREAD_H
