default:
	gcc -pthread -std=gnu99 -o philosophy philosophy.c
	gcc -pthread -std=gnu99 -D TAS -o philosophy_tas philosophy.c ../tas/lock.c
	gcc -pthread -std=gnu99 -D TATAS -o philosophy_tatas philosophy.c ../tatas/lock.c
clean:
	rm -f philosophy
	rm -f philosophy_tas
	rm -f philosophy_tatas
remake: clean default
