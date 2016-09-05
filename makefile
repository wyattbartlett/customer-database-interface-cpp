#makefile for project2
llist.o: llist.cpp	record.h	func.h	llist.h
		g++	-c	llist.cpp

UI.o: UI.cpp	record.h	func.h
		g++	-c	UI.cpp

project2:	llist.o	UI.o
		g++	-o	project2	llist.o	UI.o