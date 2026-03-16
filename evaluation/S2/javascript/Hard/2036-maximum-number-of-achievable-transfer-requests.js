// Source: https://leetcode.com/problems/maximum-number-of-achievable-transfer-requests/   |   Difficulty: Hard
//
// Problem Description:
// We have n buildings numbered from 0 to n - 1. Each building has a number of employees. It's transfer season, and some employees want to change the building they reside in.
//
// You are given an array requests where requests[i] = [fromi, toi] represents an employee's request to transfer from building fromi to building toi.
//
// All buildings are full, so a list of requests is achievable only if for each building, the net change in employee transfers is zero. This means the number of employees leaving is equal to the number of employees moving in. For example if n = 3 and two employees are leaving building 0, one is leaving building 1, and one is leaving building 2, there should be two employees moving to building 0, one employee moving to building 1, and one employee moving to building 2.
//
// Return the maximum number of achievable requests.
//
// Example:
// Input: n = 5, requests = [[0,1],[1,0],[0,1],[1,2],[2,0],[3,4]]
// Output: 5
// Explantion: Let's see the requests:
// From building 0 we have employees x and y and both want to move to building 1.
// From building 1 we have employees a and b and they want to move to buildings 2 and 0 respectively.
// From building 2 we have employee z and they want to move to building 0.
// From building 3 we have employee c and they want to move to building 4.
// From building 4 we don't have any requests.
// We can achieve the requests of users x and b by swapping their places.
// We can achieve the requests of users y, a and z by swapping the places in the 3 buildings.
//
// Constraints:
// 1 <= n <= 20
// 	1 <= requests.length <= 16
// 	requests[i].length == 2
// 	0 <= fromi, toi < n
//
// Helpful references (internal KB):
// - N/A
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {number} n
 * @param {number[][]} requests
 * @return {number}
 */
var maximumRequests = function(n, requests) {
    let maxAchievable = 0;
    const m = requests.length;
    
    for (let mask = 0; mask < (1 << m); mask++) {
        const delta = Array(n).fill(0);
        let count = 0;
        
        for (let i = 0; i < m; i++) {
            if ((mask & (1 << i)) !== 0) {
                const [from, to] = requests[i];
                delta[from]--;
                delta[to]++;
                count++;
            }
        }
        
        if (delta.every(x => x === 0)) {
            maxAchievable = Math.max(maxAchievable, count);
        }
    }
    
    return maxAchievable;
};
