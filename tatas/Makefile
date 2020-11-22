default:
	gcc -pthread -std=gnu99 -o tatas tatas.c lock.c
	gcc -pthread -std=gnu99 -D BACKOFF -o btatas tatas.c b_lock.c
clean:
	rm -f tatas
remake: clean default
