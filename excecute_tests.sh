process="../../../bin/process";
results_path="../../../results";

cd tests;

for profile in $(ls)
do
    cd $profile;
    for test_case in $(ls)
    do
        cd $test_case;
        echo "pthread $profile $test_case";
        $process 6;
        cd ..;
    done
    cd ..;
done

#cd profile_1_1;
#cd "00";
#
#$pthread > "$results_path/profile_1_1_00";

