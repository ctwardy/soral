function createEqn(node, root, s)
% Sets up a set of linear equations for the subtree containing the node "node".
global NULL IsArea
global TreeFlag TreeParent TreeFirstChild TreeNextSibling
global Eqn

if node ~= NULL
    if TreeFlag(node) == IsArea 
        Eqn(node) = s;
    end
    createEqn(TreeFirstChild(node), root, s);
    if TreeParent(node) ~= root
	createEqn(TreeNextSibling(node), root, s);
    end
end
