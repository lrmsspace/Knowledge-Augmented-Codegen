// Source: https://leetcode.com/problems/divide-players-into-teams-of-equal-skill/   |   Difficulty: Medium
//
// Problem Description:
// You are given a positive integer array skill of even length n where skill[i] denotes the skill of the ith player. Divide the players into n / 2 teams of size 2 such that the total skill of each team is equal.
//
// The chemistry of a team is equal to the product of the skills of the players on that team.
//
// Return the sum of the chemistry of all the teams, or return -1 if there is no way to divide the players into teams such that the total skill of each team is equal.
//
// Example:
// Input: skill = [3,2,5,1,3,4]
// Output: 22
// Explanation: 
// Divide the players into the following teams: (1, 5), (2, 4), (3, 3), where each team has a total skill of 6.
// The sum of the chemistry of all the teams is: 1 * 5 + 2 * 4 + 3 * 3 = 5 + 8 + 9 = 22.
//
// Constraints:
// 2 <= skill.length <= 105
// 	skill.length is even.
// 	1 <= skill[i] <= 1000
//
// Helpful references (internal KB):
// - Mergesort (array, merge-sort, divide-and-conquer, recursion)
//   • When to use: Use when a stable sort with guaranteed O(N log N) time complexity is required, even if O(N) auxiliary space is acceptable. It is suitable for sorting linked lists efficiently.
//   • Idea: Mergesort is a divide-and-conquer algorithm that recursively divides an array into two halves, sorts them, and then merges the sorted halves. It guarantees O(N log N) time complexity and uses O(N) auxiliary space.
//   • Invariants: Before merging, the left subarray `a[lo..mid]` and right subarray `a[mid+1..hi]` are individually sorted.; After each recursive call `sort(a, aux, sub_lo, sub_hi)`, the subarray `a[sub_lo..sub_hi]` is sorted.
//   • Tips: Utilize an auxiliary array for the merging step to simplify implementation and ensure stability.; Mergesort is a stable sorting algorithm, preserving the relative order of equal elements.
//   • Pitfalls: The primary disadvantage is the requirement for O(N) extra space for the auxiliary array.; Implementing an in-place merge without significant extra space is complex and often less efficient.
// - The Inclusion-Exclusion Principle (array, number, counting, sieve)
//   • When to use: Use when direct counting of elements satisfying specific conditions is difficult due to overlaps, and you need to find the count of elements satisfying at least one, exactly k, or none of several properties.
//   • Idea: The Inclusion-Exclusion Principle counts the size of a union of sets by alternately adding and subtracting the sizes of intersections of increasing numbers of sets. Its complexity is often exponential in the number of properties.
//   • Invariants: At the start of processing subsets of size k, the running total correctly accounts for all intersections of size less than k.; For every element x, its contribution to the total sum is 1 if it satisfies the target condition, and 0 otherwise.
//   • Tips: Clearly define the properties (P1, P2, ..., Pn) for which elements are counted.; Systematically calculate the sizes of all relevant intersections of properties.
//   • Pitfalls: Incorrectly defining the properties or the universe of elements being counted.; Errors in calculating the sizes of specific intersections of properties.
// - Finding the nearest pair of points (geometry, array, divide-and-conquer, merge-sort, two-pointers)
//   • When to use: Use this when finding the pair of points with the minimum Euclidean distance in a 2D plane. It efficiently handles large datasets by recursively dividing the problem and merging results.
//   • Idea: It finds the closest pair of points in a 2D plane by recursively dividing the set, solving subproblems, and merging results in O(N log N) time. The merge step efficiently handles cross-boundary pairs within a narrow strip.
//   • Invariants: The minimum distance returned by a recursive call is the true minimum for its input subset.; All points in the left subproblem have x-coordinates less than or equal to the median x-coordinate.
//   • Tips: Pre-sort points by x-coordinate to enable efficient splitting.; Maintain a y-sorted list of points for efficient merging of the strip.
//   • Pitfalls: An inefficient merge step can degrade complexity from O(N log N) to O(N^2).; Failing to correctly identify and process cross-boundary pairs.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

long long dividePlayers(int* skill, int skillSize) {
    // Sort the skill array using mergesort
    void merge(int* arr, int* aux, int left, int mid, int right) {
        int i = left;    // Starting index for left subarray
        int j = mid + 1; // Starting index for right subarray
        int k = left;    // Starting index to be sorted

        while (i <= mid && j <= right) {
            if (arr[i] <= arr[j]) {
                aux[k++] = arr[i++];
            } else {
                aux[k++] = arr[j++];
            }
        }

        while (i <= mid) {
            aux[k++] = arr[i++];
        }

        while (j <= right) {
            aux[k++] = arr[j++];
        }

        for (i = left; i <= right; i++) {
            arr[i] = aux[i];
        }
    }

    void mergeSort(int* arr, int* aux, int left, int right) {
        if (left < right) {
            int mid = left + (right - left) / 2;
            mergeSort(arr, aux, left, mid);
            mergeSort(arr, aux, mid + 1, right);
            merge(arr, aux, left, mid, right);
        }
    }

    int* aux = (int*)malloc(skillSize * sizeof(int));
    mergeSort(skill, aux, 0, skillSize - 1);
    free(aux);

    long long totalChemistry = 0;
    int teamSkill = skill[0] + skill[skillSize - 1];

    for (int i = 0; i < skillSize / 2; i++) {
        if (skill[i] + skill[skillSize - 1 - i] != teamSkill) {
            return -1;
        }
        totalChemistry += (long long)skill[i] * skill[skillSize - 1 - i];
    }

    return totalChemistry;      
}
