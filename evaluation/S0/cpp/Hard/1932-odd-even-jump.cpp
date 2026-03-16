// Source: https://leetcode.com/problems/odd-even-jump/   |   Difficulty: Hard
//
// Problem Description:
// You are given an integer array arr. From some starting index, you can make a series of jumps. The (1st, 3rd, 5th, ...) jumps in the series are called odd-numbered jumps, and the (2nd, 4th, 6th, ...) jumps in the series are called even-numbered jumps. Note that the jumps are numbered, not the indices.
//
// You may jump forward from index i to index j (with i < j) in the following way:
//
//
// 	During odd-numbered jumps (i.e., jumps 1, 3, 5, ...), you jump to the index j such that arr[i] <= arr[j] and arr[j] is the smallest possible value. If there are multiple such indices j, you can only jump to the smallest such index j.
// 	During even-numbered jumps (i.e., jumps 2, 4, 6, ...), you jump to the index j such that arr[i] >= arr[j] and arr[j] is the largest possible value. If there are multiple such indices j, you can only jump to the smallest such index j.
// 	It may be the case that for some index i, there are no legal jumps.
//
//
// A starting index is good if, starting from that index, you can reach the end of the array (index arr.length - 1) by jumping some number of times (possibly 0 or more than once).
//
// Return the number of good starting indices.
//
// Example:
// Input: arr = [10,13,12,14,15]
// Output: 2
// Explanation: 
// From starting index i = 0, we can make our 1st jump to i = 2 (since arr[2] is the smallest among arr[1], arr[2], arr[3], arr[4] that is greater or equal to arr[0]), then we cannot jump any more.
// From starting index i = 1 and i = 2, we can make our 1st jump to i = 3, then we cannot jump any more.
// From starting index i = 3, we can make our 1st jump to i = 4, so we have reached the end.
// From starting index i = 4, we have reached the end already.
// In total, there are 2 different starting indices i = 3 and i = 4, where we can reach the end with some number of
// jumps.
//
// Constraints:
// 1 <= arr.length <= 2 * 104
// 	0 <= arr[i] < 105
//

class Solution {
public:
    int oddEvenJumps(vector<int>& arr) {
        int n = arr.size();
        vector<int> nextHigher(n, -1), nextLower(n, -1);
        map<int, int> valueToIndex;

        // Compute next higher jumps
        for (int i = n - 1; i >= 0; --i) {
            auto it = valueToIndex.lower_bound(arr[i]);
            if (it != valueToIndex.end()) {
                nextHigher[i] = it->second;
            }
            valueToIndex[arr[i]] = i;
        }

        valueToIndex.clear();

        // Compute next lower jumps
        for (int i = n - 1; i >= 0; --i) {
            auto it = valueToIndex.upper_bound(arr[i]);
            if (it != valueToIndex.begin()) {
                --it;
                nextLower[i] = it->second;
            }
            valueToIndex[arr[i]] = i;
        }

        vector<bool> canReachEndOdd(n, false), canReachEndEven(n, false);
        canReachEndOdd[n - 1] = true;
        canReachEndEven[n - 1] = true;

        for (int i = n - 2; i >= 0; --i) {
            if (nextHigher[i] != -1) {
                canReachEndOdd[i] = canReachEndEven[nextHigher[i]];
            }
            if (nextLower[i] != -1) {
                canReachEndEven[i] = canReachEndOdd[nextLower[i]];
            }
        }

        int goodStartingIndices = 0;
        for (bool canReach : canReachEndOdd) {
            if (canReach) {
                ++goodStartingIndices;
            }
        }

        return goodStartingIndices;         
    }
};
