function flag = optimum(A, R)
global TOL W
global Lambda Mu
global Anew Rnew 

%% This function checks whether the Lagrangian multipliers satisfy the
%% Karush-Kuhn-Tucker conditions. These conditions are that:
%%       Lambda(j) >= W(i,j)Mu(i), i=1,..,A, j=1,..,R
%%
%% If all these conditions hold, the function returns 1. Otherwise the
%% function returns 0.
%%
%% Also, the function finds Anew and Rnew corresponding to the 
%% largest value of
%%       W(Anew,Rnew)Mu(Anew)/Lambda(Rnew)

%% Notes on Machine Precision
%% --------------------------
%% Mu(i) is basically the revised probability for area i, given
%% the resources already allocated to it. Given enough resources,
%% we could have Mu(i) < TOL. In that case, we stop allocating
%% resources to area i, as its probability is now effectively zero.
%%
%% It could still be that Lambda(j) < TOL. Since we divide by
%% Lambda(j), we trap for that, both here and in pivot.m.
  
K = 1;
for i = 1:A
    for j = 1:R
        if (Mu(i) > TOL) & (K*Lambda(j) < W(i,j)*Mu(i)); 
            Anew = i;
            Rnew = j;
			if Lambda(j) > TOL
              K = W(i,j)*Mu(i)/Lambda(j);
			else
			  K = W(i,j)*Mu(i)/TOL;
			end
        end  
    end
end

flag = 0;
if K < 1 + TOL
    flag = 1;
end
