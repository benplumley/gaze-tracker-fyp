function R = RotA( a, theta, opt )

% R = RotA( a, theta )
% Generate the (4x4) matrix about axis a with angle theta

if nargin == 2
    opt = 0;
end

a = a / norm(a ); % Ensure unit vector

t1 = atan2( a(3), a(1) ); % angle to x axis in zy=0 plane
t2 = atan2( a(2), sqrt(a(1)^2+a(3)^2) ); % angle to xy plane

R1 = RotY( -(pi-t1),opt ); % rotation to bring axis into y=0 plane
R2 = RotZ( -(pi-t2),opt ); % further rotation to align with x axis (so z = 0 too)

R = R1' * R2' * RotX( theta,opt ) * R2 * R1; % compute R

return;
