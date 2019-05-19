#!/bin/bash

awk -F ':' '{printf("USER #%d=%s\n", ++count, $1)}' < $1
