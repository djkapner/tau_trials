testtype?=single
CC=mpicxx
outdir=tau_output

all: random

random: random.c
	$(CC) -o $@ $<

run:
	#single machine
	mpiexec ./random 
	#multi-machine
	mpiexec -hostfile /etc/hosts ./random 

runwithtau: runtau taufiles

ifeq ($(testtype),single)
runtau:
	mpiexec -np 4 tau_exec ./random 
	mkdir -p $(outdir)
else
runtau:
	mpiexec -np 60 -hostfile /etc/hosts tau_exec ./random 
	mkdir -p $(outdir)
endif

ifeq ($(TAU_TRACE),0)
taufiles:
	mv -f profile.* $(outdir)
else ifeq ($(TAU_TRACE),1)
taufiles:
	tau_treemerge.pl
	tau2slog2 tau.trc tau.edf -o tau.slog2
	mv -f *.edf *.trc $(outdir)
	mv -f tau.slog2 $(outdir)
else
taufiles:
	echo "looks like TAU_TRACE is not set"
endif	

clean:
	rm -f random
	rm -rf $(outdir)


