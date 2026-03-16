// Source: https://leetcode.com/problems/construct-the-lexicographically-largest-valid-sequence/   |   Difficulty: Medium
//
// Problem Description:
// Given an integer n, find a sequence with elements in the range [1, n] that satisfies all of the following:
//
//
// 	The integer 1 occurs once in the sequence.
// 	Each integer between 2 and n occurs twice in the sequence.
// 	For every integer i between 2 and n, the distance between the two occurrences of i is exactly i.
//
//
// The distance between two numbers on the sequence, a[i] and a[j], is the absolute difference of their indices, |j - i|.
//
// Return the lexicographically largest sequence. It is guaranteed that under the given constraints, there is always a solution. 
//
// A sequence a is lexicographically larger than a sequence b (of the same length) if in the first position where a and b differ, sequence a has a number greater than the corresponding number in b. For example, [0,1,9,0] is lexicographically larger than [0,1,5,6] because the first position they differ is at the third number, and 9 is greater than 5.
//
// Example:
// Input: n = 3
// Output: [3,1,2,3,2]
// Explanation: [2,3,2,1,3] is also a valid sequence, but [3,1,2,3,2] is the lexicographically largest valid sequence.
//
// Constraints:
// 1 <= n <= 20
//

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* constructDistancedSequence(int n, int* returnSize) {
    int size = 2 * n - 1;
    int *res = (int *)calloc(size, sizeof(int));
    int *used = (int *)calloc(n + 1, sizeof(int));
    *returnSize = size;

    bool backtrack(int pos) {
        if (pos == size) {
            return true;
        }
        if (res[pos] != 0) {
            return backtrack(pos + 1);
        }
        for (int num = n; num >= 1; num--) {
            if (used[num]) {
                continue;
            }
            if (num == 1) {
                res[pos] = 1;
                used[1] = 1;
                if (backtrack(pos + 1)) {
                    return true;
                }
                res[pos] = 0;
                used[1] = 0;
            } else {
                int secondPos = pos + num;
                if (secondPos < size && res[secondPos] == 0) {
                    res[pos] = num;
                    res[secondPos] = num;
                    used[num] = 1;
                    if (backtrack(pos + 1)) {
                        return true;
                    }
                    res[pos] = 0;
                    res[secondPos] = 0;
                    used[num] = 0;
                }
            }
        }
        return false;
    }

    backtrack(0);
    free(used);
    return res;     
}
