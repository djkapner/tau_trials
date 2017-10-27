This example shows how to use the interposition method, i.e. tau_exec.\
Two examples are included: for a single machine with 20 cores, and an mpi cluster with 3 nodes.\
The function call details are limited to mpi calls.\
\
\
To build:
$ make

To run:\
$ export TAU_TRACE=0\
$ make runwithtau\
$ export TAU_TRACE=1\
$ make runwithtau

text profiling (single or multi):\
$ cd tau_single \
$ pprof

visual profiling (single or multi):\
$ cd tau_single \
$ paraprof

trace visualization:\
$ cd tau_single \
$ jumpshot tau.slog2

