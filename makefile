all: display pathPlanner bigEnv plannerTester
	gcc -o plannerTester plannerTester.o pathPlanner.o display.o -lX11
	gcc -o bigEnvironment bigEnvironment.o display.o pathPlanner.o -lX11

display: obstacles.h display.h display.c
	gcc -c display.c -lX11

pathPlanner: obstacles.h pathPlanner.c
	gcc -c pathPlanner.c

bigEnv: display bigEnvironment.c pathPlanner.c
	gcc -c bigEnvironment.c

plannerTester: pathPlanner.c display plannerTester.c
	gcc -c plannerTester.c

clean:
	rm -f display.o pathPlanner.o bigEnvironment.o plannerTester.o plannerTester bigEnvironment
