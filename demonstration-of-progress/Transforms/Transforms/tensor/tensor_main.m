clear all;
close all;
drawnow;

% http://en.wikipedia.org/wiki/Tensor#Early_history
% http://en.wikipedia.org/wiki/Tensor_(intrinsic_definition)

% Tensors are mathematical (geometric) objects that include scalars,
% vectors, matrices, as well as cubes of numbers, and hyper-cubes of numbers.
% Tensors are used to describe physical situations such as the stress forces
% acting at a point. 

% More formally, suppose V is vector space that has as field f(V);
% a field can be scalar, vector, or matrix valued; or some other tensor.
% That is, a point in a tensor field index a tensor.

% Scalars are zeroth order tensors, or are 'one dimensional'; [x].
% Sectors are first order tensors, they order a tuple of scalars,
%  x_1, x_2, ..., x_n
% where n is the dimension of the vector space.
% matrices are second order tensors or 2D, (m_11,m_12;m_21,m_22]
%    matrices order a tuple of vectors
% 'cubices' are third order

% An NxNxN tensor is more than an array of matrices.

grid_header;

n = 3; % dimension of vector space
N = 3; % order of tensor
T = rand( N,N,N ); % a tensor
T = col2grid( 1:N^3, [N,N] );

x = diag( [1 2 3] );
x = [1;1;1];

for i = 1:N
    y(:,:,i) = T(:,:,i) * x;
%    v(:,i,:) = reshape( squeeze(T(:,i,:))*x, [N 1 N]);
%    u(i,:,:) = reshape( squeeze(T(i,:,:))*x, [1 N N]);
end



