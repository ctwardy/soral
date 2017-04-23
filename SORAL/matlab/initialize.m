function initialize(R, p, T, w)
global TOL A W
global Lambda Mu
global ROOT NULL IsArea FalseArea Aindex Rindex 
global TreeValue TreeNumber TreeFlag TreeParent TreeFirstChild TreeNextSibling 

%% To optain an initial feasible solution an artifical 
%% area is added.

A = A + 1; 
weight = 5/sum(T);             % This is Washburn's suggested value.
                               % Presumably we want something less
                               % than the avg w value.
W = [w; weight*ones(1, R)];

%% Lambda(j),j=1,..R, and Mu(i),i=1,..,A, are the Lagrangian 
%% multipliers corresponding to the following equations 
%% representively:
%%
%%      sum__i^A t(i,j) <= T(j), j=1,..,R
%%      y(i) = sum_j^R w(i,j)*t(i,j), i = 1,..,A
%%
%% Every area has a Mu multiplier, initially equal to its probability p.
%% Every resource has a Lambda multiplier.

%% We start with all resources in the artificial area. We set things up so
%% the initial Mu(A) WHEN ALL RESOURCES ARE ASSIGNED TO 'A' is comfortably
%% above TOL. Therefore Mu(A) can never be less than TOL.

Mu = [p, sqrt(TOL)];
Mu(A) = Mu(A)*exp(-5);                %% Washburn's value again.
Lambda = Mu(A) * weight * ones(1,R);  %% As req'd for all res. assigned to A. 

%% Information regarding feasible solutions is stored in a
%% tree. This tree has A + R + 1 nodes. Each node has: 
%%   - a value corresponding to an allocation of a resource to an area, 
%%   - a flag indicating whether the node corresponds to a resource or an area, 
%%   - the number of the corresponding resource or area,  
%%   - the number of its parent node, 
%%   - the number of its first child, and
%%   - the number of its next sibling. 
%%
%% The value of ROOT and its flag is never used.
%%
%% Aindex - is an array. Each index in the array corresponds to an area,
%% and the value is the index of the node, corresponding to the area, in 
%% the tree.
%% Rindex - is an array. Each index in the array corresponds to a resource,
%% and the value is the index of the node, corresponding to the resource, in 
%% the tree.
%% Tree - is a structure of arrays, each index in the array corresponds to a 
%% node in the tree. 

%% Define some global constants
ROOT = 1;
NULL = 0;
IsArea = 1;
IsResource = 2;
FalseArea = A;

%% Define the main structures
Aindex = [2:A+1];
Rindex = [A+2:A+R+1];
TreeValue = [zeros(1,A+1), T];
TreeFlag = [NULL, IsArea*ones(1,A), IsResource*ones(1,R)];
TreeNumber = [NULL,(1:A),(1:R)];
TreeParent = [NULL, ROOT + zeros(1,A), A + 1 + zeros(1,R)];
TreeFirstChild = [2, NULL*ones(1,A-1),A+2,NULL*ones(1,R)];

%% The following tests are not strictly necessary, but avoid
%% Octave warnings about empty matrices when A==1 or R==1.
%% In Matlab you could just use the last version.

if R==1 & A==1
   TreeNextSibling = [NULL,NULL,NULL];
elseif R==1 & A>1
   TreeNextSibling = [NULL,(3:A+1),NULL,NULL];
elseif A==1
   TreeNextSibling = [NULL,NULL,(A+3:A+R+1),NULL];
else
   TreeNextSibling = [NULL,(3:A+1),NULL,(A+3:A+R+1),NULL];
end

