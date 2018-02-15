function R = RotX( theta, opt )

% R = RotX(theta)
% Return the (3 x 3) rotation matrix that rotates about the x axis
% The angle is in radian. Return the (4x4) matrix if opt ~= 0.

R = [
  1 0                   0;
  0 cos(theta)  -sin(theta);
  0 sin(theta)     cos(theta);
];


if nargin == 2
  if opt ~= 0
    R = [ R [0;0;0]; [ 0 0 0 1] ];
  end
end


return;
