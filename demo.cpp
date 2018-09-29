#include <cstdlib>
#include <ctime>

#include "cifar-10_reader/cifar-10_reader.h"
#include <opencv2/opencv.hpp>

cv::Mat get_cvmat_from_cifar10_image(const cifar10_reader::Image& image);

int main(int argc, char **argv) {
  if (argc != 2) {
    std::cout << "Usage: " << argv[0]
        << " <cifar10_data_dir>" << std::endl;
    return 1;
  }
  std::srand(static_cast<int>(std::time(0)));

  // Load cifar-10 dataset
  std::string data_dir(argv[1]);
  cifar10_reader::Images train_images;
  cifar10_reader::Labels train_labels;
  cifar10_reader::Images test_images;
  cifar10_reader::Labels test_labels;
  if (!cifar10_reader::load_cifar10_dataset(data_dir,
      &train_images, &train_labels,
      &test_images, &test_labels)) {
    std::cout << "load cifar-10 dataset failed\n";
    return 1;
  }

  // Show images using OpenCV
  std::cout << "********** train_images: **********\n";
  for (int i = 0; i < 10; ++i) {
    int idx = static_cast<int>(train_images.size() *
        std::rand() / (RAND_MAX + 1.0));
    cv::Mat cv_image = get_cvmat_from_cifar10_image(train_images[idx]);
    cv::resize(cv_image, cv_image, cv::Size(128, 128));
    cv::imshow("image", cv_image);
    std::cout << "class: "
        << cifar10_reader::kClassesNames.at(train_labels[idx])
        << std::endl;
    auto key = cv::waitKey(0);
    if (key == 27 || key == 'q') {
      break;
    }
  }
  std::cout << "********** test_images: **********\n";
  for (int i = 0; i < 10; ++i) {
    int idx = static_cast<int>(test_images.size() *
        std::rand() / (RAND_MAX + 1.0));
    cv::Mat cv_image = get_cvmat_from_cifar10_image(test_images[idx]);
    cv::resize(cv_image, cv_image, cv::Size(128, 128));
    cv::imshow("image", cv_image);
    std::cout << "class: "
        << cifar10_reader::kClassesNames.at(test_labels[idx])
        << std::endl;
    auto key = cv::waitKey(0);
    if (key == 27 || key == 'q') {
      break;
    }
  }
  return 0;
}

cv::Mat get_cvmat_from_cifar10_image(const cifar10_reader::Image& image) {
  cv::Mat cv_image(32, 32, CV_8UC3);
  // CHW -> HWC && rgb -> bgr
  for (int ch = 2; ch >= 0; --ch) {
    for (int row = 0; row < 32; ++row) {
      for (int col = 0; col < 32; ++col) {
        cv_image.at<cv::Vec3b>(row, col)[2 - ch] =
            image.data()[col + 32 * (row + 32 * ch)];
      }
    }
  }
  return cv_image;
}
