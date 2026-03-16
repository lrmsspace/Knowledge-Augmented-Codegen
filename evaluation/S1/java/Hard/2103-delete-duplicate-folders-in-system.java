// Source: https://leetcode.com/problems/delete-duplicate-folders-in-system/   |   Difficulty: Hard
//
// Problem Description:
// Due to a bug, there are many duplicate folders in a file system. You are given a 2D array paths, where paths[i] is an array representing an absolute path to the ith folder in the file system.
//
//
// 	For example, ["one", "two", "three"] represents the path "/one/two/three".
//
//
// Two folders (not necessarily on the same level) are identical if they contain the same non-empty set of identical subfolders and underlying subfolder structure. The folders do not need to be at the root level to be identical. If two or more folders are identical, then mark the folders as well as all their subfolders.
//
//
// 	For example, folders "/a" and "/b" in the file structure below are identical. They (as well as their subfolders) should all be marked:
//
// 	
// 		/a
// 		/a/x
// 		/a/x/y
// 		/a/z
// 		/b
// 		/b/x
// 		/b/x/y
// 		/b/z
// 	
// 	
// 	However, if the file structure also included the path "/b/w", then the folders "/a" and "/b" would not be identical. Note that "/a/x" and "/b/x" would still be considered identical even with the added folder.
//
//
// Once all the identical folders and their subfolders have been marked, the file system will delete all of them. The file system only runs the deletion once, so any folders that become identical after the initial deletion are not deleted.
//
// Return the 2D array ans containing the paths of the remaining folders after deleting all the marked folders. The paths may be returned in any order.
//
// Example:
// Input: paths = [["a"],["c"],["d"],["a","b"],["c","b"],["d","a"]]
// Output: [["d"],["d","a"]]
// Explanation: The file structure is as shown.
// Folders "/a" and "/c" (and their subfolders) are marked for deletion because they both contain an empty
// folder named "b".
//
// Constraints:
// 1 <= paths.length <= 2 * 104
// 	1 <= paths[i].length <= 500
// 	1 <= paths[i][j].length <= 10
// 	1 <= sum(paths[i][j].length) <= 2 * 105
// 	path[i][j] consists of lowercase English letters.
// 	No two paths lead to the same folder.
// 	For any folder not at the root level, its parent folder will also be in the input.
//
// Helpful references (internal KB):
// - Depth First Search (tree, graph, dfs)
//   • When to use: Use DFS to explore all reachable nodes from a starting point, find paths, or traverse tree-like structures. It's suitable for problems requiring exhaustive search or connectivity checks.
//   • Idea: Depth First Search is a graph traversal algorithm that explores as far as possible along each branch before backtracking. It typically uses a stack (explicit or implicit via recursion) and has a time complexity of O(V + E) for graphs and O(V) for trees.
//   • Invariants: All nodes reachable from the starting node are eventually visited.; The visited set/array accurately tracks all nodes currently in the recursion stack or already fully explored.
//   • Tips: Use a visited set or array to prevent cycles and redundant work.; Recursion is often the most natural way to implement DFS.
//   • Pitfalls: Stack overflow can occur with deep recursion on very large graphs.; Forgetting to mark nodes as visited can lead to infinite loops in cyclic graphs.
// - String Hashing (string, array, hashing, enumeration)
//   • When to use: Use string hashing to efficiently compare substrings or patterns within a larger text, or to quickly check for duplicate strings. It's ideal for problems requiring fast equality checks on string segments.
//   • Idea: String hashing converts a string or substring into a numerical hash value, allowing for O(1) comparison of substrings after O(N) precomputation. It typically uses polynomial hashing with a prime base and modulus to minimize collisions.
//   • Invariants: The hash value for the prefix S[0...i] is correctly computed and stored, based on the chosen polynomial hashing scheme.; The base 'p' and modulus 'm' remain constant throughout the hash computation for consistent results.
//   • Tips: Choose a large prime number for the base 'p' (e.g., 31, 53) to reduce collisions.; Select a large prime number for the modulus 'm' (e.g., 10^9+7, 10^9+9) to further minimize collision probability.
//   • Pitfalls: Avoid using 2^64 as a modulus, as specific collision-generating strings exist for this choice.; A small modulus 'm' or base 'p' drastically increases the likelihood of hash collisions.
// - Deleting from a data structure in_log_n (ds, segment-tree, dfs, recursion)
//   • When to use: Use when processing a sequence of additions, deletions, and queries offline, where elements have specific time intervals of existence. It efficiently handles dynamic data structure operations by leveraging a segment tree over time.
//   • Idea: This technique uses a segment tree over the timeline of queries to manage elements with varying lifespans. Queries are processed offline via DFS, adding elements upon entering a node and undoing additions upon exiting, achieving O(T(n) log n) deletion complexity.
//   • Invariants: When entering a segment tree node, all elements associated with that node's time range are added to the active data structure.; When exiting a segment tree node, all elements added upon entry are removed, restoring the data structure to its state before entering.
//   • Tips: Ensure the base data structure supports efficient addition and undo operations.; Carefully manage element additions and removals during DFS traversal.
//   • Pitfalls: Forgetting to undo changes when backtracking from a segment tree node.; Incorrectly mapping element lifespans to segment tree nodes.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    // Node represents a folder in the file system
    static class TrieNode {
        Map<String, TrieNode> children = new HashMap<>();
    }
    
    public List<List<String>> deleteDuplicateFolder(List<List<String>> paths) {
        // Build trie structure to represent the file system
        TrieNode root = new TrieNode();
        for (List<String> path : paths) {
            TrieNode current = root;
            for (String folder : path) {
                current.children.putIfAbsent(folder, new TrieNode());
                current = current.children.get(folder);
            }
        }
        
        // Map to count occurrences of each folder signature
        Map<String, Integer> signatureCount = new HashMap<>();
        
        // First DFS: compute signatures and count duplicates
        dfs(root, signatureCount);
        
        // Collect all remaining paths
        List<List<String>> result = new ArrayList<>();
        
        // Second DFS: collect paths that are not duplicates
        for (Map.Entry<String, TrieNode> entry : root.children.entrySet()) {
            List<String> path = new ArrayList<>();
            path.add(entry.getKey());
            String signature = computeSignature(entry.getValue(), signatureCount);
            if (signatureCount.get(signature) == 1) {
                collectPaths(entry.getValue(), path, signatureCount, result);
            }
        }
        
        return result;
    }
    
    // DFS to compute folder signatures and count occurrences
    private String dfs(TrieNode node, Map<String, Integer> signatureCount) {
        // Get all child signatures in sorted order
        List<String> childSignatures = new ArrayList<>();
        for (Map.Entry<String, TrieNode> entry : node.children.entrySet()) {
            String childName = entry.getKey();
            TrieNode childNode = entry.getValue();
            String childSignature = dfs(childNode, signatureCount);
            childSignatures.add("(" + childName + childSignature + ")");
        }
        
        Collections.sort(childSignatures);
        
        // Create signature for current folder
        StringBuilder signature = new StringBuilder();
        for (String childSig : childSignatures) {
            signature.append(childSig);
        }
        String folderSignature = signature.toString();
        
        // Count this signature
        signatureCount.put(folderSignature, signatureCount.getOrDefault(folderSignature, 0) + 1);
        
        return folderSignature;
    }
    
    // Helper method to compute signature of a node (without counting)
    private String computeSignature(TrieNode node, Map<String, Integer> signatureCount) {
        List<String> childSignatures = new ArrayList<>();
        for (Map.Entry<String, TrieNode> entry : node.children.entrySet()) {
            String childName = entry.getKey();
            TrieNode childNode = entry.getValue();
            String childSignature = computeSignature(childNode, signatureCount);
            childSignatures.add("(" + childName + childSignature + ")");
        }
        Collections.sort(childSignatures);
        StringBuilder signature = new StringBuilder();
        for (String childSig : childSignatures) {
            signature.append(childSig);
        }
        return signature.toString();
    }
    
    // Collect all paths that are not duplicates
    private void collectPaths(TrieNode node, List<String> currentPath, Map<String, Integer> signatureCount, List<List<String>> result) {
        // Add current path to result
        result.add(new ArrayList<>(currentPath));
        
        // Traverse children
        for (Map.Entry<String, TrieNode> entry : node.children.entrySet()) {
            String childName = entry.getKey();
            TrieNode childNode = entry.getValue();
            String childSignature = computeSignature(childNode, signatureCount);
            
            // Only traverse if this child is not a duplicate
            if (signatureCount.get(childSignature) == 1) {
                currentPath.add(childName);
                collectPaths(childNode, currentPath, signatureCount, result);
                currentPath.remove(currentPath.size() - 1);
            }
        }
    }
}
