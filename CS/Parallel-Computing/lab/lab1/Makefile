pi_src=$(wildcard pi-v*.c)

# psrs: psrs.cpp
# 	gcc psrs.cpp -o psrs -fopenmp -O3
all: pi-v1 pi-v2 pi-v3 pi-v4 pi-v5 psrs

run_psrs: psrs
	@echo "psrs:" && ./psrs

run_pi: pi-v1 pi-v2 pi-v3 pi-v4 pi-v5
	@echo "pi-v1:" && ./pi-v1
	@echo "pi-v2:" && ./pi-v2
	@echo "pi-v3:" && ./pi-v3
	@echo "pi-v4:" && ./pi-v4
	@echo "pi-v5:" && ./pi-v5
	

%: %.c
	gcc $< -o $* -fopenmp -O3

%: %.cpp
	g++ $< -o $* -fopenmp -O3

clean:
	rm -rf pi-v1 pi-v2 pi-v3 pi-v4 pi-v5 psrs
	