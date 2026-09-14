# Day 22, Problem 7: Maximum XOR Queries

## Problem Statement
Given an array of numbers and queries, find the maximum XOR value of each query number with all array elements. Optimize using binary trie.

## Key Concepts

### Binary Trie (Bit Trie)
A Trie where each node has exactly 2 children (0 and 1), representing binary representation of numbers.

```
Numbers: [1, 2, 3]
Binary: 1=01, 2=10, 3=11

Bit Trie:
       root
      /    \
     0      1
    / \    / \
   1   -  0   1(match)
   |     / \
  (1)   1   -
        |
       (2)
```

### XOR Properties
```
0 ⊕ x = x
x ⊕ x = 0
x ⊕ y = y ⊕ x (commutative)
(x ⊕ y) ⊕ z = x ⊕ (y ⊕ z) (associative)

For maximum XOR:
- Pick opposite bit at each level (if possible)
- If bit is 1, choose 0 branch; if 0, choose 1 branch
```

## Approach

1. **Convert to Binary**: Represent all numbers as 32-bit (or 64-bit) binary
2. **Build Bit Trie**: Insert binary representation of all array elements
3. **Query Processing**: For each query number
   - Traverse Trie, greedily choosing opposite bit at each level
   - If opposite bit not available, take same bit
   - Construct resulting maximum XOR value
4. **Return Result**: XOR value achievable at each step

## Example Walkthrough

### Input:
```
Array: [1, 2, 3]
Binary representations (4-bit): [0001, 0010, 0011]
Queries: [4, 5]
```

### Build Bit Trie:
```
Insert 0001:
root → 0 → 0 → 0 → 1

Insert 0010:
root → 0 → 0 → 1 → 0

Insert 0011:
root → 0 → 0 → 1 → 1

Trie structure (relevant paths only):
         root
        /
       0
      /
     0
    / \
   0   1
   |  / \
   1 0   1
```

### Query 4 (0100):
```
Start at root, number = 0100

Bit 0 (MSB): bit=0
- Try opposite (1): not available
- Take same (0): available → XOR contributes 0

Bit 1: bit=1
- Try opposite (0): available → XOR contributes 1

Bit 2: bit=0
- Try opposite (1): available → XOR contributes 1

Bit 3 (LSB): bit=0
- Try opposite (1): available → XOR contributes 1

Path: 0 → 0 → 1 → 1 → 1 = 0111
Query: 0100
XOR Result: 0100 ⊕ 0111 = 0011 = 3
```

### Query 5 (0101):
```
Following similar process:
Best we can do is find the number that gives max XOR
Process bit by bit, choosing optimally
```

## Time & Space Complexity

| Operation | Complexity | Notes |
|-----------|-----------|-------|
| Build Bit Trie | O(n * 32) | n = array size |
| Single Query | O(32) | Fixed bits for integer |
| **Total (m queries)** | **O(n*32 + m*32)** | O(n + m) effectively |

### vs Naive: O(n*m) - Compare each query with each element

## Bit Manipulation Insights

```
XOR bit-by-bit:
- 0 ⊕ 0 = 0
- 0 ⊕ 1 = 1
- 1 ⊕ 0 = 1
- 1 ⊕ 1 = 0

To maximize XOR:
- At each bit position, get different bit if possible
- Prioritize higher-order bits (they contribute more)

Example:
 a = 0101 (5)
 b = 0011 (3)
 XOR = 0110 (6) ← Maximize this

To get maximum:
 a = 0101
 ? = 1??? (need opposite in bit 0)
 candidates: 1000-1111
 if 1010 exists → 0101 ⊕ 1010 = 1111 (15)
```

## Greedy Strategy

At each bit position during query:
1. Check if opposite bit exists in Trie at current position
2. If yes: take that branch (XOR bit = 1)
3. If no: take same branch (XOR bit = 0)

This greedy approach works because higher bits are more significant.

## Practical Considerations

1. **Fixed Bit Width**: Use 32-bit for regular integers, 64-bit for long
2. **Leading Zeros**: Consider only significant bits
3. **Negative Numbers**: Handle two's complement representation
4. **Memory**: Bit Trie uses more memory than hash table for large integers

## Questions to Ask Yourself

- Why does greedy bit selection work?
- How would you handle negative numbers?
- What if you need k-th maximum XOR instead of maximum?
- Can you solve this without Trie? (Answer: yes, but slower)

## Related Problems
- Maximum XOR (LeetCode 421)
- XOR queries with updates
- Bit manipulation patterns
- Trie for bit operations
