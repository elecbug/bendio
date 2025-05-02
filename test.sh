mkdir build || true
cd build

cmake ..
make
./myapp $1

cd ..