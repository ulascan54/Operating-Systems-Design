all: run

run:
	gcc -o main main.c
	./main $(FLAG)

ex:
	gcc -o main main.c
	./main 10 &
	sleep 1
	./main 22 &
	sleep 1
	./main 12 &
	sleep 1
	./main 15 &
	sleep 1
	./main 20 &
	sleep 1

kill:
	killall main

show:
	ps axo pid,ppid,nice,uid,comm | grep main

clean:
	rm -f main
