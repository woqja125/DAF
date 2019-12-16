#!/bin/bash

#compile our program (name : $1)
g++ -o program $1.cpp -std=c++11

#compute linear orders for $2 query graphs
echo -ne 'computing linear orders for $2 query graphs...'
./program yeast yeast_400n $2 > yeast_400n.dag
echo 'done'

#run daf using the computed DAGs
echo -ne 'running DAF using the computed DAGs...'
./daf_2min -d yeast -q yeast_400n -a yeast_400n.dag -n $2 -m 100000 > result_dag
echo 'done'

#output result
echo '*output result*'
python sort_result.py result_dag result_dag
