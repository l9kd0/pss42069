#!/bin/bash
TIMEFORMAT='%3R';
N=16


for postfix in "" _tas _tatas
do

  if [ "$1" == "philosophy" ]; then
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

  fi

  if [ "$1" == "proco" ]; then
    #########################
    # producers-consumers
    #########################

    echo "N,t1,t2,t3,t4,t5" > ./data/proco${postfix}.csv

    for i in $(seq 2 $N)
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
  fi

  if [ "$1" == "reawri" ]; then
    #########################
    # readers-writers
    #########################

    echo "N,t1,t2,t3,t4,t5" > ./data/reawri${postfix}.csv

    for i in $(seq 2 $N)
    do
      echo -n $i >> ./data/reawri${postfix}.csv
      P=$(($i/2))
      C=$(($i/2+$i%2))
      for k in {1..5}
      do
        VAR=$( { time ./reawri/reawri${postfix} -W $P -R $C;} 2>&1 )
        echo -n ","${VAR} >> ./data/reawri${postfix}.csv
      done
      echo "">>./data/reawri${postfix}.csv
    done
  fi
done


  if [ "$1" == "tas" ]; then
  #########################
  # Pizzaoilo (test-and-set)
  #########################

  echo "N,t1,t2,t3,t4,t5" > ./data/tas.csv

  for i in $(seq 1 $N)
  do
    echo -n $i >> ./data/tas.csv
    P=$(($i/2))
    for k in {1..5}
    do
      VAR=$( { time ./tas/tas -P $P ;} 2>&1 )
      echo -n ","${VAR} >> ./data/tas.csv
    done
    echo "">>./data/tas.csv
  done
  fi

  if [ "$1" == "tatas" ]; then
  #########################
  # Hamburgers (test-and-test-and-set)
  #########################

  echo "N,t1,t2,t3,t4,t5" > ./data/tatas.csv

  for i in $(seq 1 $N)
  do
    echo -n $i >> ./data/tatas.csv
    P=$(($i/2))
    for k in {1..5}
    do
      VAR=$( { time ./tatas/tatas -P $P ;} 2>&1 )
      echo -n ","${VAR} >> ./data/tatas.csv
    done
    echo "">>./data/tatas.csv
  done
  fi
