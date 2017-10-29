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

text profiling :\
$ cd tau_output \
$ pprof

visual profiling :\
$ cd tau_output \
$ paraprof

trace visualization:\
$ cd tau_output \
$ jumpshot tau.slog2

