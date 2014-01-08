TARGET := ex
CSTUFF = -std=c++1y $(shell root-config --cflags)
CSTUFF += -I$(HOME)/window_work/NuMIana
LSTUFF = $(shell root-config --ldflags --glibs)
LSTUFF += -L$(HOME)/window_work/NuMIana/lib -lNuMIana

$(TARGET): ex.o
	$(CXX) -o $@ $< $(LSTUFF)

ex.o: ex.cpp
	$(CXX) -c $< $(CSTUFF)

.PHONY: clean

clean:
	-@rm -rf *.o $(TARGET)
