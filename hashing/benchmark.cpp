//
// Created by root on 11/29/19.
//

#include "benchmark.h"

void createRelation(relation_t *rel, relation_payload_t *relPl, int32_t key, const param_t &cmd_params,
                    char *loadfile, uint64_t rel_size, uint32_t seed) {
    fprintf(stdout,
            "[INFO ] %s relation with size = %.3lf MiB, #tuples = %llu : ",
            (loadfile != NULL) ? ("Loading") : ("Creating"),
            (double) sizeof(tuple_t) * rel_size / 1024.0 / 1024.0, rel_size);
    fflush(stdout);

    seed_generator(seed);

    /* to pass information to the create_relation methods */
    numalocalize = cmd_params.basic_numa;
    nthreads = cmd_params.nthreads;


    /** first allocate the memory for relations (+ padding based on numthreads) : */
    rel->num_tuples = cmd_params.r_size;
    size_t relRsz = rel->num_tuples * sizeof(tuple_t)
                    + RELATION_PADDING(cmd_params.nthreads, cmd_params.part_fanout);

    rel->tuples = (tuple_t *) malloc_aligned(relRsz);

    /** second allocate the memory for relation payload **/
    // TODO: not sure whether is correct
    relPl->num_tuples = cmd_params.r_size;
    size_t relPlRsz = relPl->num_tuples * sizeof(table_t)
                    + RELATION_PADDING(cmd_params.nthreads, cmd_params.part_fanout);
    relPl->rows = (table_t *) malloc_aligned(relPlRsz);

    //    /* NUMA-localize the input: */
    //    if(!nonumalocalize){
    //        numa_localize(relS.tuples, relS.num_tuples, cmd_params.nthreads);
    //    }

    if (loadfile != NULL) {
        /* load relation from file */
        load_relation(rel, relPl, key, loadfile, rel_size);
    } else if (cmd_params.fullrange_keys) {
        create_relation_nonunique(rel, rel_size, INT_MAX);
    } else if (cmd_params.nonunique_keys) {
        create_relation_nonunique(rel, rel_size, rel_size);
    } else {
        //create_relation_pk(&rel, rel_size);
        parallel_create_relation(rel, rel_size,
                                 nthreads,
                                 rel_size);
    }
    printf("OK \n");
}

result_t
*join_from_file(const param_t cmd_params,
               char *loadfileR, char *loadfileS,
               int32_t rkey, int32_t skey,
               uint64_t r_size, uint64_t s_size) {
    //TODO: add multiple relations loader, currently only support two relation
    //TODO: update structure of results, intermediate results should be a new relation or two new relations

    relation_t relR;
    relation_t relS;

    relation_payload_t relPlR;
    relation_payload_t relPlS;

    result_t *results;

    // TODO: generate dataset
    /* create relation R */
    createRelation(&relR, &relPlR, rkey, cmd_params, loadfileR, r_size, cmd_params.r_seed);
    DEBUGMSG("relR [aligned:%d]: %s", is_aligned(relR.tuples, CACHE_LINE_SIZE),
             print_relation(relR.tuples, cmd_params.r_size).c_str())

    /* create relation S */
    createRelation(&relS, &relPlS, skey, cmd_params, loadfileS, s_size, cmd_params.s_seed);
    DEBUGMSG("relS [aligned:%d]: %s", is_aligned(relS.tuples, CACHE_LINE_SIZE),
             print_relation(relS.tuples, cmd_params.s_size).c_str())

    // TODO: Execute query with dataset, need to submit a join function

    /* Run the selected join algorithm */
    printf("[INFO ] Running join algorithm %s ...\n", cmd_params.algo->name);

    results = cmd_params.algo->joinAlgo(&relR, &relS, cmd_params.nthreads);

    printf("[INFO ] Results = %ld. DONE.\n", results->totalresults);

    /* clean-up */
    delete_relation(&relR);
    delete_relation(&relS);
    delete_relation_payload(&relPlR);
    delete_relation_payload(&relPlS);
    free(results);

    return results;
}

void
//benchmark(const param_t cmd_params, relation_t *relR, relation_t *relS,
//          relation_payload_t *relPlR, relation_payload_t *relPlS, result_t *results) {/* create relation R */
benchmark(const param_t cmd_params) {
    /*SELECT
        n_name,
        sum(l_extendedprice * (1 - l_discount)) as revenue
    FROM
        customer,
        orders,
        lineitem,
        supplier,
        nation,
        region
    WHERE
        c_custkey = o_custkey
        AND l_orderkey = o_orderkey
        AND l_suppkey = s_suppkey
        AND c_nationkey = s_nationkey
        AND s_nationkey = n_nationkey
        AND n_regionkey = r_regionkey
        AND r_name = 'ASIA'
        AND o_orderdate >= date '1994-01-01'
        AND o_orderdate < date '1994-01-01' + interval '1' year
    GROUP BY
        n_name
    ORDER BY
        revenue desc;*/

    result_t *results;

    results = join_from_file(cmd_params, cmd_params.loadfileR, cmd_params.loadfileS,
            cmd_params.rkey, cmd_params.skey, cmd_params.r_size, cmd_params.s_size);
}

