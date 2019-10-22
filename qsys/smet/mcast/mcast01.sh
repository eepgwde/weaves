#!/bin/sh

python3 MCsrv.py &
pid0=$!
sleep 1
netstat -a -n -p | grep 1910

Qp mcast01t.q -exit

kill $pid0

