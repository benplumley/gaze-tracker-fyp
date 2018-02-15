% y = tensor_apply( T, x )
% Apply second order tensor T to each vector x to give y(1,:) = x' * T(:,:,i) * x.
% If x is a matrix, each column is treated as vector and the output is placed in the
% corresponding column of y.
% pre
%    T is an NxNxN tensor
%    x is a NxM matrix
% post
%    y is a NxM matrix

function y = tensor_apply( T, x )

y = zeros( size(T,3),size(x,2) );

for i = 1:size(T,3)
  y(i,:) = sum( (T(:,:,i)*x) .* x,1);
end

return;
