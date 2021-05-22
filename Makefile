all: out/process-api out/lde

out/process-api: process-api/*.c
	gcc -o $@ $^

out/lde: lde/*.c
	gcc -o $@ $^