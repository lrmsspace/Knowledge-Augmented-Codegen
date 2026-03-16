// Source: https://leetcode.com/problems/maximum-number-that-sum-of-the-prices-is-less-than-or-equal-to-k/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer k and an integer x. The price of a number num is calculated by the count of set bits at positions x, 2x, 3x, etc., in its binary representation, starting from the least significant bit. The following table contains examples of how price is calculated.
//
//
// 	
// 		
// 			x
// 			num
// 			Binary Representation
// 			Price
// 		
// 		
// 			1
// 			13
// 			000001101
// 			3
// 		
// 		
// 			2
// 			13
// 			000001101
// 			1
// 		
// 		
// 			2
// 			233
// 			011101001
// 			3
// 		
// 		
// 			3
// 			13
// 			000001101
// 			1
// 		
// 		
// 			3
// 			362
// 			101101010
// 			2
// 		
// 	
//
//
// The accumulated price of num is the total price of numbers from 1 to num. num is considered cheap if its accumulated price is less than or equal to k.
//
// Return the greatest cheap number.
//
// Example:
// Input: k = 9, x = 1
//
// Output: 6
//
// Explanation:
//
// As shown in the table below, 6 is the greatest cheap number.
//
//
// 	
// 		
// 			x
// 			num
// 			Binary Representation
// 			Price
// 			Accumulated Price
// 		
// 		
// 			1
// 			1
// 			001
// 			1
// 			1
// 		
// 		
// 			1
// 			2
// 			010
// 			1
// 			2
// 		
// 		
// 			1
// 			3
// 			011
// 			2
// 			4
// 		
// 		
// 			1
// 			4
// 			100
// 			1
// 			5
// 		
// 		
// 			1
// 			5
// 			101
// 			2
// 			7
// 		
// 		
// 			1
// 			6
// 			110
// 			2
// 			9
// 		
// 		
// 			1
// 			7
// 			111
// 			3
// 			12
//
// Constraints:
// 1 <= k <= 1015
// 	1 <= x <= 8
//
// Helpful references (internal KB):
// - Non-negative Integers without Consecutive Ones (number, recursion, backtracking)
//   • When to use: Use when counting numbers within a range that satisfy a specific digit-based or bit-based pattern constraint, especially when the constraint involves adjacent digits or bits.
//   • Idea: This algorithm recursively generates binary numbers bit by bit, ensuring no two consecutive ones are formed. It prunes branches that exceed a given upper limit or violate the consecutive one constraint, effectively counting valid numbers up to N in O(log N) time.
//   • Invariants: The `sum` generated so far never exceeds the target `num`.; The `prev` boolean accurately reflects whether the last bit added was a '1'.
//   • Tips: Generate numbers bit by bit, typically from LSB or MSB, to build up valid sequences.; Maintain state about the previously placed bit to enforce the 'no consecutive ones' rule.
//   • Pitfalls: Failing to correctly handle the base cases for the recursive function.; Incorrectly managing the 'previous bit' state, leading to invalid sequences.
// - Binary Exponentiation by Factoring (number, mod-exp, enumeration)
//   • When to use: Used to solve discrete logarithm problems of the form g^x = y mod m, specifically when the modulus m is a power of 2. It iteratively determines the bits of the exponent x.
//   • Idea: It solves the discrete logarithm problem g^x = y mod m by iteratively determining the bits of x, specifically optimized for moduli that are powers of 2. The approach involves modular exponentiation and inverse operations, typically resulting in a complexity of O(log^2 m) or O(log m) depending on modular inverse efficiency.
//   • Invariants: After k steps, the k least significant bits of x are correctly identified.; The current effective target y' is congruent to g^(2^k * x_remaining) modulo 2^d.
//   • Tips: Carefully handle modular arithmetic with powers of 2, as properties differ from prime moduli.; The order of g modulo 2^d is crucial for determining the number of bits to recover.
//   • Pitfalls: Incorrectly calculating modular inverses for non-coprime numbers with 2^d.; Off-by-one errors when determining the number of squaring steps.
// - Generating all K-combinations (array, enumeration, greedy)
//   • When to use: Use this when you need to iterate through all possible subsets of a fixed size K from a larger set, especially when a specific order like lexicographical is required.
//   • Idea: This algorithm systematically generates all unique combinations of K elements from a set of N elements. It typically proceeds in lexicographical order, allowing for efficient enumeration of all C(N, K) possibilities.
//   • Invariants: The current combination C is always sorted: C[0] < C[1] < ... < C[K-1].; All elements C[i] are distinct and within the range [0, N-1] (assuming 0-indexed).
//   • Tips: Start with the smallest lexicographical combination (e.g., {1, 2, ..., K}).; To find the next combination, locate the rightmost element that can be incremented.
//   • Pitfalls: Incorrectly handling boundary conditions when incrementing elements.; Duplicating combinations if not careful with the increment logic.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    long long findMaximumNumber(long long k, int x) {
        long long low = 1, high = 1e18, ans = 0;
        while (low <= high) {
            long long mid = low + (high - low) / 2;
            if (accumulatedPrice(mid, x) <= k) {
                ans = mid; // mid is a cheap number, try for a larger one
                low = mid + 1;
            } else {
                high = mid - 1; // mid is not cheap, try smaller numbers
            }
        }
        return ans;         
    }
};
