#!/bin/sh

ldd $1/bin/wxWrapper | grep `wx-config --basename` | \
awk -v VERSION=`wx-config --version-full | awk 'BEGIN { FS="."; } { printf("%s.%s\n", $3, $4); }'` \
    -v PREFIX=$1 '\
BEGIN {\
	printf("#/bin/sh\n\n");\
	printf("cd %s/lib\n", PREFIX);\
}\
{\
	LIBRARY=$1;\
	printf("cp `wx-config --prefix`/lib/%s %s.%s\n", LIBRARY, LIBRARY, VERSION);\
        printf("ln -s %s.%s %s\n", LIBRARY, VERSION, LIBRARY);\
}' | sh
