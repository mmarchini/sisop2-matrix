bin_path="../../../bin";
results_path="../../../results";

executions=$(python -c "from config import Config; config = Config(sector='execute'); print config.get('executions')")
threads=$(python -c "from config import Config; config = Config(sector='execute'); print ' '.join(map(str, config.get('threads')))")

cd tests;

for profile in $(ls)
do
    cd $profile;
    for test_case in $(ls)
    do
        cd $test_case;
        for test_type in process pthread
        do
            test_excecutable="$bin_path/$test_type";
            for n in $(echo $threads) 
            do
                for i in $(seq $executions)
                do
                    echo "$test_excecutable $profile $test_case $n $i";
                    $test_excecutable $n;
                    mv out.txt "out-$test_type-$n-$i.txt";
                    mv profiling.log "profiling-$test_type-$n-$i.log";
                    #sleep 0.5s;
                done
            done
        done
        cd ..;
    done
    cd ..;
done

#cd profile_1_1;
#cd "00";
#
#$pthread > "$results_path/profile_1_1_00";

