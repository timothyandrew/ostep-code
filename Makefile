all: out/process-api out/lde

out/process-api: process-api/*.c
	gcc -o $@ $^

out/lde: lde/*.c
	gcc -o $@ $^

out/address-spaces: address-spaces/*.c
	gcc -o $@ $^

out/mem-syscall: mem-syscall/*.c
	gcc -o $@ $^