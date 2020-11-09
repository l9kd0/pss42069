default:
	make -C ./philosophy
	make -C ./proco
	make -C ./reawri

remake:
	make -C ./philosophy remake
	make -C ./proco remake
	make -C ./reawri remake

clean:
	make -C ./philosophy clean
	make -C ./proco clean
	make -C ./reawri clean
	rm -f *.png
	rm -f *.csv

analysis: default
	./analysis.sh

graphs: analysis
	python3 graphs.py
