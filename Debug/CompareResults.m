% Verification and Comparison Script
% @authors: Clémence-Philomène Hinot; John Hoarau; ChatGPT; Gemini
% @date: 27/11/2025

clear all; close all; clc;

% --- 1. Define Problem Parameters (Same as C++ code) ---
Tin = 38.0;       % Initial Temperature (deg C)
Tsur = 149.0;     % Surface Temperature (deg C)
D = 93.0;         % Diffusivity (cm^2/hr)
L = 31.0;         % Thickness (cm)
dx = 0.05;        % Spatial step (cm)
dt = 0.01;        % Time step (hr)
tMax = 0.5;       % Max time (hr)

% Number of terms in the series solution
N_terms = 100; 

% Create spatial grid and time points for MATLAB calculation
x_matlab = 0:dx:L;
t_matlab = 0:dt:tMax;

% Initialize MATLAB analytical solution matrix
T_analytical_matlab = zeros(length(x_matlab), length(t_matlab));

% --- 2. Calculate Analytical Solution in MATLAB ---
% Using the formula:
% T(x,t) = Tsur + 2*(Tin - Tsur) * Sum [ exp(-D * (m*pi/L)^2 * t) * ((1 - (-1)^m)/(m*pi)) * sin(m*pi*x/L) ]

fprintf('Calculating Analytical Solution in MATLAB...\n');

for j = 1:length(t_matlab)
    current_time = t_matlab(j);
    for i = 1:length(x_matlab)
        current_x = x_matlab(i);
        
        sumTerm = 0.0;
        for m = 1:N_terms
            lambda_m = (m * pi) / L;
            term = exp(-D * lambda_m^2 * current_time) * ...
                   ((1 - (-1)^m) / (m * pi)) * ...
                   sin(lambda_m * current_x);
            sumTerm = sumTerm + term;
        end
        
        T_analytical_matlab(i, j) = Tsur + 2 * (Tin - Tsur) * sumTerm;
    end
end

% Handle initial condition explicitly (t=0) to avoid Gibbs phenomenon ringing at boundaries if desired
% (The loop above handles t=0 correctly as sumTerm becomes sum of sin series approximating step function)
T_analytical_matlab(:, 1) = Tin;
T_analytical_matlab(1, :) = Tsur;
T_analytical_matlab(end, :) = Tsur;


% --- 3. Read C++ Generated CSV Files ---
% Helper function to read your specific CSV format
function [data, header] = read_cpp_csv(filename)
    opts = detectImportOptions(filename);
    opts.VariableNamingRule = 'preserve'; % Keep column names as is
    data = readtable(filename, opts);
    header = data.Properties.VariableNames;
end

% Load the files
files = {'AnalyticSolution.csv', 'Laasonen.csv', 'CrankNicholson.csv', 'DufortFrankel.csv', 'Richardson.csv'};
scheme_names = {'Analytic (C++)', 'Laasonen', 'Crank-Nicholson', 'DuFort-Frankel', 'Richardson'};
colors = {'k--', 'b-', 'r-', 'g-', 'm-'}; % Line styles

% Initialize a struct to hold the data
cpp_results = struct();

fprintf('Reading C++ CSV files...\n');
for k = 1:length(files)
    filename = files{k};
    if exist(filename, 'file')
        [cpp_results.(sprintf('scheme_%d', k)), ~] = read_cpp_csv(filename);
        fprintf('Loaded %s\n', filename);
    else
        fprintf('Warning: File %s not found.\n', filename);
    end
end


% --- 4. Plotting and Comparison ---

% Define specific times to compare (must match columns in your CSV roughly)
% Your CSV headers are likely: "x(cm)", "T(t=0)", "T(t=0.1)", "T(t=0.2)", etc.
plot_times = [0.1, 0.3, 0.5]; 
col_indices_approx = [3, 5, 7]; % Based on: 1=x, 2=t0, 3=t0.1, 4=t0.15?, 5=t0.2... CHECK YOUR CSV HEADERS

