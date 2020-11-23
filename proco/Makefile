default:
	gcc -pthread -std=gnu99 -o proco proco.c
	gcc -pthread -std=gnu99 -D TAS -o proco_tas proco.c ../tas/lock.c
	gcc -pthread -std=gnu99 -D TATAS -o proco_tatas proco.c ../tatas/lock.c
clean:
	rm -f proco
	rm -f proco_tas
	rm -f proco_tatas
remake: clean default
