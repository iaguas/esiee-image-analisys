EXE=$(BDIR)/addconst $(BDIR)/deriche $(BDIR)/diffimage $(BDIR)/normalize $(BDIR)/threshold $(BDIR)/ppm2pgm $(BDIR)/pgm2ppm 
DOC=$(DOCDIR)/tutorialEnglish.html

CCFLAGS = -g -DUNIXIO -Wall -std=c99 -O2

IDIR = ./include
ODIR = ./obj
BDIR = ./bin
CDIR = ./src/com
LDIR = ./src/lib
DOCDIR = ./doc
CC = cc

# Documentation, if not already comiled, can be compiled thanks to 'make doc'
# You can also do a 'make clean' if you want

all:	$(EXE) 
doc:    $(DOC)


# ===============================================================
# shell commands
# ===============================================================

$(BDIR)/addconst:	$(CDIR)/addconst.c $(IDIR)/laddconst.h $(IDIR)/mcimage.h $(ODIR)/mcimage.o $(ODIR)/laddconst.o
	mkdir -p bin
	$(CC) $(CCFLAGS) -I$(IDIR) $(CDIR)/addconst.c $(ODIR)/laddconst.o $(ODIR)/mcimage.o -o $(BDIR)/addconst

$(BDIR)/deriche:	$(CDIR)/deriche.c $(IDIR)/lderiche.h $(IDIR)/mcimage.h $(ODIR)/mcimage.o $(ODIR)/lderiche.o
	$(CC) $(CCFLAGS) -I$(IDIR) $(CDIR)/deriche.c $(ODIR)/lderiche.o $(ODIR)/mcimage.o -lm -o $(BDIR)/deriche

$(BDIR)/diffimage:	$(CDIR)/diffimage.c $(IDIR)/ldiffimage.h $(IDIR)/mcimage.h $(ODIR)/mcimage.o $(ODIR)/ldiffimage.o
	$(CC) $(CCFLAGS) -I$(IDIR) $(CDIR)/diffimage.c $(ODIR)/ldiffimage.o $(ODIR)/mcimage.o -o $(BDIR)/diffimage

$(BDIR)/normalize:	$(CDIR)/normalize.c $(IDIR)/lnormalize.h $(IDIR)/mcimage.h $(IDIR)/tools.h $(ODIR)/mcimage.o $(ODIR)/tools.o $(ODIR)/lnormalize.o
	$(CC) $(CCFLAGS) -I$(IDIR) $(CDIR)/normalize.c $(ODIR)/lnormalize.o $(ODIR)/mcimage.o $(ODIR)/tools.o -o $(BDIR)/normalize

$(BDIR)/threshold:	$(CDIR)/threshold.c $(IDIR)/lthreshold.h $(IDIR)/mcimage.h $(IDIR)/tools.h $(ODIR)/mcimage.o $(ODIR)/tools.o $(ODIR)/lthreshold.o
	$(CC) $(CCFLAGS) -I$(IDIR) $(CDIR)/threshold.c $(ODIR)/lthreshold.o $(ODIR)/mcimage.o $(ODIR)/tools.o -o $(BDIR)/threshold

# ===============================================================
# Library functions 
# ===============================================================

# Basic ones:
# ===============================================================

$(ODIR)/mcimage.o:	$(LDIR)/mcimage.c $(IDIR)/mcimage.h
	mkdir -p obj
	$(CC) -c $(CCFLAGS) -I$(IDIR) $(LDIR)/mcimage.c -o $(ODIR)/mcimage.o
	
$(ODIR)/tools.o:	$(LDIR)/tools.c $(IDIR)/tools.h
	$(CC) -c $(CCFLAGS) -I$(IDIR) $(LDIR)/tools.c -o $(ODIR)/tools.o

# Operators:
# ===============================================================

$(ODIR)/laddconst.o:	$(LDIR)/laddconst.c $(IDIR)/laddconst.h $(IDIR)/mcimage.h
	$(CC) -c $(CCFLAGS) -I$(IDIR) $(LDIR)/laddconst.c -o $(ODIR)/laddconst.o

$(ODIR)/lderiche.o:	$(LDIR)/lderiche.c $(IDIR)/lderiche.h $(IDIR)/mcimage.h
	$(CC) -c $(CCFLAGS) -I$(IDIR) $(LDIR)/lderiche.c -o $(ODIR)/lderiche.o

$(ODIR)/ldiffimage.o:	$(LDIR)/ldiffimage.c $(IDIR)/ldiffimage.h $(IDIR)/mcimage.h
	$(CC) -c $(CCFLAGS) -I$(IDIR) $(LDIR)/ldiffimage.c -o $(ODIR)/ldiffimage.o
	
$(ODIR)/lnormalize.o:	$(LDIR)/lnormalize.c $(IDIR)/lnormalize.h $(IDIR)/mcimage.h $(IDIR)/tools.h
	$(CC) -c $(CCFLAGS) -I$(IDIR) $(LDIR)/lnormalize.c -o $(ODIR)/lnormalize.o

$(ODIR)/lthreshold.o:	$(LDIR)/lthreshold.c $(IDIR)/lthreshold.h $(IDIR)/mcimage.h
	$(CC) -c $(CCFLAGS) -I$(IDIR) $(LDIR)/lthreshold.c -o $(ODIR)/lthreshold.o

$(BDIR)/ppm2pgm:	$(CDIR)/ppm2pgm.c $(IDIR)/mcimage.h $(LDIR)/mcimage.c
	$(CC) $(CCFLAGS) -I$(IDIR) $(CDIR)/ppm2pgm.c  $(ODIR)/mcimage.o -o $(BDIR)/ppm2pgm

$(BDIR)/pgm2ppm:	$(CDIR)/pgm2ppm.c $(IDIR)/mcimage.h $(LDIR)/mcimage.c
	$(CC) $(CCFLAGS) -I$(IDIR) $(CDIR)/pgm2ppm.c $(ODIR)/mcimage.o -o $(BDIR)/pgm2ppm

# Documentation
# ===============================================================
$(DOCDIR)/tutorialEnglish.html: $(DOCDIR)/tutorialEnglish.tex
	cd $(DOCDIR); htlatex ./tutorialEnglish; cd ..

clean:
	rm -rf *~ $(ODIR)/* $(IDIR)/*~ $(CDIR)/*~ $(LDIR)/*~ $(DOCDIR)/*~ 
	cd $(DOCDIR); rm -rf *.4ct *.4tc *.aux *.dvi *.idv *.lg *.log *.tmp *.xref

cleanall: 
	rm -rf *~ $(BDIR) $(ODIR) $(IDIR)/*~ $(CDIR)/*~ $(LDIR)/*~ $(DOCDIR)/*~ 
	cd $(DOCDIR); rm -rf *.4ct *.4tc *.aux *.dvi *.idv *.lg *.log *.tmp *.xref