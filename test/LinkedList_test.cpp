#include "catch/catch.hpp"
#include "../LinkedList.h"
#include <stdexcept>

SCENARIO("LinkedLists can be constructed", "[linkedlist]") {
    WHEN("a new LinkedList is constructed") {
        LinkedList<int> list;

        THEN("it is empty") {
            REQUIRE(list.length() == 0);
        }
    }

    GIVEN("an existing empty LinkedList") {
        LinkedList<int> existing;

        WHEN("a new LinkedList is constructed from the existing one") {
            LinkedList<int> newList(existing);

            THEN("the new list has length 0") {
                REQUIRE(newList.length() == 0);
            }
        }

        WHEN("a new LinkedList is set equal to the existing one") {
            LinkedList<int> newList = existing;

            THEN("the new list has length 0") {
                REQUIRE(newList.length() == 0);
            }
        }
    }

    GIVEN("an existing non-empty LinkedList") {
        LinkedList<int> existing;
        existing.add(3);
        existing.add(7);
        existing.add(2);
        
        WHEN("a new LinkedList is constructed from the existing one") {
            LinkedList<int> newList(existing);

            THEN("they have different memory addresses") {
                REQUIRE(&newList != &existing);
            }

            THEN("they have the same length") {
                REQUIRE(newList.length() == existing.length());
            }

            THEN("they have the same elements") {
                for (int i = 0; i < existing.length(); i++) {
                    REQUIRE(newList.get(i) == existing.get(i));
                }
            }

            AND_WHEN("the new list is modified") {
                newList.remove(1);

                THEN("the existing list is unchanged") {
                    REQUIRE(existing.length() == 3);
                    REQUIRE(existing.get(0) == 3);
                    REQUIRE(existing.get(1) == 7);
                    REQUIRE(existing.get(2) == 2);
                }
            }
        }

        WHEN("a new LinkedList is set equal to the existing one") {
            LinkedList<int> newList = existing;

            THEN("they have different memory addresses") {
                REQUIRE(&newList != &existing);
            }

            THEN("they have the same length") {
                REQUIRE(newList.length() == existing.length());
            }

            THEN("they have the same elements") {
                for (int i = 0; i < existing.length(); i++) {
                    REQUIRE(newList.get(i) == existing.get(i));
                }
            }

            AND_WHEN("the new list is modified") {
                newList.remove(1);

                THEN("the existing list is unchanged") {
                    REQUIRE(existing.length() == 3);
                    REQUIRE(existing.get(0) == 3);
                    REQUIRE(existing.get(1) == 7);
                    REQUIRE(existing.get(2) == 2);
                }
            }
        }
    }
}

SCENARIO("elements can be added to the end of a LinkedList", "[linkedlist]") {
    GIVEN("an empty LinkedList") {
        LinkedList<int> list;

        WHEN("an element is added") {
            list.add(4);

            THEN("the length increases by 1") {
                REQUIRE(list.length() == 1);
            }

            THEN("the element is added at index 0") {
                REQUIRE(list.get(0) == 4);
            }
        }
    }
    
    GIVEN("a non-empty LinkedList") {
        LinkedList<int> list;
        list.add(3);
        list.add(7);
        list.add(2);
        int oldLen = list.length();

        WHEN("an element is added") {
            list.add(5);

            THEN("the length increases by 1") {
                REQUIRE(list.length() == oldLen + 1);
            }

            THEN("it is added to the end of the list") {
                REQUIRE(list.get(oldLen) == 5);
            }

            THEN("the rest of the list remains the same") {
                REQUIRE(list.get(0) == 3);
                REQUIRE(list.get(1) == 7);
                REQUIRE(list.get(2) == 2);
            }
        }
    }
}

SCENARIO("elements can be added at an index in a LinkedList", "[linkedlist]") {
    GIVEN("a non-empty LinkedList") {
        LinkedList<int> list;
        list.add(3);
        list.add(7);
        list.add(2);
        int oldLen = list.length();

        WHEN("an element is added at an index < 0") {
            THEN("an out of range exception is thrown") {
                REQUIRE_THROWS_AS(list.add(-1, 0), std::out_of_range);
            }
        }

        WHEN("an element is added at an index > length") {
            THEN("an out of range exception is thrown") {
                REQUIRE_THROWS_AS(list.add(4, 0), std::out_of_range);
            }
        }

        WHEN("an element is added at index 0") {
            list.add(0, 5);

            THEN("the length increases by 1") {
                REQUIRE(list.length() == oldLen + 1);
            }

            THEN("it is added to the list") {
                REQUIRE(list.get(0) == 5);
            }

            THEN("the rest of the list is shifted") {
                REQUIRE(list.get(1) == 3);
                REQUIRE(list.get(2) == 7);
                REQUIRE(list.get(3) == 2);
            }
        }

        WHEN("an element is added at index length") {
            list.add(3, 5);

            THEN("the length increases by 1") {
                REQUIRE(list.length() == oldLen + 1);
            }

            THEN("it is added to the list") {
                REQUIRE(list.get(3) == 5);
            }

            THEN("the rest of the list stays the same") {
                REQUIRE(list.get(0) == 3);
                REQUIRE(list.get(1) == 7);
                REQUIRE(list.get(2) == 2);
            }
        }

        WHEN("an element is added in the middle of the list") {
            list.add(1, 5);

            THEN("the length increases by 1") {
                REQUIRE(list.length() == oldLen + 1);
            }

            THEN("it is added to the list") {
                REQUIRE(list.get(1) == 5);
            }

            THEN("the elements before the index stay the same") {
                REQUIRE(list.get(0) == 3);
            }

            THEN("the elements after the index shift up by one index") {
                REQUIRE(list.get(2) == 7);
                REQUIRE(list.get(3) == 2);
            }
        }
    }
}

