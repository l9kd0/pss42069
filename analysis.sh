#!/bin/bash
TIMEFORMAT='%3R';
N=16

#########################
# philosophers
#########################

echo "N,t1,t2,t3,t4,t5" > philosophers.csv

for i in $(seq 1 $N)
do
  echo -n $i >> philosophers.csv
  for k in {1..5}
  do
    VAR=$( { time ./philosophy/philosophy -N $i; } 2>&1 )
    echo -n ","${VAR} >> philosophers.csv
  done
  echo "">>philosophers.csv
done

#########################
# producers-consumers
#########################

echo "N,t1,t2,t3,t4,t5" > proco.csv

for i in $(seq 1 $N)
do
  echo -n $i >> proco.csv
  P=$(($i/2))
  C=$(($i/2+$i%2))
  for k in {1..5}
  do
    VAR=$( { time ./proco/proco -P $P -C $C; } 2>&1 )
    echo -n ","${VAR} >> proco.csv
  done
  echo "">>proco.csv
done


#########################
# readers-writers
#########################

echo "N,t1,t2,t3,t4,t5" > reawri.csv

for i in $(seq 1 $N)
do
  echo -n $i >> reawri.csv
  P=$(($i/2))
  C=$(($i/2+$i%2))
  for k in {1..5}
  do
    VAR=$( { time ./reawri/reawri -W $P -R $C;} 2>&1 )
    echo -n ","${VAR} >> reawri.csv
  done
  echo "">>reawri.csv
done

#########################
# Pizzaoilo (test-and-set)
#########################

echo "N,t1,t2,t3,t4,t5" > testandset.csv

for i in $(seq 1 $N)
do
  echo -n $i >> testandset.csv
  P=$(($i/2))
  for k in {1..5}
  do
    VAR=$( { time ./testandset/testandset -P $P } 2>&1 )
    echo -n ","${VAR} >> testandset.csv
  done
  echo "">>testandset.csv
done

#########################
# Hamburgers (test-and-test-and-set)
#########################

echo "N,t1,t2,t3,t4,t5" > tatas.csv

for i in $(seq 1 $N)
do
  echo -n $i >> tatas.csv
  P=$(($i/2))
  for k in {1..5}
  do
    VAR=$( { time ./tatas/tatas -P $P } 2>&1 )
    echo -n ","${VAR} >> tatas.csv
  done
  echo "">>tatas.csv
done
