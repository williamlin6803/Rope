ROPES

NAME:  < William Lin >

BALANCED/WORST CASE RUNNIG TIME ANALYSIS:
n = characters in the string of the current Rope (*this)
m = characters in the string of the Rope passed in (for functions that take
    a second rope)
v = longest "value" of a leaf
p = longest path from root to a leaf

Copy Constructor: 
Balanced Rope: O(p)
Worse canse scenario, Unbalanced Rope: O(p)

Index:
Balanced: O(p)
Unbalanced: O(p)

Report:
Balanced:O(log(n) + v)
Unbalanced:O(n + v)

iterator operator++:
Balanced Rope: O(p)
Unbalanced Rope O(logn)

Split:
For balanced Rope: O(p)
Unbalanced Rope O(n)

Concat:
Balanced Rope: O(p)
Unbalanced Rope: O(p)


Corner cases: 
1. Giving an "invalid" index to the index function. This would include giving an index to 
a rope that is null. There is no index valid for this scenario so don't do anything here.
Another example would be if the index given is greater than the size of the Rope or if the
index is less than 0, both of these would be invalid.

2. Another corner case that I tested was with the split function, particularly if we have 
to split the node in half before we split the actual tree. This occurs when after calling
the index function and reaching the left node, our index is not equal to 0. This means that
the Node would need to split in half first. So I tested split with index 12, since for this 
instance, the index would not be 0 when it reaches the leaf node.

3. Lastly, I tested the split if the given index was 0. This would mean that all the nodes of
the left rope would move to the right rope. So essentially, I just moved the pointers of the
root nodes and then made the root pointer of the left root null so that the destuctor function
will not delete the memory from it twice.
