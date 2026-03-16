// Source: https://leetcode.com/problems/erect-the-fence/   |   Difficulty: Hard
//
// Problem Description:
// You are given an array trees where trees[i] = [xi, yi] represents the location of a tree in the garden.
//
// Fence the entire garden using the minimum length of rope, as it is expensive. The garden is well-fenced only if all the trees are enclosed.
//
// Return the coordinates of trees that are exactly located on the fence perimeter. You may return the answer in any order.
//
// Example:
// Input: trees = [[1,1],[2,2],[2,0],[2,4],[3,3],[4,2]]
// Output: [[1,1],[2,0],[4,2],[3,3],[2,4]]
// Explanation: All the trees will be on the perimeter of the fence except the tree at [2, 2], which will be inside the fence.
//
// Constraints:
// 1 <= trees.length <= 3000
// 	trees[i].length == 2
// 	0 <= xi, yi <= 100
// 	All the given positions are unique.
//

class Solution {
    public int[][] outerTrees(int[][] trees) {
        Arrays.sort(trees, (a, b) -> a[0] == b[0] ? a[1] - b[1] : a[0] - b[0]);
        List<int[]> lower = new ArrayList<>();
        for (int[] tree : trees) {
            while (lower.size() >= 2 && cross(lower.get(lower.size() - 2), lower.get(lower.size() - 1), tree) < 0) {
                lower.remove(lower.size() - 1);
            }
            lower.add(tree);
        }
        List<int[]> upper = new ArrayList<>();
        for (int i = trees.length - 1; i >= 0; i--) {
            int[] tree = trees[i];
            while (upper.size() >= 2 && cross(upper.get(upper.size() - 2), upper.get(upper.size() - 1), tree) < 0) {
                upper.remove(upper.size() - 1);
            }
            upper.add(tree);
        }
        Set<int[]> set = new HashSet<>(lower);
        set.addAll(upper);
        return set.toArray(new int[set.size()][]);          
    }
}
