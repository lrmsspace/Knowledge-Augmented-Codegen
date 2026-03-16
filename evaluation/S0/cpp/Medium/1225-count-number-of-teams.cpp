// Source: https://leetcode.com/problems/count-number-of-teams/   |   Difficulty: Medium
//
// Problem Description:
// There are n soldiers standing in a line. Each soldier is assigned a unique rating value.
//
// You have to form a team of 3 soldiers amongst them under the following rules:
//
//
// 	Choose 3 soldiers with index (i, j, k) with rating (rating[i], rating[j], rating[k]).
// 	A team is valid if: (rating[i] < rating[j] < rating[k]) or (rating[i] > rating[j] > rating[k]) where (0 <= i < j < k < n).
//
//
// Return the number of teams you can form given the conditions. (soldiers can be part of multiple teams).
//
// Example:
// Input: rating = [2,5,3,4,1]
// Output: 3
// Explanation: We can form three teams given the conditions. (2,3,4), (5,4,1), (5,3,1).
//
// Constraints:
// n == rating.length
// 	3 <= n <= 1000
// 	1 <= rating[i] <= 105
// 	All the integers in rating are unique.
//

class Solution {
public:
    int numTeams(vector<int>& rating) {
        int n = rating.size();
        int count = 0;

        for (int j = 1; j < n - 1; ++j) {
            int lessLeft = 0, greaterLeft = 0;
            int lessRight = 0, greaterRight = 0;

            for (int i = 0; i < j; ++i) {
                if (rating[i] < rating[j]) {
                    ++lessLeft;
                } else {
                    ++greaterLeft;
                }
            }

            for (int k = j + 1; k < n; ++k) {
                if (rating[k] < rating[j]) {
                    ++lessRight;
                } else {
                    ++greaterRight;
                }
            }

            count += lessLeft * greaterRight + greaterLeft * lessRight;
        }

        return count;           
    }
};
