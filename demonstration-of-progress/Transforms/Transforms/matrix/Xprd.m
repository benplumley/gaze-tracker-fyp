function X = Xprd( x )

% X = Xprd( x )
% return the matrix that forms the cross-product of x
X = [
  0 -x(3) x(2);
  x(3) 0 -x(1);
  -x(2) x(1) 0 ];

return;
