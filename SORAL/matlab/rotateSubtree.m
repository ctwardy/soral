function rotateSubtree(pivotNode)
% Rotate the subtree which contains the node "pivotNode", to make it the root
% of this subtree.
global ROOT 
global TreeParent TreeValue

parent = TreeParent(pivotNode);

if parent ~= ROOT 
    rotateSubtree(parent);

    % Delete parent from ROOT

    deleteSubtree(parent);
    
    % Delete pivotNode from parent subtree
    
    deleteSubtree(pivotNode);
    
    % Make parent the first child of pivotNode
    
    insertSubtree(parent, pivotNode);
    
    % Make pivotNode the first child of ROOT
    
    insertSubtree(pivotNode, ROOT);
    
    % Swap values of pivotNode and parent
    TreeValue([pivotNode, parent]) = TreeValue([parent, pivotNode]);
end

