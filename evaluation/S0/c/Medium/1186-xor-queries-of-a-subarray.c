// Source: https://leetcode.com/problems/xor-queries-of-a-subarray/   |   Difficulty: Medium
//
// Problem Description:
// You are given an array arr of positive integers. You are also given the array queries where queries[i] = [lefti, righti].
//
// For each query i compute the XOR of elements from lefti to righti (that is, arr[lefti] XOR arr[lefti + 1] XOR ... XOR arr[righti] ).
//
// Return an array answer where answer[i] is the answer to the ith query.
//
// Example:
// Input: arr = [1,3,4,8], queries = [[0,1],[1,2],[0,3],[3,3]]
// Output: [2,7,14,8] 
// Explanation: 
// The binary representation of the elements in the array are:
// 1 = 0001 
// 3 = 0011 
// 4 = 0100 
// 8 = 1000 
// The XOR values for queries are:
// [0,1] = 1 xor 3 = 2 
// [1,2] = 3 xor 4 = 7 
// [0,3] = 1 xor 3 xor 4 xor 8 = 14 
// [3,3] = 8
//
// Constraints:
// 1 <= arr.length, queries.length <= 3 * 104
// 	1 <= arr[i] <= 109
// 	queries[i].length == 2
// 	0 <= lefti <= righti < arr.length
//

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* xorQueries(int* arr, int arrSize, int** queries, int queriesSize, int* queriesColSize, int* returnSize) {
    // Precompute prefix XORs
    int* prefixXOR = (int*)malloc((arrSize + 1) * sizeof(int));
    prefixXOR[0] = 0;
    for (int i = 0; i < arrSize; i++) {
        prefixXOR[i + 1] = prefixXOR[i] ^ arr[i];
    }

    // Prepare the result array
    int* result = (int*)malloc(queriesSize * sizeof(int));
    *returnSize = queriesSize;

    // Process each query
    for (int i = 0; i < queriesSize; i++) {
        int left = queries[i][0];
        int right = queries[i][1];
        result[i] = prefixXOR[right + 1] ^ prefixXOR[left];
    }

    // Free the prefix XOR array
    free(prefixXOR);

    return result;      
}
