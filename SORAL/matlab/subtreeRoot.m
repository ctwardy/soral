function root = subtreeRoot(node)
% Finds the root node of the subtree containing node "node".
global ROOT
global TreeParent

parent = TreeParent(node);

while parent ~= ROOT
    node = parent;
    parent = TreeParent(node);
end
root = node;
