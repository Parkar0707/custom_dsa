# Day 8 Problem 4: B-tree Database Index - Implement Database Indexing

## Problem Statement
Implement a B-tree data structure for database indexing. B-trees maintain sorted data and allow searches, sequential access, and insertions/deletions in logarithmic time.

## Core Concepts

### B-tree Properties
A B-tree of order m has these properties:
1. Every node has at most m children (and m-1 keys)
2. Every non-leaf node has at least ⌈m/2⌉ children (except root)
3. Root has at least 2 children
4. All leaves are at the same depth
5. Keys within a node are sorted
6. Each key has associated data (in index: row pointer)

### Why B-trees for Databases?
- **Disk-based**: Minimizes disk I/O (each node = one disk block)
- **Balanced**: Guarantees logarithmic depth
- **Efficient**: Searches, insertions, deletions all O(log n)
- **Range Queries**: Can efficiently find all keys in range

## Key Concepts to Understand

1. **Node Structure**:
   - Keys array (sorted)
   - Children pointers (for internal nodes)
   - Data pointers (for leaf nodes)

2. **Insertion**:
   - Find correct position
   - Insert if space available
   - Split node if full (cascading up)

3. **Deletion**:
   - More complex than insertion
   - May need to merge or redistribute

4. **Search**:
   - Binary search within node
   - Descend to appropriate child

## Problem Variations to Consider

- **B+ tree**: Only leaf nodes store data (more efficient)
- **Dynamic Order**: Start with small order, grow as needed
- **Bulk Loading**: Efficient initial tree creation
- **Delete Operations**: Implement full deletion
- **Range Queries**: Find all keys in [a, b]

## Example Walkthrough

### B-tree of Order 3 (max 2 keys, 3 children)

#### Initial: Insert 10, 20
```
[10, 20]
```

#### Insert 5
```
[5, 10, 20]
```

#### Insert 6 (node full, split)
```
      10
     /  \
   [5]  [20]
```
Wait, let me recalculate...

Insert 5, 6, 10, 20, 30:

```
     10
    /  \
  [5,6] [20,30]
```

#### Insert 15
```
     10
    /  \
  [5,6] [15,20,30]
```

#### Insert 25 (right child full)
```
      10, 20
     /  |  \
[5,6] [15][25,30]
```

#### Insert 2, 3, 4 (left child full)
```
        5, 10, 20
       /  |   |   \
    [2,3,4][6][15][25,30]
```

## Algorithm Outline

```
function search(key):
    current = root
    while current is not null:
        i = 0
        while i < current.keyCount and key > current.keys[i]:
            i++
        
        if i < current.keyCount and key == current.keys[i]:
            return current.data[i]
        
        if current is leaf:
            return null (not found)
        
        current = current.children[i]
    
    return null

function insert(key, data):
    if root is full:
        splitRoot()
    
    insertNonFull(root, key, data)

function insertNonFull(node, key, data):
    i = node.keyCount - 1
    
    if node is leaf:
        shift keys right to make space
        node.keys[i+1] = key
        node.data[i+1] = data
        node.keyCount++
    else:
        find correct child
        if child is full:
            splitChild(node, i+1, child)
            if key > node.keys[i]:
                i++
        insertNonFull(node.children[i], key, data)

function splitChild(parent, index, fullChild):
    newChild = new Node()
    newChild.isLeaf = fullChild.isLeaf
    newChild.keyCount = m/2 - 1
    
    copy right half of fullChild to newChild
    fullChild.keyCount = m/2 - 1
    
    shift parent's children right
    parent.children[index+1] = newChild
    
    shift parent's keys right
    parent.keys[index] = fullChild.keys[m/2-1]
    parent.keyCount++
```

## Implementation Hints

1. **Node Class**: Store keys, children, data pointers, key count
2. **Key Comparisons**: Implement proper comparison logic
3. **Index Management**: Carefully track array indices
4. **Bounds Checking**: Verify before accessing arrays
5. **Special Handling**: Root behaves differently on split

## Follow-up Questions

- How would you implement B+ trees (data only in leaves)?
- How would you perform range queries efficiently?
- How would you handle deletion?
- What happens if order changes?
- How would you implement persistence to disk?

## Common Pitfalls to Avoid

1. ❌ Off-by-one errors in array indices
2. ❌ Not splitting proactively (splitting on full descent)
3. ❌ Forgetting to update keyCount
4. ❌ Not maintaining sorted order within nodes
5. ❌ Incorrect child selection logic

## Complexity Analysis to Consider

- **Search**: O(log n)
- **Insert**: O(log n) (with up to one split per level)
- **Delete**: O(log n) (can be complex with merging)
- **Space**: O(n)

## Test Cases to Think Through

1. Insert into empty tree
2. Insert in order (1,2,3...)
3. Insert reverse order (n,n-1...)
4. Insert random order
5. Search for existing/non-existing keys
6. Fill entire levels
7. Multiple splits cascading
