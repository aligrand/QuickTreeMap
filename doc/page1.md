# Introduction of Algorithm
This algorithm developed for usinf in **map** data structure.  
So it supports basic operations **assign** and **remove** and **get** and many none-basic operations like **size** and **height**.

# Basics
- This data structure use bit shifting as guide to nodes in tree.  
main bits for shift are 1, 2, 4, 8.
- For any **key**, when we move from **HEAD** node to key's node, first bits of  **key** are labels of edges in path. Examples in other sections.
- If we use a **key** that its max len is `L` Byte and we use `m` bit shifting and `n` data then we know  
$$log_{2^m}n \le height \le \frac{8 \times L}{m}$$

# Assign
For assigning we do:  
1. `i = m bits of number` then move to `child[i]`
   1. `child[i]` is null => add new Node
   2. `child[i]` is not null
      1. keys are same => update value
      2. keys are not same => go to **fisrt-number-1**  

- order is $\theta (height)$ means $O(\frac{8 \times L}{m})$

## Assign Example
https://github.com/aligrand/QuickTreeMap/assets/54209629/33c23db5-9546-432f-bfab-c0433659d1c8
  
# Remove
For removing we do:
1. find node to remove
2. move until reach to leaf of path
   1. in during move, we swap data from child node to parent node
3. when reached to leaf node, we remote it
   
- it depends on impeliment, but in orginal, we move to leaf throgh path with **more height**
- order is $\theta (height)$ means $O(\frac{8 \times L}{m})$

## Remove Example
https://github.com/aligrand/QuickTreeMap/assets/54209629/e6d55ec7-65aa-40bd-bc41-da5faa58d4a5

# Note
images are in path [images](res/qtmGraphViz/)   
videos are in path [videos](res)

> [Countinue your tour : Impelimentation Tips](page2.md)
