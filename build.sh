#!/bin/sh

run=0
force=0
debug=0
log=Bin/build.log
while getopts "rfd" option
do
        case $option in
                r) 
                        run=1
                ;;
                f) 
                        force=1
                ;;
                d)
                        debug=1
                ;;
                \?)
                        echo "Invalid"
                        exit
                ;;
        esac
done

if [ ! -e $log ];then
    if [ ! -e Bin ]; then
        mkdir Bin
    fi

    touch $log
fi

if [ $debug -eq 1 ]; then
        make --debug &> $log
else
    if [ $force -eq 1 ]; then
        make clean &> /dev/null
    fi
    make &> $log
fi

result=`tail -n1 $log`

if [ `echo $result | grep -i "success" | wc -l` -gt 0 ];then
        success=1
elif [ `echo $result | grep -i "nothing to be done" | wc -l` -gt 0 ]; then

        echo "No changes";
        # [ $run -eq 1 ] && ./out;
        success=1
else
        success=0
fi

if [ $run -eq 1 ] && [ $success -eq 1 ];then
        ./out;
fi

if [ "$success" == "0" ]; then
        echo "Build FAILED..."
        cat $log
else
        echo $result
fi
