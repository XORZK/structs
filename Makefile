RUN=test.cc
OUT=a.out

default:
	g++ -std=c++17 -lm $(RUN) -o $(OUT) && ./$(OUT)
