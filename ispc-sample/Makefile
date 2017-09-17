adder.out: main.o sample_ispc.o
	g++ $^ -o $@

main.o: main.cpp sample_ispc.o
	g++ -c $< -o $@

# We use the ISPC compiler to produce an object file with our code
# to link, along with the header to include in our C or C++ code.
sample_ispc.o: sample.ispc
	ispc -o $@ -h sample_ispc.h $<

.PHONY: clean
clean:
	rm -f adder.out *.o sample_ispc.h

