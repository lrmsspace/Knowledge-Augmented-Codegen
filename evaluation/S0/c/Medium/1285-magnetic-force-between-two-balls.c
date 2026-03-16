// Source: https://leetcode.com/problems/magnetic-force-between-two-balls/   |   Difficulty: Medium
//
// Problem Description:
// In the universe Earth C-137, Rick discovered a special form of magnetic force between two balls if they are put in his new invented basket. Rick has n empty baskets, the ith basket is at position[i], Morty has m balls and needs to distribute the balls into the baskets such that the minimum magnetic force between any two balls is maximum.
//
// Rick stated that magnetic force between two different balls at positions x and y is |x - y|.
//
// Given the integer array position and the integer m. Return the required force.
//
// Example:
// Input: position = [1,2,3,4,7], m = 3
// Output: 3
// Explanation: Distributing the 3 balls into baskets 1, 4 and 7 will make the magnetic force between ball pairs [3, 3, 6]. The minimum magnetic force is 3. We cannot achieve a larger minimum magnetic force than 3.
//
// Constraints:
// n == position.length
// 	2 <= n <= 105
// 	1 <= position[i] <= 109
// 	All integers in position are distinct.
// 	2 <= m <= position.length
//

int maxDistance(int* position, int positionSize, int m) {
    // Sort the positions
    qsort(position, positionSize, sizeof(int), (int (*)(const void*, const void*))strcmp);

    int left = 1; // Minimum possible distance
    int right = position[positionSize - 1] - position[0]; // Maximum possible distance
    int result = 0;

    while (left <= right) {
        int mid = left + (right - left) / 2; // Midpoint distance
        int count = 1; // Count of balls placed
        int lastPosition = position[0]; // Last placed ball position

        // Try to place balls with at least 'mid' distance apart
        for (int i = 1; i < positionSize; i++) {
            if (position[i] - lastPosition >= mid) {
                count++;
                lastPosition = position[i];
            }
            if (count >= m) {
                break;
            }
        }

        // If we can place at least m balls, try for a larger minimum distance
        if (count >= m) {
            result = mid; // Update result
            left = mid + 1;
        } else {
            right = mid - 1; // Try smaller distance
        }
    }

    return result;      
}
