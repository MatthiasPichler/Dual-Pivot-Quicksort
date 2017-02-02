//
// Created by matze on 1/19/17.
//

#ifndef DUALPIVOTQUICKSORT_DUALPIVOTQUICKSORT_HPP
#define DUALPIVOTQUICKSORT_DUALPIVOTQUICKSORT_HPP

#include <iostream>

/**
 * Dual-Pivot-Quicksort :
 *
 * The sorting algorithm is a Dual-Pivot Quicksort by Vladimir Yaroslavskiy, Jon Bentley, and Joshua Bloch.
 * This algorithm offers O(n log(n)) performance on many data sets that cause other quicksorts to degrade to
 * quadratic performance, and is typically faster than traditional (one-pivot) Quicksort implementations.
 *
 * Algorithm works as follows:
 * 0)	For small arrays (length < 17), use the Insertion sort algorithm.
 * 1)	Choose two pivot elements P1 and P2. For example, the first element a[left] as P1 and the last element a[right] as P2.
 * 		BETTER: Choose middle elements!!!
 * 2)	P1 must be less than P2, otherwise they are swapped.
 *
 * So, there are the following parts:
 *
 * ___________________________________________________________________________________________________
 * | P1 | 	X<P1		| L |		P1<= X <=P2		| K |		?		| G |		X>P2		| P2 |
 * ---------------------------------------------------------------------------------------------------
 *	@left	part1		@L			part2			@K		part4		@G			part3		@right
 *
 *
 * 	*#	part I with indices from left+1 to L–1 with elements, which are less than P1,
 * 	*#	part II with indices from L to K–1 with elements, which are greater or equal to P1 and less or equal to P2,
 * 	*#	part III with indices from G+1 to right–1 with elements greater than P2,
 * 	*#	part IV contains the rest of the elements to be examined with indices from K to G.
 *
 * While K ≤ G: repeat 3 & 4
 * 3) 	The next element a[K] from the part IV is compared with two pivots P1 and P2,
 * 		and placed to the corresponding part I, II, or III.
 * 4)	The pointers L, K, and G are changed in the corresponding directions.
 * 5)	The pivot element P1 is swapped with the last element from part I,
 * 		the pivot element P2 is swapped with the first element from part III.
 * 6)	The steps 0 – 5 are repeated recursively for every part I, part II, and part III.
 *
 */


#define arraysize(array) (sizeof(array)/sizeof(*array))

inline void swap(int *a, const int i, const int j) {
	int tmp = a[i];
	a[i] = a[j];
	a[j] = tmp;
}

void dualPivotQuicksort(int *a, const int left, const int right, int div, const int limit) {
	int length = right - left;
	//use insertion sort for small arrays length < 27
	if(length < limit) {
		for(int i = left + 1; i <= right; i++){
			for(int j = i; j > left && a[j] < a[j - 1]; j--){
				swap(a, j, j - 1);
			}
		}
		return;
	}
	
	int third = length / div;
	// "medians"
	int m1 = left + third;
	int m2 = right - third;
	if(m1 <= left) {
		m1 = left + 1;
	}
	if(m2 >= right) {
		m2 = right - 1;
	}
	if(a[m1] < a[m2]) {
		swap(a, m1, left);
		swap(a, m2, right);
	} else {
		swap(a, m1, right);
		swap(a, m2, left);
	}
	// pivots
	int pivot1 = a[left];
	int pivot2 = a[right];
	// pointers
	int less = left + 1;
	int great = right - 1;
	
	// sorting
	for(int k = less; k <= great; k++){
		if(a[k] < pivot1) {
			swap(a, k, less++);
		} else if(a[k] > pivot2) {
			while(k < great && a[great] > pivot2){
				great--;
			}
			swap(a, k, great--);
			if(a[k] < pivot1) {
				swap(a, k, less++);
			}
		}
	}
	// swaps
	int dist = great - less;
	if(dist < 13) {
		div++;
	}
	swap(a, less - 1, left);
	swap(a, great + 1, right);
	// subarrays
	dualPivotQuicksort(a, left, less - 2, div, limit);
	dualPivotQuicksort(a, great + 2, right, div, limit);
	// equal elements
	if(dist > length - 13 && pivot1 != pivot2) {
		for(int k = less; k <= great; k++){
			if(a[k] == pivot1) {
				swap(a, k, less++);
			} else if(a[k] == pivot2) {
				swap(a, k, great--);
				if(a[k] == pivot1) {
					swap(a, k, less++);
				}
			}
		}
	}
	// subarray
	if(pivot1 < pivot2) {
		dualPivotQuicksort(a, less, great, div,limit);
	}
	
}

void sort(int *a) {
	dualPivotQuicksort(a, 0, arraysize(a), 3, 27);
}


#endif //DUALPIVOTQUICKSORT_DUALPIVOTQUICKSORT_HPP
