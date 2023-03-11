#include <gtest/gtest.h>
#include <boundingrectangle.h>


TEST(BoundingRectangleTests, SameRectanglesCollide) {
  BoundingRectangle rect1(1000,1000,100,100);
  BoundingRectangle rect2(1000,1000,100,100);
  EXPECT_TRUE(rect1.isCollidingWith(rect2));
  EXPECT_TRUE(rect2.isCollidingWith(rect1));
}

TEST(BoundingRectangleTests, RectanglesDontCollide) {
  BoundingRectangle rect1(0,0,100,100);
  BoundingRectangle rect2(1000,1000,100,100);
  EXPECT_FALSE(rect1.isCollidingWith(rect2));
  EXPECT_FALSE(rect2.isCollidingWith(rect1));
}

TEST(BoundingRectangleTests, RectanglesDoesCollideWithPoint) {
  BoundingRectangle rect1(1000,1100,1,1);
  BoundingRectangle rect2(1000,1000,100,100);
  EXPECT_FALSE(rect1.isCollidingWith(rect2));
  EXPECT_FALSE(rect2.isCollidingWith(rect1));
}

TEST(BoundingRectangleTests, RectanglesDoesCollideWithActualPoint) {
  Point point1(1000,1000);
  Point point2(1000,1100);
  Point point3(1100,1000);
  Point point4(1100,1100);
  Point point5(0,0);
  BoundingRectangle rect1(1000,1000,100,100);
  EXPECT_TRUE(rect1.isCollidingWithPoint(point1));
  EXPECT_TRUE(rect1.isCollidingWithPoint(point2));
  EXPECT_TRUE(rect1.isCollidingWithPoint(point3));
  EXPECT_TRUE(rect1.isCollidingWithPoint(point4));
  EXPECT_FALSE(rect1.isCollidingWithPoint(point5));
}



TEST(BoundingRectangleTests, getClosestPointTo) {
  BoundingRectangle rect1(1000,1000,100,100);
  Point point1(1000,1000);
  Point point2(1100,1100);
  Point point3(1150,1150);

  EXPECT_EQ(rect1.getClosestPointTo(point1), point1);
  EXPECT_EQ(rect1.getClosestPointTo(point2), point2);
  EXPECT_EQ(rect1.getClosestPointTo(point3), point2);
}


TEST(BoundingRectangleTests, getClosestPointToInside) {
  BoundingRectangle rect1(1000,1000,100,100);
  Point point4(1001,1001);

  EXPECT_NE(rect1.getClosestPointTo(point4), point4);
}


TEST(BoundingRectangleTests, getClosestPointToSpecial) {
  BoundingRectangle rect1(249,59,733,498);
  Point point1(982,557);
  Point point2(982,556);

  EXPECT_EQ(rect1.getClosestPointTo(point1), point1);
  EXPECT_EQ(rect1.getClosestPointTo(point2), point2);
}