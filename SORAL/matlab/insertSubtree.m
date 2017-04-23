function insertSubtree(child, parent)
% Make child the first child of parent, and therefore insert
% the subtree whose root is child into the subtree containing the node parent.
global TreeParent TreeFirstChild TreeNextSibling 

TreeNextSibling(child) = TreeFirstChild(parent);
TreeFirstChild(parent) = child;
TreeParent(child) = parent;
