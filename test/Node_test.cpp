#include "catch/catch.hpp"
#include "../Node.h"

SCENARIO("Node constructors work", "[node]") {
    
    GIVEN("A new Node") {
        Node<int> *n;

        WHEN("constructed with value only") {
            int value = 5;
            n = new Node(value);

            THEN("its value is set") {
                REQUIRE(n->value == value);
            }

            AND_THEN("its next is set to nullptr") {
                REQUIRE(n->next == nullptr);
            }
        }

        WHEN("constructed with value and next") {
            int value = 5;
            Node<int> *next = new Node(2);
            n = new Node(value, next);

            THEN("its value is set") {
                REQUIRE(n->value == value);
            }

            AND_THEN("its next is set") {
                REQUIRE(n->next == next);
            }

            delete next;
        }

        delete n;
    }
}
