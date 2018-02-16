clear variables;
close all;

rand_factor =0;
face_rotation_rand = 0.01 * rand_factor;
face_translation_rand = 0.1 * rand_factor;
screen_rotation_rand = 0.01 * rand_factor;
screen_translation_rand = 0.1 * rand_factor;

%%
world = eye(3);

%%
%eyep = [1;5;1]+randn(3,1); % eye position is measured in 2D
eyep = 2*randn(2,1);
%eyep = [3;3];
%eyep(3,:) = 3; % assign any depth value, we'll calculate it later

%%
face = [ 0 0 0;
         1 0 0;
         1 1 0;
         0 1 0 ]'; % a plane
R = RotA( [1;0;0]+face_rotation_rand*randn(3,1), 0.5*pi + face_rotation_rand*pi*rand,1  ); % rotation of face in world
T = [1;5;1]+face_translation_rand*randn(3,1); % translation of face in world
M = R;
M(1:3,4) = T; % combined rotation and translation
face(4,:) = 1; % need homogeneous coordinates for it to work !

face = M*face; % do the transform
face = face(1:3,:); % pick out the new face coordinates

midface = mean(face,2); % the eye is in the middle
%x = face - eye; % work out gaze direction
% calculate normal to the face passing through the eye
a = face(:,1) - midface;
b = face(:,2) - midface;
x = cross(a,b);
[U,S,V] = svd(x); % singular value decomposition puts a reference frame onto face
gaze = U(:,3); % gaze is the so-called 'null' vector - out of the plane


% for points IN face-space the projection onto the face plane is assumed to
% be orthogonal
P = [1 0 0;0 1 0];
%P = [0 1 0;0 0 1];

%% calculate eye depth based on known coordinates and face plane
x = x ./ norm(x); % turn x into a unit vector
%eyep = eyep - (dot(x, (eyep - midface))) * x; % move eyep into the face plane

%% screen is treated like the face
screen = [ 0 0 0;
           1 0 0;
           1 1 0;
           0 1 0 ]';
screen(3,:) = 0;

R2 = RotA( [1;0;0]+screen_rotation_rand*randn(3,1), 1.5*pi + screen_rotation_rand*pi*rand,1  ); % rotation of face in world
T2 = [1;1;2]+screen_translation_rand*randn(3,1); % translation of face in world
M2 = R2;
M2(1:3,4) = T2; % combined rotation and translation
screen(4,:) = 1; % need homogeneous coordinates for it to work !

screen = M2*screen;
screen = screen(1:3,:);

mscr = mean(screen,2); % middle of screen
%x = screen - mscr; % work our gaze direction
a = screen(:,1) - mscr;
b = screen(:,2) - mscr;
x2 = cross(a,b);
[U2,S2,V2] = svd(x2); % singular value decomposition puts a reference frame onto face
nscr = U2(:,3); %  'null' vector - out of the screen plane

%% Map a point in the screen into the face coordinates, via the world

numpoints = 10; % number of points to generate the homography from
xscr = repmat(mscr, 1, numpoints)+0.3*randn(3,numpoints); % a point on the screen
%xscr = randn(3,numpoints); % a point on the screen
xscr(2,:) = 1; % zero because its in the plane



%xwrld = (U2*xscr) + repmat(mscr,1,numpoints) % could be a single matrix !
%xfce = P*U'*(xwrld - repmat(midface,1,numpoints)) % map into face coordinates, could be one matrix !
%xfce = P*U'*(xwrld - repmat(midface,1,numpoints)) % map into face coordinates, could be one matrix !




