# Day 8 Problem 9: Git Commit History - Find Lowest Common Ancestor of Branches

## Problem Statement
Find the Lowest Common Ancestor (LCA) of two commits in a Git commit history. This is useful for understanding where branches diverged and for three-way merges.

## Core Concepts

### Lowest Common Ancestor (LCA)
- **Definition**: The most recent ancestor that both commits share
- **Significance**: Shows where branches split
- **Merge Base**: Used in Git merge operations
- **Ancestors**: All commits that lead to a commit (parent, grandparent, etc.)

### Git Commit DAG (Directed Acyclic Graph)
- **Commits as Nodes**: Each commit has unique hash
- **Parents as Edges**: Points to parent commit(s)
- **Multiple Parents**: Merge commits have 2+ parents
- **Not a Tree**: Same commit can be ancestor to multiple commits

### Tree vs Graph
- **Trees**: Each node has exactly one parent (LCA is unique)
- **DAGs**: Nodes can have multiple parents
- **Challenge**: Must handle multiple paths to same ancestor

## Key Concepts to Understand

1. **Ancestry**: Traverse back through parents
2. **Common Ancestor**: Appears in both commit histories
3. **Lowest/Most Recent**: Earliest one before divergence
4. **Multiple Paths**: Same ancestor reachable different ways
5. **Merge Commits**: Have multiple parents

## Problem Variations to Consider

- **Multiple LCAs**: In DAG, might have multiple valid answers
- **Minimal LCA**: Find most specific (lowest) common ancestor
- **All Ancestors**: Find all common ancestors
- **Distance Metrics**: Which LCA is closest to commits?
- **Three-way Merge**: Find LCA of two branches for merging

## Example Walkthrough

### Simple Linear History

```
commit A (initial)
  ↓
commit B
  ↓
commit C (main branch)
  ↓
commit D
```

**LCA(C, D) = C** (C is ancestor of D)
**LCA(B, D) = B** (B is ancestor of D)

### Branched History

```
        A
        |
        B
       / \
      C   D
      |   |
      E   F
```

**LCA(E, F) = B**
- E's ancestors: E → C → B → A
- F's ancestors: F → D → B → A
- Common: B, A
- LCA (lowest/most recent): B

### Merge Commit

```
    A
   / \
  B   C
  |   |
  D   E
   \ /
    F (merge commit)
    |
    G
```

**LCA(D, E) = A**
- D's ancestors: D → B → A
- E's ancestors: E → C → A
- Common: A
- LCA: A

**LCA(G, any earlier) = ancestry from that commit**

### Complex Example

```
        A
       / \
      B   C
      |\ /|
      D E F
       \|/
        G
```

**LCA(D, F) = B** (assuming edges: D→B→A, F→E→B→A or F→C→A)
- Note: This depends on exact parent relationships

## Algorithm Outline

### Approach 1: Find All Ancestors

```
function findAllAncestors(commit):
    ancestors = new Set()
    stack = [commit]
    
    while stack is not empty:
        current = stack.pop()
        
        if current in ancestors:
            continue  // Already processed
        
        ancestors.add(current)
        
        for each parent in current.parents:
            stack.push(parent)
    
    return ancestors

function findLCA(commit1, commit2):
    ancestors1 = findAllAncestors(commit1)
    ancestors2 = findAllAncestors(commit2)
    
    commonAncestors = ancestors1 ∩ ancestors2
    
    // LCA is deepest common ancestor
    // Need to find the one with maximum distance from root
    lca = commonAncestors.maxBy(x → depthFromCommit)
    
    return lca
```

### Approach 2: Simultaneous Traversal (BFS)

```
function findLCABFS(commit1, commit2):
    visited = new Set()
    queue1 = Queue([commit1])
    queue2 = Queue([commit2])
    
    while both queues not empty:
        next1 = queue1.dequeue()
        if next1 in visited:
            return next1  // Found LCA
        visited.add(next1)
        
        for each parent in next1.parents:
            queue1.enqueue(parent)
        
        next2 = queue2.dequeue()
        if next2 in visited:
            return next2  // Found LCA
        visited.add(next2)
        
        for each parent in next2.parents:
            queue2.enqueue(parent)
    
    return null  // No common ancestor
```

### Approach 3: Depth-based (for tree-like DAGs)

```
function getDepth(commit):
    // Distance from commit to root ancestor
    depth = 0
    current = commit
    visited = new Set()
    
    while current is not null and current not in visited:
        visited.add(current)
        current = current.parent
        depth++
    
    return depth

function findLCADepth(commit1, commit2):
    depth1 = getDepth(commit1)
    depth2 = getDepth(commit2)
    
    // Move the deeper one up to same level
    while depth1 > depth2:
        commit1 = commit1.parent
        depth1--
    
    while depth2 > depth1:
        commit2 = commit2.parent
        depth2--
    
    // Move both up simultaneously
    visited = new Set()
    while commit1 != commit2:
        if commit1 in visited:
            return commit1
        visited.add(commit1)
        
        if commit2 in visited:
            return commit2
        visited.add(commit2)
        
        commit1 = commit1.parent
        commit2 = commit2.parent
    
    return commit1
```

## Implementation Hints

1. **Commit Representation**: Hash as identifier, parents array
2. **Set Operations**: Efficiently find intersections
3. **Graph Traversal**: DFS/BFS to find all ancestors
4. **Cycle Handling**: Visited set prevents infinite loops
5. **Optimization**: Bidirectional search is faster

## Follow-up Questions

- How would you find all common ancestors, not just lowest?
- How would you find the best merge base when multiple LCAs exist?
- How would you efficiently implement this for large repositories?
- How would you use LCA for three-way merge?
- How would you visualize the commit graph?

## Common Pitfalls to Avoid

1. ❌ Infinite loops in DAG (forgetting visited set)
2. ❌ Misunderstanding "lowest" (most recent, not deepest)
3. ❌ Not handling merge commits with multiple parents
4. ❌ Assuming tree structure (not a DAG)
5. ❌ Off-by-one errors in depth calculation

## Complexity Analysis to Consider

- **Time**: 
  - Finding all ancestors: O(V + E) where V = commits, E = parent edges
  - Finding LCA: O(V + E) worst case
  - Optimized BFS: O(min(V, depth))
- **Space**: O(V) for visited/ancestor sets

## Test Cases to Think Through

1. Linear history (commit is ancestor of other)
2. Two commits with recent LCA
3. Two commits with distant LCA
4. Merge commits
5. Diamond pattern (multiple paths to ancestor)
6. Same commit (LCA is itself)
7. No common ancestor (different repositories)
8. Very deep history (stress test)
9. Wide history (many branches)
10. Complex merge patterns
