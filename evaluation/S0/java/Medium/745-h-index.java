// Source: https://leetcode.com/problems/h-index/   |   Difficulty: Medium
//
// Problem Description:
// Given an array of integers citations where citations[i] is the number of citations a researcher received for their ith paper, return the researcher's h-index.
//
// According to the definition of h-index on Wikipedia: The h-index is defined as the maximum value of h such that the given researcher has published at least h papers that have each been cited at least h times.
//
// Example:
// Input: citations = [3,0,6,1,5]
// Output: 3
// Explanation: [3,0,6,1,5] means the researcher has 5 papers in total and each of them had received 3, 0, 6, 1, 5 citations respectively.
// Since the researcher has 3 papers with at least 3 citations each and the remaining two with no more than 3 citations each, their h-index is 3.
//
// Constraints:
// n == citations.length
// 	1 <= n <= 5000
// 	0 <= citations[i] <= 1000
//

class Solution {
    public int hIndex(int[] citations) {
        int n = citations.length;
        int[] paperCounts = new int[n + 1];

        for (int citation : citations) {
            if (citation >= n) {
                paperCounts[n]++;
            } else {
                paperCounts[citation]++;
            }
        }

        int totalPapers = 0;
        for (int h = n; h >= 0; h--) {
            totalPapers += paperCounts[h];
            if (totalPapers >= h) {
                return h;
            }
        }

        return 0;           
    }
}
