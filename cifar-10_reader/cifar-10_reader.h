#ifndef _CIFAR_10_READER_H_
#define _CIFAR_10_READER_H_

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <cstdint>
#include <memory>

namespace cifar10_reader {

typedef std::vector<uint8_t> Image;
typedef std::vector<Image> Images;

typedef uint8_t Label;
typedef std::vector<Label> Labels;

// each batch has 10000 images
const int kNumImagesOneBatch = 10000;
// 10 classes
const int kNumClasses = 10;
// each image has 3072 bytes (32x32x3), plus a label
const int kSingleDataSize = 3073;

const std::vector<std::string> kClassesNames = {
  "plane", "car", "bird", "cat", "deer",
  "dog", "frog", "horse", "ship", "truck"
};

bool load_cifar10_batch(const std::string& filename,
    Images* images, Labels* labels);

bool load_cifar10_dataset(const std::string& data_dir,
    Images* train_images, Labels* train_labels,
    Images* test_images, Labels* test_labels);

}  // namespace cifar10_reader

#endif
