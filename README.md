
Department of Computing and Information Systems
COMP30023: Computer Systems
Project 1

Due date: No later than 9:00am on Monday, April 13.
Weight: 15%

Project Overview
The aim of this project is to increase your familiarity with issues in memory management and 
swapping (and to a limited extent process scheduling).
Submissions that do not compile and run on the School of Engineering student machines (eg. dimefox
or nutmeg) may receive zero marks.

Part A - 10 marks

Your task is to write a simulation program written in C, which takes processes of different sizes 
and loads them into memory using one of four different algorithms and when needed, swaps processes 
out to create a sufficiently large hole for a new process to come into memory.
The four different algorithms to be used are first fit, best fit, next fit and worst fit. Assume 
that memory is partitioned into contiguous segments, where each segment is either occupied by a 
process or is a hole (a contiguous area of free memory). The free list is a list of all the holes. 
Holes in the free list are kept in ascending order of memory address. Adjacent holes in the free 
list should be merged into a single hole.
The four algorithms to be used for placing a process in memory are:

• First fit: First fit searches the free list from the beginning, and uses the first hole large 
enough to satisfy the request. If the hole is larger than necessary, it is split, with the process 
occupying the lower address range portion of the hole and the remainder being put on the free list.
• Best fit: Chooses the smallest hole from the free list that will satisfy the request. If multiple 
holes meet this criterion, choose the lowest address one in the free list. If the hole is larger 
than necessary, it is split, with the process occupying the lower address range portion of the hole 
and the remainder being put on the free list.
• Worst fit: Chooses the largest hole from the free list that will satisfy the request. If multiple 
holes meet this criterion, choose the earliest one in the free list. If the hole is larger than 
necessary, it is split, with the process occupying the lower address range portion of the hole and 
the remainder being put on the free list.
• Next Fit: This is like first fit, but begins searching the free list from the position where the 
previous hole was found. It if gets to the end of the free list without finding a large enough 
hole, it wraps around to the beginning.

The details of the behaviour of the simulation are described on the following pages. You 
implementation
must follow the sequence of events listed.

A process size file is a sequence of entries which describe an initial queue of processes waiting 
to be swapped into memory from disk. The first entry is the head of the queue and the last is the 
tail of the queue. Each entry consists of a (process-id, memory-size) pair. For example:

4 98
2 33
1 100
3 5

This models an initial queue where process 4 is at the head of the queue and is 98 MB in size, 
process 2 is second in the queue and is size 33 MB, process 1 is third in the queue and is size 100 
MB, etc.
Points to note:

• Each process id is a unique positive integer.
• Each process size is a positive integer ≤ m (the main memory size).

You may assume the input file being read in will always be in the correct format. The simulation 
should behave as follows:
• Parse the process file to obtain the initial queue of processes waiting to be swapped into 
memory.
• Assume memory is initially empty.
• Load the processes from the queue into memory, one by one, according to one of the four algo- 
rithms.
• If a process needs to be loaded, but there is no hole large enough to fit it, then processes 
should be swapped out, one by one, until there is a hole large enough to hold the process needing 
to be loaded.
• If a process needs to be swapped out, choose the one which has the largest size. If two processes 
have equal largest size, choose the one which has been in memory the longest (measured from the 
time it was most recently placed in memory).
• After a process has been swapped out, it is placed at the end of the queue of processes waiting 
to be swapped in.
• Once a process has been swapped out for the third time, we assume the process has finished and it 
is not re-queued. Note that not all processes will be swapped out for three times.
• The simulation should terminate once no more processes are waiting to be swapped into memory.

Your program should print out a line of the following form after each time a process has been 
swapped into memory

15 loaded, numprocesses=3, numholes=2, memusage=77%

where ‘15’ refers to the id of the process just loaded, ‘numprocesses’ refers to the number of 
processes currently in memory and ‘numholes’ refers to the number of holes currently in memory. 
‘memusage’ is a (rounded up) integer referring to the percentage of memory currently occupied by 
processes.

Your program must be called memswap. The name of the process size file should be specified at run 
time using a ‘-f’ filename option. The placement algorithm to be used should be specified using a 
‘-a’ algorithm name option, where algorithm name is one of {first,best,worst,next}. The size of 
main memory should be specified using a ‘-m’ memsize option, where memsize is an integer.

Part B – 5 marks

In this part of the project, you are required to investigate how the algorithms work in further 
detail. You should design and run small simulation experiments as part of your investigation and 
provide answers to the two questions listed below.
Your report, named report.txt, will be ≤ 500 words in length using plain text format. Ideally, your 
report will include a clear description of your simulation experiments; table(s) of results and a 
discussion of your findings, plus the answers to each of the questions.
You must add the file report.txt to your SVN repository.

1. Consider the following argument:
It really does not matter which of the algorithms {next, worst, first, best} fit is used for memory 
placement. Eventually, the system will reach an equilibrium and all the algorithms will perform 
similarly.
Is this true? Explain and justify your answer.
2. (a challenging question) Let the number of segments of memory containing processes be Sm. Let 
the number of segments that containing holes be SH . Show on average, SH = Sm ÷ 2. List any 
assumptions you have made.

Submission details
Please include your name and login id in a comment at the top of each file.
Our plan is to directly harvest your submissions on the due date from your SVN repository.
https://svn.eng.unimelb.edu.au/comp30023/username/project1
You must submit program file(s), including a Makefile. Make sure that your makefile, header files 
and source files are added/committed. Do not add/commit object files or executables. Anything you 
want to mention about your submission, write a text file called README.
If you do not use your SVN repository for the project  you  will  NOT  have  a  submission  and  
may  be awarded zero marks. It should be possible to “checkout“ the SVN repository, then type make 
to produce the executable memswap.
Late submissions will incur a deduction of 2 mark per day (or part thereof).
If you submit late, you MUST email the lecturer, Michael Kirley <mkirley@unimelb.edu.au>. Failure 
to do will result in our request to sysadmin for a copy of your repository to be denied.
Extension policy: If you believe you have a valid reason to require an extension you must contact 
the lecturer, Michael Kirley <mkirley@unimelb.edu.au> at the earliest opportunity, which in most 
instances should be well before the submission deadline.
Requests for extensions are not automatic and are considered on a case by case basis. You will be 
required to supply supporting evidence such as a medical certificate.
Plagiarism policy: You are reminded that all submitted project work in this subject is to be your 
own individual work. Automated similarity checking software will be used to compare submissions. It 
is University policy that cheating by students in any form is not permitted, and that work 
submitted for assessment purposes must be the independent work of the student concerned.
Using SVN is an important step in the verification of authorship.
Assessment
This project is worth 15% of your final mark for the subject. Your submission will be tested and 
marked with the following criteria:
Code:
• 2 points for the first fit option giving the expected output.
• 2 points for best fit option giving the expected output.
• 2 points for worst fit option giving the expected output.
• 2 points for next fit option giving the expected output.
• 2 points for the coding style, design and appropriate documentation (clarity of code is 
important).
Note: a diff command will be used to check program output against the expected output.
Report:
• 3 points for your answers to question B1 (2 points for your discussion + 1 point for supporting
evidence based on simulation experiments)
• 2 points for your answer to question B2
