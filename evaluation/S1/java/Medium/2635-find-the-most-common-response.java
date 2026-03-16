// Source: https://leetcode.com/problems/find-the-most-common-response/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 2D string array responses where each responses[i] is an array of strings representing survey responses from the ith day.
//
// Return the most common response across all days after removing duplicate responses within each responses[i]. If there is a tie, return the lexicographically smallest response.
//
// Example:
// Input: responses = [["good","ok","good","ok"],["ok","bad","good","ok","ok"],["good"],["bad"]]
//
// Output: "good"
//
// Explanation:
//
//
// 	After removing duplicates within each list, responses = [["good", "ok"], ["ok", "bad", "good"], ["good"], ["bad"]].
// 	"good" appears 3 times, "ok" appears 2 times, and "bad" appears 2 times.
// 	Return "good" because it has the highest frequency.
//
// Constraints:
// 1 <= responses.length <= 1000
// 	1 <= responses[i].length <= 1000
// 	1 <= responses[i][j].length <= 10
// 	responses[i][j] consists of only lowercase English letters
//
// Helpful references (internal KB):
// - String Hashing (string, array, hashing, enumeration)
//   • When to use: Use string hashing to efficiently compare substrings or patterns within a larger text, or to quickly check for duplicate strings. It's ideal for problems requiring fast equality checks on string segments.
//   • Idea: String hashing converts a string or substring into a numerical hash value, allowing for O(1) comparison of substrings after O(N) precomputation. It typically uses polynomial hashing with a prime base and modulus to minimize collisions.
//   • Invariants: The hash value for the prefix S[0...i] is correctly computed and stored, based on the chosen polynomial hashing scheme.; The base 'p' and modulus 'm' remain constant throughout the hash computation for consistent results.
//   • Tips: Choose a large prime number for the base 'p' (e.g., 31, 53) to reduce collisions.; Select a large prime number for the modulus 'm' (e.g., 10^9+7, 10^9+9) to further minimize collision probability.
//   • Pitfalls: Avoid using 2^64 as a modulus, as specific collision-generating strings exist for this choice.; A small modulus 'm' or base 'p' drastically increases the likelihood of hash collisions.
// - Generating all K-combinations (array, enumeration, greedy)
//   • When to use: Use this when you need to iterate through all possible subsets of a fixed size K from a larger set, especially when a specific order like lexicographical is required.
//   • Idea: This algorithm systematically generates all unique combinations of K elements from a set of N elements. It typically proceeds in lexicographical order, allowing for efficient enumeration of all C(N, K) possibilities.
//   • Invariants: The current combination C is always sorted: C[0] < C[1] < ... < C[K-1].; All elements C[i] are distinct and within the range [0, N-1] (assuming 0-indexed).
//   • Tips: Start with the smallest lexicographical combination (e.g., {1, 2, ..., K}).; To find the next combination, locate the rightmost element that can be incremented.
//   • Pitfalls: Incorrectly handling boundary conditions when incrementing elements.; Duplicating combinations if not careful with the increment logic.
// - String Sorts (array, string, number, radix-sort, counting-sort)
//   • When to use: Use when sorting a large collection of fixed-length strings or integers, especially when the key range (alphabet size) is small. It is efficient for data with uniform key lengths.
//   • Idea: LSD Radix Sort sorts elements by processing digits or characters from the least significant to the most significant, using a stable counting sort for each position. It achieves a time complexity of O(W * (N + R)), where W is the key length, N is the number of items, and R is the radix.
//   • Invariants: After each pass 'd' (from 'w-1' down to '0'), the array 'a' is stably sorted based on characters from position 'd' to 'w-1'.; The 'count' array accurately reflects the frequency of each character at the current digit 'd' before cumulation.
//   • Tips: Utilize counting sort as the stable inner sorting algorithm for each digit pass.; Process characters or digits from right to left (least significant to most significant).
//   • Pitfalls: Inefficient for variable-length strings without proper padding or specialized handling.; Can be slower than comparison sorts for small input sizes or very large radix (R).
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public String findCommonResponse(List<List<String>> responses) {
        Map<String, Integer> frequencyMap = new HashMap<>();

        for (List<String> dailyResponses : responses) {
            Set<String> uniqueResponses = new HashSet<>(dailyResponses);
            for (String response : uniqueResponses) {
                frequencyMap.put(response, frequencyMap.getOrDefault(response, 0) + 1);
            }
        }

        String mostCommonResponse = "";
        int highestFrequency = 0;

        for (Map.Entry<String, Integer> entry : frequencyMap.entrySet()) {
            String response = entry.getKey();
            int frequency = entry.getValue();

            if (frequency > highestFrequency || 
               (frequency == highestFrequency && response.compareTo(mostCommonResponse) < 0)) {
                mostCommonResponse = response;
                highestFrequency = frequency;
            }
        }

        return mostCommonResponse;          
    }
}
