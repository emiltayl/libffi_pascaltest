pascaltest: pascal.c
	i686-linux-gnu-gcc -g -o pascaltest pascal.c -L. -lstruct_abi -Wl,-rpath,'$$ORIGIN' -lffi