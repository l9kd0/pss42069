default:
	make -C ./philosophy
	make -C ./proco
	make -C ./reawri
	make -C ./tatas
	make -C ./tas

remake:
	make -C ./philosophy remake
	make -C ./proco remake
	make -C ./reawri remake

clean:
	make -C ./philosophy clean
	make -C ./proco clean
	make -C ./reawri clean
	make -C ./tatas clean
	make -C ./tas clean
	rm -f ./graphs/*.png
	rm -f ./data/*.csv

full_analysis: default
	./analysis.sh philosophy
	./analysis.sh tatas
	./analysis.sh btatas
	./analysis.sh tas
	./analysis.sh reawri
	./analysis.sh proco

graphs: analysis
	python3 graphs.py
