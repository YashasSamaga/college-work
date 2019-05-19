#!/bin/bash

awk '{sub("apathy", "empathy", $3); print}' < $1 | grep "" | sed ""
