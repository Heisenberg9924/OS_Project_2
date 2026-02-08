\# Parallel Prime Generator.



\## Overview



This project computes prime numbers in a given range `\[start, end]` using multiple child processes to utilize multiple CPU cores. It also measures how execution time changes with the number of processes and visualizes the results using Python.



\## OS Concepts Used



\* \*\*Process creation (`fork()`)\*\*: The parent creates `n` child processes to run computations in parallel.

\* \*\*Work partitioning\*\*: The range `\[start, end]` is split into `n` chunks; each child handles one chunk.

\* \*\*Synchronization (`wait()`)\*\*: The parent waits for all children to finish before merging outputs.

\* \*\*Parallelism \& overhead\*\*: Demonstrates speedup up to core limits and diminishing returns due to scheduling/context switching.



\## How It Works



1\. Input: `start`, `end`, and `n` (number of child processes).

2\. Each child checks primes in its assigned subrange and writes to a separate file.

3\. Parent waits, merges results into `prime.txt`, and appends execution time to `time.txt`.



\## Python Automation \& Plotting



\* \*\*tester.py\*\* runs the C program repeatedly for different ranges and values of `n`.

\* Each run appends a line to `time.txt` in the format:



&nbsp; ```

&nbsp; start end n execution\_time

&nbsp; ```

\* A \*\*plot.ipynb\*\* reads `time.txt` and plots \*\*n vs execution time\*\* to analyze scaling.



\## Files



\* `prime\_gen.c` – Parallel prime generator (C, uses fork)

\* `plot.ipynb` – Python notebook that reads from time.txt and plots \*\*n vs time taken\*\*

\* `tester.py` – Automates experiments

\* `time.txt` – Generated timing data (not tracked)

\* `prime.txt` – Merged primes output (not tracked)

\* `.gitignore` – Ignores generated files



\## Build \& Run



Compile:



```

gcc prime\_gen.c -o primes -lm

```



Run manually:



```

./primes 1 1000000 4

```



Run automated tests:



```

python3 tester.py

```



\## Key Observations



\* Time decreases as `n` increases initially (parallel speedup).

\* Gains reduce after reaching the number of logical cores.

\* Too many processes can increase overhead.



\## Author



RUPDEEP RAY(24CS8023)
NAKUL RAMTEKE(24CS8026)




