all: walkthroughd

walkthroughd: walkthroughd.c
	$(CC) -Wall -o $@ $^

install: walkthroughd
	mkdir -p $(DESTDIR)/usr/local/lib/walkthroughd/ $(DESTDIR)/usr/local/lib/systemd/system/
	cp walkthroughd.service $(DESTDIR)/usr/local/lib/systemd/system/walkthroughd.service
	cp walkthroughd $(DESTDIR)/usr/local/lib/walkthroughd/walkthroughd

clean:
	rm -f walkthroughd *.o
