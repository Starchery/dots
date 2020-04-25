#!/bin/bash

while true; do
	xsetroot -name "$(date +"%-d | %I:%M %p")"
	sleep 1m
done &
