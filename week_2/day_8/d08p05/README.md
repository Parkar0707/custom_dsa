# Day 8 Problem 5: Huffman Coding Compression - Optimal File Compression

## Problem Statement
Implement Huffman coding algorithm to create an optimal prefix-free binary code for data compression. Build a Huffman tree from frequency data to minimize average code length.

## Core Concepts

### Huffman Coding Principles
- **Goal**: Assign shorter codes to more frequent characters
- **Prefix-Free**: No code is prefix of another (enables unambiguous decoding)
- **Optimal**: Produces minimum average code length for given frequencies
- **Greedy**: Always combine two least frequent elements

### Why Huffman Coding?
- **Optimal**: Among all prefix-free codes with same alphabet
- **Practical**: Used in ZIP, JPEG, MP3, GZIP compression
- **Proven**: Huffman proved it's optimal through exchange argument
- **Efficient**: Linear time to build tree

## Key Concepts to Understand

1. **Frequency Analysis**: Count occurrences of each character
2. **Tree Construction**: 
   - Start with single-node tree for each character
   - Repeatedly merge two minimum-frequency trees
   - Root becomes the tree for all characters
3. **Code Generation**: Traverse tree (0 for left, 1 for right)
4. **Encoding**: Replace characters with codes
5. **Decoding**: Traverse tree using binary sequence

## Problem Variations to Consider

- **Adaptive Huffman**: Update frequencies as you encode
- **Canonical Huffman**: Optimize decoder with ordered bit patterns
- **Multiple Passes**: First pass counts frequencies, second encodes
- **Streaming**: Handle data arriving incrementally
- **Hybrid**: Combine with other compression (LZ77+Huffman)

## Example Walkthrough

### Sample Data
Text: "MISSISSIPPI" (11 characters)

Frequencies:
- M: 1
- I: 4
- S: 4
- P: 2

### Step 1: Create Leaf Nodes
```
M:1  P:2  I:4  S:4
```

### Step 2: Build Tree (always merge two minimum)

**Step 2a**: Merge M:1 and P:2
```
    MP:3
    / \
  M:1 P:2

I:4  S:4
```

**Step 2b**: Merge I:4 and S:4
```
MP:3    IS:8
         / \
        I:4 S:4

(Another view: now we have MP:3 and IS:8)
```

**Step 2c**: Merge MP:3 and IS:8
```
         Root:11
         /  \
       MP:3  IS:8
       / \   / \
     M:1 P:2 I:4 S:4
```

### Step 3: Generate Codes
- M: 00 (left, left)
- P: 01 (left, right)
- I: 10 (right, left)
- S: 11 (right, right)

### Step 4: Encode Text
- MISSISSIPPI
- 00 10 11 11 10 11 11 10 01 01 10
- Bit string: 001011110111011001010110

**Original**: 11 chars × 8 bits = 88 bits
**Compressed**: 24 bits (plus overhead for huffman table)

## Algorithm Outline

```
function buildHuffmanTree(frequencies):
    minHeap = new PriorityQueue()
    
    // Step 1: Create leaf nodes
    for each (char, freq) in frequencies:
        node = new TreeNode(char, freq)
        minHeap.insert(node, freq)
    
    // Step 2: Build tree
    while minHeap.size() > 1:
        node1 = minHeap.extract()  // min frequency
        node2 = minHeap.extract()  // second min
        
        parent = new TreeNode(null, node1.freq + node2.freq)
        parent.left = node1
        parent.right = node2
        
        minHeap.insert(parent, parent.freq)
    
    return minHeap.extract()  // root

function generateCodes(root, prefix, codeTable):
    if root is null:
        return
    
    if root is leaf:
        codeTable[root.char] = prefix
        return
    
    generateCodes(root.left, prefix + '0', codeTable)
    generateCodes(root.right, prefix + '1', codeTable)

function encode(text, codeTable):
    encoded = ""
    for each char in text:
        encoded += codeTable[char]
    return encoded

function decode(bitString, huffmanTree):
    decoded = ""
    current = huffmanTree
    
    for each bit in bitString:
        if bit == '0':
            current = current.left
        else:
            current = current.right
        
        if current is leaf:
            decoded += current.char
            current = huffmanTree
    
    return decoded
```

## Implementation Hints

1. **Priority Queue**: Essential for getting minimum frequencies
2. **Tree Node**: Store character, frequency, left/right children
3. **Code Table**: Map character → binary code string
4. **Prefix Property**: Guaranteed by tree structure
5. **Bit Operations**: Consider how to store/transmit binary efficiently

## Follow-up Questions

- How would you handle the huffman table in a compressed file?
- How would you decode without knowing the original text length?
- How would you implement adaptive Huffman (updating as you go)?
- What if characters have equal frequency?
- How would you handle very large files?

## Common Pitfalls to Avoid

1. ❌ Not using min-heap (inefficient sorting)
2. ❌ Stopping tree building too early
3. ❌ Assigning codes to internal nodes
4. ❌ Not transmitting huffman tree/table
5. ❌ Wrong bit direction (0 vs 1 for left/right)

## Complexity Analysis to Consider

- **Tree Building**: O(n log n) where n = alphabet size (using heap)
- **Code Generation**: O(n) to traverse tree
- **Encoding**: O(m × k) where m = text length, k = average code length
- **Decoding**: O(m × k)
- **Space**: O(n) for tree and code table

## Test Cases to Think Through

1. Single character (all same)
2. Two characters (equal frequency)
3. Exponential frequency distribution
4. Very long text
5. Text with punctuation/numbers
6. Decode and re-encode gives original
