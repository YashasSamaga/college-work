#!/bin/bash

awk 'length($0) >= 35' < $1 | sed 's/\<in\>/in fact/'
