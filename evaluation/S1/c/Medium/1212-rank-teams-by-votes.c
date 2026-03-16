// Source: https://leetcode.com/problems/rank-teams-by-votes/   |   Difficulty: Medium
//
// Problem Description:
// In a special ranking system, each voter gives a rank from highest to lowest to all teams participating in the competition.
//
// The ordering of teams is decided by who received the most position-one votes. If two or more teams tie in the first position, we consider the second position to resolve the conflict, if they tie again, we continue this process until the ties are resolved. If two or more teams are still tied after considering all positions, we rank them alphabetically based on their team letter.
//
// You are given an array of strings votes which is the votes of all voters in the ranking systems. Sort all teams according to the ranking system described above.
//
// Return a string of all teams sorted by the ranking system.
//
// Example:
// Input: votes = ["ABC","ACB","ABC","ACB","ACB"]
// Output: "ACB"
// Explanation: 
// Team A was ranked first place by 5 voters. No other team was voted as first place, so team A is the first team.
// Team B was ranked second by 2 voters and ranked third by 3 voters.
// Team C was ranked second by 3 voters and ranked third by 2 voters.
// As most of the voters ranked C second, team C is the second team, and team B is the third.
//
// Constraints:
// 1 <= votes.length <= 1000
// 	1 <= votes[i].length <= 26
// 	votes[i].length == votes[j].length for 0 <= i, j < votes.length.
// 	votes[i][j] is an English uppercase letter.
// 	All characters of votes[i] are unique.
// 	All the characters that occur in votes[0] also occur in votes[j] where 1 <= j < votes.length.
//
// Helpful references (internal KB):
// - Mergesort (array, merge-sort, divide-and-conquer, recursion)
//   • When to use: Use when a stable sort with guaranteed O(N log N) time complexity is required, even if O(N) auxiliary space is acceptable. It is suitable for sorting linked lists efficiently.
//   • Idea: Mergesort is a divide-and-conquer algorithm that recursively divides an array into two halves, sorts them, and then merges the sorted halves. It guarantees O(N log N) time complexity and uses O(N) auxiliary space.
//   • Invariants: Before merging, the left subarray `a[lo..mid]` and right subarray `a[mid+1..hi]` are individually sorted.; After each recursive call `sort(a, aux, sub_lo, sub_hi)`, the subarray `a[sub_lo..sub_hi]` is sorted.
//   • Tips: Utilize an auxiliary array for the merging step to simplify implementation and ensure stability.; Mergesort is a stable sorting algorithm, preserving the relative order of equal elements.
//   • Pitfalls: The primary disadvantage is the requirement for O(N) extra space for the auxiliary array.; Implementing an in-place merge without significant extra space is complex and often less efficient.
// - Finding the rank of a matrix (matrix, simulation, enumeration)
//   • When to use: Use when needing to determine the maximum number of linearly independent rows or columns in a matrix. It's also applicable for understanding the dimension of the vector space spanned by the matrix's rows or columns.
//   • Idea: Determines the rank of a matrix by transforming it into row echelon form using Gaussian elimination. The rank is the number of non-zero rows in the echelon form, with a time complexity of O(N^3).
//   • Invariants: The number of non-zero rows processed so far equals the current rank.; All elements below the pivot in the current column are zeroed out.
//   • Tips: Always choose the largest absolute value pivot for numerical stability.; Swap rows to bring a non-zero element to the pivot position.
//   • Pitfalls: Floating point precision issues can lead to incorrect zero checks.; Forgetting to increment rank only when a valid pivot is found.
// - Scheduling jobs on two machines (array, greedy)
//   • When to use: Use when optimizing the order of a sequence of tasks on two machines to minimize total idle time or makespan. It is typically applied when a greedy exchange argument can prove optimality.
//   • Idea: This algorithm determines an optimal sequence for jobs on two machines by iteratively applying a greedy choice, often proven optimal via an exchange argument. It typically achieves an optimal solution in polynomial time, commonly O(N log N) or O(N^2).
//   • Invariants: The relative order of jobs already placed in the schedule is optimal.; The total idle time for the current prefix of scheduled jobs is correctly calculated.
//   • Tips: Focus on the local effect of swapping adjacent elements to derive the greedy criterion.; Identify a metric (e.g., total idle time or makespan) that changes predictably with swaps.
//   • Pitfalls: The greedy choice might not be globally optimal for problems with more than two machines.; Incorrectly defining the cost function for idle time or makespan can lead to suboptimal solutions.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

char* rankTeams(char** votes, int votesSize) {
    int teamCount = votesSize > 0 ? strlen(votes[0]) : 0;
    int rankCount = teamCount;
    int counts[26][26];
    for (int i = 0; i < 26; i++) {
        for (int j = 0; j < 26; j++) {
            counts[i][j] = 0;
        }
    }

    for (int v = 0; v < votesSize; v++) {
        for (int r = 0; r < rankCount; r++) {
            int teamIndex = votes[v][r] - 'A';
            counts[teamIndex][r]++;
        }
    }

    char* teams = (char*)malloc((teamCount + 1) * sizeof(char));
    for (int i = 0; i < teamCount; i++) {
        teams[i] = votes[0][i];
    }
    teams[teamCount] = '\0';

    int compare(const void* a, const void* b) {
        char teamA = *(const char*)a;
        char teamB = *(const char*)b;
        int indexA = teamA - 'A';
        int indexB = teamB - 'A';

        for (int r = 0; r < rankCount; r++) {
            if (counts[indexA][r] != counts[indexB][r]) {
                return counts[indexB][r] - counts[indexA][r];
            }
        }
        return teamA - teamB;
    }

    qsort(teams, teamCount, sizeof(char), compare);

    return teams;       
}
