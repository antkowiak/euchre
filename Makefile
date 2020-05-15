all : gnu clang

gnu : Makefile src/main.cpp src/*.h src/unit_tests/*.h
	g++ -g -std=c++14 \
	-Wall -Wextra -Wpedantic \
	src/main.cpp -o euchre_gnu

run : 
	chmod 755 euchre_gnu euchre_clang
	./euchre_gnu && ./euchre_clang

run_gnu : 
	chmod 755 euchre_gnu
	./euchre_gnu

clang : Makefile src/main.cpp src/*.h src/unit_tests/*.h
	clang++ -g -std=c++14 \
	-Wall -Wextra -Wpedantic \
	src/main.cpp -o euchre_clang

run_clang : 
	chmod 755 euchre_clang
	./euchre_clang

format :
	clang-format -i -style=file src/main.cpp
	clang-format -i -style=file src/*.h
	clang-format -i -style=file src/unit_tests/*.h

line_endings :
	dos2unix src/*.cpp src/*.h src/unit_tests/*.h

tidy :
	clang-tidy -checks="modernize-use-override" -header-filter=.* --format-style=file src/main.cpp

clean :
	\rm -f euchre_gnu euchre_clang

strip :
	strip euchre_gnu euchre_clang

