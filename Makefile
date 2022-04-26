TARGETS = test
PARAMS = -W -Wall -Wextra -Wsign-compare \
					 --std=gnu++11 \
					 -m64 \
					 -msse \
					 -O2 \
					 -march=native \
					 -funroll-loops \
					 -ftree-vectorize \
					 -fomit-frame-pointer \
					 main.cpp mt32.cpp mt64.cpp \
					 -o
SEED = 291 564 837 1110

all: build run

build:
	g++ $(PARAMS) $(TARGETS)

run :
	./test $(SEED)

clean:
	rm -f $(TARGETS)
	clear