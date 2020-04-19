#include <iostream>
#include <list>
#include "Merge.hpp"

void printSet(const std::list<int> &S)
{
    std::cout << "( ";
    for (int i : S)
    {
        std::cout << i << ' ';
    }
    std::cout << ")\n";
}

int main()
{
    std::list<int> set1({2, 3, 4, 5, 6, 7, 8});
    std::list<int> set2({6, 7, 8, 9, 10, 11, 12});
    std::list<int> set1_Union_set2;
    std::list<int> set1_Subtract_set2;
    std::list<int> set1_Intersect_set2;
    IntersectMerge<int> setIntersect;
    UnionMerge<int> setUnion;
    SubtractMerge<int> setSubtract;

    std::cout << "Set 1\n";
    printSet(set1);
    std::cout << "\nSet 2\n";
    printSet(set2);
    std::cout << "\nUnion of set 1 and set 2\n";
    setUnion.merge(set1, set2, set1_Union_set2);
    printSet(set1_Union_set2);
    std::cout << "\nSet 1 subtract Set 2\n";
    setSubtract.merge(set1, set2, set1_Subtract_set2);
    printSet(set1_Subtract_set2);
    std::cout << "\nSet 1 intersect Set 2\n";
    setIntersect.merge(set1, set2, set1_Intersect_set2);
    printSet(set1_Intersect_set2);
}
