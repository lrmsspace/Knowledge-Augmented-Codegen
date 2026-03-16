// Source: https://leetcode.com/problems/eliminate-maximum-number-of-monsters/   |   Difficulty: Medium
//
// Problem Description:
// You are playing a video game where you are defending your city from a group of n monsters. You are given a 0-indexed integer array dist of size n, where dist[i] is the initial distance in kilometers of the ith monster from the city.
//
// The monsters walk toward the city at a constant speed. The speed of each monster is given to you in an integer array speed of size n, where speed[i] is the speed of the ith monster in kilometers per minute.
//
// You have a weapon that, once fully charged, can eliminate a single monster. However, the weapon takes one minute to charge. The weapon is fully charged at the very start.
//
// You lose when any monster reaches your city. If a monster reaches the city at the exact moment the weapon is fully charged, it counts as a loss, and the game ends before you can use your weapon.
//
// Return the maximum number of monsters that you can eliminate before you lose, or n if you can eliminate all the monsters before they reach the city.
//
// Example:
// Input: dist = [1,3,4], speed = [1,1,1]
// Output: 3
// Explanation:
// In the beginning, the distances of the monsters are [1,3,4]. You eliminate the first monster.
// After a minute, the distances of the monsters are [X,2,3]. You eliminate the second monster.
// After a minute, the distances of the monsters are [X,X,2]. You eliminate the third monster.
// All 3 monsters can be eliminated.
//
// Constraints:
// n == dist.length == speed.length
// 	1 <= n <= 105
// 	1 <= dist[i], speed[i] <= 105
//
// Helpful references (internal KB):
// - Mergesort (array, merge-sort, divide-and-conquer, recursion)
//   • When to use: Use when a stable sort with guaranteed O(N log N) time complexity is required, even if O(N) auxiliary space is acceptable. It is suitable for sorting linked lists efficiently.
//   • Idea: Mergesort is a divide-and-conquer algorithm that recursively divides an array into two halves, sorts them, and then merges the sorted halves. It guarantees O(N log N) time complexity and uses O(N) auxiliary space.
//   • Invariants: Before merging, the left subarray `a[lo..mid]` and right subarray `a[mid+1..hi]` are individually sorted.; After each recursive call `sort(a, aux, sub_lo, sub_hi)`, the subarray `a[sub_lo..sub_hi]` is sorted.
//   • Tips: Utilize an auxiliary array for the merging step to simplify implementation and ensure stability.; Mergesort is a stable sorting algorithm, preserving the relative order of equal elements.
//   • Pitfalls: The primary disadvantage is the requirement for O(N) extra space for the auxiliary array.; Implementing an in-place merge without significant extra space is complex and often less efficient.
// - Josephus Problem (number, simulation, recursion)
//   • When to use: Use when determining the survivor's position in a circular game where every k-th person is eliminated, especially for large N where direct simulation is too slow.
//   • Idea: This algorithm finds the position of the last remaining person in the Josephus problem by iteratively reducing the problem size using a recursive formula and modulo arithmetic. It achieves an optimized time complexity of O(k log n).
//   • Invariants: The number of remaining elements decreases in each recursive step.; The relative order of the remaining elements is preserved throughout the process.
//   • Tips: Handle the base case where n < k separately to avoid infinite loops or incorrect calculations.; Use 0-indexing for simpler modulo arithmetic in the recursive formulas.
//   • Pitfalls: Incorrectly handling index shifts after elements are removed can lead to wrong results.; Forgetting the base case n < k can lead to infinite recursion or incorrect behavior.
// - Optimal schedule of jobs given their deadlines and durations (array, heap, greedy)
//   • When to use: Use when given a set of tasks with deadlines and durations, and the objective is to maximize the number of completed tasks without interruption.
//   • Idea: This greedy algorithm aims to maximize the number of jobs completed by prioritizing tasks that finish earliest. It typically involves sorting and using a min-heap, achieving an O(N log N) time complexity.
//   • Invariants: All jobs processed up to the current point have been considered for scheduling.; The set of jobs in the heap represents the jobs currently scheduled to meet their deadlines.
//   • Tips: Sort jobs by their deadlines in ascending order.; Maintain a min-heap of durations for jobs currently scheduled.
//   • Pitfalls: Confusing job count maximization with total duration or profit.; Failing to update the current time correctly after scheduling a job.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int eliminateMaximum(int* dist, int distSize, int* speed, int speedSize) {
    // Calculate the time each monster takes to reach the city
    int* arrivalTimes = (int*)malloc(distSize * sizeof(int));
    for (int i = 0; i < distSize; i++) {
        arrivalTimes[i] = (dist[i] + speed[i] - 1) / speed[i]; // Ceiling division
    }

    // Mergesort implementation to sort arrival times
    void merge(int* arr, int* aux, int left, int mid, int right) {
        for (int k = left; k <= right; k++) {
            aux[k] = arr[k];
        }
        int i = left, j = mid + 1;
        for (int k = left; k <= right; k++) {
            if (i > mid) arr[k] = aux[j++];
            else if (j > right) arr[k] = aux[i++];
            else if (aux[i] <= aux[j]) arr[k] = aux[i++];
            else arr[k] = aux[j++];
        }
    }

    void mergeSort(int* arr, int* aux, int left, int right) {
        if (left >= right) return;
        int mid = left + (right - left) / 2;
        mergeSort(arr, aux, left, mid);
        mergeSort(arr, aux, mid + 1, right);
        merge(arr, aux, left, mid, right);
    }

    int* aux = (int*)malloc(distSize * sizeof(int));
    mergeSort(arrivalTimes, aux, 0, distSize - 1);
    free(aux);

    // Count how many monsters can be eliminated
    int count = 0;
    for (int i = 0; i < distSize; i++) {
        if (arrivalTimes[i] > count) {
            count++;
        } else {
            break;
        }
    }

    free(arrivalTimes);
    return count;       
}
