// Source: https://leetcode.com/problems/closest-prime-numbers-in-range/   |   Difficulty: Medium
//
// Problem Description:
// Given two positive integers left and right, find the two integers num1 and num2 such that:
//
//
// 	left <= num1 < num2 <= right .
// 	Both num1 and num2 are prime numbers.
// 	num2 - num1 is the minimum amongst all other pairs satisfying the above conditions.
//
//
// Return the positive integer array ans = [num1, num2]. If there are multiple pairs satisfying these conditions, return the one with the smallest num1 value. If no such numbers exist, return [-1, -1].
//
// Example:
// Input: left = 10, right = 19
// Output: [11,13]
// Explanation: The prime numbers between 10 and 19 are 11, 13, 17, and 19.
// The closest gap between any pair is 2, which can be achieved by [11,13] or [17,19].
// Since 11 is smaller than 17, we return the first pair.
//
// Constraints:
// 1 <= left <= right <= 106
//
//
//  
// .spoilerbutton {display:block; border:dashed; padding: 0px 0px; margin:10px 0px; font-size:150%; font-weight: bold; color:#000000; background-color:cyan; outline:0; 
// }
// .spoiler {overflow:hidden;}
// .spoiler > div {-webkit-transition: all 0s ease;-moz-transition: margin 0s ease;-o-transition: all 0s ease;transition: margin 0s ease;}
// .spoilerbutton[value="Show Message"] + .spoiler > div {margin-top:-500%;}
// .spoilerbutton[value="Hide Message"] + .spoiler {padding:5px;}
//

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* closestPrimes(int left, int right, int* returnSize) {
    int size = right - left + 1;
    char* is_prime = (char*)malloc(size);
    for (int i = 0; i < size; ++i) {
        is_prime[i] = 1;
    }
    for (int i = 2; i * i <= right; ++i) {
        int start = (left + i - 1) / i * i;
        if (start < i * 2) {
            start = i * 2;
        }
        for (int j = start; j <= right; j += i) {
            is_prime[j - left] = 0;
        }
    }
    if (left == 1) {
        is_prime[0] = 0;
    }
    int prev = -1;
    int min_diff = right - left + 1;
    int num1 = -1, num2 = -1;
    for (int i = 0; i < size; ++i) {
        if (is_prime[i]) {
            if (prev != -1) {
                int diff = (left + i) - (left + prev);
                if (diff < min_diff) {
                    min_diff = diff;
                    num1 = left + prev;
                    num2 = left + i;
                }
            }
            prev = i;
        }
    }
    free(is_prime);
    int* result = (int*)malloc(2 * sizeof(int));
    result[0] = num1;
    result[1] = num2;
    *returnSize = 2;
    return result;      
}
