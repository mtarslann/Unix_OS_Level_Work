# Unix_OS_Level_Work
### Unix Threads, Synchronization,Deadlock and Starvation Implementation

##### This project coded to carry out these conditions ( More details in pdf file ):
  Implement a C program that is explained below using Unix. You should implement a multi-threaded program that operates files that are filled with random numbers. Your program requires three types of threads:
  
        A. Cutting and Pasting threads.
        B. Prime number removing threads.
        C. Negative number removing threads.
        
  For your program; you will be given two types of resources (files).

    Resource type 1: Filled with integer numbers initially. Responsible threads should read and cut the content of a line of this file.


    Resource type 2: Empty initially. Responsible threads should append this file by pasting the lines that they already cut from Resource type 1.


  Type “A” threads should use two resources (any of one “Resource type 1” type file and one “Resource type 2” type file) at the same time. Without having both of “resources type 1” and “Resource type 2” thread cannot perform its task. Type “A” thread should cut and paste a single line at each time. Each type “A” thread should decide the total number of lines its going to cut/paste randomly. The random decision shouldn’t be less then 1 and greater than 10. 

  Type “B” and “C” threads are responsible of cleaning the negative and prime numbers in the files. These files could be “Resource type 1” or “Resources type 2” type of files. Therefore, thread types “B” and “C” can use “Resource type 1” and” Resource type 2” at any time. However, these threads should consume only one resource at a time. 

  NOTE 1: It is important that “Resource type 2” is going to be the file that has all the contents of “Resource type 1” type files and at the end all the “Resource type 1” type files should be empty. In addition, “Resource type 2” should be free of negative and prime numbers. This is the termination condition for your process.
