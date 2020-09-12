function [x k]=EqtsSOR(A,b,x0,omiga,eps)
%超松弛（SOR,Successive Over-Relaxation）迭代法求解线性方程组Ax=b
%[x k]=EqtsSOR(A,b,x0,eps)
%x:解向量，列向量
%k:迭代次数
%A:系数矩阵
%b:列向量
%x0:迭代初始值，列向量
%omiga:松弛因子，可缺省，缺省值为1，即为GS迭代法
%eps:误差限，可缺省，缺省值为0.5e-6
%
%应用举例:
%A=[4 3 0;3 4 -1;0 -1 4];b=[24;30;-24];x0=[1;1;1];omiga=1.25;
%[x k]=EqtsSOR(A,b,x0,omiga,0.5e-6)
%x=EqtsSOR(A,b,x0)

if nargin==4
eps=0.5e-6;
end
if nargin==3
omiga=1;
eps=0.5e-6;
end

%检查输入参数
n=length(b);
if size(A,1) ~= n || n ~= length(x0)
disp('输入参数有误！');
x=' ';
k=' ';
return;
end

%迭代求解
k=0;
x=zeros(n,1);
while 1
k=k+1;
for i=1:n
z=0;
for j=1:i-1
z=z+A(i,j)*x(j);
end
for j=i+1:n
z=z+A(i,j)*x0(j);
end
x(i)=(1-omiga)*x0(i)+omiga*(b(i)-z)/A(i,i);
end
if norm(x-x0)<=eps || k==30
break;
end
x0=x;
end

if k==30
disp('迭代次数太多！')
x=' ';
end

return; 