
#include "gtest/gtest.h"
#include "fianet-core.h"

using namespace Fianet;

namespace {

TEST (StringTest, memfind_works)
{
	uint8_t *ptr;
	uint8_t *str_XYZXYZ = (uint8_t*)"XYZXYZ";
	uint8_t *str_xyzXYZ = (uint8_t*)"xyzXYZ";
	uint8_t *str_XXYXYZ = (uint8_t*)"XXYXYZ";
	uint8_t *str_XYXYXZ = (uint8_t*)"XYXYXZ";

	ptr = memfind(str_XYZXYZ, 6, "XYZ", 3);
	EXPECT_EQ(str_XYZXYZ, ptr);

	ptr = memfind(str_xyzXYZ, 6, "XYZ", 3);
	EXPECT_EQ(str_xyzXYZ + 3, ptr);

	ptr = memfind(str_XYZXYZ, 6, "XZ", 2);
	EXPECT_EQ(0, ptr);

	ptr = memfind(str_XXYXYZ, 6, "XY", 2);
	EXPECT_EQ(str_XXYXYZ + 1, ptr);

	ptr = memfind(str_XXYXYZ, 6, "XYZ", 3);
	EXPECT_EQ(str_XXYXYZ + 3, ptr);

	ptr = memfind(str_XYXYXZ, 6, "XYXZ", 4);
	EXPECT_EQ(str_XYXYXZ + 2, ptr);
}

TEST (StringTest, memifind_works)
{
	uint8_t *ptr;
	uint8_t *str_XYZXYZ = (uint8_t*)"XYZXYZ";
	uint8_t *str_xyzXYZ = (uint8_t*)"xyzXYZ";
	uint8_t *str_XXYXYZ = (uint8_t*)"XXYXYZ";
	uint8_t *str_XYXYXZ = (uint8_t*)"XYXYXZ";

	ptr = memifind(str_XYZXYZ, 6, "XyZ", 3);
	EXPECT_EQ(str_XYZXYZ, ptr);

	ptr = memifind(str_xyzXYZ, 6, "XyZ", 3);
	EXPECT_EQ(str_xyzXYZ, ptr);

	ptr = memifind(str_XYZXYZ, 6, "XZ", 2);
	EXPECT_EQ(0, ptr);

	ptr = memifind(str_XXYXYZ, 6, "xy", 2);
	EXPECT_EQ(str_XXYXYZ + 1, ptr);

	ptr = memifind(str_XXYXYZ, 6, "xyZ", 3);
	EXPECT_EQ(str_XXYXYZ + 3, ptr);

	ptr = memifind(str_XYXYXZ, 6, "xYXz", 4);
	EXPECT_EQ(str_XYXYXZ + 2, ptr);
}

}
