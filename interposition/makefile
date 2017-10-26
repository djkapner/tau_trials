CC=mpicxx
all: random

random: random.c
	$(CC) -o $@ $<

run:
	#single machine
	mpiexec ./random 
	#multi-machine
	mpiexec -hostfile /etc/hosts ./random 

ifeq ($(TAU_TRACE),0)
runwithtau:
	#single machine
	mpiexec -np 20 tau_exec ./random 
	mkdir -p tau_single
	mv -f profile.* tau_single
	#multi-machine
	mpiexec -np 60 -hostfile /etc/hosts tau_exec ./random 
	mkdir -p tau_multi
	mv -f profile.* tau_multi
else
runwithtau:
	#single machine
	mpiexec -np 20 tau_exec ./random 
	mkdir -p tau_single
	tau_treemerge.pl
	tau2slog2 tau.trc tau.edf -o tau.slog2
	mv -f *.edf *.trc tau_single
	mv -f tau.slog2 tau_single
	#multi-machine
	mpiexec -np 60 -hostfile /etc/hosts tau_exec ./random 
	mkdir -p tau_multi
	tau_treemerge.pl
	tau2slog2 tau.trc tau.edf -o tau.slog2
	mv -f *.edf *.trc tau_multi
	mv -f tau.slog2 tau_multi
endif	

clean:
	rm -f random
	rm -rf tau_single
	rm -rf tau_multi


