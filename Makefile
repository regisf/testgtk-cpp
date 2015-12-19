#
# GTK+ in pure C++
#

ALL=pkg-config gtk+-2.0 --libs --cflags

# Uncomment for GTK+ 3.0
#ALL=pkg-config gtk+-3.0 --libs --cflags


all:
	g++ -o test-gtk test-gtk.cpp `$(ALL)`