void
query5(const param_t cmd_params) {
    result_t *results;

    relation_t relC;
    relation_t relO;
    relation_t relL;
    relation_t relS;
    relation_t relN;
    relation_t relR;

    relation_payload_t relPlC;
    relation_payload_t relPlO;
    relation_payload_t relPlL;
    relation_payload_t relPlS;
    relation_payload_t relPlN;
    relation_payload_t relPlR;

    // TODO: refactor
    char *customer_file = "/home/xtra/AllianceDB/dbgen/dataset/orders.tbl";
    int c_size = 150000;

    char *orders_file = "/home/xtra/AllianceDB/dbgen/dataset/orders.tbl";
    int o_size = 1500000;

    char *lineitem_file = "/home/xtra/AllianceDB/dbgen/dataset/lineitem.tbl";
    int l_zise = 6001215;

    char *supplier_file = "/home/xtra/AllianceDB/dbgen/dataset/supplier.tbl";
    int s_size = 10000;

    char *nation_file = "/home/xtra/AllianceDB/dbgen/dataset/nation.tbl";
    int n_size = 25;

    char *region_file = "/home/xtra/AllianceDB/dbgen/dataset/region.tbl";
    int r_size = 5;

    // In this part, I think at beginning, all table will have a initial keyby,
    //    // then join with corresponding table with the specified key.
    //    // TODO: should have a method to re-keyby the relation, i.e. change the key in the relation.
    //    // Psudo Code:
    //    // relation1 = load_relation(file, keyby=0) # relation1: a1, a2, a3
    //    // relation2 = load_relation(file, keyby=0) # relation2: b1, a1, b2, b3
    //    // relation3 = load_relation(file, keyby=0) # relation3: c1, b1, c2, c3
    //    // relation2 = relation2.keyby(1)
    //    // relation1, relation2 = join(relation1, relation2)
    //    // relation3.keyby(1)
    //    // relation2, relation3 = join(relation2, relation3)
    //    // final joined tuples in relation2 is the actual final results for join, use this to do aggregation.

//    // c_custkey = o_custkey
//    results = join_from_file(cmd_params, customer_file, orders_file, 0, 1, c_size, o_size);
//    // l_orderkey = o_orderkey
//    results = join_from_file(cmd_params, lineitem_file, orders_file, 0, 0, l_zise, o_size);
//    // l_suppkey = s_suppkey
//    results = join_from_file(cmd_params, lineitem_file, supplier_file, 2, 0, l_zise, s_size);
//    // c_nationkey = s_nationkey
//    results = join_from_file(cmd_params, customer_file, supplier_file, 3, 3, c_size, s_size);
//    // s_nationkey = n_nationkey
//    results = join_from_file(cmd_params, supplier_file, nation_file, 3, 0, s_size, n_size);
//    // n_regionkey = r_regionkey
//    results = join_from_file(cmd_params, nation_file, region_file, 2, 0, n_size, r_size);

//    createRelation(&relC, &relPlC, 0, cmd_params, customer_file, c_size, cmd_params.r_seed);
//    createRelation(&relO, &relPlO, 1, cmd_params, orders_file, o_size, cmd_params.r_seed);
//    createRelation(&relL, &relPlL, 0, cmd_params, lineitem_file, l_zise, cmd_params.r_seed);
//    createRelation(&relS, &relPlS, 0, cmd_params, supplier_file, s_size, cmd_params.r_seed);
//    createRelation(&relN, &relPlN, 0, cmd_params, nation_file, n_size, cmd_params.r_seed);
//    createRelation(&relR, &relPlR, 0, cmd_params, region_file, r_size, cmd_params.r_seed);

    createRelation(&relC, &relPlC, 0, cmd_params, NULL, 10, cmd_params.r_seed);
    createRelation(&relO, &relPlO, 0, cmd_params, NULL, 10, cmd_params.r_seed);
    createRelation(&relL, &relPlL, 0, cmd_params, NULL, 10, cmd_params.r_seed);

    DEBUGMSG("relC [aligned:%d]: %s", is_aligned(relC.tuples, CACHE_LINE_SIZE),
             print_relation(relC.tuples, 10).c_str())
    DEBUGMSG("relO [aligned:%d]: %s", is_aligned(relO.tuples, CACHE_LINE_SIZE),
             print_relation(relO.tuples, 10).c_str())
    DEBUGMSG("relL [aligned:%d]: %s", is_aligned(relL.tuples, CACHE_LINE_SIZE),
             print_relation(relL.tuples, 10).c_str())

     // TODO: add a new method to deal with multi-source join
    results = (*QUERY5)(&relC, &relO, &relL, &relPlC, &relPlO, &relPlL, cmd_params.nthreads);

}
