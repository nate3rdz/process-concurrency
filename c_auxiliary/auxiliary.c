#include "utilities/xfunctions.h"

int main(int argc, char *argv[]) {
    if(argc != 4) {
        printf("\nUsage: \n\t%s N_PROCESS PIPE_UP PIPE_DOWN\n", argv[0]);
        exit(1);
    }

    assert(atoi(argv[1]) > 0);


    mkfifo(INTERCHANGE_PIPE, 0666); // lets create the pipe that allows the sons of this process to communicate with the process

    long count = 0;

    for(int i = 1; i <= atoi(argv[1]); i++) {
        pid_t pid = xfork(__LINE__, __FILE__);
        if(pid == 0) { // I'm a son
            long part_count = 0;

            int down_fifo_fd = xopen(argv[3], O_RDONLY, __LINE__, __FILE__); // First, lets open the pipe down
            part_count += primal_long_integer_buffer(down_fifo_fd);
            xclose(down_fifo_fd, __LINE__, __FILE__); // close the pipe down when the read is done

            printf("\n[Subprocess PID: %d] Partial sum acquired: %ld\t\n", getpid(), part_count);

            // now writes the part_count on the buffer
            int interchange = xopen(INTERCHANGE_PIPE, O_WRONLY, __LINE__, __FILE__);

            ssize_t e = write(interchange, &part_count, sizeof(long));
            if(e != sizeof(long)) {
                xclose(interchange, __LINE__, __FILE__);
                xtermina("Error occurred when doing write back on the result from the auxiliary process", __LINE__, __FILE__);
            }

            xclose(interchange, __LINE__, __FILE__);

            exit(0);
        }
    }

    int interchange = xopen(INTERCHANGE_PIPE, O_RDONLY, __LINE__, __FILE__); // opens the read pipeline

    wait(P_ALL); // waits for all the childrens to have finished with writings task..
    count += read_long_integer_buffer(interchange);

    xclose(interchange, __LINE__, __FILE__); // close the pipeline and deletes the file.

    // Lets open the up pipe
    int up_fifo_fd = xopen(argv[2], O_WRONLY, __LINE__, __FILE__);
    xwrite(up_fifo_fd, &count, sizeof(long), __LINE__, __FILE__); // Write back the result on the pipeline
    xclose(up_fifo_fd, __LINE__, __FILE__);

    if(remove(INTERCHANGE_PIPE) != 0) xtermina("\nError while deleting the interchanging pipeline file.", __LINE__, __FILE__);
    exit(0);
}