TARGET := example_run

$(TARGET): ex.o
	$(CXX) -o $@ $< `root-config --ldflags --glibs` -L$(HOME)/Desktop/window_plots/NuMIana/lib -lNuMIana

ex.o: ex.cpp
	$(CXX) -c $< `root-config --cflags` -I$(HOME)/Desktop/window_plots/NuMIana

.PHONY: clean

clean:
	-@rm -rf *.o $(TARGET)
