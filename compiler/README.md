This example shows how to use the compiler method.
The example shows the following capabilities of tau:
1. using tau_cc.sh so that user functions are traced and profiled, in addition to the mpi calls from the previous example.
2. having both main, and another function called from main.
3. calling a function from a linked library, which was also compiled by tau_cc.sh
4. calling a function from a linked library, which was compiled by gcc, and the wrapped by tau_gen_wrapper.
5. inserting a user event
\
Same as previous example:\
Two examples are included: for a single machine with 20 cores, and an mpi cluster with 3 nodes.\
The function call details are limited to mpi calls.\

\
To build:\
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

