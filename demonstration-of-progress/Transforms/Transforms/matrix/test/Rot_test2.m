close all;
clear all;

basis = [ [0;0;0] eye(3) ]; % basis set
% a 3D model 
[x,y,z] = meshgrid( -1:2:1 );
p = [x(:) y(:) z(:)]'; 

figure;
hold on;
axis equal
plot3( [basis(1,1) basis(1,2)], [basis(2,1) basis(2,2)], [basis(3,1) basis(3,2)], 'r' ); % x axis
plot3( [basis(1,1) basis(1,3)], [basis(2,1) basis(2,3)], [basis(3,1) basis(3,3)], 'g' ); % y axis
plot3( [basis(1,1) basis(1,4)], [basis(2,1) basis(2,4)], [basis(3,1) basis(3,4)], 'b' ); % z axis

plot3( p(1,:), p(2,:), p(3,:), 'k+' );

ax = rand(3,1); % an axis of rotation

for r = 5:5:90
theta = r*pi/180; % angle of rotaion

R = RotA( ax, theta );
q = R*p;
plot3( q(1,:), q(2,:), q(3,:), 'k.' );
% [u,s,v] = svd( R-eye(3) );
% [norm( cross( ax,R*ax ) ) norm(cross( v(:,3), ax ))] ~= [0 0]

end

view(ax);

