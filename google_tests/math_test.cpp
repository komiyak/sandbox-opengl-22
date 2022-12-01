#include "gtest/gtest.h"
#include "../game_math.h"

TEST(MathTestSuite, TransformFromScreenCoordinateToDeviceCoordinateSpec) {
    const glm::vec2 result_1 =
            game_math::TransformFromScreenCoordinateToDeviceCoordinate(0, 0, 1920, 1080);
    EXPECT_FLOAT_EQ(result_1.x, -1.f);
    EXPECT_FLOAT_EQ(result_1.y, 1.f);

    const glm::vec2 result_2 =
            game_math::TransformFromScreenCoordinateToDeviceCoordinate(-1920, -1080, 1920, 1080);
    EXPECT_FLOAT_EQ(result_2.x, -3.f);
    EXPECT_FLOAT_EQ(result_2.y, 3.f);

    const glm::vec2 result_3 =
            game_math::TransformFromScreenCoordinateToDeviceCoordinate(1920, 1080, 1920, 1080);
    EXPECT_FLOAT_EQ(result_3.x, 1.f);
    EXPECT_FLOAT_EQ(result_3.y, -1.f);

    const glm::vec2 result_4 =
            game_math::TransformFromScreenCoordinateToDeviceCoordinate(1920 * 2, 1080 * 2, 1920, 1080);
    EXPECT_FLOAT_EQ(result_4.x, 3.f);
    EXPECT_FLOAT_EQ(result_4.y, -3.f);

    const glm::vec2 result_center =
            game_math::TransformFromScreenCoordinateToDeviceCoordinate(1920 / 2, 1080 / 2, 1920, 1080);
    EXPECT_FLOAT_EQ(result_center.x, 0.f);
    EXPECT_FLOAT_EQ(result_center.y, 0.f);
}
