// Source: https://leetcode.com/problems/split-message-based-on-limit/   |   Difficulty: Hard
//
// Problem Description:
// You are given a string, message, and a positive integer, limit.
//
// You must split message into one or more parts based on limit. Each resulting part should have the suffix "<a/b>", where "b" is to be replaced with the total number of parts and "a" is to be replaced with the index of the part, starting from 1 and going up to b. Additionally, the length of each resulting part (including its suffix) should be equal to limit, except for the last part whose length can be at most limit.
//
// The resulting parts should be formed such that when their suffixes are removed and they are all concatenated in order, they should be equal to message. Also, the result should contain as few parts as possible.
//
// Return the parts message would be split into as an array of strings. If it is impossible to split message as required, return an empty array.
//
// Example:
// Input: message = "this is really a very awesome message", limit = 9
// Output: ["thi<1/14>","s i<2/14>","s r<3/14>","eal<4/14>","ly <5/14>","a v<6/14>","ery<7/14>"," aw<8/14>","eso<9/14>","me<10/14>"," m<11/14>","es<12/14>","sa<13/14>","ge<14/14>"]
// Explanation:
// The first 9 parts take 3 characters each from the beginning of message.
// The next 5 parts take 2 characters each to finish splitting message. 
// In this example, each part, including the last, has length 9. 
// It can be shown it is not possible to split message into less than 14 parts.
//
// Constraints:
// 1 <= message.length <= 104
// 	message consists only of lowercase English letters and ' '.
// 	1 <= limit <= 104
//
// Helpful references (internal KB):
// - Binary search (interval, number, binary-search-answer, enumeration)
//   • When to use: When searching for a specific element in a sorted collection or finding an optimal value over a monotonic function within a defined range. It efficiently reduces the search space by half in each step.
//   • Idea: A search algorithm that finds the position of a target value within a sorted array or determines a value that satisfies a monotonic predicate. It operates in logarithmic time complexity, O(log N).
//   • Invariants: The potential answer always lies within the current search interval `[low, high]`.; All elements strictly less than `low` have been determined not to be the answer.
//   • Tips: Ensure the search space exhibits a monotonic property.; Carefully define the `low` and `high` bounds for the search interval.
//   • Pitfalls: Incorrectly updating `low` or `high` bounds leading to infinite loops.; Off-by-one errors in array indexing or loop conditions.
// - Binary search (interval, number, binary-search-answer, recursion)
//   • When to use: Use when optimizing a unimodal function (finding its maximum or minimum) over a continuous interval, where direct differentiation is hard or impossible.
//   • Idea: This algorithm finds the extremum (maximum or minimum) of a unimodal function over a given interval by repeatedly narrowing the search space. It evaluates the function at two internal points to achieve logarithmic convergence.
//   • Invariants: The extremum of the unimodal function f(x) is always within the current interval [l, r].; The function f(x) remains unimodal within the current interval [l, r].
//   • Tips: Use a fixed number of iterations as a stopping criterion instead of an epsilon value for robustness against floating point errors.; For golden section search, reuse one function evaluation from the previous step to minimize expensive computations.
//   • Pitfalls: Applying this algorithm to a non-unimodal function will yield an incorrect result.; Floating point precision issues can lead to incorrect comparisons or infinite loops if `eps` is too small.
// - Binary search (interval, number, binary-search-answer, recursion)
//   • When to use: When searching for the extremum (maximum or minimum) of a unimodal function over a continuous or discrete interval. It is efficient for functions where direct differentiation or analytical solutions are complex.
//   • Idea: Ternary search is an algorithm that efficiently finds the extremum of a unimodal function within a given interval by repeatedly narrowing the search space. It typically achieves a logarithmic time complexity, O(log N), where N is the interval size.
//   • Invariants: The extremum of the unimodal function always lies within the current search interval [l, r].; The function value at m1 is compared with m2 to narrow the interval while preserving unimodality.
//   • Tips: Ensure the function is strictly unimodal within the search interval.; Handle discrete intervals carefully, especially the stopping condition (r - l) < 3.
//   • Pitfalls: Applying to non-unimodal functions yields incorrect results.; Incorrect stopping conditions can lead to infinite loops or suboptimal answers.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    vector<string> splitMessage(string message, int limit) {
        int n = (int)message.size();
        int low = 1;
        int high = n;
        int totalParts = -1;

        while (low <= high) {
            int mid = low + (high - low) / 2;
            long long suffixLen = 3LL * mid + to_string(mid).size() * 2; // Length of "<a/b>" where b=mid
            long long contentLen = limit - suffixLen; // Available content length per part
            if (contentLen <= 0) {
                high = mid - 1; // Suffix itself exceeds limit, try fewer parts
                continue;
            }
            long long totalContentLen = contentLen * mid; // Total content length across all parts
            if (totalContentLen >= n) {
                totalParts = mid; // Found a valid number of parts, try for fewer
                high = mid - 1;
            } else {
                low = mid + 1; // Not enough content length, try more parts
            }
        }

        if (totalParts == -1) {
            return {}; // Impossible to split as required
        }

        vector<string> result(totalParts);
        long long suffixLen = 3LL * totalParts + to_string(totalParts).size() * 2; // Length of "<a/b>"
        long long contentLen = limit - suffixLen; // Available content length per part

        for (int i = 0; i < totalParts; ++i) {
            int startIdx = i * contentLen;
            int endIdx = min(startIdx + contentLen, n);
            result[i] = message.substr(startIdx, endIdx - startIdx) + "<" + to_string(i + 1) + "/" + to_string(totalParts) + ">";
        }

        return result;          
    }
};
