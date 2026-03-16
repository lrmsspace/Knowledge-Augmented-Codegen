// Source: https://leetcode.com/problems/couples-holding-hands/   |   Difficulty: Hard
//
// Problem Description:
// There are n couples sitting in 2n seats arranged in a row and want to hold hands.
//
// The people and seats are represented by an integer array row where row[i] is the ID of the person sitting in the ith seat. The couples are numbered in order, the first couple being (0, 1), the second couple being (2, 3), and so on with the last couple being (2n - 2, 2n - 1).
//
// Return the minimum number of swaps so that every couple is sitting side by side. A swap consists of choosing any two people, then they stand up and switch seats.
//
// Example:
// Input: row = [0,2,1,3]
// Output: 1
// Explanation: We only need to swap the second (row[1]) and third (row[2]) person.
//
// Constraints:
// 2n == row.length
// 	2 <= n <= 30
// 	n is even.
// 	0 <= row[i] < 2n
// 	All the elements of row are unique.
//

int minSwapsCouples(int* row, int rowSize) {
    int n = rowSize / 2;
    int *pos = (int*)malloc(rowSize * sizeof(int));
    for (int i = 0; i < rowSize; ++i) {
        pos[row[i]] = i;
    }

    int swaps = 0;
    for (int i = 0; i < rowSize; i += 2) {
        int first = row[i];
        int second = first ^ 1; /* partner */

        if (row[i + 1] != second) {
            /* swap */
            int secondPos = pos[second];
            /* update pos array */
            pos[row[i + 1]] = secondPos;
            pos[second] = i + 1;
            /* perform swap in row */
            int temp = row[i + 1];
            row[i + 1] = second;
            row[secondPos] = temp;

            swaps++;
        }
    }

    free(pos);
    return swaps;       
}
