function joinSubtrees(child, parent)
% Join the subtree whose root is "child" so that this root becomes a child
% of the node "parent".

% Delete child from its old subtree

deleteSubtree(child);

% Make child the first child of the parent node

insertSubtree(child, parent);
