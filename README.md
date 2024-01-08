# Sequence Align

## Description
Project to perform sequence alignment of short DNA sequences of Anopheles Gambiae (common mosquito). This implementation leverages distributed computing through the HTCondor and Work Queue systems to drastically improve the computational runtime. The tool utilized to compute scores of DNA comparisons is `swaligntool`, installed below.

## Installation
- This program requires Python 3. The machine tested uses Python 3.6.8.
- This program requires the installation and setup of HTCondor and Work Queue
- An installation of the `swaligntool` and `swalign` python libraries are needed:
```console
$ wget http://sakailogin.nd.edu/access/content/group/SP21-CSE-40822-CX-01/a3-1/swaligntool.tar.gz
```
- Unpack `swaligntool.tar.gz` and place within the project's root directory

## To Run
```console
$ ./seq-align ./data/agambiae.small.fasta
```

## Sequential Time Estimate
- Using the `swaligntool` command, it takes an average of 2m 36s (156s) to compare a single sequence to ten sequences.
- With this average, the estimated computation time to sequentially compare every sequence with every other sequence would be approximately 97110s (269h 45m 00s).
- Through the law of transitivity, we could reduce the sequential runtime of this compution to approximately 485550s (134h 52m 30s)
- In order for this optimized computation to finish the job in a single hour, the computation would need to be split between 135 machines.
- The above computation times refer to the time to align 250 sequences of Anopheles Cambiae. The optimized computation time of sequentially computing the full DNA sequence (consisting of 100,000 sequences) is estimated to be 77999220000s (2473y 123d 18h)

## Program Output
- Below is the output obtained by the program (with input `data/agambiae.small.fasta`)
```txt
Top Ten Matches:
1: sequence 1102140176186 matches 1102140143903 with a score of 1539
2: sequence 1102140177183 matches 1102140177182 with a score of 874
3: sequence 1102140172678 matches 1102140167168 with a score of 818
4: sequence 1102140171813 matches 1101555423227 with a score of 777
5: sequence 1102140164074 matches 1101555423815 with a score of 767
6: sequence 1102140171192 matches 1101671610328 with a score of 764
7: sequence 1102140171192 matches 1102140170611 with a score of 744
8: sequence 1102140178449 matches 1102140171192 with a score of 742
9: sequence 1102140171192 matches 1101555423803 with a score of 741
10: sequence 1102140178493 matches 1101671610328 with a score of 736
```

## Parallel Runtime Analysis
Below can be found the performance results obtained. Speedup and efficiency were computed by using the estimated optimized sequential runtime of 485550s.
- 200 Workers:
	- Runtime: 37m 59s (2279s)
	- Speedup: 213.05
	- Efficiency: 106.5%
- 150 Workers:
	- Runtime: 51m 25s (3085s)
	- Speedup: 157.39
	- Efficiency: 104.9%
- 100 Workers:
	- Runtime: 52m 04s (3124s)
	- Speedup: 155.43
	- Efficiency: 155.4%
- 50 Workers:
	- Runtime: 54m 09s (3249s)
	- Speedup: 149.45
	- Efficiency: 298.9%

### Analysis Observations
- With the runs with more machines (200 and 150), it seemed natural for the speedup to be relatively similar to the number of machines, but I was personally taken aback by the speedup seen by the lower end (100 and 50).
- With my expectation that speedup would remain relatively the same as the number of workers used, I had expected efficiency to stay around the 100% line, but I was wrong (because of the lower end).
- What also surprised me was how the runtime remained relatively constant until running with 200 workers. This might have been a fluke because of many reasons (competition within the pool, allocation of different machines, etc), but it is an interesting observation. Is the operational cost of 150 extra machines (comparing 50 vs 200 workers) for an approximate 30% increase in speedup worth it? The efficiency of the 50 workers is seemingly impossible, yet it ocurred.
- Thinking as to what might have cause these absurd efficiency results, I am guessing that many things may have ocurred
	- I utilized pipes within each worker to minimize the output of `swaligntool` (which has the default setting to writing to stdout). This alone would usually not matter, but in comparison with the paralled execution, the sequential execution takes a huge hit by writing to stdout.
	- I defined the `agambiae.small.fasta` file to be cached within the shared space of the workers. This allows each process to pipe simultaneously as none of them are writing to the input file.
	- The machine (disc01.crc.nd.edu) running the sequential computation of `swaligntool` (for the Sequential Time Estimate) is a different architecture than the machines within the Condor Pool at Notre Dame. This means different processors/memory with different amount of users utilizing the machine's resources.
