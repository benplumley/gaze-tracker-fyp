function y = tensor_map( T, x1, x2 )

% y = tensor_map( T, x1, x2 )
% Each y_i is a quadratic function such that y_i = x1' T_i x2

for i = 1:size(T,3)
  y(i,:) = sum( (T(:,:,i)*x2) .* x1,1);
end