# DSA Quick Reference Guide

## 🚀 Algorithm Quick Lookup

### String Algorithms (Day 2)

| Code | Problem | Algorithm | Time | Space | Key Insight |
|------|---------|-----------|------|-------|------------|
| d02p01 | Protein Pattern | KMP | O(n+m) | O(m) | Failure function avoids backtracking |
| d02p02 | DNA Palindrome | Manacher's | O(n) | O(n) | Leverage mirror symmetry |
| d02p03 | Gene Autocomplete | Trie+DFS | O(m+k) | O(n*m) | Shared prefixes for efficiency |
| d02p04 | RNA Structure | Stack | O(n) | O(n) | Nesting validates with stack |
| d02p05 | CRISPR Design | Rolling Hash | O(n+m) | O(m) | Sliding window for hashing |
| d02p06 | Molecular Barcode | Hamming Dist | O(n²) | O(n) | Min distance for error correction |
| d02p07 | Protein Alignment | Wagner-Fischer | O(n·m) | O(n·m) | DP table for edit distance |
| d02p08 | Genome Compression | LZ77 | O(n·w) | O(w) | Dictionary-based compression |
| d02p09 | Codon Optimization | Greedy Replace | O(n·k) | O(1) | Local optimization per position |
| d02p10 | Phylo Tree Encoding | DFS Serialize | O(n) | O(n) | Depth-first traversal order |

### Hash Tables & Distributed Systems (Day 3)

| Code | Problem | Technique | Time | Space | Key Concept |
|------|---------|-----------|------|-------|------------|
| d03p01 | Distributed Cache | LRU Hash | O(1) | O(n) | Hashmap + doubly-linked list |
| d03p02 | Load Balancer | Consistent Hash | O(log m) | O(m) | Ring topology minimizes rehashing |
| d03p03 | DB Sharding | Histogram | O(n log n) | O(n) | Analyze distribution for balance |
| d03p04 | Blockchain Dedup | Bloom Filter | O(k) | O(m) | Probabilistic set membership |
| d03p05 | CDN Optimization | Geohashing | O(1) | O(m) | Grid-based location indexing |
| d03p06 | API Rate Limit | Sliding Window | O(1) | O(n) | Timestamp-based request tracking |
| d03p07 | Session Manager | TTL Hash | O(1) | O(n) | Expire old entries automatically |
| d03p08 | Analytics Aggregation | HyperLogLog | O(1) | O(log n) | Approximate cardinality counting |
| d03p09 | User Similarity | MinHash+LSH | O(k log n) | O(n·k) | Locality-sensitive hashing |
| d03p10 | Flow Anomaly | Count-Min Sketch | O(k) | O(k·n) | Frequency estimation structure |

### Linked Lists & Memory (Day 4)

| Code | Problem | Structure | Insert | Delete | Key Pattern |
|------|---------|-----------|--------|--------|------------|
| d04p01 | Memory Alloc | DLL | O(1) | O(1) | Doubly-linked for defragmentation |
| d04p02 | Browser History | DLL+Hash | O(1) | O(1) | LRU management with links |
| d04p03 | Scheduler Queue | Multi-list | O(1) | O(1) | Multiple queues by priority |
| d04p04 | Undo/Redo | DLL+Stack | O(1) | O(1) | Bidirectional traversal |
| d04p05 | Audio Buffer | Circular | O(1) | O(1) | Circular buffer for streaming |
| d04p06 | Packet Queue | Skip List | O(log n) | O(log n) | Multi-level for priority |
| d04p07 | Inode Manager | SLL | O(n) | O(1) | Free list management |
| d04p08 | Garbage Collector | Graph DFS | O(n) | - | Mark-sweep algorithm |
| d04p09 | Transaction Log | Persistent | O(1) | - | Write-ahead logging |
| d04p10 | Work Stealing | Concurrent | O(1) | O(1) | Lock-free queue design |

### Stacks & Queues (Day 5)

