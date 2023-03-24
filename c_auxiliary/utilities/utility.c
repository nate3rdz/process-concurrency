#include "utility.h"

bool primal(int n)
{
    if(n<2) return false;
    if(n%2==0) {
        if(n==2)  return true;
        else return false; }
    for (int i=3; i*i<=n; i += 2)
        if(n%i==0) return false;
    return true;
}

long primal_long_integer_buffer(int fd) {
    long count = 0;

    while(true) { // reads the buffer
        long buffer;
        ssize_t e = read(fd, &buffer, sizeof(long));
        if(e <= 0) break; // if the buffer is empty, exit the loop
        if(primal(buffer)) count += buffer;
    }

    return count;
}

long read_long_integer_buffer(int fd) {
    long count = 0;

    while(true) { // reads the buffer
        long buffer;
        ssize_t e = read(fd, &buffer, sizeof(long));
        if(e <= 0) break; // if the buffer is empty, exit the loop
        else count += buffer;
    }

    return count;
}