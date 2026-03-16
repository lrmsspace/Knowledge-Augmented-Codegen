// Source: https://leetcode.com/problems/plates-between-candles/   |   Difficulty: Medium
//
// Problem Description:
// There is a long table with a line of plates and candles arranged on top of it. You are given a 0-indexed string s consisting of characters '*' and '|' only, where a '*' represents a plate and a '|' represents a candle.
//
// You are also given a 0-indexed 2D integer array queries where queries[i] = [lefti, righti] denotes the substring s[lefti...righti] (inclusive). For each query, you need to find the number of plates between candles that are in the substring. A plate is considered between candles if there is at least one candle to its left and at least one candle to its right in the substring.
//
//
// 	For example, s = "||**||**|*", and a query [3, 8] denotes the substring "*||**|". The number of plates between candles in this substring is 2, as each of the two plates has at least one candle in the substring to its left and right.
//
//
// Return an integer array answer where answer[i] is the answer to the ith query.
//
// Example:
// Input: s = "**|**|***|", queries = [[2,5],[5,9]]
// Output: [2,3]
// Explanation:
// - queries[0] has two plates between candles.
// - queries[1] has three plates between candles.
//
// Constraints:
// 3 <= s.length <= 105
// 	s consists of '*' and '|' characters.
// 	1 <= queries.length <= 105
// 	queries[i].length == 2
// 	0 <= lefti <= righti < s.length
//

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* platesBetweenCandles(char* s, int** queries, int queriesSize, int* queriesColSize, int* returnSize) {
    int n = strlen(s);
    int* prefix = (int*)calloc(n + 1, sizeof(int));
    int* leftCandle = (int*)malloc(n * sizeof(int));
    int* rightCandle = (int*)malloc(n * sizeof(int));

    // Build prefix sum of plates
    for (int i = 0; i < n; i++) {
        prefix[i + 1] = prefix[i] + (s[i] == '*' ? 1 : 0);
    }

    // Build leftCandle array
    int lastCandle = -1;
    for (int i = 0; i < n; i++) {
        if (s[i] == '|') {
            lastCandle = i;
        }
        leftCandle[i] = lastCandle;
    }

    // Build rightCandle array
    lastCandle = -1;
    for (int i = n - 1; i >= 0; i--) {
        if (s[i] == '|') {
            lastCandle = i;
        }
        rightCandle[i] = lastCandle;
    }

    // Process each query
    int* result = (int*)malloc(queriesSize * sizeof(int));
    for (int i = 0; i < queriesSize; i++) {
        int left = queries[i][0];
        int right = queries[i][1];

        int leftBound = rightCandle[left];
        int rightBound = leftCandle[right];

        if (leftBound != -1 && rightBound != -1 && leftBound < rightBound) {
            result[i] = prefix[rightBound + 1] - prefix[leftBound];
        } else {
            result[i] = 0;
        }
    }

    free(prefix);
    free(leftCandle);
    free(rightCandle);

    *returnSize = queriesSize;
    return result;      
}
