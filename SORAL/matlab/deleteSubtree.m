function deleteSubtree(child)
global TreeParent TreeFirstChild TreeNextSibling 

parent = TreeParent(child);
current_child = TreeFirstChild(parent);

% Delete child from its old subtree

if current_child == child
    TreeFirstChild(parent) = TreeNextSibling(child);
else
    next_child = TreeNextSibling(current_child);
    while next_child ~= child
        current_child = next_child;
        next_child = TreeNextSibling(current_child);
    end
end
TreeNextSibling(current_child) = TreeNextSibling(child);
