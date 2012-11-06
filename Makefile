#---------------------------------------------------------------#
# Written By Joe Anderson
#---------------------------------------------------------------#
# TARGETS:
# fheap - default target
# dfheap - debug target
# tag - For generating tag file
# clean/fresh - clean obj files.
#---------------------------------------------------------------#
#-- Customized variables
BINDIR=bin
OBJDIR=obj
SRCDIR=src
INCDIR=include

CC = g++
CWARN = -W -Wall -Wshadow -Wreturn-type -Wcomment -Wtrigraphs -Wformat -Wparentheses -Wpointer-arith -Wuninitialized -O

CDBG = -g $(CWARN) -fno-inline
CFLAGS = -I$(INCDIR) $(CDBG)
DFLAGS = -I$(INCDIR) -g $(CWARN) -fno-inline -DDEBUG=1

CTAG = ctags
CTAGFILE = filelist
# src, object and bin files
TGT=fheap
#Debug Target
DBGTGT=dfheap

HEADERS = $(INCDIR)/global.h $(INCDIR)/FNode.h $(INCDIR)/FHeap.h $(INCDIR)/main.h

OBJS = $(OBJDIR)/main.o $(OBJDIR)/FNode.o $(OBJDIR)/FHeap.o
DBGOBJS = $(OBJDIR)/main.dbg.o

#-- Rules
all: $(TGT)
dbg: $(DBGTGT)

$(TGT): $(BINDIR)/$(TGT)
	@echo "$@ uptodate"

$(DBGTGT): $(BINDIR)/$(DBGTGT)
	@echo "$@ uptodate"

$(BINDIR)/$(DBGTGT): $(DBGOBJS)
	$(CC) $(CFLAGS) -o $@ $(DBGOBJS)

$(OBJDIR)/%.dbg.o: $(SRCDIR)/%.cpp
	$(CC) $(CFLAGS) -DDEBUG=1 -c -o $@ $?

$(BINDIR)/$(TGT): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CC) $(CFLAGS) -c -o $@ $?

.PHONY : clean depend fresh
tag :
	find src/*.cpp include/*.h > $(CTAGFILE)
	$(CTAG) -L $(CTAGFILE)

clean :
	-rm -f $(OBJDIR)/*.o $(PARSE_C) $(PARSE_H)
	-rm -f $(SRCDIR)/*.output $(LEX_C)
	-rm -f */*~ *~ core
	-rm -f $(BINDIR)/$(TGT) $(BINDIR)/$(DBGTGT)
