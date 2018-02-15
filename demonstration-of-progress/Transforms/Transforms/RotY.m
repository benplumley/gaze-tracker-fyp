function R = RotY( theta, opt )

% R = RotY(theta,opt)
% Return the (3 x 3) rotation matrix that rotates about the y axis
% The angle is in radian. Return the (4x4) matrix if opt ~= 0.

R = [
  cos(theta)  0 sin(theta);
  0                  1 0;
 -sin(theta)   0 cos(theta);
];

if nargin == 2
  if opt ~= 0
    R = [ R [0;0;0]; [ 0 0 0 1] ];
  end
end

return;
