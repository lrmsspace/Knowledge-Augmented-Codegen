// Source: https://leetcode.com/problems/find-score-of-an-array-after-marking-all-elements/   |   Difficulty: Medium
//
// Problem Description:
// You are given an array nums consisting of positive integers.
//
// Starting with score = 0, apply the following algorithm:
//
//
// 	Choose the smallest integer of the array that is not marked. If there is a tie, choose the one with the smallest index.
// 	Add the value of the chosen integer to score.
// 	Mark the chosen element and its two adjacent elements if they exist.
// 	Repeat until all the array elements are marked.
//
//
// Return the score you get after applying the above algorithm.
//
// Example:
// Input: nums = [2,1,3,4,5,2]
// Output: 7
// Explanation: We mark the elements as follows:
// - 1 is the smallest unmarked element, so we mark it and its two adjacent elements: [2,1,3,4,5,2].
// - 2 is the smallest unmarked element, so we mark it and its left adjacent element: [2,1,3,4,5,2].
// - 4 is the only remaining unmarked element, so we mark it: [2,1,3,4,5,2].
// Our score is 1 + 2 + 4 = 7.
//
// Constraints:
// 1 <= nums.length <= 105
// 	1 <= nums[i] <= 106
//

long long findScore(int* nums, int numsSize) {
    typedef struct {
        int value;
        int index;
    } Element;

    int compare(const void* a, const void* b) {
        Element* elemA = (Element*)a;
        Element* elemB = (Element*)b;
        if (elemA->value == elemB->value) {
            return elemA->index - elemB->index;
        }
        return elemA->value - elemB->value;
    }

    Element* elements = (Element*)malloc(numsSize * sizeof(Element));
    for (int i = 0; i < numsSize; i++) {
        elements[i].value = nums[i];
        elements[i].index = i;
    }

    qsort(elements, numsSize, sizeof(Element), compare);

    int* marked = (int*)calloc(numsSize, sizeof(int));
    long long score = 0;

    for (int i = 0; i < numsSize; i++) {
        int idx = elements[i].index;
        if (!marked[idx]) {
            score += elements[i].value;
            marked[idx] = 1;
            if (idx > 0) {
                marked[idx - 1] = 1;
            }
            if (idx < numsSize - 1) {
                marked[idx + 1] = 1;
            }
        }
    }

    free(elements);
    free(marked);

    return score;       
}
