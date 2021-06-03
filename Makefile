all: out/process-api out/lde

out/process-api: process-api/*.c
	gcc -g -o $@ $^

out/lde: lde/*.c
	gcc -g -o $@ $^

out/address-spaces: address-spaces/*.c
	gcc -g -o $@ $^

out/mem-syscall: mem-syscall/*.c
	gcc -g -o $@ $^

out/mem-api: mem-api/*.c
	gcc -g -o $@ $^