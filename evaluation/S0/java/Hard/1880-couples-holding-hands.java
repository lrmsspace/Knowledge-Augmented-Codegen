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

class Solution {
    public int minSwapsCouples(int[] row) {
        int n = row.length / 2;
        UnionFind uf = new UnionFind(n);

        for (int i = 0; i < n; i++) {
            int person1 = row[2 * i];
            int person2 = row[2 * i + 1];
            uf.union(person1 / 2, person2 / 2);
        }

        return n - uf.getCount();           
    }
}
