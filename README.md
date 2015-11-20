#rshell

This project is a basic shell written in C++ and acts as a pseudo shell.  It does not fully replicate the processes a basic shell can do, such as the cd command.

#hw1

Objective is to write a command shell called rshell that can print a command and read an executable command.  The goal is to utilize connectors to excecute multiple commands at once.  Could not get connectors working.

#hw2

Objective is you utilize and create the test command to the rshell.  A build-upon from hw1.  Using test or the symbolic equivalent [], we test to find file or directories.  Could not get connectors and parentheses working.

#Bugs:

* Connectors are not supported and will not function correctly
* There is no support for autofill when pressing TAB key
* Quotes are not supported and are instead ignored
* There is a Segmentation Fault when only spaces are inputted and followed by an ENTER key
* The UP arrow and DOWN arrow keys do no filter through previous commands
* Did not get the parentheses correctly functioning
* Parentheses cause an error and will not function
