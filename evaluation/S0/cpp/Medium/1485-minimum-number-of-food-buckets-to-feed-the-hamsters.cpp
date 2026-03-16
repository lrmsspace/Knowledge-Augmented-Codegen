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
public:
    int minimumBuckets(string hamsters) {
        int n = hamsters.size();
        int buckets = 0;

        for (int i = 0; i < n; ++i) {
            if (hamsters[i] == 'H') {
                // Check if the left side has a bucket
                if (i > 0 && hamsters[i - 1] == 'B') {
                    continue;
                }
                // Check if we can place a bucket on the right side
                else if (i + 1 < n && hamsters[i + 1] == '.') {
                    buckets++;
                    hamsters[i + 1] = 'B'; // Place bucket
                }
                // Check if we can place a bucket on the left side
                else if (i > 0 && hamsters[i - 1] == '.') {
                    buckets++;
                    hamsters[i - 1] = 'B'; // Place bucket
                }
                // If neither side can have a bucket, return -1
                else {
                    return -1;
                }
            }
        }

        return buckets;         
    }
};
