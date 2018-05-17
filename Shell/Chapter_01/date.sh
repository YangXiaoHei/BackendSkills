#! /bin/bash

start=`date +%s`
sleep 1
end=`date +%s`
diff=`expr $end - $start`
echo $diff
