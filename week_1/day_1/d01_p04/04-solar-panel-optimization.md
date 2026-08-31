# Solar Panel Array Optimization

## Problem Overview

A spacecraft's electrical system relies on a large array of solar panels positioned around its hull. Each panel can be rotated to face different directions, but the spacecraft can only afford to rotate panels in a **contiguous segment** at a time (due to mechanical constraints and power budget).

Your task is to determine which contiguous segment of panels to rotate in order to **maximize the total power output** of the array.

This is a variant of **Kadane's algorithm**, the classic maximum subarray sum problem, applied to power optimization.

## Context & Real-World Application

In spacecraft power management:
- Each panel's angle determines its power output (given current sun position)
- Rotating panels consumes energy, so you choose one contiguous segment
- Goal: Select the segment rotation that yields the greatest net power gain
- Real systems might have constraints: minimum/maximum segment size, rotation costs
- Must handle negative power changes (some rotations might decrease output temporarily for long-term gain)

## Key Concepts to Understand

### Maximum Subarray Sum (Kadane's Algorithm)
- Find a contiguous subarray with the largest possible sum
- Time complexity: O(n), space: O(1) — much better than brute force
- Works by tracking the maximum sum ending at each position

### Variant: Power Optimization
- Instead of maximizing a sum, you might be:
  - Maximizing total power gain (positive values help)
  - Handling costs (negative values represent power spent on rotation)
  - Balancing: gain - cost

### Why Contiguous?
- Mechanical constraints: Only one motor can rotate panels at a time
- Electric constraints: Rotation draws power; must be worth it
- Result: Can't cherry-pick arbitrary panels, must pick a range [i, j]

## Example Scenario

Solar panels in your array respond to sun angle changes:

```
Panel index:       0    1    2    3    4    5    6
Power change:    [-2,  5,   -1,  8,   2,  -3,  1]
(if rotated)      

Interpretation:
- Panel 0: Rotation would decrease power by 2 units
- Panel 1: Rotation would increase power by 5 units
- Panel 3-4: Rotating these together gives +8 and +2 (10 units total)
- Panel 5: Rotation would decrease power by 3 units

Best decision: Rotate panels 1-4
Total gain: 5 + (-1) + 8 + 2 = 14 units

Subarray: indices [1, 4] or values [5, -1, 8, 2]
```

## What You Should Explore

1. **What constitutes "power change"?**
   - Given current sun position, what's the delta if panel i is rotated?
   - Example: Current output 100W, after rotation 105W → change = +5

2. **Edge cases**:
   - All rotations decrease power (all negative values)
     - Should the answer be "don't rotate any panel" (empty subarray)?
     - Or "rotate the least-damaging panel"?
   - All rotations increase power (all positive values)
     - Rotate everything? Or is there a size constraint?

3. **Constraints**:
   - Minimum/maximum segment size? (e.g., can only rotate 2-5 panels at once)
   - Budget limit? (e.g., can't exceed power gain of 20 units)
   - If constraints exist, Kadane's algorithm needs adaptation

4. **Output requirements**:
   - Just the maximum power gain value?
   - Or also the start/end indices of which panels to rotate?
   - Verification: Can you output which panels were selected?

## Example Input/Output Format

**Input:**
- An array of power changes (integers, can be negative)
- Optional: constraints like minimum/maximum segment size

**Output:**
- Maximum power gain achievable
- Indices of the segment to rotate (start and end)
- Edge case: what if no rotation is beneficial?

## Hints on Approach

- Start with understanding the classic maximum subarray problem
- Think about the decision at each panel:
  - Extend the current best segment?
  - Start a new segment?
  - Stop and try later?
- Track state: best sum so far, best sum ending at current position
- Be careful with edge cases: all negative, all positive, empty selection

## Why This Matters in DSA

This problem teaches:
- **Kadane's algorithm** for maximum subarray problems
- **Dynamic programming** thinking: making optimal local choices
- **Real optimization**: Balancing multiple objectives
- **Variant algorithms**: How classic algorithms adapt to constraints

---

**Difficulty:** Medium  
**Primary Concept:** Kadane's Algorithm, Dynamic Programming  
**Secondary Concepts:** Array traversal, Optimization, Constraint handling