| Code | Problem | Type | Primary Op | Secondary | Pattern |
|------|---------|------|-----------|-----------|---------|
| d05p01 | Expression Parser | Stack | Push/Pop | Peek | Operator precedence |
| d05p02 | Assembly Line | Queue | Enqueue/Dequeue | Peek | FIFO simulation |
| d05p03 | Call Profiler | Stack | Push/Pop | Peek | Nested tracking |
| d05p04 | Retry Logic | PQueue | Insert | DeleteMin | Exponential backoff |
| d05p05 | Order Matching | Deque | Both ends | Peek | Buy/sell ordering |
| d05p06 | Frame Buffer | Circular | Enqueue | Dequeue | Jitter compensation |
| d05p07 | Reaction Sim | Stack | Push/Pop | Peek | DFS simulation |
| d05p08 | Elevator | PQueue | Insert | DeleteMin | Priority scheduling |
| d05p09 | Tab Manager | Stack | Push/Pop | Peek | LIFO recovery |
| d05p10 | Task Executor | Queue+PQueue | Insert | DeleteMin | Event loop |

### Recursion & Divide-and-Conquer (Day 6)

| Code | Problem | Technique | Recurrence | Complexity | Key Principle |
|------|---------|-----------|-----------|-----------|--------------|
| d06p01 | Circuit Routing | Backtracking | T(n) | O(b^d) | Explore all paths |
| d06p02 | Fractal Design | Recursion | T(n)=4T(n/3)+O(1) | O(n^log₃4) | Self-similar structure |
| d06p03 | Merge Sort External | D&C | T(n)=2T(n/2)+O(n) | O(n log n) | Out-of-core sorting |
| d06p04 | FFT | D&C | T(n)=2T(n/2)+O(n) | O(n log n) | Cooley-Tukey algorithm |
| d06p05 | Closest Pair | D&C | T(n)=2T(n/2)+O(n) | O(n log n) | Geometric divide |
| d06p06 | Matrix Mult | D&C | T(n)=7T(n/2)+O(n²) | O(n^2.81) | Strassen algorithm |
| d06p07 | Sudoku | Backtracking | T(n) | O(9^(81-k)) | CSP with pruning |
| d06p08 | Rotated Search | Binary | T(n)=T(n/2)+O(1) | O(log n) | Modified binary search |
| d06p09 | Convex Hull | D&C | T(n)=2T(n/2)+O(n) | O(n log n) | Graham scan variant |
| d06p10 | Topologies | Enumeration | T(n) | O(n!) | Generate all configs |

### Binary Search & Optimization (Day 7)

| Code | Problem | Variant | Search Space | Predicate | Optimality |
|------|---------|---------|--------------|-----------|-----------|
| d07p01 | Fuel Mix | Ternary Search | [0, max_ratio] | Monotonic function | Unimodal |
| d07p02 | Bandwidth | Answer Search | [0, max_capacity] | Feasible allocation | Minimization |
| d07p03 | Telescope | Float BS | [min_pos, max_pos] | Continuous function | Precision |
| d07p04 | Inventory | Answer Search | [0, max_storage] | Cost function | Minimization |
| d07p05 | Learning Rate | Exponential | [min_lr, max_lr] | Convergence rate | Maximization |
| d07p06 | Query Optimizer | Binary | [0, plan_space] | Cost-based | Minimization |
| d07p07 | Load Balance | Answer Search | [0, max_power] | Capacity check | Feasibility |
| d07p08 | Vehicle Speed | Binary | [0, max_speed] | Safety predicate | Constraint |
| d07p09 | Quantum Depth | Binary | [0, max_gates] | Depth function | Minimization |
| d07p10 | Auto-scaling | Answer Search | [min_resources, max] | Capacity check | Right-sizing |

---

## 📊 Complexity Cheat Sheet

### Time Complexities
```
O(1)      ← Constant
O(log n)  ← Binary search
O(n)      ← Linear scan
O(n log n)← Sort, optimal search
O(n²)     ← Nested loops
O(n³)     ← Triple nested
O(2^n)    ← Exponential
O(n!)     ← Factorial
```

### Common Data Structures
```
Array       | Insert: O(n) | Delete: O(n) | Search: O(n) or O(log n)
Linked List | Insert: O(1) | Delete: O(1) | Search: O(n)
Hash Table  | Insert: O(1) | Delete: O(1) | Search: O(1)
Binary Tree | Insert: O(log n) | Delete: O(log n) | Search: O(log n)
Heap        | Insert: O(log n) | DeleteMin: O(log n) | GetMin: O(1)
Graph       | Insert: O(1) | Delete: O(1) | Search: O(V+E)
Trie        | Insert: O(m) | Delete: O(m) | Search: O(m)
```

---

