function s = sumMu(node, root)
%% Calculates the sum of all the Mu values, corresponding to the nodes 
%% representing areas, in the subtree with root node.

global NULL IsArea 
global TreeFlag TreeNumber TreeParent TreeFirstChild TreeNextSibling
global Mu

s = 0;
if node ~= NULL
   if TreeFlag(node) == IsArea
       s = Mu(TreeNumber(node));
   end
   s = s + sumMu(TreeFirstChild(node), root);
   if TreeParent(node) ~= root
      s = s + sumMu(TreeNextSibling(node), root);
   end
end
