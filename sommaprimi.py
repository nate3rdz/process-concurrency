#!/usr/bin/env python3

"""
esercizio sulle named pipe
  legge gli interi dal file di testo argv[1] e li
  scrive nella pipe somma_down
  al termine, aspetta dalla pipe somma_up le somme dei primi
  provenienti dai processi ausiliari
"""
import sys, os, struct, time, select

"""
funzioni utili
  os.mkfifo(path)						# crea una named fifo
  os.unlink(path)						# cancella un file
  os.open(path,flags)       # analoga alla open dal C
  os.read(fd,n)             # leggedal file descriptor fd
	struct.pack(format,val)   # trasforma int -> sequenza byte
  struct.unpack(format,bs)  # trasforma sequenza byte -> int
"""

# Variabili globali con i nomi delle pipe da usare
Pipeup = "somma_up"
Pipedown = "somma_down"


def main(filename):
    os.mkfifo(Pipedown, 0o666)
    os.chmod(Pipedown, 0o666)

    os.mkfifo(Pipeup, 0o666)
    os.chmod(Pipeup, 0o666)

    pid = os.fork()
    if pid == 0:
        if os.execvp("./auxiliary", ["auxiliary", f"{sys.argv[2]}", Pipeup, Pipedown]) == -1: print("Errore nell'apertura del processo ausiliario")
    else:
        tot = 0
        fd = os.open(Pipedown, os.O_WRONLY) #lets open the write pipe to the auxiliary process

        with open(filename, "r") as f: #lets send down the pipe all the data read from the file
            for linea in f:
                # converte linea in intero
                intero = int(linea)
                # converto intero in sequenza di byte scrive nella pipe
                bs = struct.pack("<q", intero)
                os.write(fd, bs)
                tot += 1
            os.close(fd)
        print(f"{tot} integers read from the file and wrote in the down pipeline")

        count = 0
        up = os.open(Pipeup, os.O_RDONLY)
        while True:
            bs = os.read(up, 8) # legge fino a 4 byte mettendoli in un bytarray
            if len(bs) == 0:  # non c'e' nessuno che scrive: termina
                break

            count = struct.unpack("<q", bs)[0] # converte gli 8 byte letti in un intero e lo stampa
        print(f"[Parent PID: {os.getpid()}] total sum of primal number returned from subprocesses: {count}", file=sys.stderr)

        os.unlink(Pipedown)
        os.unlink(Pipeup)


# lancio di main()
if len(sys.argv) != 3:
    print("Uso:\n\t %s nome_file_interi n_threads" % sys.argv[0])
else:
    main(sys.argv[1])

