// Project UID db1f506d06d84ab787baf250c265e24e

#include "BinarySearchTree.h"
#include "unit_test_framework.h"

bool compare_trees (BinarySearchTree<int> one, BinarySearchTree<int> two);


TEST(public_test) {
    BinarySearchTree<int> tree;
    
    tree.insert(5);
    
    ASSERT_TRUE(tree.size() == 1);
    ASSERT_TRUE(tree.height() == 1);
    
    ASSERT_TRUE(tree.find(5) != tree.end());
    
    tree.insert(7);
    tree.insert(3);
    
    ASSERT_TRUE(tree.check_sorting_invariant());
    ASSERT_TRUE(*tree.max_element() == 7);
    ASSERT_TRUE(*tree.min_element() == 3);
    ASSERT_TRUE(*tree.min_greater_than(5) == 7);
    
    std::ostringstream oss_preorder;
    tree.traverse_preorder(oss_preorder);
    ASSERT_TRUE(oss_preorder.str() == "5 3 7 ");
    
    std::ostringstream oss_inorder;
    tree.traverse_inorder(oss_inorder);
    ASSERT_TRUE(oss_inorder.str() == "3 5 7 ");
}

TEST(duplicate) {
    // Add your tests here
    BinarySearchTree<int> tree;
    
    tree.insert(7);
    tree.insert(9);
    tree.insert(5);
    tree.insert(4);
   
}

TEST(smalltree) {
    // Add your tests here
    BinarySearchTree<int> tree;
    
    tree.insert(5);
    tree.insert(7);
    tree.insert(3);
    BinarySearchTree<int>tree2(tree);

    
    ASSERT_EQUAL(*tree2.find(3), 3);
    ASSERT_EQUAL(*tree2.find(5), 5);
    ASSERT_EQUAL(*tree2.find(7), 7);
    std::ostringstream oss_inorder;
    tree.traverse_inorder(oss_inorder);
    ASSERT_TRUE(oss_inorder.str() == "3 5 7 ");

    std::ostringstream oss_inorder2;
    tree2.traverse_inorder(oss_inorder2);
    ASSERT_TRUE(oss_inorder2.str() == "3 5 7 ");
    ASSERT_TRUE(oss_inorder.str() == oss_inorder2.str());
}

TEST(test1) {
    // Add your tests here
    BinarySearchTree<int> tree;
    
    tree.insert(5);
    
    ASSERT_TRUE(tree.size() == 1);
    ASSERT_TRUE(tree.height() == 1);
    
    ASSERT_TRUE(tree.find(5) != tree.end());
    
    tree.insert(7);
    tree.insert(3);
    tree.insert(4);
    tree.insert(6);
    
    ASSERT_TRUE(tree.check_sorting_invariant());
    ASSERT_TRUE(*tree.max_element() == 7);
    ASSERT_TRUE(*tree.min_element() == 3);
    ASSERT_TRUE(*tree.min_greater_than(5) == 6);
    ASSERT_TRUE(*tree.find(3) == 3);
}

TEST(test2) {
    // Add your tests here
    BinarySearchTree<int> tree;
    
    tree.insert(10);
    
    ASSERT_EQUAL(tree.empty(), 0);
    ASSERT_TRUE(tree.size() == 1);
    ASSERT_TRUE(tree.height() == 1);
    
    ASSERT_TRUE(tree.find(10) != tree.end());
    
    tree.insert(5);
    tree.insert(1);
    tree.insert(2);
    
    ASSERT_TRUE(tree.check_sorting_invariant());
    ASSERT_TRUE(*tree.max_element() == 10);
    ASSERT_TRUE(*tree.min_element() == 1);
    ASSERT_TRUE(*tree.min_greater_than(5) == 10);
    
}

TEST(test3) {
    // Add your tests here
    BinarySearchTree<int> tree;
    ASSERT_EQUAL(tree.empty(), 1);
    ASSERT_TRUE(tree.size() == 0);
    ASSERT_TRUE(tree.height() == 0);
    tree.insert(10);
    
    tree.insert(12);
    tree.insert(1);
    tree.insert(2);
    ASSERT_TRUE(tree.size() == 4);
    
    ASSERT_TRUE(tree.check_sorting_invariant());
    
    BinarySearchTree<int>tree2(tree);
    ASSERT_TRUE(compare_trees(tree, tree2));
    
}

TEST(testingNULL) {
    // Add your tests here
    BinarySearchTree<int> tree;
    
    BinarySearchTree<int> one;
    BinarySearchTree<int>::Iterator it1 = one.begin();
    ASSERT_TRUE(tree.min_greater_than(12) == it1);
    ASSERT_TRUE(tree.find(5) == it1);

    ASSERT_TRUE(tree.max_element() == it1);
    ASSERT_TRUE(tree.min_element() == it1);
    tree.insert(10);
    
    tree.insert(12);
    tree.insert(1);
    tree.insert(2);
    ASSERT_TRUE(tree.min_greater_than(12) == it1);
    ASSERT_TRUE(tree.find(5) == it1);
}

TEST(check_sort1) {
    BinarySearchTree<int> tree;
    tree.insert(10);
    BinarySearchTree<int>::Iterator it1 = tree.begin();
    tree.insert(5);
    *it1 = 2;
    ASSERT_FALSE(tree.check_sorting_invariant());
}

TEST(check_sort2) {
    BinarySearchTree<int> tree;
    tree.insert(2);
    BinarySearchTree<int>::Iterator it1 = tree.begin();
    tree.insert(5);
    *it1 = 10;
    ASSERT_FALSE(tree.check_sorting_invariant());
}

TEST(check_sort3) {
    BinarySearchTree<int> tree;
    tree.insert(5);
    tree.insert(7);
    tree.insert(3);
    tree.insert(4);
    BinarySearchTree<int>::Iterator it1 = tree.find(4);
    *it1 = 6;
    ASSERT_FALSE(tree.check_sorting_invariant());
}

TEST(check_sort4) {
    BinarySearchTree<int> tree;
    tree.insert(5);
    tree.insert(7);
    tree.insert(3);
    tree.insert(8);
    BinarySearchTree<int>::Iterator it1 = tree.find(8);
    *it1 = 6;
    ASSERT_FALSE(tree.check_sorting_invariant());
}

TEST(check_sort_long) {
    BinarySearchTree<int> tree;
    tree.insert(7);
    tree.insert(3);
    tree.insert(12);
    tree.insert(11);
    tree.insert(2);
    tree.insert(5);
    tree.insert(10);
    tree.insert(4);
    tree.insert(9);
    tree.insert(6);
    BinarySearchTree<int>::Iterator it1 = tree.find(6);
    *it1 = 8;
    BinarySearchTree<int>::Iterator it2 = tree.find(9);
    *it2 = 6;
    ASSERT_FALSE(tree.check_sorting_invariant());
}

bool compare_trees (BinarySearchTree<int> one, BinarySearchTree<int> two) {
    if (one.size() != two.size()) {
        return false;
    }
    if (one.size() == 0 && two.size() == 0) {
        return true;
    }
    BinarySearchTree<int>::Iterator it1 = one.begin();
    
    for (BinarySearchTree<int>::Iterator it2 = two.begin(); it2 != two.end(); ++it2) {
        if (*it2 != *it1) {
            return false;
        }
        ++it1;
    }
    return true;
}



TEST_MAIN()
