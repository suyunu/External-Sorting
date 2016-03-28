# External Sorting

Sorting is the most fundamental algorithmic problem in computer science and it's usually the first step of the solutions of many large scale problems. Therefore, many sorting algorithms have been invented for different purposes. With the recent developments in networking and mobile services, we are constantly generating and processing huge amounts of data that is impossible to fit into a single memory. Instead, we use external sorting methods.

External sorting is a term for a class of sorting algorithms that can handle massive amounts of data. External sorting is required when the data being sorted do not fit into the main memory of a computing device (usually RAM) and instead they must reside in the slower external memory (usually a hard drive).

External sorting typically uses a hybrid sort-merge strategy. In the sorting phase, chunks of data small enough to fit in main memory are loaded to memory, sorted, and written out to a temporary file. In the merge phase, the sorted data portions in the temporary les are merged into a single larger file.

1. Read data from the disk that can fit into your memory.
2. Sort the data with a conventional sorting algorithm.
3. Write the sorted data to a temporary file on the disk.
4. Repeat steps [1-3] until all the data is partially sorted.
5. Merge the data in the temporary les into a single file.

![Figure 1](http://i1027.photobucket.com/albums/y338/suyunu/chart_zpsdvdi6gqv.jpg)

## Input/Output

`./externalSort [input_file] [output_file]`

The input file contains the unsorted double precision numbers, one at a line. The first line in the input file will be the total number of numbers. The output file will contain those numbers in increasingly sorted order.
