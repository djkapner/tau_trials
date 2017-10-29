testtype?=single
outdir=tau_output
CC=tau_cc.sh -optWrappersDir="./somelib_wrapper" 

all: libmytaulib.a libmygcclib.a random.o random

libmygcclib.a: mygcclib.c
	gcc -c $<
	ar -cvq $@ mygcclib.o
	tau_gen_wrapper mygcclib.h libmygcclib.a

libmytaulib.a: mytaulib.c
	$(CC) -c $<
	ar -cvq $@ mytaulib.o

random.o: random.c
	$(CC) -c $< -I./

random: random.o
	$(CC) -optTauWrapFile="mygcclib_wrapper/link_options.tau" -o $@ $< -L./ -lmytaulib 

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
	rm -f *.o
	rm -f somelib.o
	rm -f lib*.a
	rm -rf $(outdir)
	rm -rf mygcclib_wrapper


