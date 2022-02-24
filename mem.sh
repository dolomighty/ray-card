#!/bin/sh
xterm -e 'while sleep 1 ; do clear ; PID=`pgrep main` && pmap $PID ; done'
