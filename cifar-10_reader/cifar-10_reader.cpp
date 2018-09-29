#include "cifar-10_reader.h"

namespace cifar10_reader {

bool load_cifar10_batch(const std::string& filename,
    Images* images, Labels* labels) {
  std::ifstream file;
  file.open(filename, std::ios::in | std::ios::binary | std::ios::ate);
  if (!file) {
    std::cout << "Error opening file: " << filename << std::endl;
    return false;
  }
  auto file_size = file.tellg();
  std::unique_ptr<char[]> buffer(new char[file_size]);
  // Read the entire file at once
  file.seekg(0, std::ios::beg);
  file.read(buffer.get(), file_size);
  file.close();

  images->resize(kNumImagesOneBatch);
  labels->resize(kNumImagesOneBatch);
  for (int i = 0; i < kNumImagesOneBatch; ++i) {
    (*labels)[i] = static_cast<uint8_t>(buffer[i * kSingleDataSize]);
    (*images)[i].resize(kSingleDataSize - 1);
    for (int j = 1; j < kSingleDataSize; ++j) {
      (*images)[i][j - 1] = static_cast<uint8_t>(
          buffer[i * kSingleDataSize + j]);
    }
  }

  return true;
}

bool load_cifar10_dataset(const std::string& data_dir,
    Images* train_images, Labels* train_labels,
    Images* test_images, Labels* test_labels) {
  Images images_one_batch;
  Labels labels_one_batch;

  train_images->clear();
  train_labels->clear();
  for (int i = 1; i <= 5; ++i) {
    std::string filename = data_dir + "/data_batch_" +
        std::to_string(i) + ".bin";
    if (!load_cifar10_batch(filename, &images_one_batch, &labels_one_batch)) {
      return false;
    }
    train_images->insert(train_images->end(),
        images_one_batch.begin(), images_one_batch.end());
    train_labels->insert(train_labels->end(),
        labels_one_batch.begin(), labels_one_batch.end());
  }

  test_images->clear();
  test_labels->clear();
  if (!load_cifar10_batch(data_dir + "/test_batch.bin",
      test_images, test_labels)) {
    return false;
  }

  return true;
}

}  // namespace cifar10_reader