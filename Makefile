QMAKE=qmake
LATEX=texi2pdf
MAKE=make

all: relazione clean
	
	

relazione:
	cd Relazione; \
	$(LATEX) Alessandro.tex

clean:
	cd Relazione; \
	rm Alessandro.aux; \
	rm Alessandro.fls; \
	rm Alessandro.log

clean-output:
	cd Relazione; rm Alessandro.pdf

clean-all: clean clean-output

	
