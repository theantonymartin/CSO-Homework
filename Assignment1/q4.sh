#!/bin/bash
tmux new-session -d -s Q4 "watch -n 1 date"
tmux split-window -d -t Q4:0 -p20 -v "sudo tcpdump -i any port 80 or port 443"
tmux split-window -d -h -b -t Q4:0 "htop"
tmux attach -t Q4