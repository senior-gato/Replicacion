#include "mpi.h"
#include <cstdlib>
#include <iostream>
#include <math.h>
#include <sstream>

using namespace std;

/**
 * Wrapper function around MPI_Allreduce (leave this unchanged)
 * @param sendbuf Send buffer containing count doubles (input)
 * @param recvbuf Pre-allocated receive buffer (output)
 * @param count Number of elements in the send and receive buffers
 */
void allreduce(double *sendbuf, double *recvbuf, int count)
{
	MPI_Allreduce(sendbuf, recvbuf, count, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);
}

/**
 * Wrapper function around MPI_Allreduce (implement reduce-scatter / allgather algorithm)
 * @param sendbuf Send buffer containing count doubles (input)
 * @param recvbuf Pre-allocated receive buffer (output)
 * @param count Number of elements in the send and receive buffers
 */
void allreduceRSAG(double *sendbuf, double *recvbuf, int count)
{

	int thisProc, nProc;
    MPI_Comm_rank( MPI_COMM_WORLD, &thisProc );
    MPI_Comm_size( MPI_COMM_WORLD, &nProc );
    MPI_Status status;

    int dest;
    int width;
    double *myData = new double[count];
    for (int i=0; i<count; i++)
        myData[i]=sendbuf[i];

    double *temp_sendbuf = new double[count];
    for (int i=0; i<count; i++)
        temp_sendbuf[i]=sendbuf[i];

    int nPhases = log2(nProc);

    for (int p = 0; p<nPhases; p++){
        width = (count/pow(2, p+1));

        if (thisProc%((int)pow(2, p+1))<(int)pow(2, p+1)/2){
            dest = thisProc + pow(2,p);
            for (int i=0; i<width; i++)
                temp_sendbuf[i]=myData[i+width]; //second half of the message
            MPI_Send(temp_sendbuf, width, MPI_DOUBLE, dest, 0, MPI_COMM_WORLD);
            MPI_Recv(recvbuf, width, MPI_DOUBLE, dest, 1, MPI_COMM_WORLD, &status);

            for (size_t i = 0; i < width; i++)
                myData[i] += recvbuf[i]; //sum the replay
        }   
        else{
            dest = thisProc - pow(2,p);

            MPI_Recv(recvbuf, width, MPI_DOUBLE, dest, 0, MPI_COMM_WORLD, &status);

            
            for (int i=0; i<width; i++)
                temp_sendbuf[i]=myData[i]; //first half of the message

            for (size_t i = 0; i < width; i++)
                myData[i+width] += recvbuf[i]; //sum the replay
            MPI_Send(temp_sendbuf, width, MPI_DOUBLE, dest, 1, MPI_COMM_WORLD);

            //Copy the second half on the first half
            for (size_t i = 0; i < width; i++)
                myData[i]=myData[i+width];
        }
    }
    for (int p = nPhases-1; p>=0; p--){
        width = (count/pow(2, p+1));
        if (thisProc%((int)pow(2, p+1))<(int)pow(2, p+1)/2){
            dest = thisProc + pow(2,p);
            for (int i=0; i<width; i++)
                temp_sendbuf[i]=myData[i];
            MPI_Send(temp_sendbuf, width, MPI_DOUBLE, dest, 0, MPI_COMM_WORLD);
            MPI_Recv(recvbuf, width, MPI_DOUBLE, dest, 1, MPI_COMM_WORLD, &status);

            for (size_t i = 0; i < width; i++)
                myData[i+width] = recvbuf[i];
        }   
        else{
            dest = thisProc - pow(2,p);

            MPI_Recv(recvbuf, width, MPI_DOUBLE, dest, 0, MPI_COMM_WORLD, &status);
            
            for (int i=0; i<width; i++)
                temp_sendbuf[i]=myData[i];

            
            for (size_t i = 0; i < width; i++)
                myData[i+width] = myData[i];

            for (size_t i = 0; i < width; i++)
                myData[i] = recvbuf[i];
            MPI_Send(temp_sendbuf, width, MPI_DOUBLE, dest, 1, MPI_COMM_WORLD);

        }
    }

    for (size_t i = 0; i < count; i++)
        recvbuf[i] = myData[i];

    delete [] myData;
    delete [] temp_sendbuf;

}

int main(int argc, char* argv[])
{
	int thisProc;
    int nProc = 1000000;
	
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &thisProc);
	MPI_Comm_size(MPI_COMM_WORLD, &nProc);

	// initialize sendbuf
	double *sendbuf = new double[nProc];

	for (size_t i = 0; i < nProc; i++)
        sendbuf[i] = (i+1)*(thisProc+1);

    // initialize recvbuf
    double *recvbuf = new double[nProc];
   
	allreduceRSAG(sendbuf, recvbuf, nProc);

    /*
    double *recvbufGround = new double[nProc];
    allreduce(sendbuf, recvbufGround, nProc);
    allreduce(sendbuf, recvbuf, nProc);
    bool test = true;
    for (int i=0; i<nProc; i++){
        if (recvbuf[i]!=recvbufGround[i])
            test=false;
    }
    if (test)
        cout<<"Test passed"<<endl;
    else
        cout<<"Test failed"<<endl;
    */

	// optionally: write test code
	// (this is not required as we will only test the 
	// allreduceRSAG implementation itself.

	MPI_Finalize();
	exit(EXIT_SUCCESS);
}