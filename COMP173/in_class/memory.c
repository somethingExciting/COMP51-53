#include <stdio.h> 

/* 7.17
Assuming a 1-KB (1024B) page size, what are the page numbers and offsets for the following address references (provided as decimal numbers):
a. 2375 -> 2375/1024 = 2 (page number) 
			2375%1024 = 372 (offset) 
b. 19366 -> 19366/1024 = 18
			19366%1024 = 934 
c. 30000 -> 30000/1024 = 29 
			30000%1024 = 304 
d. 256 -> 256/1024 = 0 
			256%1024 = 256
e. 16385 -> 16385/1024 = 16
			16385%1024 = 1


7.18
Consider a logical address space of 32 pages with 1,024 words per page, mapped onto a physical memory of 16 frames.
a. How many bits are required in the logical address? 
32 pages; 1024 words 
2^5       2^10 
page number = 5 bits; offset = 10 bits; total = 15 bits

b. How many bits are required int he physical address? 
16 frames; 1024 words
2^4		   2^10
page number = 4 bits; offset = 10 bits; total = 14 bits


7.20
Consider a paging system with the page table stored in memory.
a. If a memory reference takes 200 nanoseconds, how long does a paged memory reference take?
400 nanoseconds

b. If we add TLBs, and 75% of all page-table references are found in the TLBs, what is the effective reference time? (Assume that finding a page-table entry in the TLBs takes 0 time if the entry is there)
hit 
75% x (0+200) + 25% x 400
= 150 + 100 
= 250


7.23 
Consider the following segment table:
Segment		Base 		Length
0			219			600
1			2300		14
2			90			100
3			1327		580
4			1952		96

a. 0,430 -> 219 + 430 = 649
b. 1,10 -> 2300 + 10 = 2310
c. 2,500 -> out of bounds
d. 3,400 -> 1327 + 400 = 1727
e. 4,112 -> out of bounds 
*/

int main() {
	printf("7.17a"); 
	printf("2375/1024 = %d\n", 2375/1024);
	printf("2375%%1024 = %d\n", 2375%1024);

	printf("7.17b");
	printf("19366/1024 = %d\n", 19366/1024);
	printf("19366%%1024 = %d\n", 19366%1024);

	printf("7.17c");
	printf("30000/1024 = %d\n", 30000/1024);
	printf("30000%%1024 = %d\n", 30000%1024);

	printf("7.17d");
	printf("256/1024 = %d\n", 256/1024);
	printf("256%%1024 = %d\n", 256%1024);

	printf("7.17e");
	printf("16385/1024 = %d\n", 16385/1024);
	printf("16385%%1024 = %d\n", 16385%1024);

	return 0;
}
