function t = solveEqn(node, root, tmax)
% Solves a set of linear equation for the subtree containing the node "node".
global W
global NULL IsArea
global TreeFlag TreeNumber TreeValue TreeParent TreeFirstChild TreeNextSibling
global Eqn PivotNode

t = tmax;
if node ~= NULL
   t = solveEqn(TreeFirstChild(node), root, t);
   if TreeParent(node) ~= root
      t = solveEqn(TreeNextSibling(node), root, t);
   end
   parentNode = TreeParent(node);
   if parentNode ~= root
      if TreeFlag(node) == IsArea
         Eqn(node) = Eqn(node)/W(TreeNumber(node), TreeNumber(parentNode));
         Eqn(parentNode) = Eqn(parentNode) - Eqn(node);
      else    
         Eqn(parentNode) = Eqn(parentNode) - Eqn(node)*W(TreeNumber(parentNode), TreeNumber(node));
      end
    
      if t*Eqn(node) > TreeValue(node)
         t = TreeValue(node)/Eqn(node);
         PivotNode = node;
      end
   else
      Eqn(node) = 0;
   end
end

