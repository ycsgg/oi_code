filename=$1
filein=${filename}".in"
fileout=${filename}".out"
execfile=${filename}".tmpout"
g++ ${filename}".cpp" -o ${execfile}
if [ $? -eq 1 ]
then
    echo "Error"
    exit 0
fi
echo "Compiled Done..."
if [ $# -eq 2 ]
then
    para=$2
    if [ ${para} = "-d" ]
    then
        if [ -r ${filein} ]
        then
            ./${execfile} < ${filein}
            rm ${execfile}
        else
            ./${execfile}
            rm ${execfile}
        fi
    else
        ./${execfile}
        rm ${execfile}
    fi
fi
if [ $# -eq 1 ]
then
    if [ -f ${filein} ]
    then
        echo "Run in Example..."
        if [ -e ${fileout} ]
        then
            ./${execfile} < ${filein} > "tmp.out"
            diff -ZB "tmp.out" ${fileout} > /dev/null
            if [ $? -ne 0 ]
            then
                diff -ZBy "tmp.out" ${fileout}
                rm ${execfile} "tmp.out"
                exit 0
            else
                echo "Passed Example"
                rm ${execfile} "tmp.out"
            fi
        else
            ./${execfile} < ${filein}
            rm ${execfile}
        fi
    else
       ./${execfile}
       rm ${execfile}
    fi
fi