default:
	gcc -pthread -std=gnu99 -o reawri reawri.c
	gcc -pthread -std=gnu99 -D TAS -o reawri_tas reawri.c ../tas/lock.c
	gcc -pthread -std=gnu99 -D TATAS -o reawri_tatas reawri.c ../tatas/lock.c
clean:
	rm -f reawri
	rm -f reawri_tatas
	rm -f reawri_tas
remake: clean default
