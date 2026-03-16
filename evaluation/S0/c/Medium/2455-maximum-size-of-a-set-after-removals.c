// Source: https://leetcode.com/problems/maximum-size-of-a-set-after-removals/   |   Difficulty: Medium
//
// Problem Description:
// You are given two 0-indexed integer arrays nums1 and nums2 of even length n.
//
// You must remove n / 2 elements from nums1 and n / 2 elements from nums2. After the removals, you insert the remaining elements of nums1 and nums2 into a set s.
//
// Return the maximum possible size of the set s.
//
// Example:
// Input: nums1 = [1,2,1,2], nums2 = [1,1,1,1]
// Output: 2
// Explanation: We remove two occurences of 1 from nums1 and nums2. After the removals, the arrays become equal to nums1 = [2,2] and nums2 = [1,1]. Therefore, s = {1,2}.
// It can be shown that 2 is the maximum possible size of the set s after the removals.
//
// Constraints:
// n == nums1.length == nums2.length
// 	1 <= n <= 2 * 104
// 	n is even.
// 	1 <= nums1[i], nums2[i] <= 109
//

int maximumSetSize(int* nums1, int nums1Size, int* nums2, int nums2Size) {
    #define TABLE_SIZE 20011

    typedef struct Node {
        int key;
        int count1;
        int count2;
        struct Node* next;
    } Node;

    Node* hashTable[TABLE_SIZE] = {0};

    int hashFunction(int key) {
        return key % TABLE_SIZE;
    }

    void insert(int key, int arrayId) {
        int hashIndex = hashFunction(key);
        Node* current = hashTable[hashIndex];
        while (current) {
            if (current->key == key) {
                if (arrayId == 1) current->count1++;
                else current->count2++;
                return;
            }
            current = current->next;
        }
        Node* newNode = (Node*)malloc(sizeof(Node));
        newNode->key = key;
        newNode->count1 = (arrayId == 1) ? 1 : 0;
        newNode->count2 = (arrayId == 2) ? 1 : 0;
        newNode->next = hashTable[hashIndex];
        hashTable[hashIndex] = newNode;
    }

    for (int i = 0; i < nums1Size; i++) {
        insert(nums1[i], 1);
    }
    for (int i = 0; i < nums2Size; i++) {
        insert(nums2[i], 2);
    }

    int totalUnique = 0;
    int commonElements = 0;

    for (int i = 0; i < TABLE_SIZE; i++) {
        Node* current = hashTable[i];
        while (current) {
            totalUnique++;
            if (current->count1 > 0 && current->count2 > 0) {
                commonElements++;
            }
            Node* temp = current;
            current = current->next;
            free(temp);
        }
    }

    int n = nums1Size; // since nums1Size == nums2Size
    int removalsPerArray = n / 2;

    int maxSetSize;
    if (commonElements >= removalsPerArray) {
        maxSetSize = totalUnique - removalsPerArray;
    } else {
        maxSetSize = totalUnique - commonElements - (removalsPerArray - commonElements);
    }

    return maxSetSize;      
}
