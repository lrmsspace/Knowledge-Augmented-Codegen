// Source: https://leetcode.com/problems/intervals-between-identical-elements/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 0-indexed array of n integers arr.
//
// The interval between two elements in arr is defined as the absolute difference between their indices. More formally, the interval between arr[i] and arr[j] is |i - j|.
//
// Return an array intervals of length n where intervals[i] is the sum of intervals between arr[i] and each element in arr with the same value as arr[i].
//
// Note: |x| is the absolute value of x.
//
// Example:
// Input: arr = [2,1,3,1,2,3,3]
// Output: [4,2,7,2,4,4,5]
// Explanation:
// - Index 0: Another 2 is found at index 4. |0 - 4| = 4
// - Index 1: Another 1 is found at index 3. |1 - 3| = 2
// - Index 2: Two more 3s are found at indices 5 and 6. |2 - 5| + |2 - 6| = 7
// - Index 3: Another 1 is found at index 1. |3 - 1| = 2
// - Index 4: Another 2 is found at index 0. |4 - 0| = 4
// - Index 5: Two more 3s are found at indices 2 and 6. |5 - 2| + |5 - 6| = 4
// - Index 6: Two more 3s are found at indices 2 and 5. |6 - 2| + |6 - 5| = 5
//
// Constraints:
// n == arr.length
// 	1 <= n <= 105
// 	1 <= arr[i] <= 105
//
//
//  
// Note: This question is the same as  2615: Sum of Distances.
//

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
long long* getDistances(int* arr, int arrSize, int* returnSize) {
    // Create a map to store the indices of each unique value in arr
    #define MAX_VAL 100000
    int* indices[MAX_VAL + 1];
    int counts[MAX_VAL + 1] = {0};
    
    // First pass: collect indices for each value
    for (int i = 0; i < arrSize; i++) {
        int val = arr[i];
        if (indices[val] == NULL) {
            indices[val] = (int*)malloc(sizeof(int) * arrSize);
        }
        indices[val][counts[val]++] = i;
    }
    
    // Prepare the result array
    long long* result = (long long*)malloc(sizeof(long long) * arrSize);
    
    // Second pass: calculate distances for each value
    for (int val = 0; val <= MAX_VAL; val++) {
        if (counts[val] == 0) continue;
        
        int* idxs = indices[val];
        int count = counts[val];
        
        // Precompute prefix sums of indices
        long long* prefixSums = (long long*)malloc(sizeof(long long) * (count + 1));
        prefixSums[0] = 0;
        for (int i = 0; i < count; i++) {
            prefixSums[i + 1] = prefixSums[i] + idxs[i];
        }
        
        // Calculate distances for each index
        for (int i = 0; i < count; i++) {
            int index = idxs[i];
            long long leftSum = prefixSums[i]; // sum of indices to the left
            long long rightSum = prefixSums[count] - prefixSums[i + 1]; // sum of indices to the right
            
            long long leftCount = i; // number of elements to the left
            long long rightCount = count - i - 1; // number of elements to the right
            
            result[index] = (long long)(index * leftCount - leftSum) + (rightSum - index * rightCount);
        }
        
        free(prefixSums);
        free(idxs);
    }
    
    *returnSize = arrSize;
    return result;      
}
