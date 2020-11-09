default:
	make -C ./philosophy
	make -C ./proco
	make -C ./reawri

clean:
	make -C ./philosophy clean
	make -C ./proco clean
	make -C ./reawri clean
	rm -f *.png
	rm -f *.csv

analysis:
	./analysis.sh

graphs:
