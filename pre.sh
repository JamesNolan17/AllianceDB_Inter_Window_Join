#!/bin/bash

exp_dir="/data1/xtra"
L3_cache_size=20971520

# download and mv datasets to exp_dir
wget https://www.dropbox.com/s/64z4xtpyhhmhojp/datasets.tar.gz
tar -zvxf datasets.tar.gz
rm datasets.tar.gz
mkdir -p $exp_dir
mv datasets $exp_dir


## Create directories on your machine.
mkdir -p $exp_dir/results/breakdown/partition_buildsort_probemerge_join
mkdir -p $exp_dir/results/breakdown/partition_only
mkdir -p $exp_dir/results/breakdown/partition_buildsort_only
mkdir -p $exp_dir/results/breakdown/partition_buildsort_probemerge_only
mkdir -p $exp_dir/results/breakdown/allIncludes

mkdir -p $exp_dir/results/figure
mkdir -p $exp_dir/results/gaps
mkdir -p $exp_dir/results/latency
mkdir -p $exp_dir/results/records
mkdir -p $exp_dir/results/timestamps

cp cpu-mapping.txt $exp_dir