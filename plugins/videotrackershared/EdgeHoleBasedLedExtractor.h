/** @file
    @brief Header

    @date 2016

    @author
    Sensics, Inc.
    <http://sensics.com/osvr>
*/

// Copyright 2016 Sensics, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//        http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef INCLUDED_EdgeHoleBasedLedExtractor_h_GUID_225A962F_C636_4CA5_2D16_964D63A0571A
#define INCLUDED_EdgeHoleBasedLedExtractor_h_GUID_225A962F_C636_4CA5_2D16_964D63A0571A

// Internal Includes
#include <BlobExtractor.h>
#include <BlobParams.h>
#include <LedMeasurement.h>

// Library/third-party includes
#include <opencv2/core/core.hpp>

// Standard includes
#include <cstdint>
#include <vector>

namespace osvr {
namespace vbtracker {
    class EdgeHoleBasedLedExtractor {
      public:
        EdgeHoleBasedLedExtractor();
        LedMeasurementVec const &operator()(cv::Mat const &gray,
                                            BlobParams const &p,
                                            bool verboseBlobOutput = false);

        void reset() {
            contours_.clear();
            measurements_.clear();
            rejectedCenters_.clear();
        }

        cv::Mat const &getInputGrayImage() const { return gray_; }
        cv::Mat const &getThresholdedImage() const { return thresh_; }
        cv::Mat const &getEdgeDetectedImage() const { return edge_; }
        cv::Mat const &getEdgeDetectedBinarizedImage() const {
            return edgeBinary_;
        }
        std::vector<ContourType> const &getContours() const {
            return contours_;
        }
        LedMeasurementVec const &getMeasurements() const {
            return measurements_;
        }
        std::vector<cv::Point2d> const &getRejectedCenters() const {
            return rejectedCenters_;
        }

      private:
        void checkBlob(ContourType &&contour, BlobParams const &p);
        void addToRejectedCenters(BlobData const &data) {
            rejectedCenters_.push_back(data.center);
        }
        double baseThreshVal_ = 75;
        std::uint8_t minBeaconCenterVal_ = 127;
        cv::Mat gray_;
        cv::Mat thresh_;
        cv::Mat edge_;
        cv::Mat edgeBinary_;
        std::vector<ContourType> contours_;
        LedMeasurementVec measurements_;
        std::vector<cv::Point2d> rejectedCenters_;
        bool verbose_ = false;

        /// parameters
        const int laplacianKSize_;
        const double laplacianScale_;
        const int edgeDetectionBlurSize_;
        const double edgeDetectionBlurThresh_;
    };
} // namespace vbtracker
} // namespace osvr
#endif // INCLUDED_EdgeHoleBasedLedExtractor_h_GUID_225A962F_C636_4CA5_2D16_964D63A0571A
