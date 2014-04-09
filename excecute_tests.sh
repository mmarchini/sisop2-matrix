pthread="../../../bin/pthread";
results_path="../../../results";

mkdir -p results;

cd tests;

for profile in $(ls)
do
    cd $profile;
    for test_case in $(ls)
    do
        cd $test_case;
        echo "pthread $profile $test_case";
        $pthread  > "$results_path/$profile.$test_case.pthread.log";
        cd ..;
    done
    cd ..;
done

#cd profile_1_1;
#cd "00";
#
#$pthread > "$results_path/profile_1_1_00";

