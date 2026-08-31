# Planetary Rover Path Validation

## Problem Overview

A rover on Mars is given a series of movement commands (up, down, left, right). Before executing them, you must verify that all movements keep the rover within a designated safe zone boundary.

Your task is to **validate the rover's path** and determine if it stays within bounds throughout its journey using **prefix sum** technique to efficiently track position changes.

## Context & Real-World Application

In planetary exploration (Mars rovers, lunar landers, etc.):
- Rovers operate in restricted safe zones where terrain has been surveyed
- Going outside the safe zone risks: cliff edges, extreme temperatures, loss of signal
- Commands are pre-planned before execution begins
- Must verify entire path before committing to movement
- Real systems might have uneven terrain, but this problem assumes 2D grid

## Key Concepts to Understand

### Movement Commands as Deltas
- Each command is a displacement: Up (+1 y), Down (-1 y), Left (-1 x), Right (+1 x)
- Track cumulative position after each command
- Need to verify: position stays within [x_min, x_max] and [y_min, y_max] at all times

### Prefix Sum for Efficient Computation
- Rather than simulating step-by-step, compute cumulative position changes
- Prefix sum: position[i] = sum of all deltas from command[0] to command[i]
- Allows O(n) verification of all positions

### Boundary Conditions
- Starting position: usually origin (0, 0) or specified
- Safe zone: a rectangular area [x_min, x_max] × [y_min, y_max]
- Must verify: each intermediate position is within bounds

## Example Scenario

A rover exploring a 10×10 Martian terrain:

```
Safe zone: x in [-5, 5], y in [-5, 5]
Starting position: (0, 0)

Command sequence: RIGHT, RIGHT, UP, UP, LEFT, LEFT, LEFT
Symbolic:         R,      R,     U,  U,   L,    L,    L

Execution trace (cumulative position):
Start:      (0,  0)  ✓ within bounds
After R:    (1,  0)  ✓ within bounds
After R:    (2,  0)  ✓ within bounds
After U:    (2,  1)  ✓ within bounds
After U:    (2,  2)  ✓ within bounds
After L:    (1,  2)  ✓ within bounds
After L:    (0,  2)  ✓ within bounds
After L:    (-1, 2)  ✓ within bounds

Result: Path is valid, all positions stay within [-5, 5] × [-5, 5]

Now consider a bad sequence:
Commands: RIGHT, RIGHT, RIGHT, RIGHT, RIGHT, RIGHT, RIGHT
Positions: (1,0), (2,0), (3,0), (4,0), (5,0), (6,0), (7,0)
                                                      ↑ Out of bounds! x=7 > x_max=5
Result: Path is INVALID
```

## What You Should Explore

1. **Representation of commands**:
   - Strings: "URDL" or "NESW"?
   - Characters: 'U', 'D', 'L', 'R'?
   - Objects with direction and magnitude?

2. **Coordinate system**:
   - 2D grid with x, y axes
   - Does the coordinate system matter? (Cartesian vs. array indexing)
   - Which direction is positive? (up = +y or -y?)

3. **Boundary checking**:
   - Inclusive or exclusive bounds?
   - Starting position in or out of bounds?
   - Must ending position be within bounds? (Usually yes)

4. **Prefix sum application**:
   - Compute x_displacement[i] = sum of all rightward commands up to i minus leftward
   - Compute y_displacement[i] = sum of all upward commands up to i minus downward
   - Verify x_displacement[i] is within [x_min, x_max] for all i

5. **Early termination**:
   - Once you find an out-of-bounds position, can you return immediately?
   - Must you check the entire path first?

## Example Input/Output Format

**Input:**
- A sequence of movement commands (array or string)
- Starting position (x, y)
- Safe zone boundaries: (x_min, x_max, y_min, y_max)

**Output:**
- Boolean: true if path stays within bounds, false otherwise
- Optional: return the first position that goes out of bounds
- Optional: return all positions that violate the boundary

## Hints on Approach

- Separate x and y movements for clarity
- Count each direction separately: +1 for right, -1 for left
- At each step, check if cumulative position is within bounds
- Think: Could you use prefix sums to answer "what's the position after command k?"
- Optimization: Find min/max x and min/max y across all positions once

## Why This Matters in DSA

This problem teaches:
- **Prefix sum** for cumulative calculations
- **Coordinate systems and transformations**
- **Boundary checking and constraint validation**
- **Real-world constraints**: Safety in autonomous systems

---

**Difficulty:** Easy to Medium  
**Primary Concept:** Prefix Sum, Array manipulation  
**Secondary Concepts:** Coordinate systems, Constraint validation
