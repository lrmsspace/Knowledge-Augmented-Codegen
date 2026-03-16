// Source: https://leetcode.com/problems/prime-pairs-with-target-sum/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer n. We say that two integers x and y form a prime number pair if:
//
//
// 	1 <= x <= y <= n
// 	x + y == n
// 	x and y are prime numbers
//
//
// Return the 2D sorted list of prime number pairs [xi, yi]. The list should be sorted in increasing order of xi. If there are no prime number pairs at all, return an empty array.
//
// Note: A prime number is a natural number greater than 1 with only two factors, itself and 1.
//
// Example:
// Input: n = 10
// Output: [[3,7],[5,5]]
// Explanation: In this example, there are two prime pairs that satisfy the criteria. 
// These pairs are [3,7] and [5,5], and we return them in the sorted order as described in the problem statement.
//
// Constraints:
// 1 <= n <= 106
//

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** findPrimePairs(int n, int* returnSize, int** returnColumnSizes) {
    int is_prime[n + 1];
    for (int i = 0; i <= n; i++) {
        is_prime[i] = 1;
    }
    is_prime[0] = is_prime[1] = 0;
    for (int i = 2; i * i <= n; i++) {
        if (is_prime[i]) {
            for (int j = i * i; j <= n; j += i) {
                is_prime[j] = 0;
            }
        }
    }

    int** result = (int**)malloc(sizeof(int*) * (n / 2));
    *returnColumnSizes = (int*)malloc(sizeof(int) * (n / 2));
    *returnSize = 0;

    for (int x = 2; x <= n / 2; x++) {
        int y = n - x;
        if (is_prime[x] && is_prime[y]) {
            result[*returnSize] = (int*)malloc(sizeof(int) * 2);
            result[*returnSize][0] = x;
            result[*returnSize][1] = y;
            (*returnColumnSizes)[*returnSize] = 2;
            (*returnSize)++;
        }
    }

    return result;      
}
