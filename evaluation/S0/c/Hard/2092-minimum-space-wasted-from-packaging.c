// Source: https://leetcode.com/problems/minimum-space-wasted-from-packaging/   |   Difficulty: Hard
//
// Problem Description:
// You have n packages that you are trying to place in boxes, one package in each box. There are m suppliers that each produce boxes of different sizes (with infinite supply). A package can be placed in a box if the size of the package is less than or equal to the size of the box.
//
// The package sizes are given as an integer array packages, where packages[i] is the size of the ith package. The suppliers are given as a 2D integer array boxes, where boxes[j] is an array of box sizes that the jth supplier produces.
//
// You want to choose a single supplier and use boxes from them such that the total wasted space is minimized. For each package in a box, we define the space wasted to be size of the box - size of the package. The total wasted space is the sum of the space wasted in all the boxes.
//
//
// 	For example, if you have to fit packages with sizes [2,3,5] and the supplier offers boxes of sizes [4,8], you can fit the packages of size-2 and size-3 into two boxes of size-4 and the package with size-5 into a box of size-8. This would result in a waste of (4-2) + (4-3) + (8-5) = 6.
//
//
// Return the minimum total wasted space by choosing the box supplier optimally, or -1 if it is impossible to fit all the packages inside boxes. Since the answer may be large, return it modulo 109 + 7.
//
// Example:
// Input: packages = [2,3,5], boxes = [[4,8],[2,8]]
// Output: 6
// Explanation: It is optimal to choose the first supplier, using two size-4 boxes and one size-8 box.
// The total waste is (4-2) + (4-3) + (8-5) = 6.
//
// Constraints:
// n == packages.length
// 	m == boxes.length
// 	1 <= n <= 105
// 	1 <= m <= 105
// 	1 <= packages[i] <= 105
// 	1 <= boxes[j].length <= 105
// 	1 <= boxes[j][k] <= 105
// 	sum(boxes[j].length) <= 105
// 	The elements in boxes[j] are distinct.
//

int minWastedSpace(int* packages, int packagesSize, int** boxes, int boxesSize, int* boxesColSize) {
    const int MOD = 1000000007;
    qsort(packages, packagesSize, sizeof(int), cmpInt);

    long long minWaste = -1;
    for (int i = 0; i < boxesSize; ++i) {
        int *boxSizes = boxes[i];
        int boxCount = boxesColSize[i];
        qsort(boxSizes, boxCount, sizeof(int), cmpInt);

        long long waste = 0;
        int pkgIdx = 0;
        for (int j = 0; j < boxCount && pkgIdx < packagesSize; ++j) {
            int boxSize = boxSizes[j];
            if (boxSize < packages[pkgIdx]) continue;

            /* fit as many packages as possible into this box size */
            int startIdx = pkgIdx;
            while (pkgIdx < packagesSize && packages[pkgIdx] <= boxSize) {
                ++pkgIdx;
            }
            int fitCount = pkgIdx - startIdx;
            waste += (long long)fitCount * (boxSize) - (long long)(packages[pkgIdx - 1] + packages[startIdx]) * fitCount / 2;
            if (waste >= 0 && minWaste >= 0 && waste >= minWaste) break; /* early stop */
        }
        if (pkgIdx == packagesSize) { /* all packages fitted */
            if (minWaste == -1 || waste < minWaste) {
                minWaste = waste;
            }
        }
    }

    return (int)(minWaste == -1 ? -1 : (minWaste % MOD));       
}
