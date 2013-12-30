TARGET := example_run
CSTUFF = $(shell root-config --cflags)
CSTUFF += -I$(HOME)/Desktop/window_plots/NuMIana
LSTUFF = $(shell root-config --ldflags --glibs)
LSTUFF += -L$(HOME)/Desktop/window_plots/NuMIana/lib -lNuMIana

$(TARGET): ex.o
	$(CXX) -o $@ $< $(LSTUFF)

ex.o: ex.cpp
	$(CXX) -c $< $(CSTUFF)

.PHONY: clean

clean:
	-@rm -rf *.o $(TARGET)
