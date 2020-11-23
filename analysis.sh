#!/bin/bash
TIMEFORMAT='%3R';
N=16


for postfix in "" _tas _tatas
do
  #########################
  # philosophers
  #########################

  echo "N,t1,t2,t3,t4,t5" > ./data/philosophers${postfix}.csv

  for i in $(seq 1 $N)
  do
    echo -n $i >> ./data/philosophers${postfix}.csv
    for k in {1..5}
    do
      VAR=$( { time ./philosophy/philosophy${postfix} -N $i; } 2>&1 )
      echo -n ","${VAR} >> ./data/philosophers${postfix}.csv
    done
    echo "">>./data/philosophers${postfix}.csv
  done

  #########################
  # producers-consumers
  #########################

  echo "N,t1,t2,t3,t4,t5" > ./data/proco${postfix}.csv

  for i in $(seq 1 $N)
  do
    echo -n $i >> ./data/proco${postfix}.csv
    P=$(($i/2))
    C=$(($i/2+$i%2))
    for k in {1..5}
    do
      VAR=$( { time ./proco/proco${postfix} -P $P -C $C; } 2>&1 )
      echo -n ","${VAR} >> ./data/proco${postfix}.csv
    done
    echo "">>./data/proco${postfix}.csv
  done


  #########################
  # readers-writers
  #########################

  echo "N,t1,t2,t3,t4,t5" > ./data/reawri${postfix}.csv

  for i in $(seq 1 $N)
  do
    echo -n $i >> reawri${postfix}.csv
    P=$(($i/2))
    C=$(($i/2+$i%2))
    for k in {1..5}
    do
      VAR=$( { time ./reawri/reawri${postfix} -W $P -R $C;} 2>&1 )
      echo -n ","${VAR} >> reawri${postfix}.csv
    done
    echo "">>./data/reawri${postfix}.csv
  done
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
