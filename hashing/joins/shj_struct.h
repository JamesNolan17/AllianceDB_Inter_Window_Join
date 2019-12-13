//
// Created by Shuhao Zhang on 1/11/19.
//

#ifndef ALLIANCEDB_SHJ_STRUCT_H
#define ALLIANCEDB_SHJ_STRUCT_H

#include "npj_types.h"
#include "../utils/t_timer.h"
#include "../helper/fetcher.h"
#include "../helper/shuffler.h"
#include "../helper/localjoiner.h"

/**
 * \ingroup arguments to the threads
 */

//struct list {
//    std::list<int> *relR_list;
//    std::list<int> *relS_list;
//};

/**
 * Thread-Local Structure.
 */
struct arg_t {
    int32_t tid;
    int64_t nthreads;
    int64_t results = 0;

    hashtable_t *htR;
    hashtable_t *htS;

    pthread_barrier_t *barrier;

    baseFetcher *fetcher;
    baseShuffler *shuffler;
    localJoiner *joiner;

    /* results of the thread */
    threadresult_t *threadresult;


#ifndef NO_TIMING
    T_TIMER *timer;
#endif
};

struct t_param {
    int64_t result;
    result_t *joinresult;

    pthread_attr_t *attr;
    pthread_barrier_t *barrier;

    arg_t *args;
    pthread_t *tid;

    baseFetcher *fetcher;
    baseShuffler *shuffler;
    localJoiner *joiner;

    t_param(int nthreads) {
        result = 0;
        joinresult = new result_t();//(result_t *) malloc(sizeof(result_t));
        attr = new pthread_attr_t();
        barrier = new pthread_barrier_t();
        args = new arg_t[nthreads];
        tid = new pthread_t[nthreads];
    }

};

// TODO: create a new structure for multi-source THREAD_TASK
/**
 * This argument is also should be applied to mutliple sources, currently only have two sources.
 * TODO: multiple fetcher/shuffler/joiner support.
 */
struct query_arg_t {
    int32_t tid;
    int64_t nthreads;
    int64_t results = 0;

    hashtable_t **htR;
    hashtable_t **htS;

    pthread_barrier_t *barrier;

    // declare a bunch of fetchers, shufflers, joiners to adapt to multiple source
    baseFetcher **fetcher;
    baseShuffler **shuffler;
    localJoiner **joiner;

    /* results of the thread */
    threadresult_t *threadresult;


#ifndef NO_TIMING
    T_TIMER *timer;
#endif
};

/**
 * for a query, should own multiple input sources, thus multiple fetcher and shuffler.
 * TODO: I think one fetcher should only read one relation. This architecture is actually not very suitable now.
 */
struct t_query_param {
    int64_t result;
    result_t *joinresult;

    pthread_attr_t *attr;
    pthread_barrier_t *barrier;

    query_arg_t *args;
    pthread_t *tid;

    // declare a bunch of fetchers, shufflers, joiners to adapt to multiple source
    baseFetcher **fetcher;
    baseShuffler **shuffler;
    localJoiner **joiner;

    t_query_param(int nthreads) {
        result = 0;
        joinresult = new result_t();//(result_t *) malloc(sizeof(result_t));
        attr = new pthread_attr_t();
        barrier = new pthread_barrier_t();
        args = new query_arg_t[nthreads];
        tid = new pthread_t[nthreads];
    }

};

#endif //ALLIANCEDB_SHJ_STRUCT_H
