cmake_minimum_required(VERSION 3.5.1)
project(AllianceDB)
set(CMAKE_CXX_STANDARD 11)

set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${./bin})
set (CMAKE_STATIC_LINKER_FLAGS -lnuma)


#set(CMAKE_CXX_FLAGS "-Wall -Wextra")
#set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -msse4.1")

add_executable(hashing main.cpp utils/types.h utils/generator.cpp utils/generator.h utils/perf_counters.cpp utils/perf_counters.h utils/cpu_mapping.cpp utils/cpu_mapping.h utils/genzipf.cpp utils/genzipf.h utils/lock.h utils/rdtsc.h utils/barrier.h utils/task_queue.h utils/config.h
        single_thread/blocking/npj_types.h single_thread/blocking/npj_params.h single_thread/blocking/no_partitioning_join.cpp single_thread/blocking/no_partitioning_join.h
        multiple_thread/parallel_radix_join.cpp multiple_thread/parallel_radix_join.h multiple_thread/prj_params.h)
target_link_libraries(hashing numa)

