// Source: https://leetcode.com/problems/reformat-date/   |   Difficulty: Easy
//
// Problem Description:
// Given a date string in the form Day Month Year, where:
//
//
// 	Day is in the set {"1st", "2nd", "3rd", "4th", ..., "30th", "31st"}.
// 	Month is in the set {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"}.
// 	Year is in the range [1900, 2100].
//
//
// Convert the date string to the format YYYY-MM-DD, where:
//
//
// 	YYYY denotes the 4 digit year.
// 	MM denotes the 2 digit month.
// 	DD denotes the 2 digit day.
//
// Example:
// Input: date = "20th Oct 2052"
// Output: "2052-10-20"
//
// Constraints:
// The given dates are guaranteed to be valid, so no error handling is necessary.
//
// Helpful references (internal KB):
// - Digit DP (array, number, digit-dp)
//   • When to use: Use Digit DP to count numbers within a given range [a, b] that satisfy a property based on their digits. It's effective when the property can be checked digit by digit.
//   • Idea: Digit DP is a dynamic programming technique to count numbers within a given range [A, B] that satisfy specific properties related to their digits. It typically involves a recursive function with memoization, building numbers digit by digit, and has a complexity roughly proportional to (number of digits * state space).
//   • Invariants: The `tight` parameter accurately reflects if the current prefix matches the upper bound's prefix.; The `is_leading_zero` parameter correctly indicates if all preceding digits chosen were zero.
//   • Tips: Define the DP state carefully, including index, tight constraint, and leading zero flag.; Handle leading zeros correctly, as they can affect properties like sum or count of digits.
//   • Pitfalls: Incorrectly handling the 'tight' constraint, leading to overcounting or undercounting.; Forgetting to account for leading zeros or mismanaging their impact on the property.
// - Shortest Paths (array, graph, dp-1d)
//   • When to use: To find the path with the minimum total weight or cost between two vertices, or from a single source to all other reachable vertices, in an edge-weighted graph.
//   • Idea: Shortest path algorithms determine the path with the least cumulative weight between nodes in a graph. This often involves a dynamic programming approach, iteratively updating minimum distances to achieve an optimal O(V*E) or O(E log V) complexity.
//   • Invariants: distTo[v] always stores the minimum path length from the source to v discovered so far.; For any edge u -> v, if distTo[u] is final, then distTo[v] will eventually be min(distTo[v], distTo[u] + weight(u,v)).
//   • Tips: Initialize the source distance to 0 and all other distances to infinity.; Use a `distTo` array to store the current shortest distances from the source.
//   • Pitfalls: Failing to detect or handle negative cycles, which can lead to infinite loops or incorrect results.; Incorrectly initializing distances or edge relaxation logic.
// - Suffix Automaton (string, enumeration)
//   • When to use: When you need to efficiently represent all substrings of a given string and perform various string operations like counting distinct substrings or pattern matching in linear time.
//   • Idea: A Suffix Automaton is a minimal finite automaton that accepts all suffixes of a given string. It implicitly represents all substrings and can be constructed in linear time, O(N) where N is the string length.
//   • Invariants: Every path from the initial state spells a substring of the original string.; Each state represents a set of substrings that share the same end positions in the original string.
//   • Tips: Understand the concept of `endpos` sets and how they define states.; The number of states and transitions in a suffix automaton is linear with respect to string length.
//   • Pitfalls: The construction algorithm can be complex and prone to off-by-one errors or incorrect link updates.; Debugging state transitions and suffix links requires careful attention.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

char* reformatDate(char* date) {
    static const char* months[] = {
        "Jan", "Feb", "Mar", "Apr", "May", "Jun",
        "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
    };

    char day[3] = {0};
    char month[3] = {0};
    char year[5] = {0};

    // Parse the input date string
    sscanf(date, "%2s %3s %4s", day, month, year);

    // Remove suffix from day
    int day_num = atoi(day);
    
    // Find month number
    int month_num = 0;
    for (int i = 0; i < 12; i++) {
        if (strcmp(month, months[i]) == 0) {
            month_num = i + 1;
            break;
        }
    }

    // Format the output date string
    static char reformatted_date[11];
    sprintf(reformatted_date, "%s-%02d-%02d", year, month_num, day_num);

    return reformatted_date;        
}
