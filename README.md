# How to Reproduce Our Experimental Results?

All of our experiments can be automatically reproduced by calling a few pre-prepared scripts.

## TODO

1. correct name in all scripts (e.g., drawing which figure.).
2. clean all data path, do not use fixed "/data1/xtra/...", both in scripts and code.  - roughly done, need to be tested.
3. move all control variables into a dedicated header file "control.hpp". Currently, they are scattered in multiple files including common_functions.h perf_counter.h, params.h
4. `modprobe msr` should be applied before run pcm.
5. draw figure scripts has not automated yet.
6. create a auto-deploy scripts in the end.
7. Auto install all required lib and tools. Auto config all required configurations.
8. All figure scripts still uses hardcoded path /data1/xtra.

## Third-party Lib

1. tex font rendering:

```shell
sudo apt-get install texlive-fonts-recommended texlive-fonts-extra
sudo apt-get install dvipng
sudo apt install font-manager
sudo apt-get install cm-super
```

2. python3:

```shell
sudo apt-get install python3
pip3 install numpy
pip3 install matplotlib
```

3.  NUMA library

```shell
sudo apt-get install -y libnuma-dev
```

4. Zlib

```shell
sudo apt install zlib1g-dev
```

5. python-tk

```shell
sudo apt-get install python-tk
```

6. perf

```shell
sudo apt install linux-tools-common
sudo apt install linux-tools-XXX # XXX is the kernel version of your linux, use uname -a to check it. e.g. 4.15.0-91-generic
sudo echo -1 > /proc/sys/kernel/perf_event_paranoid
```

### Prerequisite

1. Profiling only supports Intel CPUs.
2. Prepare cpu-mapping, and need to configure the path in hashing/cpu_mapping.txt. 
3. configure the results output path `exp_dir`, ensure you have permissions to access and modify the files inside.
4. configure cache size at `run_all.sh`.
5. prepare real world datasets, move them to the `exp_dir/datasets`, currently, the datasets path in scripts are fixed, need to update to configurable
6. `sudo bash run_all.sh`
7. Default parameters

| Parameters                       | Default         | Description                                   |
| -------------------------------- | --------------- | --------------------------------------------- |
| exp_dir                          | /data1/xtra     | path to save all results and generate figures |
| L3_CACHE_SIZE (rather important) | 20971520 (20MB) | size of l3 cache                              |
| PERF_COUNTERS/NO_PERF_COUNTERS   | No              | Unknown                                       |
| NO_TIMING/TIMING                 | No              | turn on/off breakdown timer                   |
| compile                          | 1               | compile the framework                         |
| Threads                          | 1 2 4 8         | experiments threads settings                  |

### Step 1

git clone the repo.

### Step 2
open hashing/scripts/benchmark.sh
   At Line 19, set L3 cache size according to your machine specification;
   run the benchmark.sh to conduct experiments.

Remember to adjust the following lines in the scripts according to your needs.
  1. Line 299 to 427. 
     conducts most experiments for four datasets and micro-datasets.
     At Line 296, set profile_breakdown=1 if we want to measure time breakdown.
  2. Line 432 to 477.
     conducts the scalability test for four datasets. In our paper, we only show the results of YSB as an example.
  3. Line 495 to 562.
      conducts the cache miss profiling study using YSB as an example. 
      For this test, you must run the script with sudo, i.e., "sudo ./benchmark.sh".
      After the test, you have to manually fill in the results to "profile_ysb_partition.py" and "profile_ysb_probe.py" corresponding to the test IDs.
  4. Line 566 to 673.
     conducts experiments for algorithm parameters tuning.
### Step 3
Repeat the experiments for sorting/scripts/benchmark.sh

### Step 4
call ./draw.sh to generate figures.

## Datasets

We have 4 real datasets that are compressed in [datasets.tar.gz](https://www.dropbox.com/s/64z4xtpyhhmhojp/datasets.tar.gz). Download and call tar -zvxf datasets.tar.gz to unzip those datasets.

We extracted the useful columns of those datasets, the one is joined key and another is timestamp.

DEBS: 

​	comments_key32_partitioned.csv: user_id|comments_payload

​	posts_key32_partitioned.csv: user_id|posts_payload

​	Reproduce results: open hashing/scripts/benchmark.sh, change the data path in line 274 and 275. 

YSB:

​	ad_events.txt: campaign_id|timestamp

​	campaigns_id.txt: campaign_id|campaign_payload

​	Reproduce results: open hashing/scripts/benchmark.sh, change the data path in line 246 and 247. 

Rovio:

​	1000ms_1t.txt: combined_id|payload|price|timestamp

​	Reproduce results: open hashing/scripts/benchmark.sh, change the data path in line 260 and 261. 

Stock: 

​	This dataset is not open-sourced out of privacy, the data structure is stockid|timestamp.



