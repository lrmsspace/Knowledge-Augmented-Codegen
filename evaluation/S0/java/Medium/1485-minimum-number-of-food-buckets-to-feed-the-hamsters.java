// Source: https://leetcode.com/problems/minimum-number-of-food-buckets-to-feed-the-hamsters/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 0-indexed string hamsters where hamsters[i] is either:
//
//
// 	'H' indicating that there is a hamster at index i, or
// 	'.' indicating that index i is empty.
//
//
// You will add some number of food buckets at the empty indices in order to feed the hamsters. A hamster can be fed if there is at least one food bucket to its left or to its right. More formally, a hamster at index i can be fed if you place a food bucket at index i - 1 and/or at index i + 1.
//
// Return the minimum number of food buckets you should place at empty indices to feed all the hamsters or -1 if it is impossible to feed all of them.
//
// Example:
// Input: hamsters = "H..H"
// Output: 2
// Explanation: We place two food buckets at indices 1 and 2.
// It can be shown that if we place only one food bucket, one of the hamsters will not be fed.
//
// Constraints:
// 1 <= hamsters.length <= 105
// 	hamsters[i] is either'H' or '.'.
//

class Solution {
    public int minimumBuckets(String hamsters) {
        char[] arr = hamsters.toCharArray();
        int n = arr.length;
        int buckets = 0;

        for (int i = 0; i < n; i++) {
            if (arr[i] == 'H') {
                if (i > 0 && arr[i - 1] == 'B') {
                    continue; // Already has a bucket to the left
                } else if (i < n - 1 && arr[i + 1] == '.') {
                    arr[i + 1] = 'B'; // Place bucket to the right
                    buckets++;
                } else if (i > 0 && arr[i - 1] == '.') {
                    arr[i - 1] = 'B'; // Place bucket to the left
                    buckets++;
                } else {
                    return -1; // Impossible to feed this hamster
                }
            }
        }

        return buckets;         
    }
}
