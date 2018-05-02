### Hello
The purpose of this 'nasm' github repository is to fulfill the requirements for the "SecurityTube Linux Assembly Expert" certification: http://www.securitytube-training.com/online-courses/securitytube-linux-assembly-expert/

Student ID: SLAE64-1434

Despite being instructed to use the above link on my blog for the exam purposes, the course I am actually taking is the SLAE64, the 64 bit version of the course in other words. SLAE64 Url: http://www.securitytube-training.com/online-courses/x8664-assembly-and-shellcoding-on-linux/index.html

### Blog
You can find more detailed explanation for the assembly language source code that I have posted here on my blog.
http://a41L4.blogspot.ca

###Suggested Prerequisites

Now that I am finished the training, I can recommend some prerequisites.

***GNU Debugger***

The SLAE64 course that I purchased from SecurityTube came with the SGDE - SecurityTube GNU Debugger Expert course (14 videos, sample code, pdf of the slides etc.). This is actually a prerequisite of the SLAE64 training and is an added value that I don't think is mentioned on the SLAE64 advertising. While you should not need to study the GNU Debugger prior to taking the SGDE, doing the SGDE is a requirement for the SLAE64.

***C Programming***

Besides the SGDE, and even before doing the SGDE, I think it is beneficial if the student has learned to program in C. The SGDE takes you through tracing the program flow of a C program, as well as debugging a C program, and cracking some security within a C program. Besides this, Vivek Ramachandran in the SLAE64 course, often builds a program in C and then works on converting it to Assembler. Although you may not need to know C programming to follow what he is doing, understanding C programming will go a long way towards reproducing these same development steps in your own assembly language programming practice.

***Python Scripting***

While you don't really need to know Python to do the SLAE64 course, Vivek does use it in some of his examples and reveals how useful it can be while developing an assembler shellcode.

***Bash Scripting***

Working on the BASH command line and using some BASH code snippets pulled from the Internet allows Vivek to do much of what he demonstrates with the shellcoding examples. Vivek uses the BASH history, searching BASH history, tab completion, clearing the terminal (CTRL+L), echo, cat, ps, grep, for loops, the pipe "|", redirection of standard output ">", etc..

***Linux***

You should be comfortable working within Linux and especially on a terminal command line. Some security tools that it would help to be familiar with is netstat and nc (netcat ncat etc.), also the use of ssh (secure shell) etc..

***Virtualbox/VMware***

If you are not familiar with virtualization, virtual host, virtual guest etc. now is a good time to get some experience.

### Resources

- https://software.intel.com/en-us/articles/introduction-to-x64-assembly/
- http://www.nasm.us/doc/
- http://shell-storm.org/shellcode/

```
Take Care,
Rob
```
