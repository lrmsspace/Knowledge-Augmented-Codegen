// Source: https://leetcode.com/problems/merge-k-sorted-lists/   |   Difficulty: Hard
//
// Problem Description:
// You are given an array of k linked-lists lists, each linked-list is sorted in ascending order.
//
// Merge all the linked-lists into one sorted linked-list and return it.
//
// Example:
// Input: lists = [[1,4,5],[1,3,4],[2,6]]
// Output: [1,1,2,3,4,4,5,6]
// Explanation: The linked-lists are:
// [
//   1->4->5,
//   1->3->4,
//   2->6
// ]
// merging them into one sorted linked list:
// 1->1->2->3->4->4->5->6
//
// Constraints:
// k == lists.length
// 	0 <= k <= 104
// 	0 <= lists[i].length <= 500
// 	-104 <= lists[i][j] <= 104
// 	lists[i] is sorted in ascending order.
// 	The sum of lists[i].length will not exceed 104.
//
// Helpful references (internal KB):
// - Priority Queues (heap, stack, heap-select)
//   • When to use: Use when you need to efficiently retrieve the element with the highest (or lowest) priority from a collection, especially when elements are added or removed frequently.
//   • Idea: A priority queue is a data structure that allows efficient retrieval of the element with the highest or lowest priority, and efficient insertion of new elements. Operations typically run in logarithmic time, O(log N).
//   • Invariants: The priority queue maintains the heap property: parent nodes are always greater than/equal to (or less than/equal to) their children.; For a K-selection problem, the priority queue contains at most K elements, representing the K largest/smallest seen so far.
//   • Tips: Use a min-priority queue to find the K largest elements by keeping at most K elements.; Use a max-priority queue to find the K smallest elements by keeping at most K elements.
//   • Pitfalls: Confusing min-priority queue with max-priority queue for the desired extremum.; Inefficient underlying implementation leading to O(N) operations instead of O(log N).
// - Linked-list implementations of collections (linked-list, stack, simulation)
//   • When to use: Use when a Last-In, First-Out (LIFO) data structure is required, and dynamic size with efficient O(1) push and pop operations is crucial, especially without a fixed capacity.
//   • Idea: This describes implementing a stack using a singly linked list, where elements are added and removed from the head of the list. Both push and pop operations achieve O(1) time complexity.
//   • Invariants: The 'first' pointer always points to the top element of the stack, or is null if the stack is empty.; Each node's 'next' pointer correctly links to the subsequent element in the stack, maintaining the LIFO order.
//   • Tips: Maintain a 'first' pointer to the head of the linked list, representing the stack's top.; Push operation involves creating a new node, linking it to the current 'first', then updating 'first'.
//   • Pitfalls: Forgetting to handle the empty stack case for pop, leading to `NoSuchElementException`.; Incorrectly updating the 'first' pointer during push or pop, which can break the list structure.
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

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
struct ListNode* mergeKLists(struct ListNode** lists, int listsSize) {
    if (listsSize == 0) return NULL;

    // Min-heap implementation
    typedef struct {
        struct ListNode** data;
        int size;
        int capacity;
    } MinHeap;

    MinHeap* createHeap(int capacity) {
        MinHeap* heap = (MinHeap*)malloc(sizeof(MinHeap));
        heap->data = (struct ListNode**)malloc(capacity * sizeof(struct ListNode*));
        heap->size = 0;
        heap->capacity = capacity;
        return heap;
    }

    void swap(struct ListNode** a, struct ListNode** b) {
        struct ListNode* temp = *a;
        *a = *b;
        *b = temp;
    }

    void heapifyUp(MinHeap* heap, int index) {
        while (index > 0) {
            int parent = (index - 1) / 2;
            if (heap->data[parent]->val <= heap->data[index]->val) break;
            swap(&heap->data[parent], &heap->data[index]);
            index = parent;
        }
    }

    void heapifyDown(MinHeap* heap, int index) {
        while (2 * index + 1 < heap->size) {
            int left = 2 * index + 1;
            int right = 2 * index + 2;
            int smallest = left;
            if (right < heap->size && heap->data[right]->val < heap->data[left]->val) {
                smallest = right;
            }
            if (heap->data[index]->val <= heap->data[smallest]->val) break;
            swap(&heap->data[index], &heap->data[smallest]);
            index = smallest;
        }
    }

    void insert(MinHeap* heap, struct ListNode* node) {
        if (heap->size == heap->capacity) return; // Heap full
        heap->data[heap->size] = node;
        heapifyUp(heap, heap->size);
        heap->size++;
    }

    struct ListNode* extractMin(MinHeap* heap) {
        if (heap->size == 0) return NULL; // Heap empty
        struct ListNode* minNode = heap->data[0];
        heap->data[0] = heap->data[heap->size - 1];
        heap->size--;       
        heapifyDown(heap, 0);
        return minNode;
    }
    MinHeap* heap = createHeap(listsSize);
    for (int i = 0; i < listsSize; i++) {
        if (lists[i]) {
            insert(heap, lists[i]);
        }
    }
    struct ListNode dummy;
    struct ListNode* tail = &dummy;
    while (heap->size > 0) {
        struct ListNode* minNode = extractMin(heap);
        tail->next = minNode;
        tail = tail->next;
        if (minNode->next) {
            insert(heap, minNode->next);
        }
    }
    tail->next = NULL;
    free(heap->data);
    free(heap);
    return dummy.next;
}
