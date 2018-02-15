function H = homography_est( x1,x2 )


d = size(x1,1); % dimension of datum
n = size(x2,2); % number of datum

D = zeros(n*(d-1),d^2);
j = 0;
for i = 1:n
    x = x1(:,i)';
    y = -x2(:,i);
    for i = 1:(d-1)
        j = j+1;
        D(j,:) = [zeros( 1,d*(i-1) ) x zeros(1,d*(d-i-1)) y(i)*x ];
    end
end

[U,S,V] = svd(D);
H = reshape(V(:,end),d,d)';

return;