xscr(4,:) = 1; % need homogeneous coordinates for it to work !
mscr(4,:) = 1; % need homogeneous coordinates for it to work !
xwrld(4,:) = 1; % need homogeneous coordinates for it to work !
%M2
%xwrld = (M2'*xscr) + repmat(mscr,1,numpoints); % could be a single matrix !
%xwrld = (M2*xscr)
xwrld = M2*(xscr - repmat(mscr,1,numpoints)); % could be a single matrix !

midface(4,:) = 1; % need homogeneous coordinates for it to work !
xwrld(4,:) = 1; % need homogeneous coordinates for it to work !
%xfce = P*U'*(xwrld - repmat(midface,1,numpoints)) % map into face coordinates, could be one matrix !
%xfce = M*(xwrld - repmat(midface,1,numpoints)); % map into face coordinates, could be one matrix !
%xfce = (M*xwrld) - repmat(midface,1,numpoints); % map into face coordinates, could be one matrix !
M
xfce = (M*xwrld) + repmat(midface,1,numpoints);
%xfce = M*(xwrld + repmat(midface,1,numpoints));

%xwrld(1:2,:)
%xwrld(3,:)

xfce = bsxfun(@rdivide, xfce(1:3,:), xfce(4,:)); % make face coords nonhomogeneous again
xscr = bsxfun(@rdivide, xscr(1:3,:), xscr(4,:)); % make face coords nonhomogeneous again
midface = midface(1:3,:);
mscr = mscr(1:3,:);


for i = 1:numpoints
    xfce(:,i) = xfce(:,i) - (dot(x, (xfce(:,i) - midface))) * x; % move them into the face plane
    xscr(:,i) = xscr(:,i) - (dot(x2, (xscr(:,i) - mscr))) * x2; % move them into the screen plane
end
    
%xfce = xfce - (dot(x, (xfce - repmat(midface,1,numpoints)))) * x; % move them into the face plane
%xscr = xscr - (dot(x2, (xscr - repmat(mscr,1,numpoints)))) * x2; % move them into the screen plane

%% the points xfce and xscr must be related by a homography because the
% mapping is from one plane to another. Here is a sanity check

%xscr(3,:) = 1
%xfce(3,:) = 1
%H = homography_est( xscr, xfce )
%xfce = xfce([1,3],:)
%xscr = xscr([1,3],:)
H = homography_solve( xfce([1,3],:), xscr([1,3],:) )

% z = H*xscr;
% z_nh = bsxfun(@rdivide, z(1:2,:), z(3,:));
% d = z_nh - xfce(1:2,:);
% max(abs(d(:)));

%%

eyep(3,:) = 1;
screenp = H*eyep
eyep = eyep(1:2,:);
%x2 = x2 ./ norm(x2); % turn x into a unit vector
screenp = bsxfun(@rdivide, screenp(1:2,:), screenp(3,:))
%screenp = screenp - (dot(x2, (screenp - mscr))) * x2 % move eyep into the screen plane

%%


figure
hold on;

quiver3( 0,0,0,world(1,1),world(2,1),world(3,1),0,'b' );
quiver3( 0,0,0,world(1,2),world(2,2),world(3,2),0,'b' );
quiver3( 0,0,0,world(1,3),world(2,3),world(3,3),0,'b' );

shape = [face face(:,1)];
plot3( shape(1,:), shape(2,:), shape(3,:), 'k' );
quiver3( midface(1),midface(2),midface(3), U(1,1),U(2,1),U(3,1),'k' );
quiver3( midface(1),midface(2),midface(3), U(1,2),U(2,2),U(3,2),'k--' );
quiver3( midface(1),midface(2),midface(3), gaze(1),gaze(2),gaze(3),'k--' );


shape = [screen screen(:,1)];
plot3( shape(1,:), shape(2,:), shape(3,:), 'r' );
quiver3( mscr(1),mscr(2),mscr(3), U2(1,1),U2(2,1),U2(3,1),'r' );
quiver3( mscr(1),mscr(2),mscr(3), U2(1,2),U2(2,2),U2(3,2),'r--' );
quiver3( mscr(1),mscr(2),mscr(3), nscr(1),nscr(2),nscr(3),'r--' );




%xscr([1,2,3],:) = xscr([1,3,2],:) TODO use RotA instead?
%xscr(4,:) = 1;
%xfce(4,:) = 1;
%xscr = M2*xscr
%xfce = M*xfce;
%xfce([1,2,3],:) = xfce([1,3,2],:)
plot3( xscr(1,:), xscr(2,:), xscr(3,:), 'g*' );
plot3( xfce(1,:), xfce(2,:), xfce(3,:), 'go' );
%plot3( xwrld(1,:), xwrld(2,:), xwrld(3,:), 'b*' );

x3 = U(:,1)*xfce(1,:) + U(:,2)*xfce(2,:);
%x = U(:,1)*xfce(1,:) + U(:,2)*xfce(2,:) + eye;
%plot3( x(1),x(2),x(3), 'go' );

for i = 1:size(xwrld,2)
    y = [xfce(:,i), xscr(:,i)];
    
    %y = [x3(:,i) xwrld(1:3,i)];
    plot3( y(1,:),y(2,:),y(3,:), 'g' ); % should be parallel to gaze direction
end

view( U(:,1) );
axis equal off

figure
hold on;
axis equal
axis([-10 10 -10 10]);

plot(0, 0, 'k+');
plot(eyep(1),eyep(2),'k.');
plot(screenp(1),screenp(2),'r.');


