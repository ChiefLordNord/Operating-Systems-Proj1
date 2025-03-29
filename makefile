CC = g++
FLAGS = -pthread - lrt

main: producer.cpp consumer.cpp
	$(CC) $(FLAGS) -o producer producer.cpp
	$(CC) $(FLAGS) -o consumer consumer.cpp