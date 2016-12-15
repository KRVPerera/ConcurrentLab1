# Concurrent Lab 1
##CS4532 Concurrent Programming Take Home Lab 1

Idea of the lab is to create three different implementations of a linked list. 
+ Serial version
+ Version with a mutex for the whole list
+ Read-Write lock version

Uses `pthread.h` for thread creation and mutual exclusion. Each run will default run with 2 thread if parallel version and gather 100 samples and using standard deviation and mean decide how many
test cases needed to be sampled to get an accuracy of 5% and 95% confidence interval. If it is
larger than 100, program will automatically rerun for the desired number of times until it reaches 5% accuracy and 95% confidence level.
###Building the Project
Create a folder inside the project. eg : build. Then within the folder
run `cmake ..`, In linux this will usually create a Makefile to compile the project. 
You can run `make` within the folder to build the project.

###Command line arguments
After building it will create a executable named "ConcurrentTHLab_1".
You can run it and get the help list for the command line arguments by,
`./ConcurrentTHLab_1 -h`

| argument | effect                                             |
|----------|----------------------------------------------------|
| -s       | will run the serial version                        |
| -g       | will run the mutex version                         |
| -r       | will run the read-write lock version               |
| -t N     | will change the number of threads                  |
| -i       | fraction of insert operations **eg: 0.50**         |
| -d       | fraction of delete operations **eg: 0.25**         |
| -n N     | will change the population size of initial list    |
| -m N     | will change the number of total operations         |

default values are, number of threads 2, insert fraction 0.99, delete
fractions are 0.005, membership fraction will be calculated automatically.
Population size is 1000 and total number of operations is 10,000.

