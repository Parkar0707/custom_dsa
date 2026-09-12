# Day 9 Problem 1: Stock Trading System - Order Book with Fast Insert/Delete/Query

## Problem Statement
Build a stock trading system with an order book that efficiently handles insertion, deletion, and range queries of buy/sell orders. Implement using AVL trees.

## Core Concepts

### AVL Tree
- **Self-balancing BST**: Maintains height balance during insertions/deletions
- **Balance Factor**: Height(left) - Height(right) ∈ {-1, 0, 1}
- **Rotations**: Restore balance after modifications
- **Guaranteed**: O(log n) for all operations

### Order Book Structure
- **Buy Orders**: Sorted descending price (best price first)
- **Sell Orders**: Sorted ascending price (best price first)
- **Matching**: When buy price ≥ sell price, execute trade
- **Market Making**: Spread between highest buy and lowest sell

### Rotations
- **Left Rotation**: Right-heavy rebalancing
- **Right Rotation**: Left-heavy rebalancing
- **Left-Right**: Complex rebalancing pattern
- **Right-Left**: Complex rebalancing pattern

## Key Concepts to Understand

1. **AVL Node**: Value, height, left/right children
2. **Height Calculation**: max(height(left), height(right)) + 1
3. **Balance Check**: Perform after insertion/deletion
4. **Rebalancing**: Rotations maintain balance property
5. **Order Matching**: Efficient price discovery

## Problem Variations to Consider

- **Order Types**: Limit orders, market orders, stop orders
- **Partial Fills**: One order partially matches multiple
- **Order Cancellation**: Remove orders without executing
- **Time Priority**: Same price, earlier orders execute first
- **Real-time Streaming**: Process millions of orders/second

## Example Walkthrough

### Order Book State

**Buy Orders (descending price):**
```
Price: 99.50, Volume: 100 (Customer A)
Price: 99.20, Volume: 200 (Customer B)
Price: 98.50, Volume: 150 (Customer C)
```

**Sell Orders (ascending price):**
```
Price: 100.50, Volume: 50 (Customer D)
Price: 101.00, Volume: 300 (Customer E)
Price: 101.50, Volume: 100 (Customer F)
```

**Bid-Ask Spread**: 100.50 - 99.50 = 1.00

### Add New Order: Buy 200 @ 101.00

- Market order to buy at 101.00
- Matches with Sell @ 100.50: Execute 50 shares @ 100.50
- Matches with Sell @ 101.00: Execute 150 shares @ 101.00
- Remaining 50 shares added to buy book @ 101.00

### AVL Tree for Buy Orders

After several insertions at different prices:

```
          99.20
         /     \
      98.50   99.50
      /
   97.00
```

After adding 99.75:

```
          99.20          99.50
         /     \   →    /     \
      98.50   99.50  99.20   ...
      /              /   \
   97.00         98.50   99.75
```

(Re-balanced to maintain height difference ≤ 1)

## Algorithm Outline

```
function insertOrder(order):
    if order.side == BUY:
        executeMatches(order, sellTree)
        if order.remainingVolume > 0:
            buyTree.insert(order.price, order)
    else:  // SELL
        executeMatches(order, buyTree)
        if order.remainingVolume > 0:
            sellTree.insert(order.price, order)

function executeMatches(buyOrder, sellTree):
    while buyOrder.remainingVolume > 0:
        bestSell = sellTree.findMin()
        
        if bestSell == null or bestSell.price > buyOrder.price:
            break  // No matching sell order
        
        executeVolume = min(buyOrder.remainingVolume, bestSell.remainingVolume)
        
        // Record trade
        recordTrade(buyOrder.price, executeVolume)
        
        buyOrder.remainingVolume -= executeVolume
        bestSell.remainingVolume -= executeVolume
        
        if bestSell.remainingVolume == 0:
            sellTree.delete(bestSell.price)

function getBestBid():
    return buyTree.findMax().price

function getBestAsk():
    return sellTree.findMin().price

function getOrdersInRange(minPrice, maxPrice):
    return priceTree.rangeSearch(minPrice, maxPrice)

// AVL Tree Operations
function avlInsert(root, key, value):
    if root == null:
        return new AVLNode(key, value)
    
    if key < root.key:
        root.left = avlInsert(root.left, key, value)
    else:
        root.right = avlInsert(root.right, key, value)
    
    root.height = max(height(root.left), height(root.right)) + 1
    
    return avlBalance(root)

function avlBalance(node):
    balanceFactor = height(node.left) - height(node.right)
    
    if balanceFactor > 1:  // Left heavy
        if height(node.left.left) >= height(node.left.right):
            return rightRotate(node)
        else:
            node.left = leftRotate(node.left)
            return rightRotate(node)
    
    if balanceFactor < -1:  // Right heavy
        if height(node.right.right) >= height(node.right.left):
            return leftRotate(node)
        else:
            node.right = rightRotate(node.right)
            return leftRotate(node)
    
    return node

function rightRotate(z):
    y = z.left
    T3 = y.right
    
    y.right = z
    z.left = T3
    
    z.height = max(height(z.left), height(z.right)) + 1
    y.height = max(height(y.left), height(y.right)) + 1
    
    return y

function leftRotate(z):
    y = z.right
    T2 = y.left
    
    y.left = z
    z.right = T2
    
    z.height = max(height(z.left), height(z.right)) + 1
    y.height = max(height(y.left), height(y.right)) + 1
    
    return y
```

## Implementation Hints

1. **Separate Trees**: Buy and sell orders in different AVL trees
2. **Height Tracking**: Maintain height in each node
3. **Rotation Implementation**: Carefully handle pointers
4. **Order Matching**: Process from best price first
5. **Event Recording**: Log all trades for audit trail

## Follow-up Questions

- How would you handle partial fills?
- How would you implement order cancellation?
- How would you add order time priority?
- How would you implement market depth visualization?
- How would you scale to millions of orders?

## Common Pitfalls to Avoid

1. ❌ Incorrect balance factor calculation
2. ❌ Wrong rotation logic
3. ❌ Not updating heights after rotation
4. ❌ Matching in wrong order (price priority)
5. ❌ Floating-point precision issues in price comparisons

## Complexity Analysis to Consider

- **Insert**: O(log n)
- **Delete**: O(log n)
- **Find Best Bid/Ask**: O(1) or O(log n)
- **Range Query**: O(log n + k) where k = results
- **Matching**: O(m log n) where m = matched orders

## Test Cases to Think Through

1. Insert first order
2. Insert non-matching order
3. Insert matching order (full execution)
4. Insert matching order (partial execution)
5. Multiple matches
6. Delete order
7. Best bid/ask queries
8. Range queries
9. Balance verification after rotations
10. Large order book stress test
