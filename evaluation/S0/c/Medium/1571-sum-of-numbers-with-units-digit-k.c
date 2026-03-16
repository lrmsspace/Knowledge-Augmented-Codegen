// Source: https://leetcode.com/problems/sum-of-numbers-with-units-digit-k/   |   Difficulty: Medium
//
// Problem Description:
// Given two integers num and k, consider a set of positive integers with the following properties:
//
//
// 	The units digit of each integer is k.
// 	The sum of the integers is num.
//
//
// Return the minimum possible size of such a set, or -1 if no such set exists.
//
// Note:
//
//
// 	The set can contain multiple instances of the same integer, and the sum of an empty set is considered 0.
// 	The units digit of a number is the rightmost digit of the number.
//
// Example:
// Input: num = 58, k = 9
// Output: 2
// Explanation:
// One valid set is [9,49], as the sum is 58 and each integer has a units digit of 9.
// Another valid set is [19,39].
// It can be shown that 2 is the minimum possible size of a valid set.
//
// Constraints:
// 0 <= num <= 3000
// 	0 <= k <= 9
//

int minimumNumbers(int num, int k) {
    if (num == 0) {
        return 0;
    }
    for (int count = 1; count <= 10; ++count) {
        int total = count * k;
        if (total <= num && (num - total) % 10 == 0) {
            return count;
        }
    }
    return -1;      
}
