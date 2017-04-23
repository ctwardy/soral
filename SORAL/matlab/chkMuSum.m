function chk = chkMuSum(t)
  %% chkMuSum(t)
  %% This function checks whether the sum of Mu values in the subtrees
  %% which contain Aindex(Anew) and Rindex(Rnew) is less than TOL. If one
  %% of the sums is less than TOL, it fixes the tree structure and returns
  %% true.

global TOL W
global Anew Rnew 
global ROOT NULL FalseArea Aindex Rindex 
global TreeValue 
global Lambda Mu
global Eqn PivotNode

chk = 0;
Anew_subtreeRoot = subtreeRoot(Aindex(Anew));
Rnew_subtreeRoot = subtreeRoot(Rindex(Rnew));
Anew_subtreeSum = sumMu(Anew_subtreeRoot, ROOT);
Rnew_subtreeSum = sumMu(Rnew_subtreeRoot, ROOT);

if Anew_subtreeSum < TOL | Rnew_subtreeSum < TOL
   if Anew_subtreeRoot == Rnew_subtreeRoot
      updateSubtree(Anew_subtreeRoot, ROOT, Mu(FalseArea)*W(FalseArea,Rnew)/Lambda(Rnew), 0);
      rotateSubtree(Rindex(Rnew));
      joinSubtrees(Rindex(Rnew), Aindex(FalseArea));
   elseif Rnew_sumtreeSum < TOL     
      updateSubtree(Rnew_subtreeRoot, ROOT, W(Anew, Rnew)*Mu(Anew)/Lambda(Rnew), 0);
      rotateSubtree(Rindex(Rnew));
      joinSubtrees(Rindex(Rnew), Aindex(Anew));
      TreeValue(Rindex(Rnew)) = t;
      chk = 1;

	  %% What if, in this case, Anew_sumtreeSum was also < TOL, so that
	  %% sumMu in the new tree is still < TOL ??
   else
      updateSubtree(Anew_subtreeRoot, ROOT, Lambda(Rnew)/(W(Anew, Rnew)*Mu(Anew)), 0);
      rotateSubtree(Aindex(Anew));
      joinSubtrees(Aindex(Anew), Rindex(Rnew));
      TreeValue(Aindex(Anew)) = t;
      chk = 1;
   end
end

