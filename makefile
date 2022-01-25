proj4.x: bet.o proj4_driver.o
	g++ -o proj4.x bet.o proj4_driver.o
bet.o: bet.h bet.cpp
	g++ -std=c++11 -c bet.cpp
proj4_driver.o: bet.h proj4_driver.cpp
	g++ -std=c++11 -c proj4_driver.cpp
clean:
	rm -f *.o proj4.x
