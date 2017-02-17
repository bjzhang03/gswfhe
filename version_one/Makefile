utility_test_x:utility_test.cpp parameters_test.cpp serverkeys_test.cpp userkeys_test.cpp example_keyslength.cpp example_ndata.cpp
	g++ -std=c++11 -g -O2 -I/usr/local/include utility_test.cpp -o utility_test_x -L/usr/share/lib -lntl -lgmp -lm
	g++ -std=c++11 -g -O2 -I/usr/local/include parameters_test.cpp -o parameters_test_x -L/usr/share/lib -lntl -lgmp -lm
	g++ -std=c++11 -g -O2 -I/usr/local/include serverkeys_test.cpp -o serverkeys_test_x -L/usr/share/lib -lntl -lgmp -lm
	g++ -std=c++11 -g -O2 -I/usr/local/include userkeys_test.cpp -o userkeys_test_x -L/usr/share/lib -lntl -lgmp -lm
	g++ -std=c++11 -g -O2 -I/usr/local/include example_keyslength.cpp -o example_keyslength_x -L/usr/share/lib -lntl -lgmp -lm
	g++ -std=c++11 -g -O2 -I/usr/local/include example_ndata.cpp -o example_ndata_x -L/usr/share/lib -lntl -lgmp -lm
	


clean:
	rm *_x