## 🎯 Problem Selection Guide

### If You Want to Practice...

**String Matching**
→ d02p01, d02p02, d02p05

**Data Structure Fundamentals**
→ d04p01, d04p02, d05p01, d05p02

**Distributed Systems**
→ d03p01, d03p02, d03p03

**Optimization Problems**
→ d07p01, d07p02, d07p04

**Graph/Tree Problems**
→ d06p05, d06p09, d06p10

**Probabilistic Algorithms**
→ d03p04, d03p08, d03p09, d03p10

**Memory Management**
→ d04p01, d04p07, d04p08

**Simulation Problems**
→ d05p02, d05p05, d05p07, d05p08

---

## ⚡ Algorithm Selection Decision Tree

### "I need to find something in a string"
- Exact string? → KMP (d02p01)
- Palindrome? → Manacher (d02p02)
- Prefix match? → Trie (d02p03)
- Substring? → Rolling Hash (d02p05)

### "I need to cache/store data"
- LRU requirement? → d03p01, d04p02
- Distributed? → Consistent Hash (d03p02)
- Rate limiting? → d03p06
- Session data? → d03p07

### "I need to process a sequence"
- Stack (LIFO)? → Parsing (d05p01), Simulation (d05p07)
- Queue (FIFO)? → Assembly line (d05p02), Scheduling (d05p04)
- Priority? → Elevator (d05p08), Task executor (d05p10)

### "I need to search or optimize"
- Sorted array? → Binary Search (d07p*)
- Unimodal function? → Ternary Search
- Find minimum? → Answer binary search
- Need integer optimum? → Binary + discrete check

### "I need to break problem into pieces"
- Divide & Conquer? → Merge sort (d06p03), FFT (d06p04)
- Backtracking? → Sudoku (d06p07), Routing (d06p01)
- Recursive structure? → Tree encoding (d02p10)

---

## 🔑 Key Implementation Patterns

### Linked List with Hashmap (LRU Cache)
```
Pattern: Fast lookup + Ordering
Use when: Need O(1) access AND need to maintain order
Examples: d03p01, d04p02
```

### Stack for Nesting
```
Pattern: Push on open, pop on close
Use when: Balanced pairs, precedence, nested structures
Examples: d02p04, d05p01, d05p07
```

### Hash with Counter
```
Pattern: Frequency tracking
Use when: Count occurrences, detect duplicates
Examples: d03p06, d03p07, d03p10
```

### Divide & Merge
```
Pattern: Recursively divide, then combine
Use when: Problem has optimal substructure
Examples: d06p03, d06p04, d06p05, d06p06
```

### Binary Search on Answer
```
Pattern: Search for minimum/maximum satisfying condition
Use when: Predicate is monotonic
Examples: d07p01-d07p10
```

---

## 🚨 Common Pitfalls & Solutions

| Pitfall | Solution |
|---------|----------|
| Off-by-one errors | Test with size 1, 2 arrays |
| Null pointer dereference | Check for empty cases |
| Integer overflow | Use long or mid = low + (high-low)/2 |
| Infinite loops | Verify loop termination condition |
| Wrong complexity | Count operations, don't guess |
| Cache invalidation | Clear on update/delete |
| Unbounded recursion | Verify base case exists |
| Memory leaks | Free deleted nodes/structures |

---

## 💡 Optimization Techniques

| Technique | When | Example |
|-----------|------|---------|
| Memoization | Overlapping subproblems | Caching in recursion |
| Precomputation | Same query repeated | Trie for autocomplete |
| Indexing | Fast lookup needed | Hash table |
| Approximation | Exact too slow | Bloom filter, HyperLogLog |
| Parallel | Multiple cores available | Work stealing queue |
| Lazy evaluation | Not all data needed | On-demand computation |

---

## ✅ Before You Start Each Problem

1. **Read the problem** 2-3 times
2. **Identify input/output** clearly
3. **Work through an example** by hand
4. **Recognize the pattern** (string? hash? search?)
5. **Choose data structure** based on operations
6. **Plan the algorithm** using implementation hints
7. **Code carefully** with edge cases
8. **Test thoroughly** with various inputs
9. **Analyze complexity** of your solution
10. **Optimize if needed** based on constraints

---

**Last Updated**: September 2026  
**Total Problems**: 60  
**Total Algorithms**: 40+  
**All Categorized & Indexed** ✓
