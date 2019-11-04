//
// Created by Shuhao Zhang on 1/11/19.
//

#ifndef ALLIANCEDB_THREAD_TASK_H
#define ALLIANCEDB_THREAD_TASK_H

#include <iostream>
#include <list>
#include "../utils/xxhash64.h"
#include "../utils/barrier.h"
#include "common_functions.h"
#include "../utils/t_timer.h"  /* startTimer, stopTimer */
#include "../utils/generator.h"          /* numa_localize() */
#include "../utils/cpu_mapping.h"        /* get_cpu_id */
#include "../utils/lock.h"               /* lock, unlock */
#include "npj_types.h"          /* bucket_t, hashtable_t, bucket_buffer_t */
#include "npj_params.h"         /* constant parameters */
#include "shj.h"
#include <sys/time.h>           /* gettimeofday */
#include <stdlib.h>             /* memalign */
#include <stdio.h>              /* printf */
#include <string.h>             /* memset */
#include <pthread.h>            /* pthread_* */
#include <sched.h>              /* CPU_ZERO, CPU_SET */
#include "shj_struct.h"


/**
 * Just a wrapper to call the _shj_st
 *
 * @param param the parameters of the thread, i.e. tid, ht, reln, ...
 *
 * @return
 */
void *
thread_task(void *param);

/**
 * Just a wrapper to call the _shj_st
 *
 * @param param the parameters of the thread, i.e. tid, ht, reln, ...
 *
 * @return
 */
void *
shj_thread_jb_np(void *param);

#endif //ALLIANCEDB_THREAD_TASK_H
