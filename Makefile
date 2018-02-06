override CFLAGS += -Wall -g #-DDEBUG

TARGET=trackpoint-control
HELPER=$(TARGET)-helper

PREFIX=/usr/local
BINDIR=$(PREFIX)/bin
DATADIR=$(PREFIX)/share/$(TARGET)
DATA=trackpoint.png

all: $(HELPER)

install: all
	install -m 755  $(TARGET) $(BINDIR)
	install -m 4755 $(HELPER) $(BINDIR)
	install -d $(DATADIR)
	install -m 644 -t $(DATADIR) $(DATA)

uninstall:
	rm -f $(BINDIR)/$(TARGET)
	rm -f $(BINDIR)/$(HELPER)
	rm -rf $(DATADIR)

clean:
	rm -f $(HELPER) *~
