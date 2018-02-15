function T = Trans( t )

% T = Trans( t )
% Return the (4 x 4)  matrix that translates

T = [eye(3) t(:); [0 0 0 1] ];

return;


