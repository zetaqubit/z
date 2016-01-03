#ifndef SRC_GENESIS_IO_DATATYPES_H_
#define SRC_GENESIS_IO_DATATYPES_H_

#include "src/third_party/cimg/CImg.h"

namespace genesis {

static const int kNNImageWidth = 128;
static const int kNNImageHeight = 128;

enum ImageId {
  LEFT_IMAGE = 0,
  RIGHT_IMAGE,
};

typedef cimg_library::CImg<float> Image;

}  // namespace genesis

#endif  // SRC_GENESIS_IO_DATATYPES_H_
