# Name: (Ya) Naweeya Chutiraka
# UFID: 
# Gator ID:

THIS IS MINIX 3.2.1 DONE THROUGH ORACLE VIRTUAL BOX.

(For what approaches I have taken, challenges, failures, what I accomplished, and what I did not accomplish, and what I learn is located in a separate report file.)


Please note this in this projects, I have modified many files (more than project1). And this includes files that I had to modify when I took the wrong approaches too.

I do not have a makefile included in this submission as I do not see it listed under deliverables in the project description.

But I will have
- source codes
- manpages
- patch files
- report

Please note that my patch files were created based of my minix version after project 1.
That means in some files, there are dependencies that come from project 1 as well.
I decided to submit my files for project 1 as well just in case those dependencies are required when you compile your minix. (this is located in folder called proj1)

please make sure to place those project1 files in appropriate locations 
(for example, files from folder proj1/servers will go into /usr/src/servers/pm
files from folder proj1/libc/ will go into /usr/src/lib/libc/
files in man2 will go to usr/man/man2)

I am sorry for the inconvenience. This is because I did not have a snapshot of my minix before I started project 1.

please run the following commands for running my test program

cc -c test_proj2.c
cc test_proj2.o -o test_proj2
./test_proj2

I also have my manpages for plog_state_start and plog_state_stop. They are meant to go into /usr/man/man2

There are some files in proj1 folder that are there only for earlier testing purposes, such as printmsg or printppid. If you do not need to to grade them, feel free to ignore them
