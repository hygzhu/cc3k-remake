#include <gtest/gtest.h>
#include <rectangle.h>


TEST(RectangleTests, SameRectanglesCollide) {
  Rectangle rect1(1000,1000,100,100);
  Rectangle rect2(1000,1000,100,100);
  EXPECT_TRUE(rect1.isCollidingWith(rect2));
  EXPECT_TRUE(rect2.isCollidingWith(rect1));
}

TEST(RectangleTests, RectanglesDontCollide) {
  Rectangle rect1(0,0,100,100);
  Rectangle rect2(1000,1000,100,100);
  EXPECT_FALSE(rect1.isCollidingWith(rect2));
  EXPECT_FALSE(rect2.isCollidingWith(rect1));
}

TEST(RectangleTests, RectanglesDoesCollideWithPoint) {
  Rectangle rect1(1000,1100,1,1);
  Rectangle rect2(1000,1000,100,100);
  EXPECT_FALSE(rect1.isCollidingWith(rect2));
  EXPECT_FALSE(rect2.isCollidingWith(rect1));
}

TEST(RectangleTests, RectanglesDoesCollideWithActualPoint) {
  Point point1(1000,1000);
  Point point2(1000,1100);
  Point point3(1100,1000);
  Point point4(1100,1100);
  Point point5(0,0);
  Rectangle rect1(1000,1000,100,100);
  EXPECT_TRUE(rect1.isCollidingWithPoint(point1));
  EXPECT_TRUE(rect1.isCollidingWithPoint(point2));
  EXPECT_TRUE(rect1.isCollidingWithPoint(point3));
  EXPECT_TRUE(rect1.isCollidingWithPoint(point4));
  EXPECT_FALSE(rect1.isCollidingWithPoint(point5));
}



TEST(RectangleTests, getClosestPointTo) {
  Rectangle rect1(1000,1000,100,100);
  Point point1(1000,1000);
  Point point2(1100,1100);
  Point point3(1150,1150);

  EXPECT_EQ(rect1.getClosestPointTo(point1), point1);
  EXPECT_EQ(rect1.getClosestPointTo(point2), point2);
  EXPECT_EQ(rect1.getClosestPointTo(point3), point2);
}


TEST(RectangleTests, getClosestPointToInside) {
  Rectangle rect1(1000,1000,100,100);
  Point point4(1001,1001);

  EXPECT_NE(rect1.getClosestPointTo(point4), point4);
}


TEST(RectangleTests, getClosestPointToSpecial) {
  Rectangle rect1(249,59,733,498);
  Point point1(982,557);
  Point point2(982,556);

  EXPECT_EQ(rect1.getClosestPointTo(point1), point1);
  EXPECT_EQ(rect1.getClosestPointTo(point2), point2);
}