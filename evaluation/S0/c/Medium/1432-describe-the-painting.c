// Source: https://leetcode.com/problems/describe-the-painting/   |   Difficulty: Medium
//
// Problem Description:
// There is a long and thin painting that can be represented by a number line. The painting was painted with multiple overlapping segments where each segment was painted with a unique color. You are given a 2D integer array segments, where segments[i] = [starti, endi, colori] represents the half-closed segment [starti, endi) with colori as the color.
//
// The colors in the overlapping segments of the painting were mixed when it was painted. When two or more colors mix, they form a new color that can be represented as a set of mixed colors.
//
//
// 	For example, if colors 2, 4, and 6 are mixed, then the resulting mixed color is {2,4,6}.
//
//
// For the sake of simplicity, you should only output the sum of the elements in the set rather than the full set.
//
// You want to describe the painting with the minimum number of non-overlapping half-closed segments of these mixed colors. These segments can be represented by the 2D array painting where painting[j] = [leftj, rightj, mixj] describes a half-closed segment [leftj, rightj) with the mixed color sum of mixj.
//
//
// 	For example, the painting created with segments = [[1,4,5],[1,7,7]] can be described by painting = [[1,4,12],[4,7,7]] because:
//
// 	
// 		[1,4) is colored {5,7} (with a sum of 12) from both the first and second segments.
// 		[4,7) is colored {7} from only the second segment.
// 	
// 	
//
//
// Return the 2D array painting describing the finished painting (excluding any parts that are not painted). You may return the segments in any order.
//
// A half-closed segment [a, b) is the section of the number line between points a and b including point a and not including point b.
//
// Example:
// Input: segments = [[1,4,5],[4,7,7],[1,7,9]]
// Output: [[1,4,14],[4,7,16]]
// Explanation: The painting can be described as follows:
// - [1,4) is colored {5,9} (with a sum of 14) from the first and third segments.
// - [4,7) is colored {7,9} (with a sum of 16) from the second and third segments.
//
// Constraints:
// 1 <= segments.length <= 2 * 104
// 	segments[i].length == 3
// 	1 <= starti < endi <= 105
// 	1 <= colori <= 109
// 	Each colori is distinct.
//

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
long long** splitPainting(int** segments, int segmentsSize, int* segmentsColSize, int* returnSize, int** returnColumnSizes) {
    // Step 1: Create an array to hold color changes at each point
    int maxPoint = 100000; // Given constraint: endi <= 10^5
    long long* colorChanges = (long long*)calloc(maxPoint + 1, sizeof(long long));
    
    // Step 2: Record the color changes for each segment
    for (int i = 0; i < segmentsSize; i++) {
        int start = segments[i][0];
        int end = segments[i][1];
        int color = segments[i][2];
        
        colorChanges[start] += color; // Start of segment
        colorChanges[end] -= color;   // End of segment
    }
    
    // Step 3: Prepare to collect the result segments
    long long** result = (long long**)malloc((segmentsSize * 2) * sizeof(long long*));
    *returnColumnSizes = (int*)malloc((segmentsSize * 2) * sizeof(int));
    *returnSize = 0;
    
    long long currentColorSum = 0;
    int segmentStart = -1;
    
    // Step 4: Traverse the colorChanges array to form the result segments
    for (int point = 1; point <= maxPoint; point++) {
        if (colorChanges[point] != 0) {
            currentColorSum += colorChanges[point];
        }
        
        if (currentColorSum > 0) {
            if (segmentStart == -1) {
                segmentStart = point; // Start a new segment
            }
        } else {
            if (segmentStart != -1) {
                // End the current segment
                result[*returnSize] = (long long*)malloc(3 * sizeof(long long));
                result[*returnSize][0] = segmentStart;
                result[*returnSize][1] = point;
                result[*returnSize][2] = currentColorSum - colorChanges[point]; // Color sum before this point
                (*returnColumnSizes)[*returnSize] = 3;
                (*returnSize)++;
                
                segmentStart = -1; // Reset for next segment
            }
        }
    }
    
    free(colorChanges);
    
    return result;      
}
