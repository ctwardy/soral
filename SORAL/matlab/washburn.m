function t = washburn(p, T, w)
%% function WASHBURN
%% Allocates resources to areas using Washburn's algorithm.
%% Allocate(p, T, w) returns t which minimizes
%%
%%      sum_i^A p(i)*exp(-y(i))
%%
%% subject to:
%%
%%      y(i) = sum_j^R w(i,j)*t(i,j), i = 1,..,A
%%      sum_i^A t(i,j) <= T(j), j=1,..,R
%%
%%
%% Washburn, A.R., "Finite Method for a Nonlinear Allocation Problem", 
%% Journal of Optimization Theory and Applications, 85(3), pp 705-726, 1995.
%%
%% Where:
%%   p is a row vector of initial probabilities for each area
%%   T is a row vector of total times available for each resource
%%   w is a matrix of resource effectiveness in each area
%%
%% Assumptions:
%%   p is a positive row vector of size A
%%   T is a positive row vector of size R
%%   w is a positive array of size [A, R]
%%   For each resource j, there must be some area i for which w(i,j) > 0.
%%
%% Author: David Albrecht (& Charles Twardy)
%% Date: 15/1/2002
 
global TOL A W 
global ROOT
global Solution

%% Check parameters

if any(p < 0), error('p must be non negative'); end
if any(T < 0), error('T must be non negative'); end
if any(w < 0), error('w must be non negative'); end
if any(sum(w) == 0), error('Each resource must have positive w in SOME area.'); end

%% A is number of areas. R is number of resources.
[A, R] = size(w);  
if length(p) < A | isempty(p), error('Not enough values in p'); end
if length(T) < R | isempty(T), error('Not enough values in T'); end

%%
%% Initialize variables
%%

%% Define our numerical tolerance TOL. The authors of 
%% _Numerical Recipes_ recommend TOL no smaller than
%% the square root of machine precision. In Matlab, 
%% machine precision is 'eps'. This may be overly cautious in our case.
TOL = sqrt(eps);

initialize(R, p, T, w);

%%
%% Find the optimum
%%

while ~optimum(A, R)
    pivot(A, R, T);
end

%%
%% Calculate optimal solution
%%

Solution = zeros(A-1, R);
getSolution(ROOT);
t = Solution;
