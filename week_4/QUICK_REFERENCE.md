# Week 4 Quick Reference Guide

## Algorithm Complexity Cheat Sheet

### String Algorithms (Day 22)
| Algorithm | Build Time | Query Time | Space | Best For |
|-----------|-----------|-----------|-------|----------|
| Trie | O(k*m) | O(p) | O(k*m) | Autocomplete, prefix search |
| Aho-Corasick | O(k*m) | O(n) | O(k*m) | Multiple pattern matching |
| KMP | O(m) | O(n+m) | O(m) | Single pattern, linear time |
| Edit Distance | - | O(m*n) | O(m*n) | Spell checking, similarity |
| Binary Trie | O(n*32) | O(32) | O(n*32) | XOR queries, bit ops |

### Range Query Structures (Day 23)
| Structure | Build | Point Update | Range Query | Space |
|-----------|-------|--------------|-------------|-------|
| Segment Tree | O(n) | O(log n) | O(log n) | O(n) |
| Fenwick Tree | O(n) | O(log n) | O(log n) | O(n) |
| Sparse Table | O(n log n) | N/A | O(1) | O(n log n) |
| Segment + Lazy | O(n) | O(log n) | O(log n) | O(n) |

### Advanced String Structures (Day 24)
| Structure | Build | Query | Space | Use Case |
|-----------|-------|-------|-------|----------|
| Suffix Array | O(n log n) | O(m log n) | O(n) | Pattern search |
| Suffix Tree | O(n) | O(m) | O(n) | Full-text indexing |
| Z-Algorithm | O(n+m) | - | O(n+m) | Pattern matching |
| String Hash | O(n) | O(m) | O(n) | Fast comparison |

### Geometric Algorithms (Day 25)
| Algorithm | Time | Space | Key Point |
|-----------|------|-------|-----------|
| Convex Hull | O(n log n) | O(n) | Graham scan |
| Closest Pair | O(n log n) | O(n) | Divide-and-conquer |
| Point-in-Polygon | O(n) | O(n) | Ray casting |
| Line Intersection | O(1) | O(1) | Geometric math |
| Voronoi Diagram | O(n log n) | O(n) | Fortune's algorithm |

### Advanced Trees (Day 26)
| Structure | Search | Insert | Delete | Space |
|-----------|--------|--------|--------|-------|
| Splay Tree | O(log n) amort | O(log n) amort | O(log n) amort | O(n) |
| Treap | O(log n) exp | O(log n) exp | O(log n) exp | O(n) |
| Link-Cut Tree | O(log n) amort | O(log n) amort | O(log n) amort | O(n) |
| vEB Tree | O(log log U) | O(log log U) | O(log log U) | O(U) |

### Randomized Algorithms (Day 27)
| Algorithm | Time | Space | Guarantee |
|-----------|------|-------|-----------|
| Reservoir Sampling | O(n) | O(k) | Uniform sampling |
| Skip List | O(log n) exp | O(n) | High probability |
| Bloom Filter | O(k) | O(m) | False +ves only |
| Count-Min Sketch | O(k) | O(k*m) | Upper bound |
| HyperLogLog | O(1) | O(log log n) | Probabilistic |

### ML Algorithms (Day 29)
| Algorithm | Time | Space | Type |
|-----------|------|-------|------|
| K-Means | O(n*k*i*d) | O(n*d) | Unsupervised |
| KNN | O(n*d) | O(n*d) | Supervised |
| Decision Tree | O(n*m*log n) | O(m) | Supervised |
| Gradient Descent | O(i*n*d) | O(d) | Optimization |
| PCA | O(n*d²) | O(d²) | Dimensionality |

---

## Common Problem Patterns

### Problem Type → Solution Pattern

| Pattern | Day | Example | Approach |
|---------|-----|---------|----------|
| **Prefix search** | 22 | Autocomplete | Trie + DFS |
| **Multiple patterns** | 22 | Genome search | Aho-Corasick |
| **Spelling/similarity** | 22 | Spell checker | Edit distance + Trie |
| **Range operations** | 23 | Sum queries | Segment tree/Fenwick |
| **Dynamic updates** | 23 | Real-time analytics | Lazy propagation |
| **Substring search** | 24 | Plagiarism | Suffix array + LCP |
| **Point queries** | 25 | Closest pair | Divide-and-conquer |
| **Tree paths** | 26 | Path queries | Heavy-light decomp |
| **Stream processing** | 27 | Cardinality | HyperLogLog |
| **Concurrency** | 28 | Lock-free | CAS operations |
| **Classification** | 29 | Clustering | K-Means |
| **Full system** | 30 | Cache | Multiple techniques |

---

## Implementation Checklist

### Before Coding
- [ ] Identify input constraints
- [ ] Determine time/space limits
- [ ] Choose right data structure
- [ ] Plan algorithm steps
- [ ] Consider edge cases

### While Coding
- [ ] Start with clear variable names
- [ ] Add comments for complex logic
- [ ] Handle edge cases explicitly
- [ ] Test with examples
- [ ] Verify base cases

### After Coding
- [ ] Check boundary conditions
- [ ] Trace through examples
- [ ] Verify complexity
- [ ] Optimize if needed
- [ ] Consider alternative approaches

---

## Common Pitfalls by Topic

### Trie Problems
- ❌ Not marking word endings correctly
- ❌ Not handling prefix vs full word distinction
- ❌ Missing base cases in recursion
- ✅ Always track whether current node is word end

### Range Query Problems
- ❌ Off-by-one errors in indices
- ❌ Confusing left/right boundaries
- ❌ Not updating internal nodes in segment tree
- ✅ Use inclusive ranges [l, r] consistently

