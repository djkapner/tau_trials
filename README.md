# tau_trials

learning tau by example

according to tau documentation:
https://www.cs.uoregon.edu/research/tau/docs/usersguide/ch01.html

there are 3 ways to profile:
interposition: use tau_exec in the mpiexec call. nothing special needed for compile. only shpws mpi events.
compiler: use compiler directives in the code.
source: use PDT to automatically instrument the code: https://www.cs.uoregon.edu/research/pdt/home.php

