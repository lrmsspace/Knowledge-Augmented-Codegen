// Source: https://leetcode.com/problems/alert-using-same-key-card-three-or-more-times-in-a-one-hour-period/   |   Difficulty: Medium
//
// Problem Description:
// LeetCode company workers use key-cards to unlock office doors. Each time a worker uses their key-card, the security system saves the worker's name and the time when it was used. The system emits an alert if any worker uses the key-card three or more times in a one-hour period.
//
// You are given a list of strings keyName and keyTime where [keyName[i], keyTime[i]] corresponds to a person's name and the time when their key-card was used in a single day.
//
// Access times are given in the 24-hour time format "HH:MM", such as "23:51" and "09:49".
//
// Return a list of unique worker names who received an alert for frequent keycard use. Sort the names in ascending order alphabetically.
//
// Notice that "10:00" - "11:00" is considered to be within a one-hour period, while "22:51" - "23:52" is not considered to be within a one-hour period.
//
// Example:
// Input: keyName = ["daniel","daniel","daniel","luis","luis","luis","luis"], keyTime = ["10:00","10:40","11:00","09:00","11:00","13:00","15:00"]
// Output: ["daniel"]
// Explanation: "daniel" used the keycard 3 times in a one-hour period ("10:00","10:40", "11:00").
//
// Constraints:
// 1 <= keyName.length, keyTime.length <= 105
// 	keyName.length == keyTime.length
// 	keyTime[i] is in the format "HH:MM".
// 	[keyName[i], keyTime[i]] is unique.
// 	1 <= keyName[i].length <= 10
// 	keyName[i] contains only lowercase English letters.
//
// Helpful references (internal KB):
// - String Hashing (string, array, hashing, enumeration)
//   • When to use: Use string hashing to efficiently compare substrings or patterns within a larger text, or to quickly check for duplicate strings. It's ideal for problems requiring fast equality checks on string segments.
//   • Idea: String hashing converts a string or substring into a numerical hash value, allowing for O(1) comparison of substrings after O(N) precomputation. It typically uses polynomial hashing with a prime base and modulus to minimize collisions.
//   • Invariants: The hash value for the prefix S[0...i] is correctly computed and stored, based on the chosen polynomial hashing scheme.; The base 'p' and modulus 'm' remain constant throughout the hash computation for consistent results.
//   • Tips: Choose a large prime number for the base 'p' (e.g., 31, 53) to reduce collisions.; Select a large prime number for the modulus 'm' (e.g., 10^9+7, 10^9+9) to further minimize collision probability.
//   • Pitfalls: Avoid using 2^64 as a modulus, as specific collision-generating strings exist for this choice.; A small modulus 'm' or base 'p' drastically increases the likelihood of hash collisions.
// - Sqrt Decomposition (array, ds, sliding-window, two-pointers)
//   • When to use: Use when performing frequent range queries and point updates on an array, especially when a segment tree is too complex or memory-intensive, or when query types are diverse. It offers a balanced time complexity for both operations.
//   • Idea: Sqrt decomposition divides an array into blocks of size approximately sqrt(N) to optimize range queries and point updates. It achieves O(sqrt(N)) time complexity for both operations.
//   • Invariants: Each element `arr[i]` belongs to exactly one block `block[i / block_size]`.; The summary for each block `block_summary[j]` accurately reflects the state of elements within block `j`.
//   • Tips: Choose block size carefully, typically sqrt(N) for balanced performance.; Precompute block summaries (e.g., sum, min, max) for efficient queries.
//   • Pitfalls: Off-by-one errors when calculating block indices or boundaries.; Forgetting to update the block's summary after a point update.
// - Scheduling jobs on one machine (array, number, greedy, merge-sort)
//   • When to use: Use when scheduling a set of jobs on a single machine to minimize the total weighted completion time, where each job has a processing time and a linear penalty coefficient.
//   • Idea: This algorithm finds an optimal schedule for jobs on a single machine with linear penalty functions by sorting jobs based on a specific ratio. It achieves an optimal solution in O(N log N) time complexity.
//   • Invariants: The partial schedule constructed so far is optimal for the jobs included.; For any two adjacent jobs 'j' and 'k' in the final schedule, if 'j' precedes 'k', then 'c_j/t_j >= c_k/t_k'.
//   • Tips: Derive the sorting criterion using an exchange argument for adjacent jobs.; The optimal order is determined by the ratio of cost coefficient to processing time.
//   • Pitfalls: Incorrectly applying the sorting criterion, especially the ratio order.; Overlooking edge cases like zero processing times or zero penalty coefficients.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public List<String> alertNames(String[] keyName, String[] keyTime) {
        Map<String, List<Integer>> map = new HashMap<>();
        int n = keyName.length;

        for (int i = 0; i < n; i++) {
            String name = keyName[i];
            String time = keyTime[i];
            int minutes = Integer.parseInt(time.substring(0, 2)) * 60 + Integer.parseInt(time.substring(3, 5));
            map.putIfAbsent(name, new ArrayList<>());
            map.get(name).add(minutes);
        }

        Set<String> resultSet = new HashSet<>();

        for (String name : map.keySet()) {
            List<Integer> times = map.get(name);
            Collections.sort(times);

            for (int i = 2; i < times.size(); i++) {
                if (times.get(i) - times.get(i - 2) <= 60) {
                    resultSet.add(name);
                    break;
                }
            }
        }

        List<String> result = new ArrayList<>(resultSet);
        Collections.sort(result);
        return result;          
    }
}
