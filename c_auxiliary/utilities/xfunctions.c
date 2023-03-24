#include "xfunctions.h"

// collezione di chiamate a funzioni di sistema con controllo output
// i prototipi sono in xerrori.h


// termina un processo con eventuale messaggio d'errore
void termina(const char *messaggio) {
    if(errno==0)  fprintf(stderr,"== %d == %s\n",getpid(), messaggio);
    else fprintf(stderr,"== %d == %s: %s\n",getpid(), messaggio,
                 strerror(errno));
    exit(1);
}

// termina un processo con eventuale messaggio d'errore + linea e file
void xtermina(const char *messaggio, int linea, char *file) {
    if(errno==0)  fprintf(stderr,"== %d == %s\n",getpid(), messaggio);
    else fprintf(stderr,"== %d == %s: %s\n",getpid(), messaggio,
                 strerror(errno));
    fprintf(stderr,"== %d == Linea: %d, File: %s\n",getpid(),linea,file);

    exit(1);
}



// ---------- operazioni su FILE *
FILE *xfopen(const char *path, const char *mode, int linea, char *file) {
    FILE *f = fopen(path,mode);
    if(f==NULL) {
        perror("Errore apertura file");
        fprintf(stderr,"== %d == Linea: %d, File: %s\n",getpid(),linea,file);
        exit(1);
    }
    return f;
}

// ----------- operazioni su file descriptors
void xclose(int fd, int linea, char *file) {
    int e = close(fd);
    if(e!=0) {
        perror("Errore chiusura file descriptor");
        fprintf(stderr,"== %d == Linea: %d, File: %s\n",getpid(),linea,file);
        exit(1);
    }
    return;
}

int xopen(char* path, int flags, int linea, char* file) {
    int e = open(path, flags);
    if(e<0) {
        perror("Errore apertura file descriptor");
        fprintf(stderr,"== %d == Linea: %d, File: %s\n",getpid(),linea,file);
        exit(1);
    }
    return e;
}

void xwrite(int fd, long* input, int dimension, int linea, char* file) {
    int e = write(fd, input, dimension);
    if(e < dimension) {
        perror("Errore scrittura su file descriptor");
        fprintf(stderr,"== %d == Linea: %d, File: %s\n",getpid(),linea,file);
        exit(1);
    }
    return;
}


// -------------- operazioni su processi
pid_t xfork(int linea, char *file)
{
    pid_t p = fork();
    if(p<0) {
        perror("Errore fork");
        fprintf(stderr,"== %d == Linea: %d, File: %s\n",getpid(),linea,file);
        exit(1);
    }
    return p;
}

pid_t xwait(int *status, int linea, char *file)
{
    pid_t p = wait(status);
    if(p<0) {
        perror("Errore wait");
        fprintf(stderr,"== %d == Linea: %d, File: %s\n",getpid(),linea,file);
        exit(1);
    }
    return p;
}


int xpipe(int pipefd[2], int linea, char *file) {
    int e = pipe(pipefd);
    if(e!=0) {
        perror("Errore creazione pipe");
        fprintf(stderr,"== %d == Linea: %d, File: %s\n",getpid(),linea,file);
        exit(1);
    }
    return e;
}