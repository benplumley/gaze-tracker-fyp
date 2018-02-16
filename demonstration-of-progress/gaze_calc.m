function retmat = gaze_calc(head_x, head_y, head_z, head_roll, head_pitch, head_yaw, left_eye_x, left_eye_y, right_eye_x, right_eye_y)

world = eye(3);

%%
lefteyep = [left_eye_x;left_eye_y];
righteyep = [right_eye_x;right_eye_y];

%%
face = [ 0 0 0 0;
         1 0 0 0;
         1 1 0 0;
         0 1 0 0 ]'; % a plane
%R = RotA( [1;0;0]+face_rotation_rand*randn(3,1), 0.5*pi + face_rotation_rand*pi*rand,1  ); % rotation of face in world
head_roll = deg2rad(head_roll);
head_pitch = deg2rad(head_pitch);
head_yaw = deg2rad(head_yaw);
R = zeros(4);
R = RotX(head_roll) * RotY(head_pitch) * RotZ(head_yaw);
R(4, 4) = 1;
%R = eul2rotm(head_roll, head_pitch, head_yaw); % convert rotation angles to direction cosine matrix

%T = [1;5;1]+face_translation_rand*randn(3,1); % translation of face in world
T = [head_x; head_y; head_z];
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
%[U,S,V] = svd(x); % singular value decomposition puts a reference frame onto face
%gaze = U(:,3); % gaze is the so-called 'null' vector - out of the plane


% for points IN face-space the projection onto the face plane is assumed to
% be orthogonal
%P = [1 0 0;0 1 0];
%P = [0 1 0;0 0 1];

%% calculate eye depth based on known coordinates and face plane
x = x ./ norm(x); % turn x into a unit vector
%eyep = eyep - (dot(x, (eyep - midface))) * x; % move eyep into the face plane

%% screen is treated like the face
screen = [ 0 0 0 0;
           1 0 0 0;
           1 1 0 0;
           0 1 0 0 ]';
screen(3,:) = 0;

%R2 = RotA( [1;0;0]+screen_rotation_rand*randn(3,1), 1.5*pi + screen_rotation_rand*pi*rand,1  ); % rotation of face in world
%T2 = [1;1;2]+screen_translation_rand*randn(3,1); % translation of face in world
R2 = eye(3);
T2 = [0;0;0];
M2 = zeros(4);
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
%[U2,S2,V2] = svd(x2); % singular value decomposition puts a reference frame onto face
%nscr = U2(:,3); %  'null' vector - out of the screen plane

%% Map a point in the screen into the face coordinates, via the world

numpoints = 4; % number of points to generate the homography from
%xscr = repmat(mscr, 1, numpoints)+0.3*randn(3,numpoints); % a point on the screen
xscr = [ 0 0 0;
           1 0 0;
           1 1 0;
           0 1 0 ]';
%xscr = randn(3,numpoints); % a point on the screen
xscr(2,:) = 1; % zero because its in the plane



%xwrld = (U2*xscr) + repmat(mscr,1,numpoints) % could be a single matrix !
%xfce = P*U'*(xwrld - repmat(midface,1,numpoints)) % map into face coordinates, could be one matrix !
%xfce = P*U'*(xwrld - repmat(midface,1,numpoints)) % map into face coordinates, could be one matrix !




%xscr(4,:) = 1 % need homogeneous coordinates for it to work !
xscr_h = [xscr; ones(1, numpoints)]; % create homogeneous version
mscr_h = [mscr; 1]; % create homogeneous version
%mscr(4,:) = 1; % need homogeneous coordinates for it to work !
%xwrld(4,:) = 1; % need homogeneous coordinates for it to work !
%M2
%xwrld = (M2'*xscr) + repmat(mscr,1,numpoints); % could be a single matrix !
%xwrld = (M2*xscr)
xwrld = M2*(xscr_h - repmat(mscr_h,1,numpoints)); % could be a single matrix !

%midface(4,:) = 1; % need homogeneous coordinates for it to work !
midface_h = [midface; 1]; % create homogeneous version
xwrld(4,:) = 1; % need homogeneous coordinates for it to work !
%xfce = P*U'*(xwrld - repmat(midface,1,numpoints)) % map into face coordinates, could be one matrix !
%xfce = M*(xwrld - repmat(midface,1,numpoints)); % map into face coordinates, could be one matrix !
%xfce = (M*xwrld) - repmat(midface,1,numpoints); % map into face coordinates, could be one matrix !
xfce = (M*xwrld) + repmat(midface_h,1,numpoints);
%xfce = M*(xwrld + repmat(midface,1,numpoints));

%xwrld(1:2,:)
%xwrld(3,:)

xfce = bsxfun(@rdivide, xfce(1:3,:), xfce(4,:)); % make face coords nonhomogeneous again
%xscr = bsxfun(@rdivide, xscr(1:3,:), xscr(4,:)); % make face coords nonhomogeneous again
midface = midface(1:3,:);
%mscr = mscr(1:3,:);


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
H = homography_solve( xfce([1,3],:), xscr([1,3],:) );

% z = H*xscr;
% z_nh = bsxfun(@rdivide, z(1:2,:), z(3,:));
% d = z_nh - xfce(1:2,:);
% max(abs(d(:)));

%%

lefteyep_h = [lefteyep; 1];
righteyep_h = [righteyep; 1];
leftscreenp = H*lefteyep_h;
rightscreenp = H*righteyep_h;
%lefteyep = lefteyep(1:2,:);
%righteyep = righteyep(1:2,:);
%x2 = x2 ./ norm(x2); % turn x into a unit vector
leftscreenp = bsxfun(@rdivide, leftscreenp(1:2,:), leftscreenp(3,:));
rightscreenp = bsxfun(@rdivide, rightscreenp(1:2,:), rightscreenp(3,:));
retmat = [leftscreenp'; rightscreenp'];
return;













