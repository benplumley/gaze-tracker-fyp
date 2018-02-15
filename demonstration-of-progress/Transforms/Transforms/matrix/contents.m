% Rotation matrices in 3D
% Using a right-handed coordinate system, all angles in radian.
%   RotX( theta )
%   RotY( tehta )
%   RotZ( theta )
%   RotA( a, theta ) a is any 3-vector - the axis of rotation
% The matrix corresponding to a left-sided cross product
%    Xprd(x)
% is such that Xprd(x)*y == cross(x,y)
%
% Third order tensor
%   tensor_apply( T, x )
% implements T_{ij}x_{i}x_{j}
%   tensor_map( T, x,y )
% implements T_{ij}x_{j}y_{i}