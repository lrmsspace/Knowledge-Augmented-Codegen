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
// - Non-negative Integers without Consecutive Ones (number, enumeration, simulation)
//   • When to use: Use when counting numbers up to a given limit that satisfy a specific bit pattern constraint, particularly when the limit is small enough for direct iteration and checking.
//   • Idea: This approach iterates through every non-negative integer from 0 up to the given limit num. For each integer, it simulates checking its binary representation to determine if it contains any two consecutive '1's.
//   • Invariants: count stores the number of integers k (where 0 <= k < i) that do not have consecutive ones.; All integers j such that 0 <= j < i have been processed.
//   • Tips: Use bitwise operations like (i & (i >> 1)) to efficiently detect consecutive ones.; Remember to include 0 in the count as it satisfies the condition (no consecutive ones).
//   • Pitfalls: Performance degradation for large num due to linear scan and per-number bit check.; Incorrectly handling the upper bound of the iteration (e.g., i < num instead of i <= num).
// - Submask Enumeration
//  (number, bitset, enumeration, bitmask-dp)
//   • When to use: When a problem requires iterating through all possible submasks for each given mask. This is common in bitmask dynamic programming problems where relationships between a set and its subsets are crucial.
//   • Idea: This algorithm efficiently iterates through all submasks for every mask from 0 to 2^N - 1. It has a total time complexity of O(3^N) for all masks and their submasks.
//   • Invariants: For a given `mask`, `submask` always represents a subset of `mask`.; Each `submask` is visited exactly once for its corresponding `mask`.
//   • Tips: The `submask = (submask - 1) & mask` trick is crucial for efficient iteration.; Ensure the outer loop iterates through all masks from 0 to 2^N - 1.
//   • Pitfalls: Forgetting the `& mask` part in the inner loop can lead to incorrect submasks or infinite loops.; Misunderstanding the O(3^N) total complexity, leading to Time Limit Exceeded for large N.
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
        long long sum = 0, num = 0;
        for (int i = x - 1; sum <= k; i += x) {
            sum += (1LL << i);
            if (sum > k) break;
            num += (1LL << i);
        }
        return num;         
    }
};
