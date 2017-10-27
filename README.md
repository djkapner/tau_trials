# tau_trials

 "TAU Performance System® is a portable profiling and tracing toolkit for performance analysis of parallel programs written in Fortran, C, C++, UPC, Java, Python."
 https://www.cs.uoregon.edu/research/tau/home.php

# learning tau by example

according to tau documentation (https://www.cs.uoregon.edu/research/tau/docs/usersguide/ch01.html), there are 3 ways to profile:
1. interposition: use tau_exec in the mpiexec call. nothing special needed for compile. only shpws mpi events.
2. compiler: use compiler directives in the code.
3. source: use PDT to automatically instrument the code: https://www.cs.uoregon.edu/research/pdt/home.php

I believe that both 2 and 3 are covered in the compiler folder and example.

These examples were run with these packages installed:
- mpich3.2
- pdt (see https://www.cs.uoregon.edu/research/tau/downloads.php)
- tau (see https://www.cs.uoregon.edu/research/tau/downloads.php)
- jumpshot (http://www.mcs.anl.gov/research/projects/perfvis/download/index.htm#slog2sdk)

The goal here is to get some visualization of what's going on, with meaningful, user-defined execution blocks and events:
![Alt text](./images/jumpshot_output.png?raw=true "Jumpshot visualization")
