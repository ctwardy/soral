function pivot(A, R, T)
  %% Pivot does what is necessary to join Rnew to Anew while keeping
  %% all the equations satisfied. This may involve any number of
  %% intermediate steps where parts of branches get cut away and
  %% hung off of ROOT. The code is made a little uglier by having
  %% to check that we don't divide by zero.
  
  global TOL W
  global Anew Rnew 
  global ROOT NULL IsArea Aindex Rindex 
  global TreeValue TreeFirstChild 
  global Lambda Mu
  global Eqn PivotNode        % PivotNode is where the tree may be cut.
  
  %% Assumes optimum.m checks that Mu(i) > TOL, we don't have	
  %% to worry about Anew's subtree having sumMu < TOL.
  
  t_increase = 0;
  finished = 0;
  
  while ~finished
    Anew_subtreeRoot = subtreeRoot(Aindex(Anew));
    Rnew_subtreeRoot = subtreeRoot(Rindex(Rnew));
	
    Eqn = zeros(1, A+R+1);
	
    if Anew_subtreeRoot == Rnew_subtreeRoot
      
      %% Find how much to increase t(Anew, Rnew)
      %% First set up Eqns for t(Anew, Rnew)
      s = (Lambda(Rnew)-W(Anew,Rnew)*Mu(Anew))/sumMu(Anew_subtreeRoot, ROOT);
      
      createEqn(Anew_subtreeRoot, ROOT, s);
      Eqn(Rindex(Rnew)) = 1;
      Eqn(Aindex(Anew)) = Eqn(Aindex(Anew)) + W(Anew, Rnew);
      
      %% Solve Eqns for t(Anew, Rnew). Solve may change PivotNode.
      PivotNode = Rindex(Rnew);
      t_step = solveEqn(Anew_subtreeRoot, ROOT, T(Rnew));
	  
      %% Update the Tree, subtreeRoots, Lambda, and Mu 
	  
      updateSubtree(Anew_subtreeRoot, ROOT, exp(s*t_step), t_step);
      t_increase = t_increase + t_step;
	  
      if PivotNode == Rindex(Rnew) & TreeFirstChild(Rindex(Rnew)) == NULL
        Lambda(Rnew) = W(Anew,Rnew)*Mu(Anew);
        joinSubtrees(PivotNode, Aindex(Anew));
        TreeValue(PivotNode) = t_increase;
        finished = 1;
	  else
        joinSubtrees(PivotNode, ROOT);
        finished = chkMuSum(t_increase);
      end
	  
    else 
	  
	  %% It is possible that sumMu for Rnew's subtree is < TOL. If so,
	  %% we should first join Rnew's subtree to the false area, to fix that.
	  
	  if sumMu(Rnew_subtreeRoot, ROOT) < TOL
		updateSubtree(Rnew_subtreeRoot, ROOT, Mu(FalseArea)*W(FalseArea,Rnew)/Lambda(Rnew), 0);
		rotateSubtree(Rindex(Rnew));
		joinSubtrees(Rindex(Rnew), Aindex(FalseArea));
	  end
	  
	  
      %% Find how much to increase t(Anew, Rnew)
      %% Set up Eqns for t(Anew, Rnew) for subtreeRoot with node 
      %% corresponding to resource Rnew
      s_r = Lambda(Rnew)/sumMu(Rnew_subtreeRoot, ROOT);
      
      createEqn(Rnew_subtreeRoot, ROOT, s_r);
      Eqn(Rindex(Rnew)) = 1;
      
      %% Solve Eqns for t(Anew, Rnew) for subtreeRoot with node 
      %% corresponding to resource Rnew. Solve may change PivotNode.
      
      PivotNode = Rindex(Rnew);
      t_r = solveEqn(Rnew_subtreeRoot, ROOT, T(Rnew));
	  
      %% Set up Eqns for t(Anew, Rnew) for subtreeRoot with node corresponding
      %% to area Anew
      
      s_a = -W(Anew,Rnew)*Mu(Anew)/sumMu(Anew_subtreeRoot, ROOT);
      
      if TreeFirstChild(Anew_subtreeRoot) == NULL
        t_a = t_r;
        Eqn(Anew_subtreeRoot) = 0;
	  else
        createEqn(Anew_subtreeRoot, ROOT, s_a);
        Eqn(Aindex(Anew)) = Eqn(Aindex(Anew)) + W(Anew, Rnew);
		
        %% Solve Eqns for t(Anew, Rnew) for subtreeRoot with node.
		%% corresponding to Anew. Solve may change PivotNode.
		
        t_a = solveEqn(Anew_subtreeRoot, ROOT, t_r);
	  end
      
      %% Solve the following equation for t_l
	  %% 
      %%    t_l*s_r = log(w(Anew, Rnew)*Mu(Anew)/Lambda(Rnew)) + t_l*s_a
      %%
      
      if Lambda(Rnew) > TOL
		t_l = log(W(Anew, Rnew)*Mu(Anew)/Lambda(Rnew))/(s_r - s_a);
	  else
		t_l = log(W(Anew, Rnew)*Mu(Anew)/TOL)/(s_r - s_a);
	  end
	  
      %% t_step is the minimum of t_a, t_r and t_l
      %% Note by construction t_a is always less than or equal to t_r.
      
      t_step = min(t_a, t_l);
      
      t_increase = t_increase + t_step;
      
      %% Update the Tree, Lambda, and Mu 
	  
      updateSubtree(Rnew_subtreeRoot, ROOT, exp(s_r*t_step), t_step);
      updateSubtree(Anew_subtreeRoot, ROOT, exp(s_a*t_step), t_step);
	  
      if t_step < t_l & PivotNode == Rindex(Rnew) & TreeFirstChild(Rindex(Rnew)) == NULL
        Lambda(Rnew) = W(Anew,Rnew)*Mu(Anew);
        joinSubtrees(PivotNode, Aindex(Anew));
        TreeValue(PivotNode) = t_increase;
        finished = 1;
		
      elseif t_step < t_l
        joinSubtrees(PivotNode, ROOT);
        finished = chkMuSum(t_increase);
		
      elseif Aindex(Anew) == Anew_subtreeRoot
        joinSubtrees(Aindex(Anew), Rindex(Rnew));
        TreeValue(Aindex(Anew)) = t_increase;
        finished = 1;
		
      elseif Rindex(Rnew) == Rnew_subtreeRoot
        joinSubtrees(Rindex(Rnew), Aindex(Anew));
        TreeValue(Rindex(Rnew)) = t_increase;
        finished = 1;
		
      else
        rotateSubtree(Rindex(Rnew));
        joinSubtrees(Rindex(Rnew), Aindex(Anew));
        TreeValue(Rindex(Rnew)) = t_increase;
        finished = 1;
		
	  end
	  
	end
  end
  
  %% A note on exit conditions from pivot.m
  %% ---------------------------------------
  %%
  %% Pivot tries to join Rnew to Anew (or vice versa). Before
  %% it can do that, it may have to cut various other subtrees
  %% and hang them off ROOT. Any of those interim subtrees
  %% could have sumMu < TOL, or any Lambda or Mu < TOL.  We think.
  %%
  %% Sometimes pivot calls chkMuSum. The result is that 
  %% Anew and Rnew are in the same subtree. In the case where
  %% Anew and Rnew were orginally in the same subtree, we continue in
  %% pivot else we finish.
  %%
  %% THEREFORE: we need to check each Mu and Lambda value in optimum.m
  %% lest we divide by zero there. If optimum.m avoids choosing
  %% for Anew any area with Mu < TOL (why bother reducing it further?),
  %% then pivot needs only check that sumMu(Rnew's subtree) > TOL.
  
