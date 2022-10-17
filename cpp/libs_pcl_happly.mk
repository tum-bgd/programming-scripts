all: 
	g++ -Wall -march=native -Ofast -o libs_pcl_happly libs_pcl_happly.cpp  `pkg-config --cflags --libs eigen3`
run: 
	./libs_pcl_happly ../data/sofa_0007.off.ply
