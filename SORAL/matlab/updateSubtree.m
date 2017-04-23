function updateSubtree(node, root, s, t)
% Update the values of the nodes in the subtree containing the node "node",
% and update the Lambda and Mu values corresponding nodes in this subtree.
global NULL IsArea 
global Eqn
global Lambda Mu
global TreeFlag TreeNumber TreeValue TreeParent TreeFirstChild TreeNextSibling

if node ~= NULL
    TreeValue(node) = TreeValue(node)-t*Eqn(node);
    if TreeFlag(node) == IsArea
        Mu(TreeNumber(node)) = Mu(TreeNumber(node))*s;
    else
        Lambda(TreeNumber(node)) = Lambda(TreeNumber(node))*s;
    end
    updateSubtree(TreeFirstChild(node), root, s, t);
    if TreeParent(node) ~= root
       updateSubtree(TreeNextSibling(node), root, s, t);
    end
end
