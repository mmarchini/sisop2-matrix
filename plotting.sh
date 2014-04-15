plotting_files=$(ls results);

for plot_file in $(echo $plotting_files)
do
    octave "results/$plot_file";
done
