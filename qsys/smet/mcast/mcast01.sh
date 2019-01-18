#!/bin/sh

python MCsrv.py &
pid0=$!
sleep 1
netstat -a -n -p | grep 1910

Qp mcast01t.q -exit

kill $pid0

# Qp egex2.q -exit
