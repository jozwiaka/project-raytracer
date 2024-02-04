prepare:
	rm -rf build
	mkdir build
conan: prepare
	pip install conan
	conan profile detect --force # Let Conan try to guess the profile, based on the current operating system and installed tools
	cat /root/.conan2/profiles/default || echo "Wrong profile path"
	conan install ./ --output-folder=build --build=missing
configure: conan
	cd build && cmake ..
build: configure
	# cd build && cmake --build . -v
	cd build && cmake --build .
test: build
	# cd build && make test
run:
	cd build && ./src/exe
callgrind:
	cd build && valgrind --tool=callgrind ./exe && kcachegrin callgrind.out.*
all: prepare conan configure build test run