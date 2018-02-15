function R = RotZ( theta, opt )

% R = RotZ(theta)
% Return the (3 x 3) rotation matrix that rotates about the z axis
% The angle is in radian.

R = [
  cos(theta) -sin(theta) 0;
  sin(theta)   cos(theta) 0;
  0                  0                 1;
];


if nargin == 2
  if opt ~= 0
    R = [ R [0;0;0]; [ 0 0 0 1] ];
  end
end

return;
