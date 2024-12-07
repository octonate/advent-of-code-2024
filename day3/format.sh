#!/bin/bash

 grep -oE "mul\(.{1,3},.{1,3}\)" inputCorrupted.txt > input.txt
 sed -i "s/,/ /;s/mul(//;s/)//" input.txt
 
 grep -oE "mul\(.{1,3},.{1,3}\)|do\(\)|don't\(\)" inputCorrupted.txt > input2.txt
 sed -i "s/,/ /;s/mul(//;s/)//;s/(//" input2.txt
