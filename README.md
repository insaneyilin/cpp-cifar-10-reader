# cpp-cifar-10-reader
A simple CIFAR-10 dataset reader in C++

## Usage

Download `CIFAR-10 binary version (suitable for C programs)` at 

```
http://www.cs.toronto.edu/~kriz/cifar.html
```

```cpp
#include "cifar-10_reader/cifar-10_reader.h"

// ...
std::string cifar10_data_dir = "/path/to/cifar-10-dataset";
cifar10_reader::Images train_images;
cifar10_reader::Labels train_labels;
cifar10_reader::Images test_images;
cifar10_reader::Labels test_labels;

cifar10_reader::load_cifar10_dataset(cifar10_data_dir,
    &train_images, &train_labels,
    &test_images, &test_labels)

```

## Demo

`OpenCV(>=2.0)` required.

```
mkdir build
cd build
cmake ..
make
./cifar-10_reader_demo cifar10_data_dir
```