### String Algorithm Problems
- ❌ Confusing 0-indexed vs 1-indexed
- ❌ Not handling string edge cases
- ❌ Forgetting about wrapping in circular strings
- ✅ Build failure functions carefully

### Geometry Problems
- ❌ Floating point precision errors
- ❌ Not handling collinear points
- ❌ Wrong orientation/winding
- ✅ Use cross product for orientation

### Tree Problems
- ❌ Not maintaining tree invariants
- ❌ Forgetting to update all paths
- ❌ Confusing parent/child relationships
- ✅ Clear node structure definition

### Concurrent Problems
- ❌ Race conditions
- ❌ Deadlocks
- ❌ Not using proper synchronization
- ✅ Use established patterns carefully

---

## Quick Decision Trees

### Need to Search Strings?
```
Single pattern?
├─ Yes → KMP (O(n+m)) or use Trie
└─ No → Aho-Corasick (O(n+m))

Prefix matching?
├─ Yes → Trie
└─ No → Suffix array/tree

Need similarity?
├─ Yes → Edit distance
└─ No → Exact matching
```

### Need Range Queries?
```
Single point updates?
├─ Yes → Segment Tree / Fenwick
└─ No → Range updates → Lazy Propagation

Query type?
├─ Sum → Any work
├─ Min/Max → Segment Tree
├─ GCD → Segment Tree
└─ Custom → Segment Tree

Read-heavy?
├─ Yes → Sparse Table (O(1) query)
└─ No → Segment Tree/Fenwick
```

### Need Geometric Algorithm?
```
Need hull?
├─ Yes → Convex Hull (Graham/Jarvis)
└─ No → Continue

Need intersections?
├─ Yes → Sweep Line
└─ No → Continue

Need distance?
├─ Closest pair → Divide-and-conquer
├─ Distance queries → Voronoi/Delaunay
└─ Minimum radius → Welzl's algorithm
```

### Need Tree Algorithm?
```
Dynamic?
├─ Yes → Link-Cut Tree / Splay Tree
└─ No → Standard operations

Path queries?
├─ Yes → Heavy-Light Decomp / Centroid
└─ No → Tree DP

Self-balancing?
├─ Yes → Treap / Splay Tree
└─ No → Standard Binary Tree
```

### Need Data Structure for Integers?
```
Need fast operations?
├─ Yes, with large range → vEB Tree
├─ Yes, cache-friendly → Binary Trie
└─ Standard operations → Hash Table

Need randomization?
├─ Yes → Skip List / Treap
└─ No → Balanced BST
```

---

## Space vs Time Trade-offs

| Technique | Time Gain | Space Cost | When to Use |
|-----------|-----------|-----------|------------|
| Precomputation | ✓✓ Better | ✓✓ More | Frequent queries |
| Caching/Memoization | ✓ Better | ✓ More | Overlapping subproblems |
| Lazy Propagation | ✓✓ Better | Same | Range updates |
| Sparse Table | ✓✓✓ O(1) | ✓✓ O(n log n) | Immutable data |
| Persistent DS | ✓ Better | ✓✓✓ More | Version tracking |
| Compression | Same | ✓✓ Less | Memory limited |

---

## Interview Tips

### Explaining Your Approach
1. **State the problem**: "I need to find..."
2. **Identify constraints**: "The input can be..."
3. **Choose structure**: "I'll use X because..."
4. **Walk through example**: "Let me show how..."
5. **Analyze complexity**: "Time is O(...) because..."
6. **Discuss trade-offs**: "Another approach would..."

### Common Questions
- **Q: Can you optimize further?**
  - A: Check if you can trade space for time (caching, precomputation)

- **Q: What about edge cases?**
  - A: Empty input, single element, duplicates, large values

- **Q: How would you scale this?**
  - A: Distributed system, partitioning, consistent hashing

- **Q: Can you use simpler approach?**
  - A: Tradeoff analysis - which is better for given constraints?

---

## Study Resources by Topic

### Trie & Strings
- Practice: LeetCode Trie tag, String problems
- Concept: Suffix trees and suffix arrays (advanced)
- Theory: Pattern matching algorithms

### Range Queries
- Practice: Range sum, min, GCD queries
- Concept: Lazy propagation, persistent trees
- Theory: Query optimization techniques

### Geometry
- Practice: Line/polygon problems
- Concept: Cross product, orientation
- Theory: Computational geometry algorithms

### Advanced Trees
- Practice: Tree decomposition problems
- Concept: Self-balancing, randomization
- Theory: Amortized analysis

### ML
- Practice: Implement from scratch
- Concept: Mathematical foundations
- Theory: Convergence, optimization

### Systems
- Practice: Full system design
- Concept: Scalability patterns
- Theory: Distributed computing

---

## Performance Optimization Checklist

### Algorithm Level
- [ ] Correct complexity analysis
- [ ] Early termination conditions
- [ ] Pruning unnecessary branches
- [ ] Caching/memoization
- [ ] Bidirectional search

### Data Structure Level
- [ ] Right structure for problem
- [ ] Efficient operations
- [ ] Space optimization
- [ ] Lazy evaluation
- [ ] Compression techniques

### Implementation Level
- [ ] Avoid unnecessary allocations
- [ ] Use appropriate types
- [ ] Minimize function calls
- [ ] Cache locality
- [ ] Parallelization

### System Level
- [ ] Load balancing
- [ ] Sharding/partitioning
- [ ] Caching layers
- [ ] Concurrent access
- [ ] Monitoring

---

**Last Updated**: 2025
**Topics Covered**: 70+ problems across 9 days
**Total Study Time**: 60-100+ hours depending on depth
