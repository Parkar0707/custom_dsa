# Asteroid Belt Density Mapping

## Problem Overview

A spacecraft is navigating through an asteroid belt. To avoid collisions, you need to identify the **k closest asteroids to the spacecraft's current position**. The spacecraft's limited computational resources mean you must do this efficiently.

Your task is to implement **quickselect** or **heap-based** approach to find the k-nearest asteroids without sorting the entire dataset.

## Context & Real-World Application

In space navigation and collision avoidance:
- Asteroid positions are continuously updated (3D coordinates)
- Need fast response time (can't sort millions of asteroids every update)
- Only care about nearest k asteroids (typically k << n)
- Quickselect: O(n) average time (better than O(n log n) sorting)
- Heap: O(n log k) when k << n
- Real systems: Use both methods depending on k value and data distribution

## Key Concepts to Understand

### Distance Metric
- Euclidean distance from spacecraft to asteroid: √(x² + y² + z²)
- Often work with squared distance to avoid expensive square root
- Comparison still works correctly: if a² < b² then a < b

### Quickselect Algorithm
- Select the kth smallest element in O(n) average time
- Partition array around pivot (like quicksort)
- Recursively search only the partition containing the kth element
- Avoid sorting unnecessary elements

### Min-Heap Approach
- Maintain a min-heap of asteroids sorted by distance
- Can be built in O(n) time or incrementally
- Extract k minimum elements efficiently
- Useful when k is much smaller than n

### Max-Heap Approach
- Maintain a max-heap of size k
- For each asteroid: if distance < max element, remove max and insert asteroid
- Final heap contains exactly k nearest asteroids
- Time: O(n log k), Space: O(k)

## Example Scenario

Spacecraft at position (0, 0) in 2D space (ignoring z for simplicity):

```
Asteroids (x, y) coordinates:
A: (3, 4)      → distance = √(9+16) = 5
B: (1, 1)      → distance = √(1+1) ≈ 1.41
C: (8, 0)      → distance = √(64+0) = 8
D: (1, 2)      → distance = √(1+4) ≈ 2.24
E: (6, 8)      → distance = √(36+64) = 10
F: (-3, -4)    → distance = √(9+16) = 5
G: (0, 2)      → distance = √(0+4) = 2

Find k=3 nearest asteroids:
Sorted by distance: B(1.41), G(2), D(2.24), A(5), F(5), C(8), E(10)

Answer: B, G, D are the 3 nearest
        (or A, F if tied at distance 5)

Using quickselect:
- Partition array, find the 3rd smallest distance element
- No need to sort positions 4-7 (beyond k=3)
- O(n) average vs O(n log n) for full sort
```

## What You Should Explore

1. **Distance calculation**:
   - Full Euclidean distance or squared distance?
   - Squared: avoid sqrt, but confirm comparison is still valid
   - 2D, 3D, or n-dimensional?

2. **Tiebreaking**:
   - If two asteroids are equidistant, does order matter?
   - If k=3 and 4 asteroids tie at same distance, return which 3?
   - Typical: any k of them is acceptable, or use a secondary sort

3. **Algorithm choice**:
   - Quickselect: O(n) average, O(n²) worst case (partition adversarial)
   - Min-heap: O(n + k log n) to build and extract k
   - Max-heap of size k: O(n log k), useful when k << n
   - Which is better depends on n, k, and constant factors

4. **Output format**:
   - Return the k asteroids themselves (coordinates)?
   - Return indices into the asteroid array?
   - Return distances?
   - Return sorted by distance?

5. **Edge cases**:
   - k = 1 (single nearest)
   - k = n (all asteroids)
   - k > n (more asteroids requested than exist)
   - Duplicate positions (same asteroid?)
   - Spacecraft at same position as asteroid (distance 0)?

## Example Input/Output Format

**Input:**
- Array of asteroids (coordinates: x, y, or x, y, z)
- Spacecraft position (x, y, z)
- Integer k (number of nearest to find)

**Output:**
- Array of k asteroids (or their indices) closest to spacecraft
- Optionally sorted by distance
- Handle ties consistently

## Hints on Approach

- Start with a simpler approach (heap or sort) to get correctness
- Profile performance: Is quickselect actually faster than sort for your k, n?
- Remember: Squared distance avoids sqrt but gives same ordering
- Consider: If asteroids move, how often do you recalculate?
- For production: Combine both methods (quickselect for k near n/2, heap for small k)

## Why This Matters in DSA

This problem teaches:
- **Quickselect** for efficient selection without sorting
- **Heap-based algorithms** for k-way operations
- **Space-time tradeoffs**: Sorting O(n log n) vs. quickselect O(n) vs. heap O(n log k)
- **Real constraints**: When you don't need a fully sorted result, don't compute it

---

**Difficulty:** Medium to Hard  
**Primary Concept:** Quickselect, Heap (Min/Max), K-way selection  
**Secondary Concepts:** Distance metrics, Algorithm tradeoffs
