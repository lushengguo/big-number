all:inifnit_bit_example infinit_bit_test

OPTIONS=-std=c++2a -g -Wall -Werror

main:big_integer.cpp main.cpp 
	clang++ $^ ${OPTIONS} -o main

infinit_bit_test:infinit_bit.cpp  infinit_bit_version_test.cpp
	clang++ $^ ${OPTIONS} -o infinit_bit_test

clean:
	rm main