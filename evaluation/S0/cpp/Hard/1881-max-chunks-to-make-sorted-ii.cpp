// Source: https://leetcode.com/problems/max-chunks-to-make-sorted-ii/   |   Difficulty: Hard
//
// Problem Description:
// You are given an integer array arr.
//
// We split arr into some number of chunks (i.e., partitions), and individually sort each chunk. After concatenating them, the result should equal the sorted array.
//
// Return the largest number of chunks we can make to sort the array.
//
// Example:
// Input: arr = [5,4,3,2,1]
// Output: 1
// Explanation:
// Splitting into two or more chunks will not return the required result.
// For example, splitting into [5, 4], [3, 2, 1] will result in [4, 5, 1, 2, 3], which isn't sorted.
//
// Constraints:
// 1 <= arr.length <= 2000
// 	0 <= arr[i] <= 108
//

class Solution {
public:
    int maxChunksToSorted(vector<int>& arr) {
        int n = arr.size();
        vector<int> maxLeft(n), minRight(n + 1, INT_MAX);
        
        maxLeft[0] = arr[0];
        for (int i = 1; i < n; i++) {
            maxLeft[i] = max(maxLeft[i - 1], arr[i]);
        }
        
        for (int i = n - 1; i >= 0; i--) {
            minRight[i] = min(minRight[i + 1], arr[i]);
        }
        
        int chunks = 0;
        for (int i = 0; i < n; i++) {
            if (maxLeft[i] <= minRight[i + 1]) {
                chunks++;
            }
        }
        
        return chunks;          
    }
};
