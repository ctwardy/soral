function getSolution(node)
% This function gets the feasible solution corresponding
% to the values stored in the Tree.
global ROOT NULL IsArea FalseArea 
global TreeFlag TreeNumber TreeValue TreeParent TreeFirstChild TreeNextSibling
global Solution

if node ~= NULL 
    parentNode = TreeParent(node);
    if parentNode ~= ROOT & parentNode ~= NULL 
        if TreeFlag(node) == IsArea
            i = TreeNumber(node);
            j = TreeNumber(parentNode);
        else
            i = TreeNumber(parentNode);
            j = TreeNumber(node);
        end
        
        if i ~= FalseArea % Remember there is one artificial area which we want to ignore.
            Solution(i,j) = TreeValue(node);
        end
    end
    getSolution(TreeFirstChild(node));
    getSolution(TreeNextSibling(node));
end
