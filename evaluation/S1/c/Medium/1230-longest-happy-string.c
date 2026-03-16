// Source: https://leetcode.com/problems/longest-happy-string/   |   Difficulty: Medium
//
// Problem Description:
// A string s is called happy if it satisfies the following conditions:
//
//
// 	s only contains the letters 'a', 'b', and 'c'.
// 	s does not contain any of "aaa", "bbb", or "ccc" as a substring.
// 	s contains at most a occurrences of the letter 'a'.
// 	s contains at most b occurrences of the letter 'b'.
// 	s contains at most c occurrences of the letter 'c'.
//
//
// Given three integers a, b, and c, return the longest possible happy string. If there are multiple longest happy strings, return any of them. If there is no such string, return the empty string "".
//
// A substring is a contiguous sequence of characters within a string.
//
// Example:
// Input: a = 1, b = 1, c = 7
// Output: "ccaccbcc"
// Explanation: "ccbccacc" would also be a correct answer.
//
// Constraints:
// 0 <= a, b, c <= 100
// 	a + b + c > 0
//
// Helpful references (internal KB):
// - Priority Queues (array, heap, heap-select)
//   • When to use: Use when you need to efficiently retrieve the highest or lowest priority item from a dynamic collection. It's ideal for scenarios requiring frequent insertions and extractions of extreme values without full sorting.
//   • Idea: A Priority Queue is an abstract data type that provides efficient retrieval of the maximum or minimum element. It is typically implemented using a binary heap, which stores elements in an array representing a complete binary tree, maintaining the heap-ordered property for O(log N) insertion and deletion.
//   • Invariants: For a max-heap, every parent node's key is greater than or equal to its children's keys.; The heap structure is always a complete binary tree, represented contiguously in an array.
//   • Tips: Represent the complete binary tree using an array, often 1-indexed for simpler parent/child calculations.; Use 'swim' (bottom-up reheapify) after insertion to restore heap order.
//   • Pitfalls: Forgetting to handle 0-indexed vs 1-indexed array representations correctly (parent/child formulas differ).; Violating the heap-ordered property during updates or custom operations.
// - Optimal schedule of jobs given their deadlines and durations (heap, interval, greedy, simulation)
//   • When to use: When needing to find an optimal schedule for a set of jobs, each with a deadline and duration, typically to maximize completed jobs or minimize total lateness. This approach often involves processing jobs based on deadlines and dynamically selecting tasks.
//   • Idea: This algorithm finds an optimal job schedule by processing jobs sorted by their deadlines, using a priority queue to manage available tasks. It greedily selects jobs with the shortest run-time that can be completed within the current time window, achieving an optimal solution in O(N log N) time complexity.
//   • Invariants: All jobs with deadlines greater than the current job's deadline have been considered.; The priority queue contains jobs that can potentially be scheduled within the current time window.
//   • Tips: Sort jobs by deadline in descending order to process later deadlines first.; Use a min-priority queue to efficiently retrieve the job with the least run-time.
//   • Pitfalls: Incorrectly sorting jobs (e.g., ascending deadline or by duration).; Not handling overlapping time intervals or deadlines properly.
// - The Inclusion-Exclusion Principle (string, counting)
//   • When to use: Use when you need to determine the frequency of characters or substrings within a string. It is essential for tasks like anagram detection or checking character distribution.
//   • Idea: This technique involves iterating through a string to tally the occurrences of its constituent elements, typically characters or words. It generally operates in O(N) time complexity, where N is the string's length.
//   • Invariants: The count for each character reflects its total occurrences processed so far.; All characters encountered up to the current position have been tallied.
//   • Tips: Use a hash map (dictionary) for arbitrary character sets.; Use an array for fixed-size character sets (e.g., ASCII, lowercase English).
//   • Pitfalls: Forgetting to handle case sensitivity or ignore non-alphanumeric characters.; Incorrectly handling Unicode characters with fixed-size arrays.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

char* longestDiverseString(int a, int b, int c) {
    // Max-heap structure to store character counts and their corresponding characters
    typedef struct {
        int count;
        char ch;
    } HeapNode;

    // Swap two heap nodes
    void swap(HeapNode* x, HeapNode* y) {
        HeapNode temp = *x;
        *x = *y;
        *y = temp;
    }

    // Heapify function to maintain max-heap property
    void heapify(HeapNode heap[], int n, int i) {
        int largest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        if (left < n && heap[left].count > heap[largest].count)
            largest = left;
        if (right < n && heap[right].count > heap[largest].count)
            largest = right;
        if (largest != i) {
            swap(&heap[i], &heap[largest]);
            heapify(heap, n, largest);
        }
    }

    // Build max-heap from the array
    void buildHeap(HeapNode heap[], int n) {
        for (int i = n / 2 - 1; i >= 0; i--)
            heapify(heap, n, i);
    }

    // Extract max from the heap
    HeapNode extractMax(HeapNode heap[], int* n) {
        HeapNode root = heap[0];
        heap[0] = heap[*n - 1];
        (*n)--;
        heapify(heap, *n, 0);
        return root;
    }

    // Insert a node into the heap
    void insertHeap(HeapNode heap[], int* n, HeapNode node) {
        heap[*n] = node;
        (*n)++;
        int i = *n - 1;
        while (i != 0 && heap[(i - 1) / 2].count < heap[i].count) {
            swap(&heap[i], &heap[(i - 1) / 2]);
            i = (i - 1) / 2;
        }
    }

    // Initialize the heap with available characters
    HeapNode heap[3];
    int heapSize = 0;
    if (a > 0) { heap[heapSize++] = (HeapNode){a, 'a'}; }
    if (b > 0) { heap[heapSize++] = (HeapNode){b, 'b'}; }
    if (c > 0) { heap[heapSize++] = (HeapNode){c, 'c'}; }
    buildHeap(heap, heapSize);
    char* result = (char*)malloc((a + b + c + 1) * sizeof(char));
    int index = 0;
    while (heapSize > 0) {
        HeapNode first = extractMax(heap, &heapSize);
        int len = index >= 2 && result[index - 1] == first.ch && result[index - 2] == first.ch ? 1 : 2;
        for (int i = 0; i < len && first.count > 0; i++) {
            result[index++] = first.ch;
            first.count--;
        }
        if (first.count > 0) {
            if (heapSize == 0) break;
            HeapNode second = extractMax(heap, &heapSize);
            result[index++] = second.ch;
            second.count--;
            if (second.count > 0) {
                insertHeap(heap, &heapSize, second);
            }
            insertHeap(heap, &heapSize, first);
        }
    }
    result[index] = '\0';
    return result;
}
