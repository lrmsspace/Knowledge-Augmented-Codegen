// Source: https://leetcode.com/problems/number-of-ways-where-square-of-number-is-equal-to-product-of-two-numbers/   |   Difficulty: Medium
//
// Problem Description:
// Given two arrays of integers nums1 and nums2, return the number of triplets formed (type 1 and type 2) under the following rules:
//
//
// 	Type 1: Triplet (i, j, k) if nums1[i]2 == nums2[j] * nums2[k] where 0 <= i < nums1.length and 0 <= j < k < nums2.length.
// 	Type 2: Triplet (i, j, k) if nums2[i]2 == nums1[j] * nums1[k] where 0 <= i < nums2.length and 0 <= j < k < nums1.length.
//
// Example:
// Input: nums1 = [7,4], nums2 = [5,2,8,9]
// Output: 1
// Explanation: Type 1: (1, 1, 2), nums1[1]2 = nums2[1] * nums2[2]. (42 = 2 * 8).
//
// Constraints:
// 1 <= nums1.length, nums2.length <= 1000
// 	1 <= nums1[i], nums2[i] <= 105
//
// Helpful references (internal KB):
// - The Inclusion-Exclusion Principle (matrix, array, dp-2d, counting)
//   • When to use: Use when needing to count elements satisfying "at least one" of several properties, especially when direct counting is complicated by overlapping sets. It's also applicable for counting elements satisfying "none" of the properties by subtracting from the total.
//   • Idea: The Inclusion-Exclusion Principle is a combinatorial method to determine the size of the union of multiple finite sets. It works by summing the sizes of individual sets, subtracting the sizes of all pairwise intersections, adding back the sizes of all three-way intersections, and so on, with alternating signs.
//   • Invariants: The count for any element satisfying `k` properties is adjusted to be exactly 1 in the final sum.; Each term in the sum corresponds to the size of an intersection of a distinct subset of properties.
//   • Tips: Clearly define the universe and the properties (sets) you are interested in.; Systematically list all combinations of properties for intersection terms.
//   • Pitfalls: Incorrectly identifying or defining the properties or sets.; Missing certain intersection terms or double-counting them.
// - Euler's totient function
//  (array, number, enumeration)
//   • When to use: Use when needing to count positive integers up to n that are relatively prime to n. It is also efficient for computing totient values for all numbers in a given range.
//   • Idea: Euler's totient function, φ(n), counts positive integers less than or equal to n that are relatively prime to n. It can be computed for a single n in O(sqrt(n)) using prime factorization, or for all numbers up to N in O(N log log N) using a sieve-like algorithm.
//   • Invariants: phi[i] stores the current totient value for i, which is i initially, then updated by (1 - 1/p) for each prime p dividing i.; After iterating through all primes p up to sqrt(N), phi[i] holds the correct totient value for all i <= N.
//   • Tips: For a single n, compute φ(n) using its prime factorization.; For all φ(i) up to N, use a sieve approach similar to Sieve of Eratosthenes.
//   • Pitfalls: Confusing 'relatively prime' with 'prime number'.; Applying the multiplicative property incorrectly when numbers share common factors.
// - Minkowski sum of convex polygons (geometry, array, two-pointers)
//   • When to use: When needing to compute the sum of two convex polygons, or efficiently determine the minimum distance or intersection between them.
//   • Idea: The Minkowski sum of two convex polygons P and Q is a new convex polygon formed by vector addition of all points from P and Q. It can be computed in O(|P| + |Q|) time by merging their edge vectors.
//   • Invariants: The current edge added to the Minkowski sum is the one with the smallest angle among the remaining edges from both polygons.; The sequence of edges in the Minkowski sum maintains convexity.
//   • Tips: The vertices of P+Q are sums of vertices of P and Q.; The edges of P+Q are the edges of P and Q, sorted by angle.
//   • Pitfalls: Incorrectly handling edge cases like collinear edges or degenerate polygons.; Floating point precision issues in geometric calculations.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    private long countTriplets(int[] nums1, int[] nums2) {
        Map<Long, Integer> freqMap2 = new HashMap<>();
        for (int num : nums2) {
            freqMap2.put((long) num, freqMap2.getOrDefault((long) num, 0) + 1);
        }

        long tripletCount = 0;
        for (int num1 : nums1) {
            long square = (long) num1 * num1;
            for (Map.Entry<Long, Integer> entry : freqMap2.entrySet()) {
                long factor = entry.getKey();
                if (square % factor == 0) {
                    long complement = square / factor;
                    if (freqMap2.containsKey(complement)) {
                        if (factor == complement) {
                            int count = entry.getValue();
                            tripletCount += (long) count * (count - 1) / 2;
                        } else if (factor < complement) {
                            tripletCount += (long) entry.getValue() * freqMap2.get(complement);
                        }
                    }
                }
            }
        }
        return tripletCount;
    }
    public int numTriplets(int[] nums1, int[] nums2) {
        return (int) (countTriplets(nums1, nums2) + countTriplets(nums2, nums1));           
    }
}
