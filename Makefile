all: main.tex
	xelatex main.tex
	xelatex main.tex

main.tex:
	cp temp.tex main.tex
	./makecpp.sh src >> main.tex
	./makedoc.sh doc >> main.tex
	echo '\end{document}' >> main.tex

clean:
	rm main* ; true
