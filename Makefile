CC = clang 
CFLAGS = -Wall -O0 -g
LFLAGS = - O0 -g
LIBS = -lgsl -lm
GRAPH = gnuplot 
BROWSER = google-chrome
FILE = out
# DIR=/path	#uncomment #7 and #21 for output to be opened effortlessly 
URL = https://github.com/AlexisPrel/pendulum.git

all: pendulum run graph clean

pendulum: pendulum.c pendulum-ode.c pendulum-evolution.c
	${CC} -o $@ $^ $(LIBS)

run:
	./pendulum

graph: pendulum.gpl ${FILE}
	${GRAPH} pendulum.gpl
#	${BROWSER} ${DIR}/pendulum.png
    
git-first:
	touch README.md
	git init
	git add .
	git remote add origin ${URL}
	git commit -m 'First commit'
	# Done initialization
	make git-update
	
git-update:
	# Please make sure you have updated README.md
	#indent *.c
	git add .
	git commit -m 'update' #date
	git push origin master

clean:
	rm -f *.o *~ pendulum