SCENARIO("elements can be retrieved from a LinkedList", "[linkedlist]") {
    GIVEN("a non-empty LinkedList") {
        LinkedList<int> list;
        list.add(3);
        list.add(7);
        list.add(2);

        WHEN("the desired index is less than 0") {
            THEN("an out of range exception is thrown") {
                REQUIRE_THROWS_AS(list.get(-1), std::out_of_range);
            }
        }

        WHEN("the desired index is equal to the length") {
            THEN("an out of range exception is thrown") {
                REQUIRE_THROWS_AS(list.get(3), std::out_of_range);
            }
        }

        WHEN("the desired index is 0") {
            THEN("the element is returned") {
                REQUIRE(list.get(0) == 3);
            }
        }

        WHEN("the desired index is length - 1") {
            THEN("the element is returned") {
                REQUIRE(list.get(2) == 2);
            }
        }

        WHEN("the desired index is between 0 and length - 1") {
            THEN("the element is returned") {
                REQUIRE(list.get(1) == 7);
            }
        }
    }
}

SCENARIO("elements can be removed from a LinkedList", "[linkedlist]") {
    GIVEN("a non-empty LinkedList") {
        LinkedList<int> list;
        list.add(3);
        list.add(7);
        list.add(2);
        int oldLen = list.length();

        WHEN("the desired index is less than 0") {
            THEN("an out of range exception is thrown") {
                REQUIRE_THROWS_AS(list.remove(-1), std::out_of_range);
            }
        }

        WHEN("the desired index is equal to the length") {
            THEN("an out of range exception is thrown") {
                REQUIRE_THROWS_AS(list.remove(3), std::out_of_range);
            }
        }

        WHEN("the head is removed") {
            list.remove(0);

            THEN("the length decreases by 1") {
                REQUIRE(list.length() == oldLen - 1);
            }

            THEN("the rest of the list shifts down by 1 index") {
                REQUIRE(list.get(0) == 7);
                REQUIRE(list.get(1) == 2);
            }
        }

        WHEN("the tail is removed") {
            list.remove(2);

            THEN("the length decreases by 1") {
                REQUIRE(list.length() == oldLen - 1);
            }

            THEN("the rest of the list stays the same") {
                REQUIRE(list.get(0) == 3);
                REQUIRE(list.get(1) == 7);
            }
        }

        WHEN("a middle element is removed") {
            list.remove(1);

            THEN("the length decreases by 1") {
                REQUIRE(list.length() == oldLen - 1);
            }

            THEN("the previous elements of the list stay the same") {
                REQUIRE(list.get(0) == 3);
            }

            THEN("the following elements of the list shift down by 1 index") {
                REQUIRE(list.get(1) == 2);
            }
        }
    }
}

SCENARIO("elements can be changed in a LinkedList", "[linkedlist]") {
    GIVEN("a non-empty LinkedList") {
        LinkedList<int> list;
        list.add(3);
        list.add(7);
        list.add(2);

        WHEN("the desired index is less than 0") {
            THEN("an out of range exception is thrown") {
                REQUIRE_THROWS_AS(list.set(-1, 0), std::out_of_range);
            }
        }

        WHEN("the desired index is equal to the length") {
            THEN("an out of range exception is thrown") {
                REQUIRE_THROWS_AS(list.set(3, 0), std::out_of_range);
            }
        }

        WHEN("the desired index is 0") {
            list.set(0, 10);

            THEN("the element is changed") {
                REQUIRE(list.get(0) == 10);
            }
        }

        WHEN("the desired index is length - 1") {
            list.set(2, 10);

            THEN("the element is changed") {
                REQUIRE(list.get(2) == 10);
            }
        }

        WHEN("the desired index is between 0 and length - 1") {
            list.set(1, 10);

            THEN("the element is changed") {
                REQUIRE(list.get(1) == 10);
            }
        }
    }
}

SCENARIO("LinkedLists can be swapped", "[linkedlist]") {
    GIVEN("two non-empty LinkedLists") {
        LinkedList<int> list1;
        list1.add(1);
        list1.add(2);
        list1.add(3);

        LinkedList<int> list2;
        list2.add(5);
        list2.add(6);

        WHEN("the lists are swapped") {
            using std::swap;
            swap(list1, list2);

            THEN("the lengths are swapped") {
                REQUIRE(list1.length() == 2);
                REQUIRE(list2.length() == 3);
            }

            THEN("the elements are swapped") {
                REQUIRE(list1.get(0) == 5);
                REQUIRE(list1.get(1) == 6);
                REQUIRE(list2.get(0) == 1);
                REQUIRE(list2.get(1) == 2);
                REQUIRE(list2.get(2) == 3);
            }
        }
    }
}
