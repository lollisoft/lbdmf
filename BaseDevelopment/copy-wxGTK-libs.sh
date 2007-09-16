#!/bin/sh

ldd ~/bin/wxWrapper | grep `wx-config --basename` | awk -v VERSION=`wx-config --version-full | awk 'BEGIN { FS="."; } { printf("%s.%s\n", $3, $4); }'` -v PREFIX=$1 'BEGIN { printf("#/bin/sh\n\n"); } { LIBRARY=$1; printf("cp `wx-config --prefix`/lib/%s %s/lib/%s.%s\n", LIBRARY, PREFIX, LIBRARY, VERSION);}' | sh
