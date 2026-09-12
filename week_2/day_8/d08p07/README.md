# Day 8 Problem 7: UI Component Hierarchy - React-like Virtual DOM Diffing

## Problem Statement
Implement a virtual DOM system similar to React that efficiently updates UI by comparing component trees and computing minimal changes.

## Core Concepts

### Virtual DOM Concept
- **Virtual Representation**: In-memory tree of UI components
- **Reconciliation**: Comparing old and new trees to find differences
- **Diffing**: Minimal set of changes to transform old → new
- **Patching**: Efficiently apply changes to actual DOM

### Tree Comparison Algorithm
- **Depth-First**: Compare nodes level by level
- **Node Matching**: Identify if nodes represent same component
- **Property Changes**: Detect what properties changed
- **Structural Changes**: Detect additions/removals/moves

## Key Concepts to Understand

1. **Component Types**:
   - Same type and key → update properties
   - Different type → remove old, add new
   - Different key → remove old, add new

2. **Keys in Lists**:
   - Enable tracking elements across updates
   - Without keys: index-based matching (inefficient)
   - With keys: semantic matching

3. **Props vs State**:
   - Props: Immutable inputs
   - State: Mutable internal data
   - Changes trigger re-render

4. **Reconciliation**:
   - Compare virtual trees
   - Generate list of operations
   - Apply operations to real DOM

## Problem Variations to Consider

- **Fiber Architecture**: Interruptible rendering
- **Hooks**: Functional components with state
- **Memoization**: Skip re-renders if props unchanged
- **Lazy Loading**: Code-split and load on demand
- **Portals**: Render to different DOM subtree

## Example Walkthrough

### Virtual DOM Structure

**Initial Component Tree:**
```javascript
{
  type: "div",
  props: { className: "container" },
  children: [
    { type: "h1", props: {}, children: ["Hello"] },
    {
      type: "ul",
      props: {},
      children: [
        { type: "li", key: "1", children: ["Item 1"] },
        { type: "li", key: "2", children: ["Item 2"] }
      ]
    }
  ]
}
```

**Updated Component Tree (added Item 3, changed title):**
```javascript
{
  type: "div",
  props: { className: "container active" },
  children: [
    { type: "h1", props: {}, children: ["Hello World"] },
    {
      type: "ul",
      props: {},
      children: [
        { type: "li", key: "1", children: ["Item 1"] },
        { type: "li", key: "2", children: ["Item 2"] },
        { type: "li", key: "3", children: ["Item 3"] }
      ]
    }
  ]
}
```

### Diff Process:

1. **Compare root**:
   - Type: same (div)
   - Props: className changed "container" → "container active"
   - Action: UPDATE PROPS

2. **Compare first child (h1)**:
   - Type: same
   - Props: same
   - Children changed: "Hello" → "Hello World"
   - Action: UPDATE TEXT

3. **Compare ul**:
   - Type: same
   - Props: same
   - Children: different length

4. **Compare list items**:
   - key "1": same (no changes)
   - key "2": same (no changes)
   - key "3": new (INSERT at end)

### Resulting Operations:
```
1. Update root props: { className: "container active" }
2. Update h1 text: "Hello World"
3. Insert new li with key "3"
```

## Algorithm Outline

```
function diffTrees(oldNode, newNode):
    if oldNode == null and newNode != null:
        return [{ type: 'CREATE', node: newNode }]
    
    if oldNode != null and newNode == null:
        return [{ type: 'REMOVE' }]
    
    if oldNode.type != newNode.type:
        return [
            { type: 'REMOVE' },
            { type: 'CREATE', node: newNode }
        ]
    
    // Same type, check properties
    operations = []
    
    if oldNode.props != newNode.props:
        operations.push({
            type: 'UPDATE_PROPS',
            props: newNode.props
        })
    
    // Check children
    if oldNode.type is not LEAF:
        childOps = diffChildren(oldNode.children, newNode.children)
        operations.push(...childOps)
    else if oldNode.text != newNode.text:
        operations.push({
            type: 'UPDATE_TEXT',
            text: newNode.text
        })
    
    return operations

function diffChildren(oldChildren, newChildren):
    operations = []
    
    // Build map of keyed children
    oldMap = buildKeyMap(oldChildren)
    newMap = buildKeyMap(newChildren)
    
    // Process new children
    for i = 0 to max(oldChildren.length, newChildren.length):
        oldChild = oldChildren[i]
        newChild = newChildren[i]
        
        if newChild is not null:
            if oldChild is null:
                operations.push({
                    type: 'INSERT',
                    index: i,
                    node: newChild
                })
            else:
                childOps = diffTrees(oldChild, newChild)
                operations.push(...childOps)
        else:
            operations.push({
                type: 'REMOVE',
                index: i
            })
    
    return operations

function patch(node, operations):
    for each op in operations:
        switch op.type:
            case 'CREATE':
                createElement(op.node)
            case 'REMOVE':
                node.remove()
            case 'UPDATE_PROPS':
                updateProps(node, op.props)
            case 'UPDATE_TEXT':
                node.textContent = op.text
            case 'INSERT':
                insertChild(node, op.index, op.node)
```

## Implementation Hints

1. **Node Representation**: Simple objects with type, props, children
2. **Key Management**: Use keys to match elements across updates
3. **Operation Queue**: Collect all changes, then apply
4. **Recursion**: Tree traversal naturally uses recursion
5. **Comparison Function**: Deep comparison for props/text

## Follow-up Questions

- How would you handle component lifecycle hooks?
- How would you optimize deeply nested trees?
- How would you handle async rendering?
- How would you support animations during updates?
- How would you track which elements need re-render?

## Common Pitfalls to Avoid

1. ❌ Not using keys in lists (causes wrong element updates)
2. ❌ Modifying old tree during diff
3. ❌ Not deep comparing props objects
4. ❌ Wrong index tracking during insertion/removal
5. ❌ Comparing by reference instead of value

## Complexity Analysis to Consider

- **Diffing**: O(n) where n = total nodes (with key optimization)
  - Worst case: O(n³) without key optimization
- **Patching**: O(m) where m = number of changes
- **Space**: O(h) for recursion, O(n) for change queue

## Test Cases to Think Through

1. Empty tree → tree with elements
2. Tree → empty tree
3. Same structure, different props
4. Same structure, different text
5. Added elements
6. Removed elements
7. Reordered elements (with keys)
8. Reordered elements (without keys)
9. Nested changes
10. Components changing type
