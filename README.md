# diskScheduler
## Class
CPSC 380: Operating Systems  
Spring 2020  
05/02/2020

## Author
Matt Raymond  
raymo116@mail.chapman.edu  
2270559  

## Usage
```
gcc -ansi -w diskScheduler.c -o diskScheduler
./diskScheduler <initial cylinder position> <cylinder request file>
```

## Questions
- What is the initial head direction
    - move to the right in all scans/looks

## Sources
- **General C**
    - https://stackoverflow.com/questions/9410/how-do-you-pass-a-function-as-a-parameter-in-c
    - https://stackoverflow.com/questions/5309859/how-to-define-an-array-of-functions-in-c
- **FCFS**
    - https://www.guru99.com/fcfs-scheduling.html
-**SSTF**
    - https://www.geeksforgeeks.org/disk-scheduling-algorithms/
    - https://en.wikipedia.org/wiki/Shortest_seek_first
- **SCAN**
    - https://www.gatevidyalay.com/scan-algorithm-disk-scheduling-algorithms/
    - https://en.wikipedia.org/wiki/Elevator_algorithm
    - https://www.geeksforgeeks.org/scan-elevator-disk-scheduling-algorithms/
    - https://www.cs.usask.ca/faculty/makaroff/cgi-bin/disk_sched.pl
- **C-SCAN**
    - https://www.geeksforgeeks.org/disk-scheduling-algorithms/
- **LOOK**
    - https://www.geeksforgeeks.org/disk-scheduling-algorithms/
    - https://en.wikipedia.org/wiki/LOOK_algorithm
    - https://www.gatevidyalay.com/look-algorithm-disk-scheduling-algorithms/
- **C-LOOK**
    - https://www.geeksforgeeks.org/disk-scheduling-algorithms/
