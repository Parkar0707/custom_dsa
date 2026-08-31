# Telescope Image Sensor Calibration

## Problem Overview

Telescope image sensors capture astronomical data but often contain "hot pixels" — defective sensor elements that produce erroneous values regardless of actual light input. These corrupted values can distort scientific measurements and introduce noise into the data stream.

Your task is to remove hot pixels from a sensor array using **median filtering with a sliding window approach**.

## Context & Real-World Application

In actual telescope systems like the Hubble Space Telescope or ground-based observatories:
- Sensors accumulate manufacturing defects and radiation damage over time
- Hot pixels typically show as abnormally bright values in the data
- Median filtering is preferred over averaging because it's robust to outliers
- The filter must preserve fine details while eliminating spikes

## Key Concepts to Understand

### Sliding Window Technique
- Maintain a window of fixed size that moves across the array
- For each window position, extract and process elements within bounds
- The window's center element gets replaced with a computed value

### Median as Noise Filter
- Median is the middle value when elements are sorted
- Unlike mean/average, median ignores extreme outliers
- A "hot pixel" (extreme value) won't affect the median of surrounding pixels
- Particularly effective for impulse noise (sudden spikes)

### Implementation Considerations
- **Edge handling**: How do you process pixels at array boundaries where you can't form a complete window?
  - Common approaches: mirror the values, pad with zeros, or skip edges
- **Window size**: Larger windows remove more noise but blur fine details
  - Typical choices: 3×3 or 5×5 for 2D image arrays; window size 3-5 for 1D sensor data
- **Efficiency**: Naive approach sorts window elements repeatedly (O(k log k) per window)
  - Optimization: Use data structures to maintain sorted order as window slides

## Example Scenario

Imagine a 1D sensor array reading temperature from a telescope's thermal sensor:

```
Raw sensor data (noisy, with hot pixel):
[15, 16, 18, 95, 17, 19, 16, 18, 20]
           ↑ hot pixel (far out of range)

After median filtering (window size 3):
[15, 17, 17, 17, 17, 18, 18, 19, 20]
        ↑ noisy spike removed
```

Each position's value becomes the median of itself and its neighbors. The hot pixel at index 3 (value 95) gets replaced with something reasonable (the median of [18, 95, 17]).

## What You Should Explore

1. **Window boundaries**: How do you handle the first and last elements when they can't have full windows on both sides?

2. **Median extraction**: Given a window of 3-5 elements, what's an efficient way to find the median?
   - Simple sort? Heap? Two-pointer technique?

3. **Time complexity trade-offs**:
   - Naive median calculation per window: O(n × k log k) where k is window size
   - Optimized with data structures: Can you do better?

4. **2D extension**: How would your approach scale to 2D image arrays (height × width)?
   - Would your window now be 3×3 or 5×5?

## Example Input/Output Format

**Input:**
- An array of sensor readings (integers)
- Window size parameter

**Output:**
- A new array with hot pixels filtered out
- Dimensions/structure preserved

## Hints on Approach

- Think about how to efficiently maintain a sorted order of window elements
- Consider what data structures (heaps, sorted containers) might help
- Remember that median of an odd-sized array is straightforward; even-sized needs care
- Don't optimize prematurely; correctness first, efficiency second

## Why This Matters in DSA

This problem teaches:
- **Sliding window** pattern for array traversal
- **Sorting/selection** for statistical operations on subarrays
- **Data structure choice** for maintaining order while sliding
- **Real-world constraints**: balancing accuracy, speed, and memory

---

**Difficulty:** Medium  
**Primary Concept:** Sliding Window, Sorting  
**Secondary Concepts:** Array manipulation, Edge handling
