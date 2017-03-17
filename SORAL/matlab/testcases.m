function t = testcases()
  %% TESTCASES      Test cases for washburn.m
  %%     Returns 0 if everything is OK.
  %%     Returns 1 and prints errors otherwise.
  
  clear failure;
  failure = 0;
  
 %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 %% Cases Charnes-Cooper could solve.
 %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

  % Case 0: 1 area, 1 resource
  clear p T w answer;
  %load case0.mat;
  p      = 4;
  w      = 4;
  T      = 0.05;
  answer = 0.05;
  temp = washburn(p,T,w);
  if temp ~= answer
	error('Case 0 failed.');
	failure = 1;
  end

  % Case 1: 4 areas, 1 resource
  clear p T w answer;
  p      = [8 4 1 2];
  w      = [1 4 12 8]';
  T      = 0.05;
  answer = [0 0.033333 0 0.0166667]';
  temp = washburn(p,T,w);
  if temp ~= answer
	error('Case 1 failed.');
	temp
	failure = 1;
  end

  % Case 2: 4 areas, 1 resource
  clear p T w answer;
  p      = [4 2 8 1];
  w      = [4 1 1 12]';
  T      = 0.10;
  answer = [0.92980 0 0 0.007020]';  
  temp = washburn(p,T,w);
  if temp ~= answer
	error('Case 2 failed');
	temp
	failure = 1;
  end

  % Case 3: 3 areas, 1 resource
  clear p T w answer;
  p      = [2 4 2];
  w      = [9 3 6]';
  T      = 0.20;
  answer = [0.07322410073711 0.08451726617526 0.04225863308763]';
  temp = washburn(p,T,w);
  if (round(temp*10000) ~= round(answer*10000))
	temp
	answer
	error('Case 3 failed.');
	failure = 1;
  end

  % Case 4: 4 areas, 1 resource
  % Two unviable search areas
  clear p T w answer;
  p      = [1 4 20 0];
  w      = [8 4 0 10]';
  T      = 0.50;
  answer = [0.10890 0.39110 0 0 ]';
  temp = washburn(p,T,w);
  if (round(temp*10000) ~= round(answer*10000))
	temp
	answer
	error('Case 4 failed.');
	temp
	failure = 1;
  end

  % Case 5: 3 areas, 1 resource
  % 
  clear p T w answer;
  p      = [2 6 4];
  w      = [6 2 3]';
  T      = 0.50;
  answer = [0.083333 0.25 0.166667]';  
  temp = washburn(p,T,w);
  if (round(temp*10000) ~= round(answer*10000))
	temp
	answer
	error('Case 5 failed.');
	failure = 1;
  end

  % Case 6: 4 areas, 1 resource
  % No viable searches
  clear p T w answer;
  p      = [0 7 0 5];
  w      = [8 0 0 0]';
  T      = 0.50;
  answer = [0 0 0 0 ]';
  temp = washburn(p,T,w);
  if (round(temp*10000) ~= round(answer*10000))
	temp
	answer
	error('Case 6 failed.');
	failure = 1;
  end

 %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 %% Cases that require Washburn
 %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

  % Case 7: 2 resources, 2 areas
  % A case we could solve by hand. 
  clear p T w answer;
  p      = [0.5 0.5];
  w		 = [0.1 0.05; 0.02 0.005];
  T      = [16.1 13.9];
  answer = [10.30365 13.9; 5.79635 0];  
  temp = washburn(p,T,w);
  if (round(temp*10000) ~= round(answer*10000))
	temp
	answer
	error('Case 7 failed.');
	failure = 1;
  end

  % Case 8: 4 areas, 3 resources
  % From Washburn's JOTA paper
  clear p T w answer;
  p      = [1000 1000 2000 2000];
  w		 = [1 3 0; 2 2 1; 3 2 0; 4 1 1];
  T		 = [3 2 1];
  answer = [0 1.22976 0; 0.37167 0.77024 1; 1.46081 0 0; 1.16753 0 0];
  temp = washburn(p,T,w);
  if (round(temp*10000) ~= round(answer*10000))
	temp
	answer
	error('Case 8 failed.');
	failure = 1;
  end

  % Case 9: 1 area, 1 resource
  % Things exactly balance:
  %   Lambda(1) = W(1,1) * Mu(1), so T = 5*exp(-5)*sqrt(TOL)/2.
  % So no resource is allocated even though Mu(1) > TOL.
  clear p T w answer; 
  TOL = sqrt(eps);
  p = [2*TOL];
  w = [1/TOL];
  T = 5*exp(-5)*sqrt(TOL)/2;
  clear TOL;
  answer = 0;
  temp = washburn(p,T,w);
  if temp ~= answer
	error('Exactly tolerance case did not pass.');
	failure = 1;
  end


t = failure;
