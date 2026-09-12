# Day 8 Problem 10: Network Routing Tree - Spanning Tree Protocol

## Problem Statement
Implement a network routing algorithm that builds a spanning tree to avoid loops and ensure reliable communication. Find the minimum spanning tree for network topology.

## Core Concepts

### Spanning Tree
- **Definition**: A subset of edges that connects all vertices with no cycles
- **Network Property**: Prevents duplicate packet forwarding
- **Redundancy**: Provides alternate paths while using minimal edges
- **Root Bridge**: Central point for tree construction

### Spanning Tree Protocol (STP)
- **Goal**: Automatically build loop-free topology
- **Algorithm**: Similar to MST (Minimum Spanning Tree)
- **Root Selection**: Bridge with lowest priority/ID
- **Path Cost**: Metric determining tree structure
- **Bridge Protocol Data Units (BPDUs)**: Messages exchanged

### Tree Traversal for Updates
- **Broadcast**: Propagate changes to entire tree
- **Convergence**: Time for all devices to learn new topology
- **Failure Recovery**: Recompute tree when link fails

## Key Concepts to Understand

1. **Switches/Bridges**: Network nodes (vertices)
2. **Links**: Physical connections (edges)
3. **Root Bridge**: Designated root of spanning tree
4. **Bridge ID**: Priority + MAC address
5. **Port States**: Root, designated, blocking
6. **Cost**: Bandwidth-based metric for edges
7. **BPDUs**: Messages containing topology information

## Problem Variations to Consider

- **Rapid STP**: Faster convergence (RSTP)
- **Multiple Trees**: Different trees for different VLANs
- **Load Balancing**: Use non-spanning-tree links intelligently
- **Path Cost Calculation**: Different weightings
- **Failure Scenarios**: Recovery after link/node failure

## Example Walkthrough

### Network Topology (Before STP)

```
    S1 ---- S2
    |   \   |
    |    \ /|
    |     X |
    |    / \|
    S4 ---- S3
```

With direct connections:
- S1-S2, S1-S3, S1-S4
- S2-S3
- S3-S4

This creates loops! Packets can loop infinitely.

### STP Build Process

**Step 1: Elect Root Bridge**
- S1 has lowest bridge ID → becomes root

**Step 2: Select Root Ports**
- Each non-root switch picks port to root with lowest cost
- S2 root port: port to S1 (cost 1)
- S3 root port: port to S1 (cost 1)
- S4 root port: port to S1 (cost 1)

**Step 3: Select Designated Ports**
- For each segment, determine which port is "designated"
- Designated port closest to root blocks other ports

**Step 4: Block Remaining Ports**
- Ports not root/designated are blocked
- Prevents loops

### Resulting Spanning Tree

```
      S1 (Root)
      /|\
     / | \
    /  |  \
   S2  S3  S4
```

All switches connected, no loops!

### Link Costs (Example)

```
Bandwidth  | Cost
-----------|-------
10 Mbps    | 100
100 Mbps   | 19
1 Gbps     | 4
10 Gbps    | 2
```

If S1-S2 is 100 Mbps (cost 19) and S1-S3 is 1 Gbps (cost 4):
- S3's root port: S1 (cost 4, preferred)
- S2's root port: S1 (cost 19)

## Algorithm Outline

### Simplified STP Algorithm

```
function buildSpanningTree(switches, links):
    // Step 1: Elect root
    rootBridge = selectRootBridge(switches)
    rootBridge.isRoot = true
    rootBridge.rootDistance = 0
    
    // Step 2: BFS/Dijkstra from root
    priority_queue = new PriorityQueue()
    priority_queue.add(rootBridge, 0)
    
    visited = new Set()
    spanningTreeEdges = new Set()
    
    while priority_queue not empty:
        cost, switch = priority_queue.extract()
        
        if switch in visited:
            continue
        
        visited.add(switch)
        
        for each link connecting switch:
            neighbor = other end of link
            
            if neighbor not in visited:
                edgeCost = cost + link.cost
                
                // Add to spanning tree
                spanningTreeEdges.add(link)
                neighbor.rootDistance = edgeCost
                neighbor.rootPort = link to switch
                
                priority_queue.add(neighbor, edgeCost)
        
        // For remaining neighbors (already visited)
        for each link to visited neighbor:
            designatedPort = selectDesignatedPort(...)
            if current is not designated:
                blockPort(current)
    
    return spanningTreeEdges

function selectRootBridge(switches):
    return switches.minBy(s → (s.priority, s.macAddress))

function selectDesignatedPort(switch1, switch2, link):
    // For a link, one end is designated (forwarding)
    // The one closer to root wins
    // If equal distance, lower bridge ID wins
    
    cost1ToRoot = switch1.rootDistance
    cost2ToRoot = switch2.rootDistance
    
    if cost1ToRoot < cost2ToRoot:
        return switch1's port on this link
    else if cost2ToRoot < cost1ToRoot:
        return switch2's port on this link
    else:
        // Same distance to root
        // Lower bridge ID is designated
        if switch1.bridgeID < switch2.bridgeID:
            return switch1's port
        else:
            return switch2's port
```

### Reconvergence (Link Failure)

```
function handleLinkFailure(failedLink):
    // Recompute spanning tree
    // Remove failed link from topology
    
    affectedSwitches = []
    for each switch in failedLink.switches:
        if failedLink == switch.rootPort:
            affectedSwitches.add(switch)
    
    // Recompute root ports for affected switches
    for each switch in affectedSwitches:
        findNewRootPort(switch)
    
    // Restart STP convergence process
    buildSpanningTree(...)
```

## Implementation Hints

1. **Bridge ID**: Combine priority (2 bytes) + MAC (6 bytes)
2. **Cost Calculation**: Standard IEEE values per link speed
3. **BPDU Format**: Store root ID, bridge ID, cost
4. **Port Status**: Root, designated, or blocked
5. **Timers**: Hello, forward delay, max age

## Follow-up Questions

- How would you simulate topology changes?
- How would you handle Rapid STP (RSTP)?
- How would you implement VLAN-aware spanning tree?
- How would you calculate optimal cost values?
- How would you visualize the spanning tree?

## Common Pitfalls to Avoid

1. ❌ Selecting wrong root (higher priority instead of lower)
2. ❌ Incorrect cost calculation
3. ❌ Not handling tie-breaking properly
4. ❌ Forgetting to block non-designated ports
5. ❌ Not handling topology changes

## Complexity Analysis to Consider

- **Tree Building**: O(V log V + E) with priority queue
- **Root Election**: O(V)
- **Port Selection**: O(E) 
- **Reconvergence**: O(V log V + E) after change
- **Space**: O(V + E) for tree storage

## Test Cases to Think Through

1. Simple linear topology
2. Ring topology
3. Mesh topology with redundant links
4. Single switch failure
5. Single link failure
6. Multiple failures
7. Root bridge failure
8. Cost variations affecting tree
9. MAC address tie-breaking
10. Convergence timing
