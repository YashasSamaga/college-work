#!/bin/bash

grep -E '^TS([- ])..\1..(55|SS)\1[0O]' < $1
