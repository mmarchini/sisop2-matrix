result_folder=$(python -c "from config import Config; config = Config(sector='plotting'); print config.get('result_folder');")

plotting_files=$(ls $result_folder);

for plot_file in $(echo $plotting_files)
do
    octave "$result_folder/$plot_file";
done

