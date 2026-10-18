% COMPSYS 303 Version B - report figures from phases.csv and dwell.csv
% (written by ../export_figure_data.py from the raw board logs).
%
% Run from this folder:   matlab -batch "make_figures"
% Writes a_measured_vs_intended.png, b_phase_error.png, c_ticks_per_event.png,
% d_camera_dwell.png. Figure (e) (Version A vs B) needs Version A traces, which
% are not in the repository yet.
%
% AI Use Declaration: The design and all design decisions were made by Harold and Lucas.
% This plotting script was written with the assistance of a generative AI tool (Claude,
% Anthropic), then reviewed, tested and verified by Harold and Lucas.

here = fileparts(mfilename('fullpath'));
P = readtable(fullfile(here, 'phases.csv'), 'TextType', 'string');
D = readtable(fullfile(here, 'dwell.csv'), 'TextType', 'string', 'VariableNamingRule', 'preserve');
exps = unique(P.experiment, 'stable');
phaseNames = unique(P.phase, 'stable');
markers = {'o', 's', 'd', '^', 'v'};

%% (a) measured vs intended phase duration, every experiment
f = figure('Visible', 'off', 'Position', [100 100 760 560]);
theme(f, 'light');
hold on; grid on; box on;
lim = [0 13000];
plot(lim, lim, 'k--', 'DisplayName', 'measured = intended');
for k = 1:numel(exps)
    r = P.experiment == exps(k);
    errorbar(P.intended_ms(r), P.mean_ms(r), P.mean_ms(r) - P.min_ms(r), P.max_ms(r) - P.mean_ms(r), ...
        markers{k}, 'MarkerSize', 7, 'LineWidth', 1.1, 'DisplayName', exps(k));
end
xlim(lim); ylim(lim);
xlabel('Intended phase duration (ms)');
ylabel('Measured phase duration on the DE2-115 (ms)');
title('(a) Measured vs intended phase duration (mean, bars = min..max)');
legend('Location', 'northwest');
exportgraphics(f, fullfile(here, 'a_measured_vs_intended.png'), 'Resolution', 200);
close(f);

%% (b) phase error per phase at 1 / 10 / 100 / 300 ms
rates = ["E2a 1 ms", "E2b 10 ms", "E2c 100 ms", "E3 300 ms"];
E = zeros(numel(phaseNames), numel(rates)); Lo = E; Hi = E;
for k = 1:numel(rates)
    for p = 1:numel(phaseNames)
        r = P.experiment == rates(k) & P.phase == phaseNames(p);
        E(p, k) = P.mean_error_ms(r);
        Lo(p, k) = P.mean_ms(r) - P.min_ms(r);
        Hi(p, k) = P.max_ms(r) - P.mean_ms(r);
    end
end
f = figure('Visible', 'off', 'Position', [100 100 900 520]);
theme(f, 'light');
b = bar(E, 'grouped'); hold on; grid on; box on;
for k = 1:numel(rates)
    x = b(k).XEndPoints;
    errorbar(x, E(:, k), Lo(:, k), Hi(:, k), 'k.', 'HandleVisibility', 'off');
end
set(gca, 'XTickLabel', phaseNames, 'XTickLabelRotation', 20);
ylabel('Measured - intended (ms)');
xlabel('Phase');
title('(b) Phase timing error by timer period (mean, bars = min..max)');
legend(rates, 'Location', 'southoutside', 'Orientation', 'horizontal');
exportgraphics(f, fullfile(here, 'b_phase_error.png'), 'Resolution', 200);
close(f);

%% (c) ticks per timer event and share of ticks without a timer event
tpe = zeros(numel(exps), 1); idle = tpe;
for k = 1:numel(exps)
    r = P.experiment == exps(k);
    tpe(k) = sum(P.mean_ticks(r) .* P.n(r)) / sum(P.mean_events(r) .* P.n(r));
    idle(k) = 100 * (1 - 1 / tpe(k));
end
f = figure('Visible', 'off', 'Position', [100 100 900 420]);
theme(f, 'light');
subplot(1, 2, 1);
bar(categorical(exps, exps), tpe); set(gca, 'YScale', 'log'); grid on;
ylabel('Ticks per timer event (log scale)'); xlabel('Experiment');
title('(c) Reactions per timer event');
text(1:numel(exps), tpe * 1.15, compose('%.1f', tpe), 'HorizontalAlignment', 'center');
subplot(1, 2, 2);
bar(categorical(exps, exps), idle); grid on; ylim([0 112]);
ylabel('Ticks without a timer event (%)'); xlabel('Experiment');
title('Ticks with no timer event');
text(1:numel(exps), idle + 3, compose('%.1f %%', idle), 'HorizontalAlignment', 'center');
exportgraphics(f, fullfile(here, 'c_ticks_per_event.png'), 'Resolution', 200);
close(f);

%% (d) E6 camera dwell at 100 ms
cases = unique(D.("case"), 'stable');
f = figure('Visible', 'off', 'Position', [100 100 640 480]);
theme(f, 'light');
hold on; grid on; box on;
patch([0.5 2.5 2.5 0.5], [900 900 1000 1000], [0.85 0.93 1.0], 'EdgeColor', 'none', ...
    'DisplayName', 'expected band for entry during yellow (900-1000 ms)');
for k = 1:numel(cases)
    y = D.dwell_ms(D.("case") == cases(k));
    plot(k + 0.06 * ((1:numel(y)) - mean(1:numel(y))), y, markers{k}, 'MarkerSize', 9, 'LineWidth', 1.5, ...
        'DisplayName', sprintf('%s (n = %d)', cases(k), numel(y)));
end
yline(1000, 'k--', 'chart dwell 10 events = 1000 ms', 'HandleVisibility', 'off');
xlim([0.5 2.5]); ylim([880 1020]);
set(gca, 'XTick', 1:numel(cases), 'XTickLabel', cases);
ylabel('Measured camera dwell (ms)'); xlabel('E6 case (TIMER\_MS = TIMER\_PERIOD\_MS = 100)');
title('(d) Camera dwell: armed at yellow start vs entered during yellow');
legend('Location', 'southoutside');
exportgraphics(f, fullfile(here, 'd_camera_dwell.png'), 'Resolution', 200);
close(f);

disp('figures written');
