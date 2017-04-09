REFDIR=.
SRCDIR=$(REFDIR)/src
BINDIR=$(REFDIR)/bin
INCDIR=$(REFDIR)/include
OBJDIR=$(REFDIR)/obj
DOCDIR=$(REFDIR)/doc
REPORTDIR=$(REFDIR)/rapport

CC=cc
LATEXC=pdflatex
DOCC=doxygen
CFLAGS=-g -Wall -I$(INCDIR)

LATEXSOURCE=$(wildcard $(REPORTDIR)/*.tex)
CSOURCE=$(wildcard $(SRCDIR)/compileBST.c)
CSOURCE2=$(wildcard $(SRCDIR)/compileABROpt.c)
PDF=$(LATEXSOURCE:.tex=.pdf)

all: binary report doc

$(BINDIR)/compileBST: $(OBJDIR)/BST.o $(OBJDIR)/compileBST.o
	$(CC) $^ -o $@

$(OBJDIR)/compileBST.o: $(SRCDIR)/compileBST.c
	$(CC) -c $(CFLAGS) $< -o $@

$(BINDIR)/computeABROpt: $(OBJDIR)/BST.o $(OBJDIR)/computeABROpt.o
	$(CC) $^ -o $@

$(OBJDIR)/computeABROpt.o: $(SRCDIR)/computeABROpt.c
	$(CC) -c $(CFLAGS) $< -o $@

$(OBJDIR)/BST.o: $(SRCDIR)/BST.c $(INCDIR)/BST.h
	$(CC) -c $(CFLAGS) $< -o $@

%.pdf: $(LATEXSOURCE)
	$(LATEXC) -output-directory $(REPORTDIR) $^ 

$(DOCDIR)/index.html: $(SRCDIR)/Doxyfile $(CSOURCE) 
	$(DOCC) $(SRCDIR)/Doxyfile

binary: $(BINDIR)/compileBST $(BINDIR)/computeABROpt

report: $(PDF) 

doc: $(DOCDIR)/index.html

clean:
	rm -rf $(DOCDIR) $(BINDIR)/* $(REPORTDIR)/*.aux $(REPORTDIR)/*.log  $(REPORTDIR)/rapport.pdf $(OBJDIR)/*.o


.PHONY: all doc binary report 
