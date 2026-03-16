// Source: https://leetcode.com/problems/queries-on-a-permutation-with-key/   |   Difficulty: Medium
//
// Problem Description:
// Given the array queries of positive integers between 1 and m, you have to process all queries[i] (from i=0 to i=queries.length-1) according to the following rules:
//
//
// 	In the beginning, you have the permutation P=[1,2,3,...,m].
// 	For the current i, find the position of queries[i] in the permutation P (indexing from 0) and then move this at the beginning of the permutation P. Notice that the position of queries[i] in P is the result for queries[i].
//
//
// Return an array containing the result for the given queries.
//
// Example:
// Input: queries = [3,1,2,1], m = 5
// Output: [2,1,2,1] 
// Explanation: The queries are processed as follow: 
// For i=0: queries[i]=3, P=[1,2,3,4,5], position of 3 in P is 2, then we move 3 to the beginning of P resulting in P=[3,1,2,4,5]. 
// For i=1: queries[i]=1, P=[3,1,2,4,5], position of 1 in P is 1, then we move 1 to the beginning of P resulting in P=[1,3,2,4,5]. 
// For i=2: queries[i]=2, P=[1,3,2,4,5], position of 2 in P is 2, then we move 2 to the beginning of P resulting in P=[2,1,3,4,5]. 
// For i=3: queries[i]=1, P=[2,1,3,4,5], position of 1 in P is 1, then we move 1 to the beginning of P resulting in P=[1,2,3,4,5]. 
// Therefore, the array containing the result is [2,1,2,1].
//
// Constraints:
// 1 <= m <= 10^3
// 	1 <= queries.length <= m
// 	1 <= queries[i] <= m
//

class Solution {
    public int[] processQueries(int[] queries, int m) {
        int[] P = new int[m];
        for (int i = 0; i < m; i++) {
            P[i] = i + 1;
        }

        int[] result = new int[queries.length];

        for (int i = 0; i < queries.length; i++) {
            int query = queries[i];
            int index = 0;

            // Find the index of the query in P
            for (int j = 0; j < m; j++) {
                if (P[j] == query) {
                    index = j;
                    break;
                }
            }

            result[i] = index;

            // Move the queried element to the front
            for (int j = index; j > 0; j--) {
                P[j] = P[j - 1];
            }
            P[0] = query;
        }

        return result;          
    }
}
