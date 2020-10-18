ALL : bin/main

bin/main : source/main.cpp source/Coins.cpp source/balance.c source/Coins.h source/balance.h
	g++ source/main.cpp source/Coins.cpp source/balance.c -o bin/main

clean : 
	rm bin/main

.PHONY : ALL clean
