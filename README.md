# process-concurrency


HOW TO USE:

1) Run the file_primi.py script, selecting a number of integers that you want to generate on a new file
2) Run the compile bash script to compile the c auxiliary program
3) Run the sommaprimi.py script, selecting the file that you've generated through the file_primi script and a number of process. I recommend to use a number < 11 (or the number of logical threads of your machine)
4) The program, using a concurrent algorithm, will generate n processes and through some named pipes will calculate the sum of all the primal numbers in the given gile.
