function h = homography_estimate( x, u )

%  h = homography_estimate( x, u )
% estimate homography give source points x and target points u

if size(x,1) == 2
  x(3,:) = 1;
end
if size(u,1) == 2
  u(3,:) = 1;
end

X = [];
z = zeros(1,3);
for i = 1:length(x)
  rowx = [x(:,i)' z -u(1,i)*x(:,i)'];
  rowy = [z x(:,i)' -u(2,i)*x(:,i)'];
  X = [X; rowx; rowy];
end

[U,S,V] = svd( X );
h = reshape(V(:,end),3,3)';


return;