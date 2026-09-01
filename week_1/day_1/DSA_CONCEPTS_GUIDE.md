# DSA Concepts Guide: Essential Techniques for Practice Problems

A comprehensive guide to all the data structures and algorithms needed to solve the 9 space-themed DSA problems. This guide covers advanced concepts beyond basic programming.

---

## Table of Contents

1. [Sliding Window Technique](#1-sliding-window-technique)
2. [Two-Pointer Technique](#2-two-pointer-technique)
3. [Hashing & Hash Tables](#3-hashing--hash-tables)
4. [Kadane's Algorithm (Maximum Subarray)](#4-kadanes-algorithm-maximum-subarray)
5. [Prefix Sum](#5-prefix-sum)
6. [Quickselect Algorithm](#6-quickselect-algorithm)
7. [Heaps & Priority Queues](#7-heaps--priority-queues)
8. [Dynamic Programming & Longest Common Subsequence](#8-dynamic-programming--longest-common-subsequence)
9. [Circular Arrays & Cyclic Buffers](#9-circular-arrays--cyclic-buffers)
10. [K-way Merge Algorithm](#10-k-way-merge-algorithm)

---

## 1. Sliding Window Technique

### Concept Overview

The sliding window technique maintains a window of fixed or variable size that moves across a data structure (usually an array or string). Instead of recalculating for each position from scratch, you update the window by removing the leftmost element and adding a new rightmost element.

**Key Insight:** Avoid redundant calculations by maintaining state as you move.

### When to Use

- Finding maximum/minimum in all subarrays of size k
- Finding patterns in strings
- Calculating statistics on consecutive elements
- Noise filtering (like median filtering)

### Example 1: Fixed Window Size (Median Filtering)

```python
# Problem: Remove hot pixels using median of window
# Window size = 3, slide across array

def median_filter(arr, window_size=3):
    """Filter noise using median of sliding window"""
    result = []
    
    # For each position where a full window fits
    for i in range(len(arr) - window_size + 1):
        # Extract window
        window = arr[i:i + window_size]
        
        # Find median (middle value when sorted)
        window_sorted = sorted(window)
        median = window_sorted[window_size // 2]
        
        result.append(median)
    
    return result

# Example: Sensor data with hot pixel spike
sensor_data = [15, 16, 18, 95, 17, 19, 16, 18, 20]
#                              ↑ hot pixel
filtered = median_filter(sensor_data, 3)
# Window 1: [15,16,18] → sorted [15,16,18] → median 16
# Window 2: [16,18,95] → sorted [16,18,95] → median 18
# Window 3: [18,95,17] → sorted [17,18,95] → median 18 ✓ noise removed!
# ...
print(filtered)  # [16, 18, 18, 17, 17, 18, 18, 19]
```

### Example 2: Optimized Median Filtering (Better Approach)

```python
from collections import deque

def efficient_median_filter(arr, window_size=3):
    """Use deque for better efficiency"""
    if window_size > len(arr):
        return []
    
    result = []
    window = deque()
    
    for num in arr:
        # Add new element
        window.append(num)
        
        # Remove oldest if window exceeds size
        if len(window) > window_size:
            window.popleft()
        
        # Calculate median when window is full
        if len(window) == window_size:
            sorted_window = sorted(window)
            median = sorted_window[window_size // 2]
            result.append(median)
    
    return result

# Same example as before but more efficient
sensor_data = [15, 16, 18, 95, 17, 19, 16, 18, 20]
print(efficient_median_filter(sensor_data, 3))
# Output: [16, 18, 18, 17, 17, 18, 18, 19]

# Time Complexity: O(n*k*log k) where k=window size, n=array length
# Space Complexity: O(k)
```

### Key Points

- **Fixed Window:** Size doesn't change (like median filtering)
- **Variable Window:** Size changes based on conditions (like finding longest substring)
- **Optimization:** Use data structures (deque, heap) to avoid recalculating everything

### Used In

- **Problem 2:** Telescope Image Sensor Calibration (median filtering)
- **Problem 8:** DNA Sequence Mutation Detection (sliding window variant)

---

## 2. Two-Pointer Technique

### Concept Overview

Use two pointers moving through a data structure, often in opposite directions or at different speeds. This technique is powerful for problems involving:
- Finding pairs with target sum
- Removing duplicates in-place
- Reversing arrays
- Partitioning data

**Key Insight:** Pointers move based on logic, not always step-by-step.

### Example 1: Finding Duplicates (In-place Deduplication)

```python
def remove_duplicates(arr):
    """Remove duplicates from SORTED array in-place"""
    if len(arr) == 0:
        return 0
    
    # left pointer: where to write unique elements
    # right pointer: where to read from
    left = 0
    
    for right in range(1, len(arr)):
        if arr[right] != arr[left]:
            left += 1
            arr[left] = arr[right]
    
    return left + 1  # number of unique elements

# Example: Deduplication signal IDs
signals = [1, 1, 2, 2, 2, 3, 4, 4]
#          ↑ 
#         left (write pointer)
#             ↑
#            right (read pointer)

unique_count = remove_duplicates(signals)
print(signals[:unique_count])  # [1, 2, 3, 4]
print(f"Unique signals: {unique_count}")

# How it works:
# Start: left=0, right=1
# arr[1]=1 == arr[0]=1, so right++
# arr[2]=2 != arr[0]=1, so left++, arr[1]=2, right++
# arr[3]=2 == arr[1]=2, so right++
# ... continues until all processed
# Final array has unique elements at indices 0 to left
```

### Example 2: Two Pointers From Ends

```python
def move_zeros_to_end(arr):
    """Move all zeros to end while preserving order"""
    # left: position for next non-zero
    # right: current element
    left = 0
    
    for right in range(len(arr)):
        if arr[right] != 0:
            arr[left], arr[right] = arr[right], arr[left]
            left += 1
    
    return arr

movements = [1, 0, 2, 0, 3, 0, 4]
print(move_zeros_to_end(movements))
# Output: [1, 2, 3, 4, 0, 0, 0]

# Rover commands: move (non-zero), skip (zero)
# Efficiently reorganizes without extra space
```

### Example 3: Partition (Used in Quickselect)

```python
def partition(arr, low, high):
    """Partition array around pivot"""
    pivot = arr[high]
    left = low
    right = high - 1
    
    while left <= right:
        # Find element > pivot from left
        while left <= right and arr[left] <= pivot:
            left += 1
        
        # Find element < pivot from right
        while left <= right and arr[right] > pivot:
            right -= 1
        
        # Swap if pointers haven't crossed
        if left < right:
            arr[left], arr[right] = arr[right], arr[left]
    
    # Place pivot in correct position
    arr[left], arr[high] = arr[high], arr[left]
    return left

asteroid_distances = [3, 1, 4, 1, 5, 9, 2, 6]
pivot_idx = partition(asteroid_distances, 0, len(asteroid_distances) - 1)
print(f"Pivot at: {pivot_idx}, Array: {asteroid_distances}")
```

### Key Points

- **Same Direction:** Both pointers move forward (deduplication)
- **Opposite Direction:** One from start, one from end (reversing, finding pairs)
- **Different Speeds:** Fast pointer and slow pointer (detecting cycles)
- **Partition:** Rearranging elements around a pivot

### Used In

- **Problem 3:** Radio Telescope Signal Deduplication
- **Problem 5:** Spacecraft Memory Compaction
- **Problem 7:** Asteroid Belt Density Mapping (with quickselect)

---

## 3. Hashing & Hash Tables

### Concept Overview

Hash tables (dictionaries in Python, HashMap in Java) provide O(1) average-case lookup, insertion, and deletion. A hash function converts data to an index in the hash table.

**Key Insight:** Trade memory for speed - store what you've seen for instant lookup.

### Example 1: Deduplication with Hash Set

```python
def find_unique_signals(signal_stream):
    """Find unique signals from stream"""
    seen = set()  # Hash set for O(1) lookup
    unique = []
    
    for signal in signal_stream:
        if signal not in seen:  # O(1) lookup
            seen.add(signal)     # O(1) insertion
            unique.append(signal)
    
    return unique

# Incoming signals (with duplicates)
signals = ['A001', 'B042', 'A001', 'C999', 'B042', 'A001', 'D123']

result = find_unique_signals(signals)
print(result)
# Output: ['A001', 'B042', 'C999', 'D123']

# Time Complexity: O(n)
# Space Complexity: O(n) - for the hash set
```

### Example 2: Frequency Counting

```python
def count_signal_frequencies(signals):
    """Count how many times each signal appears"""
    frequency = {}  # Hash map
    
    for signal in signals:
        frequency[signal] = frequency.get(signal, 0) + 1
    
    return frequency

signals = ['A', 'B', 'A', 'C', 'A', 'B']
freq = count_signal_frequencies(signals)
print(freq)
# Output: {'A': 3, 'B': 2, 'C': 1}

# Find most common signal (for anomaly detection)
most_common = max(freq, key=freq.get)
print(f"Most common signal: {most_common}")  # 'A'
```

### Example 3: Two Sum Problem (Using Hash Map)

```python
def find_signal_pair_with_sum(signals, target_sum):
    """Find two signals that sum to target"""
    seen = {}  # signal -> index
    
    for i, signal in enumerate(signals):
        complement = target_sum - signal
        
        # Check if we've seen the complement before
        if complement in seen:  # O(1) lookup
            return [seen[complement], i]  # Found pair!
        
        seen[signal] = i
    
    return None

signals = [15, 7, 11, 4]
pair = find_signal_pair_with_sum(signals, 18)
print(pair)  # [0, 2] (signals[0]=15 + signals[2]=11 = 26)

# Without hash: O(n²) with nested loops
# With hash: O(n) single pass
```

### Example 4: Handling Collisions

```python
# Python dict handles collisions internally
# But good to understand what happens:

def simple_hash_table(data):
    """Conceptual hash table"""
    table = {}
    
    for key, value in data:
        # If key exists, update (collision handling)
        # Python dicts use open addressing + chaining internally
        table[key] = value
    
    return table

# Real world: duplicate packet sequence numbers
packets = [
    (101, "data_A"),
    (102, "data_B"),
    (101, "data_A_retransmitted"),  # Same sequence number!
]

packet_map = simple_hash_table(packets)
print(packet_map)
# Output: {101: 'data_A_retransmitted', 102: 'data_B'}
# Latest value wins (last insertion)
```

### Key Points

- **Hash Set:** For membership testing (O(1) lookup)
- **Hash Map:** For key-value storage (O(1) access)
- **Collision Handling:** Python handles internally
- **Load Factor:** When table gets full, rehashing occurs

### Used In

- **Problem 3:** Radio Telescope Signal Deduplication
- **Problem 8:** DNA Sequence Mutation Detection

---

## 4. Kadane's Algorithm (Maximum Subarray)

### Concept Overview

Kadane's algorithm finds the maximum sum of a contiguous subarray in O(n) time. It's a dynamic programming approach that tracks:
1. Maximum sum ending at current position
2. Maximum sum found so far

**Key Insight:** At each position, decide: extend the previous sequence or start fresh?

### Example 1: Basic Maximum Subarray

```python
def max_subarray_sum(arr):
    """Find maximum sum of contiguous subarray"""
    max_ending_here = arr[0]  # Best sum ending at current position
    max_so_far = arr[0]       # Best sum overall
    
    for i in range(1, len(arr)):
        # Either extend previous sequence or start new
        max_ending_here = max(arr[i], max_ending_here + arr[i])
        
        # Update global maximum
        max_so_far = max(max_so_far, max_ending_here)
    
    return max_so_far

# Power output changes when rotating panels
power_changes = [-2, 5, -1, 8, 2, -3, 1]
#                                ↑↑↑
#                          Best subarray

result = max_subarray_sum(power_changes)
print(f"Maximum power gain: {result}")  # 14 (subarray [5, -1, 8, 2])

# Trace:
# i=0: max_ending=−2, max_so_far=−2
# i=1: max_ending=max(5, −2+5)=5, max_so_far=5
# i=2: max_ending=max(−1, 5−1)=4, max_so_far=5
# i=3: max_ending=max(8, 4+8)=12, max_so_far=12
# i=4: max_ending=max(2, 12+2)=14, max_so_far=14
# i=5: max_ending=max(−3, 14−3)=11, max_so_far=14
# i=6: max_ending=max(1, 11+1)=12, max_so_far=14

# Time Complexity: O(n)
# Space Complexity: O(1)
```

### Example 2: With Index Tracking

```python
def max_subarray_with_indices(arr):
    """Find max subarray AND return start/end indices"""
    max_ending_here = arr[0]
    max_so_far = arr[0]
    
    temp_start = 0  # Start of current subarray
    start = 0       # Start of best subarray
    end = 0         # End of best subarray
    
    for i in range(1, len(arr)):
        # If adding new element is better than continuing
        if arr[i] > max_ending_here + arr[i]:
            max_ending_here = arr[i]
            temp_start = i  # Reset start position
        else:
            max_ending_here += arr[i]
        
        # Update global max
        if max_ending_here > max_so_far:
            max_so_far = max_ending_here
            start = temp_start
            end = i
    
    return max_so_far, start, end

power_changes = [-2, 5, -1, 8, 2, -3, 1]
max_gain, panel_start, panel_end = max_subarray_with_indices(power_changes)

print(f"Max gain: {max_gain}")  # 14
print(f"Panels to rotate: {panel_start} to {panel_end}")  # 1 to 4
print(f"Actual panels: {power_changes[panel_start:panel_end+1]}")  # [5, -1, 8, 2]
```

### Example 3: Modified Kadane (With Constraint)

```python
def max_subarray_with_constraint(arr, min_size, max_size):
    """Maximum subarray with size constraints"""
    n = len(arr)
    max_gain = float('-inf')
    
    # Try all subarrays within size constraints
    for i in range(n):
        current_sum = 0
        for j in range(i, n):
            current_sum += arr[j]
            subarray_size = j - i + 1
            
            if min_size <= subarray_size <= max_size:
                max_gain = max(max_gain, current_sum)
    
    return max_gain

# Real constraint: can only rotate 2-5 panels at once
power_changes = [-2, 5, -1, 8, 2, -3, 1]
result = max_subarray_with_constraint(power_changes, 2, 5)
print(f"Max gain (with constraints): {result}")

# Time Complexity: O(n²) - not as efficient as pure Kadane
# But respects problem constraints
```

### Key Points

- **Invariant:** max_ending_here tracks best sum ending at current position
- **Decision:** Extend or restart - depends on whether current element helps
- **Edge Cases:** All negative numbers (still need to return one)
- **Variant:** Constraints on subarray size, minimum sum threshold, etc.

### Used In

- **Problem 4:** Solar Panel Array Optimization

---

## 5. Prefix Sum

### Concept Overview

Prefix sum is a technique where you precompute cumulative sums up to each position. This allows you to calculate the sum of any subarray in O(1) time after O(n) preprocessing.

**Key Insight:** Trade space (memory) for speed (time).

### Formula

```
prefix[i] = prefix[i-1] + arr[i]
sum(arr[j:i+1]) = prefix[i] - prefix[j-1]
```

### Example 1: Basic Prefix Sum

```python
def compute_prefix_sum(arr):
    """Compute prefix sum array"""
    n = len(arr)
    prefix = [0] * (n + 1)  # Extra space to avoid index issues
    
    for i in range(n):
        prefix[i + 1] = prefix[i] + arr[i]
    
    return prefix

def range_sum(prefix, left, right):
    """Get sum of arr[left:right+1] in O(1)"""
    return prefix[right + 1] - prefix[left]

# Movement commands: +1 for right, -1 for left
commands = [1, 1, -1, 1, -1]

prefix = compute_prefix_sum(commands)
print(f"Prefix sum: {prefix}")  # [0, 1, 2, 1, 2, 1]

# What's rover position after command 2?
position_after_2 = range_sum(prefix, 0, 2)
print(f"Position after 2 commands: {position_after_2}")  # 2

# What's position change from command 1 to 4?
change = range_sum(prefix, 1, 4)
print(f"Position change (commands 1-4): {change}")  # 0
```

### Example 2: 2D Prefix Sum (Rectangle Sum)

```python
def compute_2d_prefix_sum(matrix):
    """Compute 2D prefix sum for submatrix queries"""
    rows, cols = len(matrix), len(matrix[0])
    prefix = [[0] * (cols + 1) for _ in range(rows + 1)]
    
    for i in range(1, rows + 1):
        for j in range(1, cols + 1):
            prefix[i][j] = (
                matrix[i-1][j-1] +
                prefix[i-1][j] +        # Sum above
                prefix[i][j-1] -        # Sum left
                prefix[i-1][j-1]        # Subtract overlap
            )
    
    return prefix

def submatrix_sum(prefix, r1, c1, r2, c2):
    """Sum of submatrix from (r1,c1) to (r2,c2)"""
    return (
        prefix[r2+1][c2+1] -
        prefix[r1][c2+1] -
        prefix[r2+1][c1] +
        prefix[r1][c1]
    )

# 2D asteroid positions (density map)
asteroid_density = [
    [1, 2, 3],
    [4, 5, 6],
    [7, 8, 9]
]

prefix_2d = compute_2d_prefix_sum(asteroid_density)

# Sum of asteroids in rectangle from (0,0) to (1,1)
density = submatrix_sum(prefix_2d, 0, 0, 1, 1)
print(f"Asteroids in zone: {density}")  # 1+2+4+5 = 12
```

### Example 3: Boundary Checking (Rover Problem)

```python
def validate_path(commands, x_min, x_max, y_min, y_max):
    """Check if rover path stays within bounds"""
    # Convert commands to coordinates
    x, y = 0, 0
    positions = [(x, y)]  # Starting position
    
    for cmd in commands:
        if cmd == 'R':
            x += 1
        elif cmd == 'L':
            x -= 1
        elif cmd == 'U':
            y += 1
        elif cmd == 'D':
            y -= 1
        
        positions.append((x, y))
    
    # Validate all positions
    for x, y in positions:
        if not (x_min <= x <= x_max and y_min <= y <= y_max):
            return False, (x, y)  # Out of bounds!
    
    return True, positions[-1]  # Safe path, final position

# Rover commands
commands = ['R', 'R', 'U', 'U', 'L']
valid, result = validate_path(commands, -5, 5, -5, 5)

print(f"Path valid: {valid}")  # True
print(f"Final position: {result}")  # (1, 2)

# With prefix sum optimization:
def validate_path_optimized(commands, x_min, x_max, y_min, y_max):
    """Same but using prefix sums"""
    # Count moves in each direction
    right_count = commands.count('R')
    left_count = commands.count('L')
    up_count = commands.count('U')
    down_count = commands.count('D')
    
    # Calculate final position
    final_x = right_count - left_count
    final_y = up_count - down_count
    
    # Check if final position is in bounds
    return x_min <= final_x <= x_max and y_min <= final_y <= y_max
```

### Key Points

- **Preprocessing:** O(n) to build prefix array
- **Query:** O(1) to answer range sum queries
- **2D:** Same concept, adds prefix sums in 2D
- **Use When:** Multiple queries on same array

### Used In

- **Problem 6:** Planetary Rover Path Validation
- **Problem 10:** Sensor Fusion (time-based queries)

---

## 6. Quickselect Algorithm

### Concept Overview

Quickselect finds the kth smallest element in unsorted array in O(n) average time (similar to quicksort but doesn't fully sort). It's based on partitioning around a pivot.

**Key Insight:** You don't need to sort everything to find k smallest elements.

### Example 1: Basic Quickselect

```python
def quickselect(arr, k):
    """
    Find kth smallest element (1-indexed)
    Returns the element, not the sorted array
    """
    def select(left, right, k_smallest):
        if left == right:
            return arr[left]
        
        # Partition around random pivot
        pivot_idx = partition_random(left, right)
        
        if k_smallest == pivot_idx:
            return arr[k_smallest]
        elif k_smallest < pivot_idx:
            return select(left, pivot_idx - 1, k_smallest)
        else:
            return select(pivot_idx + 1, right, k_smallest)
    
    def partition_random(left, right):
        """Partition and return pivot index"""
        import random
        pivot_idx = random.randint(left, right)
        
        # Move pivot to end
        arr[pivot_idx], arr[right] = arr[right], arr[pivot_idx]
        pivot_value = arr[right]
        
        # Partition
        i = left
        for j in range(left, right):
            if arr[j] < pivot_value:
                arr[i], arr[j] = arr[j], arr[i]
                i += 1
        
        arr[i], arr[right] = arr[right], arr[i]
        return i
    
    return select(0, len(arr) - 1, k - 1)  # k-1 for 0-indexing

# Find 3 nearest asteroids (3 smallest distances)
distances = [10, 8, 15, 3, 6, 20, 1]

kth_smallest = quickselect(distances, 3)
print(f"3rd smallest distance: {kth_smallest}")  # 6
# The 3 nearest are: 1, 3, 6

# Time Complexity: O(n) average, O(n²) worst case
# Space Complexity: O(log n) for recursion stack
```

### Example 2: Finding Top K Elements

```python
def find_k_nearest_asteroids(asteroids, k):
    """
    Find k closest asteroids using quickselect
    asteroids: list of (x, y) coordinates
    k: number of closest to find
    """
    def distance(point):
        x, y = point
        return x*x + y*y  # Squared distance (faster, same ordering)
    
    def quickselect_k(left, right, k_idx):
        if left >= right:
            return
        
        # Partition by distance
        pivot_idx = partition_by_distance(left, right)
        
        if pivot_idx == k_idx:
            return  # Found the kth element
        elif pivot_idx < k_idx:
            quickselect_k(pivot_idx + 1, right, k_idx)
        else:
            quickselect_k(left, pivot_idx - 1, k_idx)
    
    def partition_by_distance(left, right):
        pivot_idx = (left + right) // 2
        pivot_dist = distance(asteroids[pivot_idx])
        
        asteroids[pivot_idx], asteroids[right] = asteroids[right], asteroids[pivot_idx]
        
        i = left
        for j in range(left, right):
            if distance(asteroids[j]) < pivot_dist:
                asteroids[i], asteroids[j] = asteroids[j], asteroids[i]
                i += 1
        
        asteroids[i], asteroids[right] = asteroids[right], asteroids[i]
        return i
    
    quickselect_k(0, len(asteroids) - 1, k - 1)
    return asteroids[:k]

# Asteroid positions relative to spacecraft
asteroids = [(3, 4), (1, 1), (8, 0), (1, 2), (6, 8)]

nearest_3 = find_k_nearest_asteroids(asteroids.copy(), 3)
print(f"3 nearest asteroids: {nearest_3[:3]}")

# Distances: (3,4)=25, (1,1)=2, (8,0)=64, (1,2)=5, (6,8)=100
# Sorted: (1,1)=2, (1,2)=5, (3,4)=25
# Result will include these 3 nearest
```

### Example 3: Using Heap (Alternative to Quickselect)

```python
import heapq

def find_k_nearest_with_heap(asteroids, k):
    """
    Alternative: Use max-heap of size k
    More efficient when k << n
    """
    # Build max-heap of k smallest distances
    max_heap = []
    
    for point in asteroids:
        distance = point[0]**2 + point[1]**2
        
        if len(max_heap) < k:
            # Use negative for max-heap (Python has min-heap by default)
            heapq.heappush(max_heap, (-distance, point))
        elif distance < -max_heap[0][0]:  # Smaller than largest in heap
            heapq.heapreplace(max_heap, (-distance, point))
    
    # Extract results
    return [point for _, point in max_heap]

asteroids = [(3, 4), (1, 1), (8, 0), (1, 2), (6, 8)]
nearest_3 = find_k_nearest_with_heap(asteroids, 3)
print(f"3 nearest asteroids: {nearest_3}")

# Time Complexity: O(n log k)
# Space Complexity: O(k)
# Better when k is much smaller than n
```

### Comparison: Quickselect vs Heap

```
                Quickselect     Heap (Top K)
Time:           O(n) avg        O(n log k)
Space:          O(log n)        O(k)
Best When:      k ≈ n/2         k << n
Worst Case:     O(n²)           O(n log k)
```

### Key Points

- **Purpose:** Find kth element without full sorting
- **Partition:** Around pivot, recursively search relevant half
- **Random Pivot:** Helps avoid worst-case O(n²)
- **Top K Pattern:** Quickselect k-1 to get k smallest elements

### Used In

- **Problem 7:** Asteroid Belt Density Mapping

---

## 7. Heaps & Priority Queues

### Concept Overview

A heap is a complete binary tree where each parent is smaller (min-heap) or larger (max-heap) than its children. Allows O(log n) insertion and O(1) extraction of min/max element.

**Key Insight:** Maintain ordering efficiently without full sorting.

### Example 1: Min-Heap for K-way Merge

```python
import heapq

def merge_k_sorted_streams(streams):
    """
    Merge k sorted sensor data streams
    streams: list of lists, each pre-sorted by timestamp
    """
    heap = []
    results = []
    
    # Initialize: add first element from each stream
    for stream_id, stream in enumerate(streams):
        if stream:
            # (value, stream_id, position_in_stream)
            heapq.heappush(heap, (stream[0], stream_id, 0))
    
    # Extract minimum and add next element from same stream
    while heap:
        value, stream_id, position = heapq.heappop(heap)
        results.append(value)
        
        # Add next element from this stream
        next_position = position + 1
        if next_position < len(streams[stream_id]):
            next_value = streams[stream_id][next_position]
            heapq.heappush(heap, (next_value, stream_id, next_position))
    
    return results

# Three sensors reporting temperature readings
sensor_1_temps = [1.0, 2.5, 4.2]  # At times 0, 1, 2 seconds
sensor_2_temps = [0.5, 1.5, 3.7]  # At times 0.5, 1.5, 2.5 seconds
sensor_3_temps = [0.8, 2.2, 3.5]  # At times 0.8, 2.2, 3.5 seconds

sensors = [sensor_1_temps, sensor_2_temps, sensor_3_temps]
merged = merge_k_sorted_streams(sensors)
print(f"Merged readings: {merged}")
# Output: [0.5, 0.8, 1.0, 1.5, 2.2, 2.5, 3.5, 3.7, 4.2]

# Time Complexity: O(n log k) where n = total elements, k = number of streams
# Space Complexity: O(k) for heap
```

### Example 2: Max-Heap for Top K (Python trick)

```python
import heapq

def find_k_farthest_asteroids(asteroids, k):
    """
    Find k farthest asteroids using max-heap
    Python has min-heap, so negate values
    """
    min_heap = []  # Will store (-distance, asteroid)
    
    for asteroid in asteroids:
        distance = asteroid[0]**2 + asteroid[1]**2
        
        if len(min_heap) < k:
            heapq.heappush(min_heap, (-distance, asteroid))
        elif distance > -min_heap[0][0]:  # Larger than smallest in heap
            heapq.heapreplace(min_heap, (-distance, asteroid))
    
    return [ast for _, ast in min_heap]

asteroids = [(1, 1), (3, 4), (8, 0), (1, 2), (6, 8)]
farthest_2 = find_k_farthest_asteroids(asteroids, 2)
print(f"2 farthest asteroids: {farthest_2}")
# Distances: 2, 25, 64, 5, 100
# Farthest 2: (6,8)=100 and (8,0)=64
```

### Example 3: Priority Queue with Custom Comparator

```python
import heapq

class Asteroid:
    def __init__(self, x, y):
        self.x = x
        self.y = y
        self.distance = x*x + y*y
    
    def __lt__(self, other):
        """Custom comparison for heap ordering"""
        return self.distance < other.distance
    
    def __repr__(self):
        return f"({self.x},{self.y})"

def find_nearest_asteroids(asteroid_list, k):
    """Use heap with custom object"""
    heap = [Asteroid(x, y) for x, y in asteroid_list]
    heapq.heapify(heap)  # Build heap in O(n)
    
    # Extract k smallest
    return [heapq.heappop(heap) for _ in range(k)]

asteroids = [(3, 4), (1, 1), (8, 0), (1, 2)]
nearest = find_nearest_asteroids(asteroids, 2)
print(f"Nearest 2: {nearest}")  # [(1,1), (1,2)]
```

### Heap Operations

```python
import heapq

# Create heap
heap = []
heapq.heappush(heap, 5)
heapq.heappush(heap, 3)
heapq.heappush(heap, 7)
heapq.heappush(heap, 1)

# Extract min
smallest = heapq.heappop(heap)
print(f"Smallest: {smallest}")  # 1

# Peek at top (without removing)
print(f"Smallest without pop: {heap[0]}")  # 3

# Build from list (bottom-up, more efficient)
heap = [5, 3, 7, 1]
heapq.heapify(heap)  # O(n) not O(n log n)

# Heapreplace (pop then push in one operation)
new_val = heapq.heapreplace(heap, 9)
# old: [1, 3, 7, 5] → pops 1, pushes 9 → [3, 5, 7, 9]

print(f"Heap size: {len(heap)}")
```

### Heap Properties

```
Min-Heap:           Max-Heap:
        1                   10
       / \                 /  \
      3   5               9    8
     / \                 / \
    7   6               3   4

Parent ≤ Children   Parent ≥ Children

Array representation (1-indexed):
[-, 1, 3, 5, 7, 6]      [-, 10, 9, 8, 3, 4]

Child at index i → children at 2i, 2i+1
Parent at index i → parent at i//2
```

### Key Points

- **Min-Heap:** Root is minimum (useful for Dijkstra, k-way merge)
- **Max-Heap:** Root is maximum (simulate using negation in Python)
- **Building:** O(n) with heapify, not O(n log n)
- **Peek:** O(1) to see top element
- **Extract:** O(log n) to remove top

### Used In

- **Problem 7:** Asteroid Belt Density Mapping (finding k nearest)
- **Problem 10:** Sensor Fusion Timestamp Alignment (k-way merge)

---

## 8. Dynamic Programming & Longest Common Subsequence

### Concept Overview

Dynamic programming solves problems by breaking them into overlapping subproblems and storing results to avoid recomputation. LCS finds the longest sequence of characters that appear in the same order in two strings (not necessarily contiguous).

**Key Insight:** Build solutions bottom-up from smaller subproblems.

### Example 1: Basic LCS with 2D DP Table

```python
def longest_common_subsequence(text1, text2):
    """
    Find longest common subsequence of two strings
    DNA example: "AGGTAB" and "GXTXAYB" → "GTAB"
    """
    m, n = len(text1), len(text2)
    
    # dp[i][j] = LCS length of text1[0:i] and text2[0:j]
    dp = [[0] * (n + 1) for _ in range(m + 1)]
    
    for i in range(1, m + 1):
        for j in range(1, n + 1):
            if text1[i-1] == text2[j-1]:
                # Characters match: extend previous LCS
                dp[i][j] = dp[i-1][j-1] + 1
            else:
                # Characters don't match: take best from skipping either
                dp[i][j] = max(dp[i-1][j], dp[i][j-1])
    
    return dp[m][n]

# DNA sequences from two species
dna1 = "AGGTAB"
dna2 = "GXTXAYB"

lcs_length = longest_common_subsequence(dna1, dna2)
print(f"LCS length: {lcs_length}")  # 4

# Trace the DP table:
#       ""  G  X  T  X  A  Y  B
#   ""   0  0  0  0  0  0  0  0
#   A    0  0  0  0  0  1  1  1
#   G    0  1  1  1  1  1  1  1
#   G    0  1  1  1  1  1  1  1
#   T    0  1  1  2  2  2  2  2
#   A    0  1  1  2  2  3  3  3
#   B    0  1  1  2  2  3  3  4  ← LCS length = 4

# Time Complexity: O(m × n)
# Space Complexity: O(m × n)
```

### Example 2: Reconstructing the LCS String

```python
def lcs_with_reconstruction(text1, text2):
    """Find LCS and return the actual string"""
    m, n = len(text1), len(text2)
    dp = [[0] * (n + 1) for _ in range(m + 1)]
    
    # Build DP table (same as before)
    for i in range(1, m + 1):
        for j in range(1, n + 1):
            if text1[i-1] == text2[j-1]:
                dp[i][j] = dp[i-1][j-1] + 1
            else:
                dp[i][j] = max(dp[i-1][j], dp[i][j-1])
    
    # Backtrack to find actual LCS
    lcs = []
    i, j = m, n
    
    while i > 0 and j > 0:
        if text1[i-1] == text2[j-1]:
            lcs.append(text1[i-1])
            i -= 1
            j -= 1
        elif dp[i-1][j] > dp[i][j-1]:
            i -= 1  # Character in text1 not in LCS
        else:
            j -= 1  # Character in text2 not in LCS
    
    return ''.join(reversed(lcs))

dna1 = "AGGTAB"
dna2 = "GXTXAYB"

lcs_string = lcs_with_reconstruction(dna1, dna2)
print(f"LCS string: {lcs_string}")  # "GTAB"
```

### Example 3: Space-Optimized LCS

```python
def lcs_space_optimized(text1, text2):
    """LCS using only O(min(m,n)) space"""
    if len(text1) < len(text2):
        text1, text2 = text2, text1  # Ensure text1 is longer
    
    m, n = len(text1), len(text2)
    
    # Only need 2 rows
    prev = [0] * (n + 1)
    curr = [0] * (n + 1)
    
    for i in range(1, m + 1):
        for j in range(1, n + 1):
            if text1[i-1] == text2[j-1]:
                curr[j] = prev[j-1] + 1
            else:
                curr[j] = max(prev[j], curr[j-1])
        
        # Swap rows for next iteration
        prev, curr = curr, prev
    
    return prev[n]

dna1 = "AGGTAB"
dna2 = "GXTXAYB"

lcs_length = lcs_space_optimized(dna1, dna2)
print(f"LCS length (space-optimized): {lcs_length}")  # 4

# Space Complexity: O(min(m, n)) instead of O(m × n)
# Time Complexity: Still O(m × n)
```

### Example 4: Longest Increasing Subsequence (Similar Problem)

```python
def longest_increasing_subsequence(arr):
    """Find longest subsequence where each element > previous"""
    n = len(arr)
    if n == 0:
        return 0
    
    # dp[i] = length of LIS ending at index i
    dp = [1] * n
    
    for i in range(1, n):
        for j in range(i):
            if arr[j] < arr[i]:
                dp[i] = max(dp[i], dp[j] + 1)
    
    return max(dp)

# Signal strength over time (increasing trend signals health)
signal_strength = [10, 9, 2, 5, 3, 7, 101, 18]
lis_length = longest_increasing_subsequence(signal_strength)
print(f"LIS length: {lis_length}")  # [10,101] or [2,3,7,101] → 4

# Time Complexity: O(n²)
# Space Complexity: O(n)
```

### DP Problems Summary

```
LCS:  Find longest sequence common to both strings
LIS:  Find longest strictly increasing subsequence
Edit: Find minimum edits (insertions, deletions) to transform string
0-1:  Solve knapsack problem (items, weight limits)
Coin: Minimum coins to make amount
Path: Shortest/longest path in grid
```

### Key Points

- **Recurrence Relation:** Define how subproblems combine
- **Base Cases:** Handle small inputs directly
- **Memoization:** Store results of subproblems
- **Reconstruction:** Backtrack to find actual solution
- **Space Optimization:** Often possible with careful bookkeeping

### Used In

- **Problem 8:** DNA Sequence Mutation Detection

---

## 9. Circular Arrays & Cyclic Buffers

### Concept Overview

A circular array (cyclic buffer) is a fixed-size array that wraps around - when you reach the end, you continue from the beginning. Useful for:
- Queue implementations (fixed memory)
- Network packet buffers
- Ring buffers in streaming data
- Modulo arithmetic for wrapping indices

**Key Insight:** Use modulo operation to map indices to physical positions.

### Example 1: Basic Circular Buffer

```python
class CircularBuffer:
    def __init__(self, capacity):
        self.buffer = [None] * capacity
        self.capacity = capacity
        self.head = 0  # Position to write next element
        self.size = 0  # Current number of elements
    
    def enqueue(self, value):
        """Add element to buffer"""
        self.buffer[self.head] = value
        self.head = (self.head + 1) % self.capacity
        
        if self.size < self.capacity:
            self.size += 1
        # If full, head overwrites oldest element
    
    def dequeue(self):
        """Remove oldest element"""
        if self.size == 0:
            return None
        
        idx = (self.head - self.size) % self.capacity
        value = self.buffer[idx]
        self.size -= 1
        return value
    
    def peek(self):
        """View oldest element without removing"""
        if self.size == 0:
            return None
        idx = (self.head - self.size) % self.capacity
        return self.buffer[idx]

# Network packet buffer (fixed 5-packet capacity)
packet_buffer = CircularBuffer(5)

packets = [101, 102, 103, 104, 105, 106]

for pkt in packets:
    packet_buffer.enqueue(pkt)
    print(f"Enqueued {pkt}, buffer size: {packet_buffer.size}")

# Output:
# Enqueued 101, buffer size: 1
# Enqueued 102, buffer size: 2
# ...
# Enqueued 105, buffer size: 5
# Enqueued 106, buffer size: 5 (overwrites oldest, 101)

print(f"Dequeue: {packet_buffer.dequeue()}")  # 102 (oldest remaining)
print(f"Dequeue: {packet_buffer.dequeue()}")  # 103
```

### Example 2: Packet Reordering with Sequence Numbers

```python
def reorder_packets_circular(packets, window_size):
    """
    Reorder out-of-sequence packets using circular buffer
    packets: list of (sequence_num, data)
    window_size: max sequence numbers in window
    """
    # Circular array to store packets in window
    buffer = [None] * window_size
    
    received_packets = []
    current_seq = 0  # Expected sequence number
    
    for seq_num, data in packets:
        # Check if sequence number is in acceptable window
        if seq_num < current_seq:
            # Duplicate or out-of-window packet
            continue
        
        if seq_num >= current_seq + window_size:
            # Too far ahead, skip
            continue
        
        # Store packet at position in circular buffer
        position = seq_num % window_size
        buffer[position] = (seq_num, data)
        
        # Deliver all in-order packets from front of window
        while buffer[current_seq % window_size] is not None:
            delivered = buffer[current_seq % window_size]
            received_packets.append(delivered)
            buffer[current_seq % window_size] = None
            current_seq += 1
    
    return received_packets

# Out-of-order packet arrivals
packets = [
    (0, "A"), (1, "B"), (3, "D"), (2, "C"), (4, "E")
]

ordered = reorder_packets_circular(packets, window_size=5)
print(f"Reordered packets: {[(s, d) for s, d in ordered]}")
# Output: [(0, 'A'), (1, 'B'), (2, 'C'), (3, 'D'), (4, 'E')]

# How it works:
# (0,A): pos=0, deliver 0 → current_seq=1
# (1,B): pos=1, deliver 1 → current_seq=2
# (3,D): pos=3, hold (gap at 2)
# (2,C): pos=2, deliver 2,3,4 → current_seq=4
# (4,E): already processed
```

### Example 3: Circular Array Indexing

```python
def circular_array_operations():
    """Demonstrate modulo arithmetic for circular arrays"""
    
    arr = [10, 20, 30, 40, 50]
    n = len(arr)
    
    # Access with wrapping
    start = 3
    for i in range(5):
        pos = (start + i) % n
        print(f"Index {i}: position {pos}, value {arr[pos]}")
    
    # Output:
    # Index 0: position 3, value 40
    # Index 1: position 4, value 50
    # Index 2: position 0, value 10 ← wraps around
    # Index 3: position 1, value 20
    # Index 4: position 2, value 30

# Sensor data ring buffer (continuous data collection)
class RingBuffer:
    def __init__(self, size):
        self.buffer = [0] * size
        self.write_pos = 0
        self.size = size
    
    def add(self, value):
        self.buffer[self.write_pos] = value
        self.write_pos = (self.write_pos + 1) % self.size
    
    def read_last_n(self, n):
        """Read last n values"""
        if n > self.size:
            n = self.size
        
        result = []
        for i in range(n):
            pos = (self.write_pos - n + i) % self.size
            result.append(self.buffer[pos])
        return result

sensor = RingBuffer(5)
readings = [10, 20, 30, 40, 50, 60, 70]

for reading in readings:
    sensor.add(reading)

print(f"Last 3 readings: {sensor.read_last_n(3)}")  # [50, 60, 70]
```

### Key Modulo Patterns

```python
# Increment with wrap
next_pos = (current_pos + 1) % capacity

# Decrement with wrap
prev_pos = (current_pos - 1) % capacity

# Access n positions ahead
ahead_pos = (current_pos + n) % capacity

# Access n positions behind
behind_pos = (current_pos - n) % capacity

# Find physical position from logical index
physical = logical_index % capacity

# Check if value is in range [start, start+size)
in_range = start <= value < start + size
```

### Key Points

- **Fixed Memory:** Capacity never grows
- **Overwrites:** Oldest data overwritten when full
- **Efficient:** O(1) enqueue/dequeue
- **Modulo Arithmetic:** Essential for index wrapping
- **Window Concept:** Only care about recent data

### Used In

- **Problem 9:** Network Packet Reordering

---

## 10. K-way Merge Algorithm

### Concept Overview

K-way merge combines k sorted lists into one sorted list. It's more efficient than concatenating and sorting separately. It's the foundation for merge sort and useful for merging sensor streams.

**Key Insight:** Always take the smallest from front of k lists.

### Example 1: Simple K-way Merge with Heap

```python
import heapq

def merge_k_sorted_lists(lists):
    """
    Merge k sorted lists into one sorted list
    Uses min-heap to efficiently track minimum
    """
    heap = []
    results = []
    
    # Initialize heap with first element from each list
    for list_id, lst in enumerate(lists):
        if lst:  # Non-empty list
            # Store: (value, list_id, element_index)
            heapq.heappush(heap, (lst[0], list_id, 0))
    
    # Extract minimum and add next element from same list
    while heap:
        value, list_id, idx = heapq.heappop(heap)
        results.append(value)
        
        # Add next element from the same list
        if idx + 1 < len(lists[list_id]):
            next_val = lists[list_id][idx + 1]
            heapq.heappush(heap, (next_val, list_id, idx + 1))
    
    return results

# Three sensor data streams (already sorted by timestamp)
sensor1 = [1.0, 2.5, 4.2, 5.1]
sensor2 = [0.5, 1.5, 2.5]
sensor3 = [0.8, 2.2, 3.5, 4.0]

merged = merge_k_sorted_lists([sensor1, sensor2, sensor3])
print(f"Merged readings: {merged}")
# Output: [0.5, 0.8, 1.0, 1.5, 2.2, 2.5, 2.5, 3.5, 4.0, 4.2, 5.1]

# Time Complexity: O(n log k) where n = total elements, k = number of lists
# Space Complexity: O(k) for heap
```

### Example 2: Merge Two Sorted Lists (Foundation)

```python
def merge_two_sorted_lists(list1, list2):
    """Merge two sorted lists using two pointers"""
    result = []
    i = j = 0
    
    # Compare elements from both lists
    while i < len(list1) and j < len(list2):
        if list1[i] <= list2[j]:
            result.append(list1[i])
            i += 1
        else:
            result.append(list2[j])
            j += 1
    
    # Add remaining elements
    result.extend(list1[i:])
    result.extend(list2[j:])
    
    return result

timestamps1 = [0.5, 1.5, 3.5]
timestamps2 = [0.8, 2.2, 4.0]

merged = merge_two_sorted_lists(timestamps1, timestamps2)
print(f"Merged: {merged}")
# Output: [0.5, 0.8, 1.5, 2.2, 3.5, 4.0]

# Time Complexity: O(n + m)
# Space Complexity: O(n + m)
```

### Example 3: K-way Merge with Tuples (Sensor + ID + Value)

```python
import heapq

def merge_k_sensor_streams(sensor_streams):
    """
    Merge k sensor streams maintaining (timestamp, sensor_id, value)
    sensor_streams: list of lists, each containing (timestamp, value)
    """
    heap = []
    results = []
    
    # Initialize with first reading from each sensor
    for sensor_id, stream in enumerate(sensor_streams):
        if stream:
            timestamp, value = stream[0]
            heapq.heappush(heap, (timestamp, sensor_id, 0))  # (ts, id, idx)
    
    # Process all readings in order
    while heap:
        timestamp, sensor_id, idx = heapq.heappop(heap)
        value = sensor_streams[sensor_id][idx][1]
        
        results.append({
            'timestamp': timestamp,
            'sensor_id': sensor_id,
            'value': value
        })
        
        # Add next reading from same sensor
        if idx + 1 < len(sensor_streams[sensor_id]):
            next_ts, _ = sensor_streams[sensor_id][idx + 1]
            heapq.heappush(heap, (next_ts, sensor_id, idx + 1))
    
    return results

# Three sensors with (timestamp, reading)
thermometer = [(0.0, 15), (1.0, 16), (2.0, 18)]
pressure = [(0.5, 1.2), (1.5, 1.5), (2.5, 1.8)]
radiation = [(0.8, 50), (2.2, 52), (3.5, 55)]

merged_data = merge_k_sensor_streams([thermometer, pressure, radiation])

print("Sensor Fusion Timeline:")
for reading in merged_data:
    print(f"  {reading['timestamp']}s: Sensor {reading['sensor_id']} = {reading['value']}")

# Output:
# Sensor Fusion Timeline:
#   0.0s: Sensor 0 = 15
#   0.5s: Sensor 1 = 1.2
#   0.8s: Sensor 2 = 50
#   1.0s: Sensor 0 = 16
#   1.5s: Sensor 1 = 1.5
#   2.0s: Sensor 0 = 18
#   2.2s: Sensor 2 = 52
#   2.5s: Sensor 1 = 1.8
#   3.5s: Sensor 2 = 55
```

### Example 4: External Merge Sort (Using K-way Merge)

```python
def external_merge_sort(data, chunk_size=2):
    """
    Sort data in chunks (simulating reading from disk)
    Then merge all chunks
    """
    # Break data into chunks and sort each
    chunks = []
    for i in range(0, len(data), chunk_size):
        chunk = sorted(data[i:i + chunk_size])
        chunks.append(chunk)
    
    # Merge all chunks using k-way merge
    return merge_k_sorted_lists(chunks)

unsorted_data = [38, 27, 43, 3, 9, 82, 10]
sorted_data = external_merge_sort(unsorted_data, chunk_size=2)
print(f"Sorted: {sorted_data}")
# Output: [3, 9, 10, 27, 38, 43, 82]

# Useful for sorting data larger than RAM
```

### Comparison: Different Merge Approaches

```
Method          Time              Space       Use Case
─────────────────────────────────────────────────────────
Concatenate     O(n log n)       O(n)        When k is small
  + Sort        

Two-pointer     O(n + m)         O(n+m)      Exactly 2 lists
  (2 lists)     

K-way merge     O(n log k)       O(k)        Many lists, k << n
  with heap     

Merge sort      O(n log n)       O(n)        General sorting
```

### Key Points

- **Heap-based:** Most efficient for k > 2
- **Always take minimum:** From front of k lists
- **Add next:** When a list is consumed
- **Common:**  Foundation for distributed systems (MapReduce uses this)

### Used In

- **Problem 10:** Sensor Fusion Timestamp Alignment

---

## Summary Table: Concepts by Problem

| Problem | Main Concepts | Algorithms | Complexity |
|---------|---------------|-----------|-----------|
| #2 Telescope | Sliding Window, Sorting | Median Filtering | O(n*k*log k) |
| #3 Radio Telescope | Hashing, Two-Pointer | Deduplication | O(n) avg |
| #4 Solar Panel | Dynamic Programming | Kadane's Algorithm | O(n) |
| #5 Memory | Array Manipulation, Two-Pointer | In-place Rearrange | O(n) |
| #6 Rover | Prefix Sum, Boundary Checking | Cumulative Sum | O(n) |
| #7 Asteroids | Quickselect, Heaps | K-way Selection | O(n) avg |
| #8 DNA | Dynamic Programming, DP | Longest Common Subseq | O(m*n) |
| #9 Packets | Circular Array, Modulo | Ring Buffer | O(n) |
| #10 Sensor | Heaps, K-way Merge | Priority Queue Merge | O(n log k) |

---

## Learning Strategies

### 1. **Start Simple**
```python
# Start with working solution (maybe inefficient)
# Get it working first
# Then optimize

def simple_solution(data):
    # Straightforward, maybe slow
    pass

# Test thoroughly
assert simple_solution([1,2,3]) == expected
```

### 2. **Understand Tradeoffs**
```
Time         vs      Space
O(n) + O(n)  vs      O(n²) time, O(1) space
Cache misses vs      Memory bloat
Readability  vs      Performance
```

### 3. **Practice Variants**
```
If you solve LCS:
  - Try LIS (longest increasing)
  - Try edit distance
  - Try weighted LCS

Each variant teaches something new
```

### 4. **Use Visualization**
```
# Draw the state at each step
# Helps understand algorithm flow
# Especially for DP, heaps, trees
```

### 5. **Test Edge Cases**
```python
# Empty arrays, single element
# All same elements
# Reverse sorted
# Already sorted
# Maximum size limits
```

---

## Recommended Reading Order

1. **Start:** Sliding Window, Two-Pointer, Hashing (fundamentals)
2. **Then:** Prefix Sum, Circular Arrays (understanding state)
3. **Next:** Quickselect, Heaps (advanced selection)
4. **Finally:** Kadane's, LCS, K-way Merge (optimization algorithms)

---

## Quick Reference: When to Use What

### **Finding Extremes (Min/Max)**
- Single extremum → Scan O(n)
- K extremes → Heap O(n log k) or Quickselect O(n)

### **Searching/Matching**
- Exact match → Hash O(1) average
- Pattern → Sliding Window O(n)

### **Sorting**
- Need fully sorted → Merge O(n log n)
- Need kth → Quickselect O(n)

### **Consecutive Elements**
- All subarrays size k → Sliding Window O(n)
- Any subarray with property → Two-Pointer O(n)

### **Time Series / Streams**
- Multiple sorted streams → K-way Merge O(n log k)
- Circular buffer → Modulo arithmetic
- Cumulative queries → Prefix Sum O(1) query

### **Optimization Problems**
- Maximum subarray → Kadane's O(n)
- General optimization → Dynamic Programming O(varies)

---

## Conclusion

These 10 algorithms cover most interview questions and practical problems:

1. **Sliding Window** - Arrays/Strings problems
2. **Two-Pointer** - Array manipulation
3. **Hashing** - Lookup and counting
4. **Kadane's** - Optimization
5. **Prefix Sum** - Range queries
6. **Quickselect** - Finding k smallest/largest
7. **Heaps** - Priority and k-way operations
8. **Dynamic Programming** - Complex optimization
9. **Circular Arrays** - Bounded memory problems
10. **K-way Merge** - Combining sorted data

Master these, and you can solve most algorithmic problems!

---

**Remember:** The goal is not to memorize algorithms, but to understand the patterns and develop intuition for when to apply them.
