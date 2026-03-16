// Source: https://leetcode.com/problems/the-number-of-weak-characters-in-the-game/   |   Difficulty: Medium
//
// Problem Description:
// You are playing a game that contains multiple characters, and each of the characters has two main properties: attack and defense. You are given a 2D integer array properties where properties[i] = [attacki, defensei] represents the properties of the ith character in the game.
//
// A character is said to be weak if any other character has both attack and defense levels strictly greater than this character's attack and defense levels. More formally, a character i is said to be weak if there exists another character j where attackj > attacki and defensej > defensei.
//
// Return the number of weak characters.
//
// Example:
// Input: properties = [[5,5],[6,3],[3,6]]
// Output: 0
// Explanation: No character has strictly greater attack and defense than the other.
//
// Constraints:
// 2 <= properties.length <= 105
// 	properties[i].length == 2
// 	1 <= attacki, defensei <= 105
//
// Helpful references (internal KB):
// - Mergesort (array, merge-sort, divide-and-conquer, recursion)
//   • When to use: Use when a stable sort with guaranteed O(N log N) time complexity is required, even if O(N) auxiliary space is acceptable. It is suitable for sorting linked lists efficiently.
//   • Idea: Mergesort is a divide-and-conquer algorithm that recursively divides an array into two halves, sorts them, and then merges the sorted halves. It guarantees O(N log N) time complexity and uses O(N) auxiliary space.
//   • Invariants: Before merging, the left subarray `a[lo..mid]` and right subarray `a[mid+1..hi]` are individually sorted.; After each recursive call `sort(a, aux, sub_lo, sub_hi)`, the subarray `a[sub_lo..sub_hi]` is sorted.
//   • Tips: Utilize an auxiliary array for the merging step to simplify implementation and ensure stability.; Mergesort is a stable sorting algorithm, preserving the relative order of equal elements.
//   • Pitfalls: The primary disadvantage is the requirement for O(N) extra space for the auxiliary array.; Implementing an in-place merge without significant extra space is complex and often less efficient.
// - Optimal schedule of jobs given their deadlines and durations (heap, interval, greedy, simulation)
//   • When to use: When needing to find an optimal schedule for a set of jobs, each with a deadline and duration, typically to maximize completed jobs or minimize total lateness. This approach often involves processing jobs based on deadlines and dynamically selecting tasks.
//   • Idea: This algorithm finds an optimal job schedule by processing jobs sorted by their deadlines, using a priority queue to manage available tasks. It greedily selects jobs with the shortest run-time that can be completed within the current time window, achieving an optimal solution in O(N log N) time complexity.
//   • Invariants: All jobs with deadlines greater than the current job's deadline have been considered.; The priority queue contains jobs that can potentially be scheduled within the current time window.
//   • Tips: Sort jobs by deadline in descending order to process later deadlines first.; Use a min-priority queue to efficiently retrieve the job with the least run-time.
//   • Pitfalls: Incorrectly sorting jobs (e.g., ascending deadline or by duration).; Not handling overlapping time intervals or deadlines properly.
// - Generating all K-combinations (array, enumeration, greedy)
//   • When to use: Use this when you need to iterate through all possible subsets of a fixed size K from a larger set, especially when a specific order like lexicographical is required.
//   • Idea: This algorithm systematically generates all unique combinations of K elements from a set of N elements. It typically proceeds in lexicographical order, allowing for efficient enumeration of all C(N, K) possibilities.
//   • Invariants: The current combination C is always sorted: C[0] < C[1] < ... < C[K-1].; All elements C[i] are distinct and within the range [0, N-1] (assuming 0-indexed).
//   • Tips: Start with the smallest lexicographical combination (e.g., {1, 2, ..., K}).; To find the next combination, locate the rightmost element that can be incremented.
//   • Pitfalls: Incorrectly handling boundary conditions when incrementing elements.; Duplicating combinations if not careful with the increment logic.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int numberOfWeakCharacters(int** properties, int propertiesSize, int* propertiesColSize) {
    // Sort properties by attack ascending, and by defense descending for equal attacks
    int aux[propertiesSize][2];
    for (int i = 0; i < propertiesSize; i++) {
        aux[i][0] = properties[i][0];
        aux[i][1] = properties[i][1];
    }

    // Mergesort implementation
    void merge(int arr[][2], int aux[][2], int lo, int mid, int hi) {
        for (int k = lo; k <= hi; k++) {
            aux[k][0] = arr[k][0];
            aux[k][1] = arr[k][1];
        }
        int i = lo, j = mid + 1;
        for (int k = lo; k <= hi; k++) {
            if (i > mid) {
                arr[k][0] = aux[j][0];
                arr[k][1] = aux[j][1];
                j++;
            } else if (j > hi) {
                arr[k][0] = aux[i][0];
                arr[k][1] = aux[i][1];
                i++;
            } else if (aux[i][0] < aux[j][0] || (aux[i][0] == aux[j][0] && aux[i][1] > aux[j][1])) {
                arr[k][0] = aux[i][0];
                arr[k][1] = aux[i][1];
                i++;
            } else {
                arr[k][0] = aux[j][0];
                arr[k][1] = aux[j][1];
                j++;
            }
        }
    }

    void sort(int arr[][2], int aux[][2], int lo, int hi) {
        if (hi <= lo) return;
        int mid = lo + (hi - lo) / 2;
        sort(arr, aux, lo, mid);
        sort(arr, aux, mid + 1, hi);
        merge(arr, aux, lo, mid, hi);
    }

    sort(aux, aux, 0, propertiesSize - 1);

    // Count weak characters
    int max_defense = 0;
    int weak_count = 0;

    for (int i = propertiesSize - 1; i >= 0; i--) {
        if (aux[i][1] < max_defense) {
            weak_count++;
        } else {
            if (aux[i][1] > max_defense) {
                max_defense = aux[i][1];
            }
        }
    }
    return weak_count;
}
