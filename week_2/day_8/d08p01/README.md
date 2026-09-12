# Day 8 Problem 1: File System Directory Tree - Compute Disk Usage Efficiently

## Problem Statement
Compute the total disk usage of a file system directory tree efficiently. This involves traversing the entire directory structure and calculating the total size of all files while handling nested directories.

## Core Concepts

### Postorder DFS (Depth-First Search)
- **Definition**: Visit left subtree → visit right subtree → process current node
- **Why Postorder for This Problem**: 
  - You need to know the size of all children before calculating the parent's size
  - Process bottom-up from leaves to root
  - Perfect for aggregating values from entire subtree

### Tree Traversal Patterns
```
        root/          <- Process LAST
        /   \
      dir1  dir2       <- Process SECOND
      / \      |
    f1  f2   dir3      <- Process FIRST (leaves)
          /  \
        f3   f4
```

## Key Concepts to Understand

1. **Recursive Structure**: Each directory contains files and subdirectories (which are themselves directories)
2. **Aggregation**: Parent size = sum of children sizes
3. **Base Cases**: 
   - A file with no children has size = its own size
   - An empty directory has size = 0
4. **Time Complexity Consideration**: Visit each file and directory exactly once

## Problem Variations to Consider

- **With Metadata**: What if files/directories have different block sizes?
- **With Exclusions**: Skip certain file types or directories (e.g., hidden files, cache directories)
- **With Limits**: Find directories exceeding certain size thresholds
- **Path Tracking**: Return not just size, but also the path to each directory

## Example Walkthrough

### Directory Structure:
```
root/
├── file1.txt (50 KB)
├── dir1/
│   ├── file2.txt (30 KB)
│   └── file3.txt (20 KB)
└── dir2/
    ├── file4.txt (40 KB)
    └── subdir/
        └── file5.txt (60 KB)
```

### Step-by-Step Computation (Postorder):

1. **Process file1.txt**: size = 50 KB
2. **Process file2.txt**: size = 30 KB
3. **Process file3.txt**: size = 20 KB
4. **Process dir1**: size = 30 + 20 = 50 KB
5. **Process file4.txt**: size = 40 KB
6. **Process file5.txt**: size = 60 KB
7. **Process subdir**: size = 60 KB
8. **Process dir2**: size = 40 + 60 = 100 KB
9. **Process root**: size = 50 + 50 + 100 = 200 KB

## Algorithm Outline

```
function computeSize(node):
    if node is a file:
        return node.size
    
    totalSize = 0
    for each child in node.children:
        totalSize += computeSize(child)
    
    return totalSize
```

## Implementation Hints

1. **Data Structure**: You'll need to represent both files and directories
2. **Recursive Call**: Make recursive calls on children first
3. **Accumulation**: Sum up the results from child calls
4. **Return**: Return the total for the current node

## Follow-up Questions

- How would you handle symbolic links (shortcuts to other directories)?
- What if the directory tree is extremely deep? How would you handle stack overflow?
- How would you modify the algorithm to also track the largest directory?
- What if files can be shared between directories?

## Common Pitfalls to Avoid

1. ❌ Forgetting to add the current node's contribution before returning
2. ❌ Counting files multiple times if they appear in multiple places
3. ❌ Not handling the base case (file node) correctly
4. ❌ Modifying the tree structure during traversal

## Complexity Analysis to Consider

- **Time**: O(N) where N is total number of files/directories
- **Space**: O(H) where H is height (recursion stack)
  - Best case: Balanced tree → O(log N)
  - Worst case: Linear tree → O(N)

## Test Cases to Think Through

1. Single file
2. Empty directory
3. Deeply nested structure
4. Wide structure (many files in one directory)
5. Mixed sizes
