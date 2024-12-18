// #include <gtest/gtest.h>
// #include "main.h"  // Include the source file where the manageCatalog function is defined

// TEST(ManageCatalogTest, RestockItem) {
//   // Arrange
//   std::vector<Item> catalog = {{"Product A", 10, 0}};
//   std::string item = "Product A";

//   // Act
//   manageCatalog(catalog);
//   int index = findItemIndex(catalog, item);
//   catalog[index].stock = 0;  // Simulate item being out of stock
//   manageCatalog(catalog);

//   // Assert
//   EXPECT_EQ(catalog[index].stock, 5);  // Assuming restocking adds 5 items
// }