#!/bin/bash

RUNTIMES=10
while [ $RUNTIMES -gt 0 ]; do
	argos3 -c experiments/1.argos
	newFileName=profile${RUNTIMES}.txt
	cp profile.txt $newFileName
	RUNTIMES=$(($RUNTIMES-1))
done
