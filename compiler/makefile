CC=tau_cc.sh -optWrappersDir="./somelib_wrapper" 
#CC=mpicc

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

ifeq ($(TAU_TRACE),0)
runwithtau:
	#single machine
	mpiexec -np 20 ./random 
	mkdir -p tau_single
	mv -f profile.* tau_single
	#multi-machine
	mpiexec -np 60 -hostfile /etc/hosts ./random 
	mkdir -p tau_multi
	mv -f profile.* tau_multi
else ifeq ($(TAU_TRACE),1)
runwithtau:
	#single machine
	mpiexec -np 20 ./random 
	mkdir -p tau_single
	tau_treemerge.pl
	tau2slog2 tau.trc tau.edf -o tau.slog2
	mv -f *.edf *.trc tau_single
	mv -f tau.slog2 tau_single
	#multi-machine
	mpiexec -np 60 -hostfile /etc/hosts ./random 
	mkdir -p tau_multi
	tau_treemerge.pl
	tau2slog2 tau.trc tau.edf -o tau.slog2
	mv -f *.edf *.trc tau_multi
	mv -f tau.slog2 tau_multi
else
runwithtau:
	echo "looks like TAU_TRACE is not set"
endif	

clean:
	rm -f random
	rm -f *.o
	rm -f somelib.o
	rm -f lib*.a
	rm -rf tau_single
	rm -rf tau_multi
	rm -rf mygcclib_wrapper


