// Source: https://leetcode.com/problems/odd-even-jump/   |   Difficulty: Hard
//
// Problem Description:
// You are given an integer array arr. From some starting index, you can make a series of jumps. The (1st, 3rd, 5th, ...) jumps in the series are called odd-numbered jumps, and the (2nd, 4th, 6th, ...) jumps in the series are called even-numbered jumps. Note that the jumps are numbered, not the indices.
//
// You may jump forward from index i to index j (with i < j) in the following way:
//
//
// 	During odd-numbered jumps (i.e., jumps 1, 3, 5, ...), you jump to the index j such that arr[i] <= arr[j] and arr[j] is the smallest possible value. If there are multiple such indices j, you can only jump to the smallest such index j.
// 	During even-numbered jumps (i.e., jumps 2, 4, 6, ...), you jump to the index j such that arr[i] >= arr[j] and arr[j] is the largest possible value. If there are multiple such indices j, you can only jump to the smallest such index j.
// 	It may be the case that for some index i, there are no legal jumps.
//
//
// A starting index is good if, starting from that index, you can reach the end of the array (index arr.length - 1) by jumping some number of times (possibly 0 or more than once).
//
// Return the number of good starting indices.
//
// Example:
// Input: arr = [10,13,12,14,15]
// Output: 2
// Explanation: 
// From starting index i = 0, we can make our 1st jump to i = 2 (since arr[2] is the smallest among arr[1], arr[2], arr[3], arr[4] that is greater or equal to arr[0]), then we cannot jump any more.
// From starting index i = 1 and i = 2, we can make our 1st jump to i = 3, then we cannot jump any more.
// From starting index i = 3, we can make our 1st jump to i = 4, so we have reached the end.
// From starting index i = 4, we have reached the end already.
// In total, there are 2 different starting indices i = 3 and i = 4, where we can reach the end with some number of
// jumps.
//
// Constraints:
// 1 <= arr.length <= 2 * 104
// 	0 <= arr[i] < 105
//

int oddEvenJumps(int* arr, int arrSize) {
    int goodStartingIndices = 0;        
    int oddJumpNext[arrSize];
    int evenJumpNext[arrSize];
    int oddJumpReachable[arrSize];
    int evenJumpReachable[arrSize];
    for (int i = 0; i < arrSize; i++) {
        oddJumpNext[i] = -1;
        evenJumpNext[i] = -1;
        oddJumpReachable[i] = 0;
        evenJumpReachable[i] = 0;
    }
    oddJumpReachable[arrSize - 1] = 1;
    evenJumpReachable[arrSize - 1] = 1;
    goodStartingIndices = 1;
    typedef struct {
        int value;
        int index;
    } ValIndexPair;
    ValIndexPair valIndexPairs[arrSize];
    for (int i = 0; i < arrSize; i++) {
        valIndexPairs[i].value = arr[i];
        valIndexPairs[i].index = i;
    }
    int compareAsc(const void* a, const void* b) {
        ValIndexPair* pairA = (ValIndexPair*)a;
        ValIndexPair* pairB = (ValIndexPair*)b;
        if (pairA->value == pairB->value) {
            return pairA->index - pairB->index;
        }
        return pairA->value - pairB->value;
    }
    int compareDesc(const void* a, const void* b) {
        ValIndexPair* pairA = (ValIndexPair*)a;
        ValIndexPair* pairB = (ValIndexPair*)b;
        if (pairA->value == pairB->value) {
            return pairA->index - pairB->index;
        }
        return pairB->value - pairA->value;
    }
    void computeNextJumps(ValIndexPair* pairs, int size, int* nextJumps) {
        int stack[size];
        int stackSize = 0;
        for (int i = 0; i < size; i++) {
            int index = pairs[i].index;
            while (stackSize > 0 && stack[stackSize - 1] < index) {
                nextJumps[stack[--stackSize]] = index;
            }
            stack[stackSize++] = index;
        }
    }
    qsort(valIndexPairs, arrSize, sizeof(ValIndexPair), compareAsc);
    computeNextJumps(valIndexPairs, arrSize, oddJumpNext);
    qsort(valIndexPairs, arrSize, sizeof(ValIndexPair), compareDesc);
    computeNextJumps(valIndexPairs, arrSize, evenJumpNext);
    for (int i = arrSize - 2; i >= 0; i--) {
        if (oddJumpNext[i] != -1) {
            oddJumpReachable[i] = evenJumpReachable[oddJumpNext[i]];
        }
        if (evenJumpNext[i] != -1) {
            evenJumpReachable[i] = oddJumpReachable[evenJumpNext[i]];
        }
        if (oddJumpReachable[i]) {
            goodStartingIndices++;
        }
    }
    return goodStartingIndices;
}
