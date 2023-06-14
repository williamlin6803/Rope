HOMEWORK 8: ROPES


NAME:  < William Lin >


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

< Javier upperclassmen Tyler lab mentor Fu lab mentor Lecture 18 >

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.


ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  < 30 hours >

BALANCED/WORST CASE RUNNIG TIME ANALYSIS:
n = characters in the string of the current Rope (*this)
m = characters in the string of the Rope passed in (for functions that take
    a second rope)
v = longest "value" of a leaf
p = longest path from root to a leaf
Using these variables, state and explain the big-O running time of each 
of the following operations two ways: 1) with a balanced Rope, 2) with an 
extremely unbalanced Rope. Explain what you considered an extremely 
unbalanced rope for the string "Hello my name is Simon".

Copy Constructor: 
Balanced Rope: O(p)
Worse canse scenario, Unbalanced Rope: O(p)
The time complexity of the copy constructor would be O(p) because it has to
recursively travel down the tree to each leaf node since that is where the 
strings for it are located so the run time would be dependent on the height
of the tree.

Index:
Balanced: O(p)
Unbalanced: O(p)
In both a balanced and an unbalanced tree, the entire tree would need to be traversed 
through. Visualizing a tree similar to my initial explanation, we would have to access 
practically every node in order to acquire the value indicated within the index function, 
therefore the time complexity would have to be O(p).

Report:
Balanced:O(log(n) + v)
A single leaf index function is initially called within report() which accounts for the
log(n) aspect. The function continues to append strings to the ret value until i reaches
j, therefore the rest of the complexity depends on the path to the next leaf and the 
length of the value within each leaf. Since report adds only a certain amount of
characters from a leaf's value, space permitting, through the substr string function,
which operates with a linear time complexity, the complexity of report with a balanced
tree is O(log(n) + v).

Unbalanced:O(n + v)
An unbalanced tree means linear complexity for n and v for the same reason that index operated
on a linear time complexity. However, since it is called at the start of the report function,
the complexity of report with an unbalanced tree should O(n + v).

iterator operator++:
For balanced Rope: O(p)
The time complexity for a balanced tree would be O(p) because the iterator has to continue 
iterating and incrementing itself until it is the leftmost leaf node of the subtree, since 
it is an in-order traversal. Thus, it would be p since it would just be the longest path 
from the current subtree's root.

Worst case scenario, Unbalanced Rope O(logn)
Unbalanced: O(1)
Iterator operator ++ would, in most worst cases, have little to no need to increment
itself to the leftmost child node since every node has a single child. Practically
no while loops will be iterated through during the increment operator, and since
the if statements are the most likely only operations occurring during this operation,
operator++ would have a constant complexity of O(1).

Split:
For balanced Rope: O(p)
Worst case scenario, Unbalanced Rope O(n)
In both a balanced and an unbalanced tree, the entire tree would need to be traversed 
through. The index function was called first and it goes to the leaf node that the index
is located. Then the rest of the function is essentially traversing upwards until its
parent is null, in which case we stop. The entire time that it is moving upwards, it is
checking whatever it is the children of its parent left side or its parent right side.
Therefore, the runtime would be O(p).

Concat:
Balanced Rope: O(p)
Worse canse scenario, Unbalanced Rope: O(p)
The time complexity of concat would be O(p) because it is calling the copy tree function which 
is recursively traveling down from the root of the tree to the leaf node since that is where 
that is where the strings for it are located so the run time would again be dependent on the 
height of the tree.


TESTING & DEBUGGING STRATEGY: 
Briefly describe the tests in your StudentTests() function.
How did you test the "corner cases" of your implementation?

The corner cases I tested were 
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

MISC. COMMENTS TO GRADER:  
(optional, please be concise!)
Have a nice day :)
