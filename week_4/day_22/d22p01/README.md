# Day 22, Problem 1: Autocomplete System

## Problem Statement
Design an autocomplete system that suggests search queries as a user types. The suggestions should be ranked by frequency/popularity.

## Key Concepts

### Data Structure: Trie (Prefix Tree)
A Trie is a tree where each node represents a character. The path from root to a node represents a prefix string.

```
    root
   /  |  \
  a   b   c
 / \       \
p   c       a
|   |       |
p   t       t
```

### Core Idea
- Store all possible searches in a Trie
- Each node tracks the frequency of words ending at that node
- When user types "ap", traverse to 'a' → 'p' node
- All words under this subtree are potential suggestions
- Rank them by frequency and return top-k results

## Approach

1. **Build the Trie**: Insert all previously searched queries with their frequency
2. **Search Prefix**: Traverse Trie to the node representing the typed prefix
3. **DFS Traversal**: From that node, perform DFS to find all words in the subtree
4. **Rank Results**: Sort by frequency (descending) and return top suggestions

## Example Walkthrough

### Input:
```
Queries: ["apple", "app", "application", "apply"]
Frequencies: [5, 8, 3, 6]
User types: "app"
```

### Process:
1. Build Trie with frequencies at each word node
2. Traverse to node 'a' → 'p' → 'p'
3. From this node, find all complete words:
   - "app" (frequency: 8)
   - "apple" (frequency: 5)
   - "application" (frequency: 3)
   - "apply" (frequency: 6)
4. Sort by frequency: ["app", "apply", "apple", "application"]
5. Return top-3: ["app", "apply", "apple"]

## Time & Space Complexity

| Operation | Complexity | Notes |
|-----------|-----------|-------|
| Insert word | O(m) | m = word length |
| Search prefix | O(p) | p = prefix length |
| DFS from node | O(n) | n = words in subtree |
| **Total for suggestion** | **O(p + n*m)** | Return top-k suggestions |

## Optimizations to Consider

1. **Store top-k at each node**: Maintain top suggestions at every node to avoid full DFS
   - Trade memory for faster query time
   
2. **Frequency caching**: Update frequencies based on recent searches
   
3. **Trie compression**: Merge single-child nodes (Patricia Trie)

## Questions to Ask Yourself

- How would you handle dynamic frequency updates (user searches a new query)?
- What if you need to return results faster? How would caching help?
- How does this scale with millions of queries?
- How would you implement auto-correction (did you mean "apple" instead of "aple")?

## Related Problems
- Search Suggestions (LeetCode 1268)
- Trie problems
- String matching problems
