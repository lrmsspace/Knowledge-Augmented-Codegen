// Source: https://leetcode.com/problems/inverse-coin-change/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 1-indexed integer array numWays, where numWays[i] represents the number of ways to select a total amount i using an infinite supply of some fixed coin denominations. Each denomination is a positive integer with value at most numWays.length.
//
// However, the exact coin denominations have been lost. Your task is to recover the set of denominations that could have resulted in the given numWays array.
//
// Return a sorted array containing unique integers which represents this set of denominations.
//
// If no such set exists, return an empty array.
//
// Example:
// Input: numWays = [0,1,0,2,0,3,0,4,0,5]
//
// Output: [2,4,6]
//
// Explanation:
//
//
// 	
// 		
// 			Amount
// 			Number of ways
// 			Explanation
// 		
// 		
// 			1
// 			0
// 			There is no way to select coins with total value 1.
// 		
// 		
// 			2
// 			1
// 			The only way is [2].
// 		
// 		
// 			3
// 			0
// 			There is no way to select coins with total value 3.
// 		
// 		
// 			4
// 			2
// 			The ways are [2, 2] and [4].
// 		
// 		
// 			5
// 			0
// 			There is no way to select coins with total value 5.
// 		
// 		
// 			6
// 			3
// 			The ways are [2, 2, 2], [2, 4], and [6].
// 		
// 		
// 			7
// 			0
// 			There is no way to select coins with total value 7.
// 		
// 		
// 			8
// 			4
// 			The ways are [2, 2, 2, 2], [2, 2, 4], [2, 6], and [4, 4].
// 		
// 		
// 			9
// 			0
// 			There is no way to select coins with total value 9.
// 		
// 		
// 			10
// 			5
// 			The ways are [2, 2, 2, 2, 2], [2, 2, 2, 4], [2, 4, 4], [2, 2, 6], and [4, 6].
//
// Constraints:
// 1 <= numWays.length <= 100
// 	0 <= numWays[i] <= 2 * 108
//
// Helpful references (internal KB):
// - MEX (minimal excluded) of a sequence (array, enumeration)
//   • When to use: Use when you need to find the smallest non-negative integer that is not present in a given collection of numbers. It's often applied in problems involving game theory or combinatorial analysis.
//   • Idea: This algorithm finds the smallest non-negative integer not present in a given sequence or set. It typically involves marking present numbers and then iterating from zero to find the first unmarked number, achieving O(N) or O(N log N) complexity.
//   • Invariants: All non-negative integers less than the current candidate MEX value have been found in the input sequence.; The data structure used for presence tracking accurately reflects which non-negative integers up to a certain bound are present.
//   • Tips: Use a boolean array or hash set for efficient presence checking.; The MEX value is at most N (for N elements) if all numbers are distinct and within [0, N-1].
//   • Pitfalls: Forgetting to handle the case where all numbers from 0 to N-1 are present, meaning MEX is N.; Using an inefficient method for presence checking, leading to higher time complexity.
// - Generating all K-combinations (array, enumeration, greedy)
//   • When to use: Use this when you need to iterate through all possible subsets of a fixed size K from a larger set, especially when a specific order like lexicographical is required.
//   • Idea: This algorithm systematically generates all unique combinations of K elements from a set of N elements. It typically proceeds in lexicographical order, allowing for efficient enumeration of all C(N, K) possibilities.
//   • Invariants: The current combination C is always sorted: C[0] < C[1] < ... < C[K-1].; All elements C[i] are distinct and within the range [0, N-1] (assuming 0-indexed).
//   • Tips: Start with the smallest lexicographical combination (e.g., {1, 2, ..., K}).; To find the next combination, locate the rightmost element that can be incremented.
//   • Pitfalls: Incorrectly handling boundary conditions when incrementing elements.; Duplicating combinations if not careful with the increment logic.
// - Linear Sieve (array, sieve)
//   • When to use: Use when you need to find all prime numbers up to a given limit N, or compute the least prime factor for all numbers in that range, efficiently in linear time.
//   • Idea: The Linear Sieve finds all prime numbers up to N in O(N) time by ensuring each composite number is marked exactly once by its least prime factor. It also computes the least prime factor for every number up to N.
//   • Invariants: The 'primes' list always contains all prime numbers found so far in increasing order.; lpf[i] stores the least prime factor of 'i' if 'i' is composite, or 'i' itself if 'i' is prime.
//   • Tips: Store the least prime factor (LPF) for each number in an array.; Maintain a dynamically growing list of primes found so far.
//   • Pitfalls: Incorrectly marking multiples can lead to O(N log log N) or worse complexity.; Forgetting to store the least prime factor can break the linear time guarantee.
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {number[]} numWays
 * @return {number[]}
 */
var findCoins = function(numWays) {
    const denominations = [];
    const n = numWays.length;
    
    for (let i = 1; i < n; i++) {
        if (numWays[i] === 0) continue;
        
        let found = false;
        for (const coin of denominations) {
            if (i - coin >= 0 && numWays[i - coin] > 0) {
                found = true;
                break;
            }
        }
        
        if (!found) {
            denominations.push(i);
        }
    }
    
    return denominations.sort((a, b) => a - b);
};
