function t = allocate(p, T, w)
%ALLOCATE Allocates resources to areas
% Allocate(p, T, w) returns t which minimizes
%      sum_i^A p(i)*exp(-sum_j^R w(i,j)*t(i,j))
% subject to:
%      sum__i^A t(i,j) <= T(j), j=1,..,R
%
% Assumptions:
%   p is a positive row vector of size A
%   T is a positive row vector of size R
%   w is a positive array of size [A, R]
%
% Author: David Albrecht
% Date: 23/10/2001

% Check parameters
if any(p < 0), error('p must be positive'); end
if any(T < 0), error('T must be positive'); end
if any(w < 0), error('w must be positive'); end
ChkP = size(p);
ChkT = size(T);
[A, R] = size(w);
if ChkP < A, error('Not enough values in p'); end
if ChkT < R, error('Not enough values in T'); end

% Initialize r, a, t, Resources
r = zeros(A, 1); % r(i) is the number of resources used in area i
a = ones(R, 1); % a(j) is the number of areas that use resource j
t = zeros(A,R);
grad = zeros(A, R);

for i = 1:A
    grad(i, :) = -p(i)*w(i, :);
end
[gradSort, index] = sort(grad);
clear gradSort;
for j = 1:R
    r(index(1,j)) = r(index(1,j)) + 1;
end
c = zeros(R, 1);
d = zeros(R, 1);

while any(T > 0)
    Resources = find(T > 0);
    for j = Resources
        sum = 0;
        for i = 1:a(j)
            sum = sum + 1/w(index(i,j), j);
        end
        c(j) = T(j)/sum;
        
        newArea = a(j) + 1;
        if newArea <= A & r(index(newArea,j)) < r(index(1, j))
            d(j) = log(p(index(1,j))*w(index(1,j),j)/(p(index(newArea,j))*w(index(newArea,j),j)))/(r(index(1,j))-r(index(newArea,j)));
        end
    end
   
    s = min(min(c(Resources)), min(d(Resources)));
    
    for j = Resources
        for i = 1:a(j)
            t(index(i,j),j) = t(index(i,j),j) + s/w(index(i,j),j);
            T(j) = T(j) - s/w(index(i,j),j);
            p(index(i,j)) = p(index(i,j))*exp(-s);
        end
    end
    
    for j = find(c == s)
        for i = 1:a(j)
            r(index(i,j)) = r(index(i,j))-1;
        end
    end
    
    for j = find(d == s)
        a(j) = a(j) + 1;
        r(index(a(j),j)) = r(index(a(j),j)) + 1;
    end
end
    
