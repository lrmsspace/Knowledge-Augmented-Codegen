// Source: https://leetcode.com/problems/implement-rand10-using-rand7/   |   Difficulty: Medium
//
// Problem Description:
// Given the API rand7() that generates a uniform random integer in the range [1, 7], write a function rand10() that generates a uniform random integer in the range [1, 10]. You can only call the API rand7(), and you shouldn't call any other API. Please do not use a language's built-in random API.
//
// Each test case will have one internal argument n, the number of times that your implemented function rand10() will be called while testing. Note that this is not an argument passed to rand10().
//
// Example:
// Input: n = 1
// Output: [2]
//
// Constraints:
// 1 <= n <= 105
//
//
//  
// Follow up:
//
//
// 	What is the expected value for the number of calls to rand7() function?
// 	Could you minimize the number of calls to rand7()?
//

/**
 * The rand7() API is already defined for you.
 * var rand7 = function() {}
 * @return {number} a random integer in the range 1 to 7
 */
var rand10 = function() {
    while (true) {
        const row = rand7();
        const col = rand7();
        const idx = (row - 1) * 7 + col; // Generate a number from 1 to 49
        if (idx <= 40) return 1 + (idx - 1) % 10;
    }
};
