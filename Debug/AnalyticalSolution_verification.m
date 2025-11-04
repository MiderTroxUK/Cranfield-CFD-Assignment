% Verification of the algorithm for the analytical solution
% @authors: Clémence-Philomène Hinot; ChatGPT
% @date: 21/10/2025

% Latex equation:
% T = T_{\text{sur}} + 2 (T_{\text{in}} - T_{\text{sur}}) 
%       \sum_{m=1}^{\infty} 
%       e^{-D\left(\frac{m\pi}{L}\right)^2 t} 
%       \frac{1 - (-1)^m}{m\pi} 
%       \sin\left(\frac{m\pi x}{L}\right)

% Parameters
Tin = 38;
Tsur = 149;
D = 155e-6;
L = 0.31;
N = 100;
x = 0:0.05:0.31;
t = 0:0.01:0.1;

% stability check
CFL = D * 0.01/0.05;
fprintf("CFL = %d\n", CFL);

% initialisation
term = 0.0;
T = zeros(length(x), length(t));

% algorithm
for j = 1:length(t)
    for i = 1:length(x)
        sumTerm = 0.0;
        for m = 1:N
            term = exp(-D*(m*pi/L)^2 * t(j)) * ...
                   (1 - (-1)^m)/(m*pi) * ...
                   sin(m*pi*x(i)/L);
            sumTerm = sumTerm + term;
        end
        T(i,j) = Tsur + 2*(Tin - Tsur) * sumTerm;
    end
end

% print the results
fprintf('\n%-8s %-8s %-12s\n', 'x (m)', 't (s)', 'T (°C)');
fprintf('-------------------------------------\n');
for j = 1:length(t)
    for i = 1:length(x)
        fprintf('%-8.2f %-8.2f %-12.4f\n', x(i), t(j), T(i,j));
    end
end