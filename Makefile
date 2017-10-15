all: main.tex
	xelatex main.tex
	xelatex main.tex

main.tex:
	cp temp.tex main.tex
	./makeTex.sh src >> main.tex
	./makeTex.sh doc >> main.tex
	echo '\tableofcontents' >> main.tex
	echo '\end{document}' >> main.tex

clean:
	rm main* ; true
