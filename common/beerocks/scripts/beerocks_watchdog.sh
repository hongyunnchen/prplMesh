#!/bin/sh
#############################################################################
# SPDX-License-Identifier: BSD-2-Clause-Patent
# Copyright (c) 2016-2019 Intel Corporation
# This code is subject to the terms of the BSD+Patent license.
# See LICENSE file for more details.
#############################################################################

if [ -f "/opt/multiap/framework/bpl_err.sh" ] # if UGW
then
. /opt/multiap/framework/bpl_err.sh
fi

BEEROCKS_PATH=/opt/beerocks

BEEROCKS_LOG_PATH=/rdklogs/logs

BEEROCKS_TMP_PATH=/tmp/beerocks

BEEROCKS_ERROR_HANDLER=$BEEROCKS_PATH/beerocks_error_handler.sh

killall_program(){
    PROGRAM_NAME=$1
    if [ "$#" -eq 2 ]; then
        KILL_SIG=$2
    else
        KILL_SIG=$SIG_TERM
    fi
    for PID in $(ps -ef | grep $PROGRAM_NAME | grep -v grep | awk '{print $1}'); do
        echo "kill $KILL_SIG $PID $PROGRAM_NAME";
        kill $KILL_SIG $PID > /dev/null 2>&1;
    done
}

is_program_running(){
    PROGRAM_NAME=$1
    for PID in $(ps -ef | grep $PROGRAM_NAME | grep -v grep | awk '{print $1}'); do
        echo "true"
        return
    done
    echo "false"
}

PID_STUCK_RETRIES=0
PID_STUCK_RETRIES_LIMIT=15
WATCHDOG_CYCLE_SECONDS=10

# save PID of script to file
echo $$ > $BEEROCKS_TMP_PATH/pid/beerocks_watchdog

while true :
do
    sleep $WATCHDOG_CYCLE_SECONDS
    #check beerocks
    for FILE in beerocks_controller beerocks_agent; do
        BEEROCKS_FILE=$BEEROCKS_PATH/$FILE
        PID_FILE=$BEEROCKS_TMP_PATH/pid/$FILE
        if [ -f $BEEROCKS_FILE ] && [ -f $PID_FILE ]; then
            PID=`cat $PID_FILE`
            PID_ZOMBIE=`ps | grep $PID | awk '$4=="Z"{print "Z"}'`
            if [ ! -f /proc/$PID/exe ] || [ ! -z $PID_ZOMBIE ] ; then
                echo "$0: CRITICAL: $FILE PID $PID error, trigger error handler"
                $BEEROCKS_ERROR_HANDLER 0 $BPL_ERR_WATCHDOG_PROCESS_ZOMBIE
            fi
        fi
    done

    PID_SUM_COUNTER=0
    PID_RUNNING_COUNTER=0
    PID_STUCK_RETRIES_LIMIT=4
    # Check for stuck processes
    NOW_EPOCH=$(date +%s)
    PID_FILES=$(ls $BEEROCKS_TMP_PATH/pid/ | grep -e master -e slave )
    PID_STUCK=false
    
    for PID_FILE in $PID_FILES; do
        FILE_EPOCH_TIMEOUT=$(( $(date -r $BEEROCKS_TMP_PATH/pid/$PID_FILE +%s) + $WATCHDOG_CYCLE_SECONDS ))
        PID=`cat $BEEROCKS_TMP_PATH/pid/$PID_FILE`
        if [ -f /proc/$PID/exe ] && [ $NOW_EPOCH -gt $FILE_EPOCH_TIMEOUT ]; then
            echo "$0: WARNING [`date`]: Process $PID_FILE detected system slow down!"
            echo "$0: WARNING [`date`]: Process $PID_FILE detected system slow down!" >> $BEEROCKS_LOG_PATH/logs/slow_down.log
            top -b -n1 >> $BEEROCKS_LOG_PATH/logs/slow_down.log
            echo " "
            df >> $BEEROCKS_LOG_PATH/logs/slow_down.log
            echo " "
            PID_STUCK=true
        fi
    done

     [ "$PID_STUCK" == "true" ] && {
        let PID_STUCK_RETRIES++
        echo "$0: WARNING [`date`]: Beerocks processes stuck retry count=$PID_STUCK_RETRIES"
        echo "$0: WARNING [`date`]: Beerocks processes stuck retry count=$PID_STUCK_RETRIES"  >> $BEEROCKS_LOG_PATH/logs/slow_down.log
        top -b -n1 >> $BEEROCKS_LOG_PATH/logs/slow_down.log                                                               
        echo " "                                                                                                     
        df >> $BEEROCKS_LOG_PATH/logs/slow_down.log
        echo " "  
    } || PID_STUCK_RETRIES=0

    if [ $PID_STUCK_RETRIES -gt $PID_STUCK_RETRIES_LIMIT ]; then
        echo "$0: CRITICAL: Beerocks processes are stuck (max retries expired), trigger error handler"
        PID_STUCK_RETRIES=0
        $BEEROCKS_ERROR_HANDLER 0 $BPL_ERR_WATCHDOG_PROCESS_STUCK
    fi   
    
done
