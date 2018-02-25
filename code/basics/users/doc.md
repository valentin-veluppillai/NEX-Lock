# user system
In this program, each user is represented by a line in a text file.
The program reads and saves the entire file, makes all needed changes and overrides the old file. To add/edit/remove users, the file can be modified manually.

## v0.2 [21.1.18]
managed to fix the system w/o too much troble, simply forgot to reset file
pointer (userData) after counting the lines in the lines in the file. fixed
that by resetting the file pointer.

### added
* test scenario, you can now enter an "uid", and the system decides
wheter to grant you access or not

* logfiles

## v0.1 [21.1.18]
* first attempts, code is working (after a bit of bug fixing)

### problems:
unexpected behaviour (as expected), fixed by rewriting the reading routine