% Note: Adjust col_indices_approx based on your actual CSV column structure.
% Assuming standard output from your Output.cpp:
% Col 1: x
% Col 2: t=0
% Col 3: t=0.1
% Col 4: t=0.2
% Col 5: t=0.3
% Col 6: t=0.4
% Col 7: t=0.5

% Create a figure for each time step
for pt_idx = 1:length(plot_times)
    target_time = plot_times(pt_idx);
    
    % Find corresponding index in MATLAB time vector
    [~, t_idx_matlab] = min(abs(t_matlab - target_time));
    
    figure('Name', sprintf('Temperature Profile at t = %.2f hr', target_time), 'NumberTitle', 'off');
    hold on;
    box on; grid on;
    
    % 1. Plot MATLAB Analytical Solution (Ground Truth)
    plot(x_matlab, T_analytical_matlab(:, t_idx_matlab), 'k-', 'LineWidth', 2, 'DisplayName', 'MATLAB Analytic');
    
    % 2. Plot C++ Results
    for k = 1:length(files)
        scheme_key = sprintf('scheme_%d', k);
        if isfield(cpp_results, scheme_key)
            data_table = cpp_results.(scheme_key);
            
            % Extract X (assuming 1st column)
            x_cpp = data_table{:, 1}; 
            
            % Extract Temperature for this time step
            % We look for a column name containing the time, e.g., "T(t=0.1)"
            % This is more robust than hardcoding indices
            col_name_pattern = sprintf('T(t=%.1g)', target_time); % Simple pattern matching
            
            % Try to find the column
            found_col = false;
            col_names = data_table.Properties.VariableNames;
            for c = 2:length(col_names)
                if contains(col_names{c}, sprintf('%.1g', target_time)) || contains(col_names{c}, sprintf('%.2g', target_time))
                     T_cpp = data_table{:, c};
                     plot(x_cpp, T_cpp, colors{k}, 'LineWidth', 1.5, 'DisplayName', scheme_names{k});
                     found_col = true;
                     break;
                end
            end
            
            if ~found_col
                 % Fallback to hardcoded indices if naming fails
                 % Assuming columns match plot_times: 0.1 -> col 3, 0.3 -> col 5, 0.5 -> col 7
                 csv_col_idx = 0;
                 if target_time == 0.1; csv_col_idx = 3; end
                 if target_time == 0.3; csv_col_idx = 5; end
                 if target_time == 0.5; csv_col_idx = 7; end
                 
                 if csv_col_idx > 0 && csv_col_idx <= width(data_table)
                    T_cpp = data_table{:, csv_col_idx};
                    plot(x_cpp, T_cpp, colors{k}, 'LineWidth', 1.5, 'DisplayName', [scheme_names{k} ' (Idx)']);
                 end
            end
        end
    end
    
    title(sprintf('Temperature Distribution at t = %.2f hr', target_time));
    xlabel('Position x (cm)');
    ylabel('Temperature T (°C)');
    legend('Location', 'best');
    ylim([30 160]); % Set limits based on boundary conditions
    hold off;
end

% --- 5. Error Norm Calculation (Optional) ---
% Compare C++ Analytical to MATLAB Analytical to verify implementation
if isfield(cpp_results, 'scheme_1') % AnalyticSolution.csv
    data_cpp = cpp_results.scheme_1;
    % Get final time column
    T_cpp_final = data_cpp{:, end}; 
    x_cpp = data_cpp{:, 1};
    
    % Interpolate MATLAB solution to C++ grid points (if they differ, though they shouldn't)
    T_matlab_interp = interp1(x_matlab, T_analytical_matlab(:, end), x_cpp);
    
    error_L2 = sqrt(sum((T_cpp_final - T_matlab_interp).^2) * dx);
    fprintf('\nVerification:\n');
    fprintf('L2 Error between C++ Analytic and MATLAB Analytic at t=%.2f: %e\n', tMax, error_L2);
end