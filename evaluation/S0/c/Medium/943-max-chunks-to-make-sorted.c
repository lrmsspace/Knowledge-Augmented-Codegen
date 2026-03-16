// Source: https://leetcode.com/problems/max-chunks-to-make-sorted/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer array arr of length n that represents a permutation of the integers in the range [0, n - 1].
//
// We split arr into some number of chunks (i.e., partitions), and individually sort each chunk. After concatenating them, the result should equal the sorted array.
//
// Return the largest number of chunks we can make to sort the array.
//
// Example:
// Input: arr = [4,3,2,1,0]
// Output: 1
// Explanation:
// Splitting into two or more chunks will not return the required result.
// For example, splitting into [4, 3], [2, 1, 0] will result in [3, 4, 0, 1, 2], which isn't sorted.
//
// Constraints:
// n == arr.length
// 	1 <= n <= 10
// 	0 <= arr[i] < n
// 	All the elements of arr are unique.
//

int maxChunksToSorted(int* arr, int arrSize) {
    int max_so_far = -1;
    int chunk_count = 0;

    for (int i = 0; i < arrSize; i++) {
        if (arr[i] > max_so_far) {
            max_so_far = arr[i];
        }
        if (max_so_far == i) {
            chunk_count++;
        }
    }

    return chunk_count;     
}
