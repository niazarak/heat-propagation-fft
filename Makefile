build:
	clang++ -std=c++11 heat.cpp -o heat

run:
	./heat 
clean:
	rm out/*; rm heat
