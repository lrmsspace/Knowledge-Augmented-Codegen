// Source: https://leetcode.com/problems/removing-minimum-number-of-magic-beans/   |   Difficulty: Medium
//
// Problem Description:
// You are given an array of positive integers beans, where each integer represents the number of magic beans found in a particular magic bag.
//
// Remove any number of beans (possibly none) from each bag such that the number of beans in each remaining non-empty bag (still containing at least one bean) is equal. Once a bean has been removed from a bag, you are not allowed to return it to any of the bags.
//
// Return the minimum number of magic beans that you have to remove.
//
// Example:
// Input: beans = [4,1,6,5]
// Output: 4
// Explanation: 
// - We remove 1 bean from the bag with only 1 bean.
//   This results in the remaining bags: [4,0,6,5]
// - Then we remove 2 beans from the bag with 6 beans.
//   This results in the remaining bags: [4,0,4,5]
// - Then we remove 1 bean from the bag with 5 beans.
//   This results in the remaining bags: [4,0,4,4]
// We removed a total of 1 + 2 + 1 = 4 beans to make the remaining non-empty bags have an equal number of beans.
// There are no other solutions that remove 4 beans or fewer.
//
// Constraints:
// 1 <= beans.length <= 105
// 	1 <= beans[i] <= 105
//

long long minimumRemoval(int* beans, int beansSize) {
    // Sort the array of beans
    qsort(beans, beansSize, sizeof(int), (int (*)(const void*, const void*))strcmp);

    long long totalBeans = 0;
    for (int i = 0; i < beansSize; i++) {
        totalBeans += beans[i];
    }

    long long minRemoval = totalBeans;
    for (int i = 0; i < beansSize; i++) {
        long long currentRemoval = totalBeans - (long long)(beansSize - i) * beans[i];
        if (currentRemoval < minRemoval) {
            minRemoval = currentRemoval;
        }
    }

    return minRemoval;      
}
