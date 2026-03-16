// Source: https://leetcode.com/problems/high-access-employees/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 2D 0-indexed array of strings, access_times, with size n. For each i where 0 <= i <= n - 1, access_times[i][0] represents the name of an employee, and access_times[i][1] represents the access time of that employee. All entries in access_times are within the same day.
//
// The access time is represented as four digits using a 24-hour time format, for example, "0800" or "2250".
//
// An employee is said to be high-access if he has accessed the system three or more times within a one-hour period.
//
// Times with exactly one hour of difference are not considered part of the same one-hour period. For example, "0815" and "0915" are not part of the same one-hour period.
//
// Access times at the start and end of the day are not counted within the same one-hour period. For example, "0005" and "2350" are not part of the same one-hour period.
//
// Return a list that contains the names of high-access employees with any order you want.
//
// Example:
// Input: access_times = [["a","0549"],["b","0457"],["a","0532"],["a","0621"],["b","0540"]]
// Output: ["a"]
// Explanation: "a" has three access times in the one-hour period of [05:32, 06:31] which are 05:32, 05:49, and 06:21.
// But "b" does not have more than two access times at all.
// So the answer is ["a"].
//
// Constraints:
// 1 <= access_times.length <= 100
// 	access_times[i].length == 2
// 	1 <= access_times[i][0].length <= 10
// 	access_times[i][0] consists only of English small letters.
// 	access_times[i][1].length == 4
// 	access_times[i][1] is in 24-hour time format.
// 	access_times[i][1] consists only of '0' to '9'.
//
// Helpful references (internal KB):
// - Sparse Table (array, sparse-table, enumeration)
//   • When to use: Use when performing many range queries on a static array where the query operation is idempotent (e.g., min, max, GCD) to achieve O(1) query time after O(N log N) precomputation.
//   • Idea: A data structure that precomputes answers for all possible range queries of power-of-two lengths, allowing O(1) query time for idempotent operations like range minimum/maximum queries. Precomputation takes O(N log N) time and space.
//   • Invariants: The `st[k][i]` entry stores the result of the operation for the range `[i, i + 2^k - 1]`.; All ranges of length `2^k` starting at `i` are correctly computed in `st[k][i]` during precomputation.
//   • Tips: Precompute logarithms for O(1) lookup of `floor(log2(length))` during queries.; Sparse tables are most efficient for idempotent operations (min, max, GCD, OR, AND) due to overlapping segments.
//   • Pitfalls: Not suitable for dynamic arrays or scenarios requiring updates, as modifications invalidate the precomputed table.; High memory usage: requires O(N log N) space, which can be significant for large N.
// - Scheduling jobs on one machine (array, number, greedy, merge-sort)
//   • When to use: When tasks need to be processed sequentially on a single resource to optimize a cumulative metric like total completion time or weighted sum of completion times.
//   • Idea: This algorithm finds an optimal sequence for processing jobs on a single machine by applying a greedy strategy, often involving sorting based on specific criteria. It typically achieves an optimal schedule in O(N log N) time complexity.
//   • Invariants: The list of jobs is sorted according to the chosen greedy criterion.; For any prefix of the sorted jobs, the current schedule minimizes the objective function for those jobs.
//   • Tips: Identify the correct sorting key (e.g., processing time, weight/time ratio) for the objective function.; Prove optimality using an exchange argument to justify the greedy choice.
//   • Pitfalls: Applying an incorrect sorting criterion for the specific optimization objective.; Assuming a greedy approach is always optimal without a formal proof.
// - Digit DP (array, number, digit-dp)
//   • When to use: Use Digit DP to count numbers within a given range [a, b] that satisfy a property based on their digits. It's effective when the property can be checked digit by digit.
//   • Idea: Digit DP is a dynamic programming technique to count numbers within a given range [A, B] that satisfy specific properties related to their digits. It typically involves a recursive function with memoization, building numbers digit by digit, and has a complexity roughly proportional to (number of digits * state space).
//   • Invariants: The `tight` parameter accurately reflects if the current prefix matches the upper bound's prefix.; The `is_leading_zero` parameter correctly indicates if all preceding digits chosen were zero.
//   • Tips: Define the DP state carefully, including index, tight constraint, and leading zero flag.; Handle leading zeros correctly, as they can affect properties like sum or count of digits.
//   • Pitfalls: Incorrectly handling the 'tight' constraint, leading to overcounting or undercounting.; Forgetting to account for leading zeros or mismanaging their impact on the property.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char** findHighAccessEmployees(char*** access_times, int access_timesSize, int* access_timesColSize, int* returnSize) {
    // Helper function to convert time string "HHMM" to minutes
    int timeToMinutes(const char* timeStr) {
        int hours = (timeStr[0] - '0') * 10 + (timeStr[1] - '0');
        int minutes = (timeStr[2] - '0') * 10 + (timeStr[3] - '0');
        return hours * 60 + minutes;
    }

    // Structure to hold employee access times
    typedef struct {
        char name[11];
        int times[100];
        int count;
    } Employee;

    Employee employees[100];
    int empCount = 0;

    // Populate employee access times
    for (int i = 0; i < access_timesSize; i++) {
        char* name = access_times[i][0];
        char* timeStr = access_times[i][1];
        int timeInMinutes = timeToMinutes(timeStr);

        // Find or add employee
        int found = 0;
        for (int j = 0; j < empCount; j++) {
            if (strcmp(employees[j].name, name) == 0) {
                employees[j].times[employees[j].count++] = timeInMinutes;
                found = 1;
                break;
            }
        }
        if (!found) {
            strcpy(employees[empCount].name, name);
            employees[empCount].times[0] = timeInMinutes;
            employees[empCount].count = 1;
            empCount++;
        }
    }

    // Check for high-access employees
    char** result = (char**)malloc(empCount * sizeof(char*));
    int resCount = 0;

    for (int i = 0; i < empCount; i++) {
        // Sort access times
        qsort(employees[i].times, employees[i].count, sizeof(int), (int (*)(const void*, const void*))strcmp);

        // Check for three accesses within one hour
        for (int j = 0; j <= employees[i].count - 3; j++) {
            if (employees[i].times[j + 2] - employees[i].times[j] < 60) {
                result[resCount] = (char*)malloc((strlen(employees[i].name) + 1) * sizeof(char));
                strcpy(result[resCount], employees[i].name);
                resCount++;
                break;
            }
        }
    }
    *returnSize = resCount;
    return result;
}
