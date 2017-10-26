#include <mpi.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include "./mytaulib.h"
#include "./mygcclib.h"
#include "TAU.h"
#define RMAX 10000000

long random_processing(int,int);

int main(int argc, char** argv) {
    long ntrial;
    int i;
    MPI_Request send_request,recv_request;
    MPI_Status status;

    // Initialize the MPI environment
    MPI_Init(NULL, NULL);

    // Get the number of processes
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    // Get the rank of the process
    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    // Get the name of the processor
    char processor_name[MPI_MAX_PROCESSOR_NAME];
    int name_len;
    MPI_Get_processor_name(processor_name, &name_len);

    int mseed,seed;

    //everyone is waiting for a communication from the master, non-blocking
    MPI_Irecv(&seed, 1, MPI_INT, 0, 0, MPI_COMM_WORLD,&recv_request); //workers receive
 
    //have the master seed the workers, and itself with a random #
    if (world_rank==0){
        srand(time(NULL));
        for (i=0;i<world_size;i++){
            mseed = rand() % 1000000;
            MPI_Send(&mseed, 1, MPI_INT, i, 0, MPI_COMM_WORLD);  //seeding workers
        }
    }

    long mntrial;

    //everyone runs a function and sends the results
    MPI_Wait(&recv_request,&status);
    ntrial = libfunc_compwith_tau(world_rank);
    MPI_Isend(&ntrial, 1, MPI_LONG, 0, 0, MPI_COMM_WORLD,&send_request); //workers send in their results
    if (world_rank == 0) {
        for (i=0;i<world_size;i++){
            MPI_Recv(&mntrial, 1, MPI_LONG, i, 0, MPI_COMM_WORLD,MPI_STATUS_IGNORE); //master receives results
            printf("Process 0 received number %ld from process %d\n",mntrial,i);
        }
    }

    ntrial = libfunc_compwith_gcc(world_rank);
    MPI_Isend(&ntrial, 1, MPI_LONG, 0, 0, MPI_COMM_WORLD,&send_request); //workers send in their results
    if (world_rank == 0) {
        for (i=0;i<world_size;i++){
            MPI_Recv(&mntrial, 1, MPI_LONG, i, 0, MPI_COMM_WORLD,MPI_STATUS_IGNORE); //master receives results
            printf("Process 0 received number %ld from process %d\n",mntrial,i);
        }
    }

    ntrial = random_processing(seed,(int)RMAX);
    MPI_Isend(&ntrial, 1, MPI_LONG, 0, 0, MPI_COMM_WORLD,&send_request); //workers send in their results
    if (world_rank == 0) {
        for (i=0;i<world_size;i++){
            MPI_Recv(&mntrial, 1, MPI_LONG, i, 0, MPI_COMM_WORLD,MPI_STATUS_IGNORE); //master receives results
            printf("Process 0 received number %ld from process %d\n",mntrial,i);
        }
    }

    // Finalize the MPI environment.
    MPI_Finalize();

}

long random_processing(int seed,int ndec){
    //keep going until a random number is the same as the first one 
    int target,secondtarget,trial;
    long ntrial;
    int world_rank;
    double x;
   
    TAU_REGISTER_EVENT(ue1, "My event"); 
    srand(seed);
    target = rand() % ndec;
    secondtarget = rand() % ndec;
    trial = rand() % ndec;
    ntrial = 1;
    while (trial!=target){
        trial = rand() % ndec;
        ntrial++;
        if (trial==secondtarget){
            TAU_EVENT(ue1,ntrial);
        }
    }
    
    return ntrial;
}


