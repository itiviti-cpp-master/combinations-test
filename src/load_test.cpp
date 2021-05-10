#include "Combinations.h"
#include "Component.h"

#include <gtest/gtest.h>

#include <random>
#include <thread>
#include <vector>

namespace {

const std::vector<std::vector<Component>> test_data = {
    {
        Component::from_string("F 1 2010-03-01"),
        Component::from_string("F -1 2010-03-01"),
    },
    {
        Component::from_string("F -1 2010-03-01"),
        Component::from_string("F 1 2010-03-01"),
    },
    {
        Component::from_string("F 1 2010-03-01"),
        Component::from_string("F -1 2010-03-02"),
    },
    {
        Component::from_string("F -1 2010-03-02"),
        Component::from_string("F 1 2010-03-01"),
    },
    {
        Component::from_string("F 1 2010-03-01"),
        Component::from_string("F -2 2010-03-02"),
        Component::from_string("F 1 2010-03-03"),
    },
    {
        Component::from_string("F 1 2010-03-03"),
        Component::from_string("F -2 2010-03-02"),
        Component::from_string("F 1 2010-03-01"),
    },
    {
        Component::from_string("F -2 2010-03-02"),
        Component::from_string("F 1 2010-03-03"),
        Component::from_string("F 1 2010-03-01"),
    },
    {
        Component::from_string("F 1 2010-03-01"),
        Component::from_string("F -1 2010-03-02"),
        Component::from_string("F -1 2010-03-03"),
        Component::from_string("F 1 2010-03-04"),
    },
    {
        Component::from_string("F 1 2010-03-04"),
        Component::from_string("F -1 2010-03-03"),
        Component::from_string("F -1 2010-03-02"),
        Component::from_string("F 1 2010-03-01"),
    },
    {
        Component::from_string("F 1 2010-03-01"),
        Component::from_string("F -1 2010-03-03"),
        Component::from_string("F 1 2010-03-04"),
        Component::from_string("F -1 2010-03-02"),
    },
    {
        Component::from_string("F 1 2010-03-01"),
        Component::from_string("F 1 2010-06-01"),
        Component::from_string("F 1 2010-09-01"),
        Component::from_string("F 1 2010-12-01"),
    },
    {
        Component::from_string("F 1 2010-12-01"),
        Component::from_string("F 1 2010-09-01"),
        Component::from_string("F 1 2010-06-01"),
        Component::from_string("F 1 2010-03-01"),
    },
    {
        Component::from_string("F 1 2010-09-01"),
        Component::from_string("F 1 2010-12-01"),
        Component::from_string("F 1 2010-03-01"),
        Component::from_string("F 1 2010-06-01"),
    },
    {
        Component::from_string("F 1 2010-03-01"),
        Component::from_string("F 1 2010-06-01"),
        Component::from_string("F 1 2010-09-01"),
        Component::from_string("F 1 2010-12-01"),
        Component::from_string("F 1 2010-03-01"),
        Component::from_string("F 1 2010-06-01"),
        Component::from_string("F 1 2010-09-01"),
        Component::from_string("F 1 2010-12-01"),
    },
    {
        Component::from_string("F 1 2010-12-01"),
        Component::from_string("F 1 2010-09-01"),
        Component::from_string("F 1 2010-06-01"),
        Component::from_string("F 1 2010-03-01"),
        Component::from_string("F 1 2010-12-01"),
        Component::from_string("F 1 2010-09-01"),
        Component::from_string("F 1 2010-06-01"),
        Component::from_string("F 1 2010-03-01"),
    },
    {
        Component::from_string("F 1 2010-03-01"),
        Component::from_string("F 1 2010-03-01"),
        Component::from_string("F 1 2010-06-01"),
        Component::from_string("F 1 2010-09-01"),
        Component::from_string("F 1 2010-06-01"),
        Component::from_string("F 1 2010-09-01"),
        Component::from_string("F 1 2010-12-01"),
        Component::from_string("F 1 2010-12-01"),
    },
    {
        Component::from_string("F 10 2010-03-01"),
        Component::from_string("F 10 2010-03-01"),
        Component::from_string("F 10 2010-03-01"),
        Component::from_string("F 10 2010-03-01"),
        Component::from_string("F 10 2010-03-01"),
        Component::from_string("F 10 2010-03-01"),
    },
    {
        Component::from_string("C -1 2000 2010-03-01"),
        Component::from_string("P 1 2000 2010-03-01"),
        Component::from_string("C 1 2100 2010-03-02"),
        Component::from_string("P -1 2100 2010-03-02"),
    },
    {
        Component::from_string("P -1 2100 2010-03-02"),
        Component::from_string("C 1 2100 2010-03-02"),
        Component::from_string("P 1 2000 2010-03-01"),
        Component::from_string("C -1 2000 2010-03-01"),
    },
    {
        Component::from_string("P 1 2000 2010-03-01"),
        Component::from_string("C -1 2000 2010-03-01"),
        Component::from_string("P -1 2100 2010-03-02"),
        Component::from_string("C 1 2100 2010-03-02"),
    },
    {
        Component::from_string("C 1 2000 2010-03-01"),
        Component::from_string("C -2 2100 2010-03-01"),
        Component::from_string("C 1 2200 2010-03-01"),
    },
    {
        Component::from_string("C 1 2200 2010-03-01"),
        Component::from_string("C -2 2100 2010-03-01"),
        Component::from_string("C 1 2000 2010-03-01"),
    },
    {
        Component::from_string("C -2 2100 2010-03-01"),
        Component::from_string("C 1 2000 2010-03-01"),
        Component::from_string("C 1 2200 2010-03-01"),
    },
    {
        Component::from_string("C 1 2000 2010-03-01"),
        Component::from_string("C -2 2000 2010-03-02"),
        Component::from_string("C 1 2000 2010-03-03"),
    },
    {
        Component::from_string("C 1 2000 2010-03-03"),
        Component::from_string("C -2 2000 2010-03-02"),
        Component::from_string("C 1 2000 2010-03-01"),
    },
    {
        Component::from_string("C -2 2000 2010-03-02"),
        Component::from_string("C 1 2000 2010-03-01"),
        Component::from_string("C 1 2000 2010-03-03"),
    },
    {
        Component::from_string("C 1 2000 2010-03-01"),
        Component::from_string("C -1 2100 2010-03-01"),
        Component::from_string("C 1 2200 2010-03-01"),
    },
    {
        Component::from_string("C 1 2200 2010-03-01"),
        Component::from_string("C -1 2100 2010-03-01"),
        Component::from_string("C 1 2000 2010-03-01"),
    },
    {
        Component::from_string("C 1 2200 2010-03-01"),
        Component::from_string("C 1 2000 2010-03-01"),
        Component::from_string("C -1 2100 2010-03-01"),
    },
    {
        Component::from_string("P 1 2000 2010-03-01"),
        Component::from_string("P -2 2100 2010-03-01"),
        Component::from_string("P 1 2200 2010-03-01"),
    },
    {
        Component::from_string("P 1 2200 2010-03-01"),
        Component::from_string("P -2 2100 2010-03-01"),
        Component::from_string("P 1 2000 2010-03-01"),
    },
    {
        Component::from_string("P -2 2100 2010-03-01"),
        Component::from_string("P 1 2200 2010-03-01"),
        Component::from_string("P 1 2000 2010-03-01"),
    },
    {
        Component::from_string("P 1 2000 2010-03-01"),
        Component::from_string("P -2 2000 2010-03-02"),
        Component::from_string("P 1 2000 2010-03-03"),
    },
    {
        Component::from_string("P 1 2000 2010-03-03"),
        Component::from_string("P -2 2000 2010-03-02"),
        Component::from_string("P 1 2000 2010-03-01"),
    },
    {
        Component::from_string("P -2 2000 2010-03-02"),
        Component::from_string("P 1 2000 2010-03-03"),
        Component::from_string("P 1 2000 2010-03-01"),
    },
    {
        Component::from_string("P 1 2000 2010-03-01"),
        Component::from_string("P -1 2100 2010-03-01"),
        Component::from_string("P 1 2200 2010-03-01"),
    },
    {
        Component::from_string("P 1 2200 2010-03-01"),
        Component::from_string("P -1 2100 2010-03-01"),
        Component::from_string("P 1 2000 2010-03-01"),
    },
    {
        Component::from_string("P -1 2100 2010-03-01"),
        Component::from_string("P 1 2000 2010-03-01"),
        Component::from_string("P 1 2200 2010-03-01"),
    },
    {
        Component::from_string("C 1 2000 2010-03-01"),
        Component::from_string("C -1 2100 2010-03-01"),
    },
    {
        Component::from_string("C -1 2100 2010-03-01"),
        Component::from_string("C 1 2000 2010-03-01"),
    },
    {
        Component::from_string("P 1 2000 2010-03-01"),
        Component::from_string("P -1 1900 2010-03-01"),
    },
    {
        Component::from_string("P -1 1900 2010-03-01"),
        Component::from_string("P 1 2000 2010-03-01"),
    },
    {
        Component::from_string("C -1 2000 2010-03-01"),
        Component::from_string("C 1 2000 2010-03-02"),
    },
    {
        Component::from_string("C 1 2000 2010-03-02"),
        Component::from_string("C -1 2000 2010-03-01"),
    },
    {
        Component::from_string("P -1 2000 2010-03-01"),
        Component::from_string("P 1 2000 2010-03-02"),
    },
    {
        Component::from_string("P 1 2000 2010-03-02"),
        Component::from_string("P -1 2000 2010-03-01"),
    },
    {
        Component::from_string("C -1 2000 2010-03-01"),
        Component::from_string("C 1 2100 2010-03-02"),
    },
    {
        Component::from_string("C 1 2100 2010-03-02"),
        Component::from_string("C -1 2000 2010-03-01"),
    },
    {
        Component::from_string("P -1 2000 2010-03-01"),
        Component::from_string("P 1 2100 2010-03-02"),
    },
    {
        Component::from_string("P 1 2100 2010-03-02"),
        Component::from_string("P -1 2000 2010-03-01"),
    },
    {
        Component::from_string("C 1 2000 2010-03-01"),
        Component::from_string("P 1 2100 2010-03-01"),
    },
    {
        Component::from_string("P 1 2100 2010-03-01"),
        Component::from_string("C 1 2000 2010-03-01"),
    },
    {
        Component::from_string("C -1 2000 2010-03-01"),
        Component::from_string("C 2 2100 2010-03-01"),
    },
    {
        Component::from_string("C 2 2100 2010-03-01"),
        Component::from_string("C -1 2000 2010-03-01"),
    },
    {
        Component::from_string("C -1 2000 2010-03-01"),
        Component::from_string("C 3 2100 2010-03-01"),
    },
    {
        Component::from_string("C 3 2100 2010-03-01"),
        Component::from_string("C -1 2000 2010-03-01"),
    },
    {
        Component::from_string("C 1 2000 2010-03-01"),
        Component::from_string("C -2 2100 2010-03-01"),
    },
    {
        Component::from_string("C -2 2100 2010-03-01"),
        Component::from_string("C 1 2000 2010-03-01"),
    },
    {
        Component::from_string("C 1 2000 2010-03-01"),
        Component::from_string("C -3 2100 2010-03-01"),
    },
    {
        Component::from_string("C -3 2100 2010-03-01"),
        Component::from_string("C 1 2000 2010-03-01"),
    },
    {
        Component::from_string("C 2 2000 2010-03-01"),
        Component::from_string("C -3 2100 2010-03-01"),
    },
    {
        Component::from_string("C -3 2100 2010-03-01"),
        Component::from_string("C 2 2000 2010-03-01"),
    },
    {
        Component::from_string("P -1 2000 2010-03-01"),
        Component::from_string("P 2 1900 2010-03-01"),
    },
    {
        Component::from_string("P 2 1900 2010-03-01"),
        Component::from_string("P -1 2000 2010-03-01"),
    },
    {
        Component::from_string("P -1 2000 2010-03-01"),
        Component::from_string("P 3 1900 2010-03-01"),
    },
    {
        Component::from_string("P 3 1900 2010-03-01"),
        Component::from_string("P -1 2000 2010-03-01"),
    },
    {
        Component::from_string("P 1 2000 2010-03-01"),
        Component::from_string("P -2 1900 2010-03-01"),
    },
    {
        Component::from_string("P -2 1900 2010-03-01"),
        Component::from_string("P 1 2000 2010-03-01"),
    },
    {
        Component::from_string("P 1 2000 2010-03-01"),
        Component::from_string("P -3 1900 2010-03-01"),
    },
    {
        Component::from_string("P -3 1900 2010-03-01"),
        Component::from_string("P 1 2000 2010-03-01"),
    },
    {
        Component::from_string("P 2 2000 2010-03-01"),
        Component::from_string("P -3 1900 2010-03-01"),
    },
    {
        Component::from_string("P -3 1900 2010-03-01"),
        Component::from_string("P 2 2000 2010-03-01"),
    },
    {
        Component::from_string("P -1 2000 2010-03-01"),
        Component::from_string("P 1 2100 2010-03-01"),
        Component::from_string("C 1 2100 2010-03-01"),
        Component::from_string("C -1 2200 2010-03-01"),
    },
    {
        Component::from_string("C -1 2200 2010-03-01"),
        Component::from_string("C 1 2100 2010-03-01"),
        Component::from_string("P 1 2100 2010-03-01"),
        Component::from_string("P -1 2000 2010-03-01"),
    },
    {
        Component::from_string("C 1 2100 2010-03-01"),
        Component::from_string("C -1 2200 2010-03-01"),
        Component::from_string("P -1 2000 2010-03-01"),
        Component::from_string("P 1 2100 2010-03-01"),
    },
    {
        Component::from_string("C -1 2000 2010-03-01"),
        Component::from_string("P 1 1900 2010-03-01"),
    },
    {
        Component::from_string("P 1 1900 2010-03-01"),
        Component::from_string("C -1 2000 2010-03-01"),
    },
    {
        Component::from_string("P 1 2000 2010-03-01"),
        Component::from_string("C 1 2100 2010-03-01"),
    },
    {
        Component::from_string("C 1 2100 2010-03-01"),
        Component::from_string("P 1 2000 2010-03-01"),
    },
    {
        Component::from_string("C 1 2000 2010-03-01"),
        Component::from_string("C -1 2100 2010-03-01"),
        Component::from_string("C -1 2200 2010-03-01"),
    },
    {
        Component::from_string("C -1 2200 2010-03-01"),
        Component::from_string("C -1 2100 2010-03-01"),
        Component::from_string("C 1 2000 2010-03-01"),
    },
    {
        Component::from_string("C -1 2100 2010-03-01"),
        Component::from_string("C -1 2200 2010-03-01"),
        Component::from_string("C 1 2000 2010-03-01"),
    },
    {
        Component::from_string("P -1 2000 2010-03-01"),
        Component::from_string("P -1 2100 2010-03-01"),
        Component::from_string("P 1 2200 2010-03-01"),
    },
    {
        Component::from_string("P 1 2200 2010-03-01"),
        Component::from_string("P -1 2100 2010-03-01"),
        Component::from_string("P -1 2000 2010-03-01"),
    },
    {
        Component::from_string("P 1 2200 2010-03-01"),
        Component::from_string("P -1 2000 2010-03-01"),
        Component::from_string("P -1 2100 2010-03-01"),
    },
    {
        Component::from_string("P -1 2000 2010-03-01"),
        Component::from_string("C -1 2000 2010-03-01"),
        Component::from_string("P 1 2000 2010-03-02"),
        Component::from_string("C 1 2000 2010-03-02"),
    },
    {
        Component::from_string("C 1 2000 2010-03-02"),
        Component::from_string("P 1 2000 2010-03-02"),
        Component::from_string("C -1 2000 2010-03-01"),
        Component::from_string("P -1 2000 2010-03-01"),
    },
    {
        Component::from_string("C -1 2000 2010-03-01"),
        Component::from_string("P -1 2000 2010-03-01"),
        Component::from_string("C 1 2000 2010-03-02"),
        Component::from_string("P 1 2000 2010-03-02"),
    },
    {
        Component::from_string("P -1 2000 2010-03-01"),
        Component::from_string("C -1 2000 2010-03-01"),
        Component::from_string("P 1 2100 2010-03-02"),
        Component::from_string("C 1 2100 2010-03-02"),
    },
    {
        Component::from_string("C 1 2100 2010-03-02"),
        Component::from_string("P 1 2100 2010-03-02"),
        Component::from_string("C -1 2000 2010-03-01"),
        Component::from_string("P -1 2000 2010-03-01"),
    },
    {
        Component::from_string("C 1 2100 2010-03-02"),
        Component::from_string("P 1 2100 2010-03-02"),
        Component::from_string("P -1 2000 2010-03-01"),
        Component::from_string("C -1 2000 2010-03-01"),
    },
    {
        Component::from_string("P 1 2000 2010-03-01"),
        Component::from_string("C 1 2000 2010-03-01"),
    },
    {
        Component::from_string("C 1 2000 2010-03-01"),
        Component::from_string("P 1 2000 2010-03-01"),
    },
    {
        Component::from_string("C 1 2000 2010-03-01"),
        Component::from_string("C -1 2100 2010-03-01"),
        Component::from_string("C -1 2200 2010-03-01"),
        Component::from_string("C 1 2300 2010-03-01"),
    },
    {
        Component::from_string("C 1 2300 2010-03-01"),
        Component::from_string("C -1 2200 2010-03-01"),
        Component::from_string("C -1 2100 2010-03-01"),
        Component::from_string("C 1 2000 2010-03-01"),
    },
    {
        Component::from_string("C -1 2100 2010-03-01"),
        Component::from_string("C 1 2300 2010-03-01"),
        Component::from_string("C -1 2200 2010-03-01"),
        Component::from_string("C 1 2000 2010-03-01"),
    },
    {
        Component::from_string("P 1 2000 2010-03-01"),
        Component::from_string("P -1 2100 2010-03-01"),
        Component::from_string("P -1 2200 2010-03-01"),
        Component::from_string("P 1 2300 2010-03-01"),
    },
    {
        Component::from_string("P 1 2300 2010-03-01"),
        Component::from_string("P -1 2200 2010-03-01"),
        Component::from_string("P -1 2100 2010-03-01"),
        Component::from_string("P 1 2000 2010-03-01"),
    },
    {
        Component::from_string("P 1 2000 2010-03-01"),
        Component::from_string("P -1 2200 2010-03-01"),
        Component::from_string("P -1 2100 2010-03-01"),
        Component::from_string("P 1 2300 2010-03-01"),
    },
    {
        Component::from_string("C 1 2000 2010-03-01"),
        Component::from_string("P -1 2000 2010-03-01"),
        Component::from_string("P 1 2100 2010-03-01"),
        Component::from_string("C -1 2100 2010-03-01"),
    },
    {
        Component::from_string("C -1 2100 2010-03-01"),
        Component::from_string("P 1 2100 2010-03-01"),
        Component::from_string("P -1 2000 2010-03-01"),
        Component::from_string("C 1 2000 2010-03-01"),
    },
    {
        Component::from_string("P -1 2000 2010-03-01"),
        Component::from_string("P 1 2100 2010-03-01"),
        Component::from_string("C -1 2100 2010-03-01"),
        Component::from_string("C 1 2000 2010-03-01"),
    },
    {
        Component::from_string("C 1 2000 2010-03-01"),
        Component::from_string("P -1 2000 2010-03-01"),
    },
    {
        Component::from_string("P -1 2000 2010-03-01"),
        Component::from_string("C 1 2000 2010-03-01"),
    },
    {
        Component::from_string("C 1 2000 2010-03-01"),
        Component::from_string("P -1 1900 2010-03-01"),
    },
    {
        Component::from_string("P -1 1900 2010-03-01"),
        Component::from_string("C 1 2000 2010-03-01"),
    },
    {
        Component::from_string("P -1 2000 2010-03-01"),
        Component::from_string("P 1 2100 2010-03-01"),
        Component::from_string("C 1 2200 2010-03-01"),
        Component::from_string("C -1 2300 2010-03-01"),
    },
    {
        Component::from_string("C -1 2300 2010-03-01"),
        Component::from_string("C 1 2200 2010-03-01"),
        Component::from_string("P 1 2100 2010-03-01"),
        Component::from_string("P -1 2000 2010-03-01"),
    },
    {
        Component::from_string("C -1 2300 2010-03-01"),
        Component::from_string("P 1 2100 2010-03-01"),
        Component::from_string("P -1 2000 2010-03-01"),
        Component::from_string("C 1 2200 2010-03-01"),
    },
    {
        Component::from_string("C 1 2000 2010-03-01"),
        Component::from_string("C -1 2100 2010-03-01"),
        Component::from_string("P -1 2000 2010-03-01"),
    },
    {
        Component::from_string("P -1 2000 2010-03-01"),
        Component::from_string("C -1 2100 2010-03-01"),
        Component::from_string("C 1 2000 2010-03-01"),
    },
    {
        Component::from_string("C 1 2000 2010-03-01"),
        Component::from_string("P -1 2000 2010-03-01"),
        Component::from_string("C -1 2100 2010-03-01"),
    },
    {
        Component::from_string("P 1 2000 2010-03-01"),
        Component::from_string("P -1 1900 2010-03-01"),
        Component::from_string("C -1 2000 2010-03-01"),
    },
    {
        Component::from_string("C -1 2000 2010-03-01"),
        Component::from_string("P -1 1900 2010-03-01"),
        Component::from_string("P 1 2000 2010-03-01"),
    },
    {
        Component::from_string("P 1 2000 2010-03-01"),
        Component::from_string("C -1 2000 2010-03-01"),
        Component::from_string("P -1 1900 2010-03-01"),
    },
    {
        Component::from_string("P 1 2000 2010-03-01"),
        Component::from_string("C 1 2000 2010-03-01"),
        Component::from_string("C -1 2000 2010-03-01"),
    },
    {
        Component::from_string("C -1 2000 2010-03-01"),
        Component::from_string("C 1 2000 2010-03-01"),
        Component::from_string("P 1 2000 2010-03-01"),
    },
    {
        Component::from_string("C 1 2000 2010-03-01"),
        Component::from_string("C -1 2000 2010-03-01"),
        Component::from_string("P 1 2000 2010-03-01"),
    },
    {
        Component::from_string("P 1 2000 2010-03-01"),
        Component::from_string("C 1 2000 2010-03-01"),
        Component::from_string("P -1 2000 2010-03-01"),
    },
    {
        Component::from_string("P -1 2000 2010-03-01"),
        Component::from_string("C 1 2000 2010-03-01"),
        Component::from_string("P 1 2000 2010-03-01"),
    },
    {
        Component::from_string("P -1 2000 2010-03-01"),
        Component::from_string("P 1 2000 2010-03-01"),
        Component::from_string("C 1 2000 2010-03-01"),
    },
    {
        Component::from_string("C 1 2000 2010-03-01"),
        Component::from_string("C 1 2100 2010-03-01"),
    },
    {
        Component::from_string("C 1 2100 2010-03-01"),
        Component::from_string("C 1 2000 2010-03-01"),
    },
    {
        Component::from_string("P 1 2000 2010-03-01"),
        Component::from_string("P 1 1900 2010-03-01"),
    },
    {
        Component::from_string("P 1 1900 2010-03-01"),
        Component::from_string("P 1 2000 2010-03-01"),
    },
    {
        Component::from_string("C 1 2000 2010-03-01"),
        Component::from_string("P 1 2000 2010-03-01"),
        Component::from_string("C 1 2000 2010-06-01"),
        Component::from_string("P 1 2000 2010-06-01"),
        Component::from_string("C 1 2000 2010-09-01"),
        Component::from_string("P 1 2000 2010-09-01"),
        Component::from_string("C 1 2000 2010-12-01"),
        Component::from_string("P 1 2000 2010-12-01"),
    },
    {
        Component::from_string("P 1 2000 2010-12-01"),
        Component::from_string("C 1 2000 2010-12-01"),
        Component::from_string("P 1 2000 2010-09-01"),
        Component::from_string("C 1 2000 2010-09-01"),
        Component::from_string("P 1 2000 2010-06-01"),
        Component::from_string("C 1 2000 2010-06-01"),
        Component::from_string("P 1 2000 2010-03-01"),
        Component::from_string("C 1 2000 2010-03-01"),
    },
    {
        Component::from_string("C 1 2000 2010-09-01"),
        Component::from_string("P 1 2000 2010-03-01"),
        Component::from_string("P 1 2000 2010-06-01"),
        Component::from_string("C 1 2000 2010-06-01"),
        Component::from_string("P 1 2000 2010-09-01"),
        Component::from_string("P 1 2000 2010-12-01"),
        Component::from_string("C 1 2000 2010-12-01"),
        Component::from_string("C 1 2000 2010-03-01"),
    },
    {
        Component::from_string("O 1 2000 2010-03-01"),
        Component::from_string("O 1 2000 2010-03-01"),
        Component::from_string("O 1 2000 2010-03-01"),
        Component::from_string("O 1 2000 2010-03-01"),
        Component::from_string("O 1 2000 2010-03-01"),
        Component::from_string("O 1 2000 2010-03-01"),
        Component::from_string("O 1 2000 2010-03-01"),
        Component::from_string("O 1 2000 2010-03-01"),
        Component::from_string("O 1 2000 2010-03-01"),
    },
    {
        Component::from_string("C 2 2000 2010-03-01"),
        Component::from_string("C -3 2100 2010-03-01"),
        Component::from_string("C 2 2200 2010-03-01"),
    },
    {
        Component::from_string("C 2 2200 2010-03-01"),
        Component::from_string("C -3 2100 2010-03-01"),
        Component::from_string("C 2 2000 2010-03-01"),
    },
    {
        Component::from_string("C -3 2100 2010-03-01"),
        Component::from_string("C 2 2200 2010-03-01"),
        Component::from_string("C 2 2000 2010-03-01"),
    },
    {
        Component::from_string("P 2 2000 2010-03-01"),
        Component::from_string("P -3 2100 2010-03-01"),
        Component::from_string("P 2 2200 2010-03-01"),
    },
    {
        Component::from_string("P 2 2200 2010-03-01"),
        Component::from_string("P -3 2100 2010-03-01"),
        Component::from_string("P 2 2000 2010-03-01"),
    },
    {
        Component::from_string("P -3 2100 2010-03-01"),
        Component::from_string("P 2 2000 2010-03-01"),
        Component::from_string("P 2 2200 2010-03-01"),
    },
    {
        Component::from_string("P -2 2000 2010-03-01"),
        Component::from_string("P 3 1900 2010-03-01"),
    },
    {
        Component::from_string("P 3 1900 2010-03-01"),
        Component::from_string("P -2 2000 2010-03-01"),
    },
    {
        Component::from_string("C -2 2000 2010-03-01"),
        Component::from_string("C 3 2100 2010-03-01"),
    },
    {
        Component::from_string("C 3 2100 2010-03-01"),
        Component::from_string("C -2 2000 2010-03-01"),
    },
    {
        Component::from_string("C 1 2000 2010-03-01"),
        Component::from_string("P 1 2000 2010-03-01"),
        Component::from_string("C -2 2000 2010-03-02"),
        Component::from_string("P -2 2000 2010-03-02"),
        Component::from_string("C 1 2000 2010-03-03"),
        Component::from_string("P 1 2000 2010-03-03"),
    },
    {
        Component::from_string("P 1 2000 2010-03-03"),
        Component::from_string("C 1 2000 2010-03-03"),
        Component::from_string("P -2 2000 2010-03-02"),
        Component::from_string("C -2 2000 2010-03-02"),
        Component::from_string("P 1 2000 2010-03-01"),
        Component::from_string("C 1 2000 2010-03-01"),
    },
    {
        Component::from_string("P 1 2000 2010-03-03"),
        Component::from_string("C -2 2000 2010-03-02"),
        Component::from_string("C 1 2000 2010-03-01"),
        Component::from_string("P -2 2000 2010-03-02"),
        Component::from_string("C 1 2000 2010-03-03"),
        Component::from_string("P 1 2000 2010-03-01"),
    },
    {
        Component::from_string("P -1 2000 2010-03-01"),
        Component::from_string("C 1 2100 2010-03-01"),
        Component::from_string("P 1 2000 2010-03-02"),
        Component::from_string("C -1 2100 2010-03-02"),
    },
    {
        Component::from_string("C -1 2100 2010-03-02"),
        Component::from_string("P 1 2000 2010-03-02"),
        Component::from_string("C 1 2100 2010-03-01"),
        Component::from_string("P -1 2000 2010-03-01"),
    },
    {
        Component::from_string("P 1 2000 2010-03-02"),
        Component::from_string("C 1 2100 2010-03-01"),
        Component::from_string("P -1 2000 2010-03-01"),
        Component::from_string("C -1 2100 2010-03-02"),
    },
    {
        Component::from_string("C 1 2000 2010-03-01"),
        Component::from_string("C -1 2100 2010-03-01"),
        Component::from_string("C -1 2000 2010-03-02"),
        Component::from_string("C 1 2100 2010-03-02"),
    },
    {
        Component::from_string("C 1 2100 2010-03-02"),
        Component::from_string("C -1 2000 2010-03-02"),
        Component::from_string("C -1 2100 2010-03-01"),
        Component::from_string("C 1 2000 2010-03-01"),
    },
    {
        Component::from_string("C 1 2000 2010-03-01"),
        Component::from_string("C 1 2100 2010-03-02"),
        Component::from_string("C -1 2100 2010-03-01"),
        Component::from_string("C -1 2000 2010-03-02"),
    },
    {
        Component::from_string("P 1 2000 2010-03-01"),
        Component::from_string("P -1 1900 2010-03-01"),
        Component::from_string("P -1 2000 2010-03-02"),
        Component::from_string("P 1 1900 2010-03-02"),
    },
    {
        Component::from_string("P 1 1900 2010-03-02"),
        Component::from_string("P -1 2000 2010-03-02"),
        Component::from_string("P -1 1900 2010-03-01"),
        Component::from_string("P 1 2000 2010-03-01"),
    },
    {
        Component::from_string("P 1 1900 2010-03-02"),
        Component::from_string("P -1 2000 2010-03-02"),
        Component::from_string("P 1 2000 2010-03-01"),
        Component::from_string("P -1 1900 2010-03-01"),
    },
    {
        Component::from_string("P -1 2000 2010-03-01"),
        Component::from_string("C -1 2000 2010-03-01"),
        Component::from_string("P 1 2100 2010-03-01"),
        Component::from_string("C 1 2100 2010-03-01"),
    },
    {
        Component::from_string("C 1 2100 2010-03-01"),
        Component::from_string("P 1 2100 2010-03-01"),
        Component::from_string("C -1 2000 2010-03-01"),
        Component::from_string("P -1 2000 2010-03-01"),
    },
    {
        Component::from_string("C 1 2100 2010-03-01"),
        Component::from_string("P 1 2100 2010-03-01"),
        Component::from_string("P -1 2000 2010-03-01"),
        Component::from_string("C -1 2000 2010-03-01"),
    },
    {
        Component::from_string("C 1 2000 2010-03-01"),
        Component::from_string("U -10 2010-03-01"),
    },
    {
        Component::from_string("U -10 2010-03-01"),
        Component::from_string("C 1 2000 2010-03-01"),
    },
    {
        Component::from_string("P 1 2000 2010-03-01"),
        Component::from_string("U 10 2010-03-01"),
    },
    {
        Component::from_string("U 10 2010-03-01"),
        Component::from_string("P 1 2000 2010-03-01"),
    },
    {
        Component::from_string("C 1 2000 2010-03-01"),
        Component::from_string("C -1 2100 2010-03-01"),
        Component::from_string("U -10 2010-03-01"),
    },
    {
        Component::from_string("U -10 2010-03-01"),
        Component::from_string("C -1 2100 2010-03-01"),
        Component::from_string("C 1 2000 2010-03-01"),
    },
    {
        Component::from_string("C -1 2100 2010-03-01"),
        Component::from_string("C 1 2000 2010-03-01"),
        Component::from_string("U -10 2010-03-01"),
    },
    {
        Component::from_string("P 1 2000 2010-03-01"),
        Component::from_string("P -1 1900 2010-03-01"),
        Component::from_string("U 10 2010-03-01"),
    },
    {
        Component::from_string("U 10 2010-03-01"),
        Component::from_string("P -1 1900 2010-03-01"),
        Component::from_string("P 1 2000 2010-03-01"),
    },
    {
        Component::from_string("P -1 1900 2010-03-01"),
        Component::from_string("U 10 2010-03-01"),
        Component::from_string("P 1 2000 2010-03-01"),
    },
    {
        Component::from_string("P 1 2000 2010-03-01"),
        Component::from_string("C 1 2000 2010-03-01"),
        Component::from_string("U 10 2010-03-01"),
    },
    {
        Component::from_string("U 10 2010-03-01"),
        Component::from_string("C 1 2000 2010-03-01"),
        Component::from_string("P 1 2000 2010-03-01"),
    },
    {
        Component::from_string("C 1 2000 2010-03-01"),
        Component::from_string("P 1 2000 2010-03-01"),
        Component::from_string("U 10 2010-03-01"),
    },
    {
        Component::from_string("P 1 2000 2010-03-01"),
        Component::from_string("C 1 2000 2010-03-01"),
        Component::from_string("U -10 2010-03-01"),
    },
    {
        Component::from_string("U -10 2010-03-01"),
        Component::from_string("C 1 2000 2010-03-01"),
        Component::from_string("P 1 2000 2010-03-01"),
    },
    {
        Component::from_string("C 1 2000 2010-03-01"),
        Component::from_string("P 1 2000 2010-03-01"),
        Component::from_string("U -10 2010-03-01"),
    },
    {
        Component::from_string("P 1 2000 2010-03-01"),
        Component::from_string("C 1 2100 2010-03-01"),
        Component::from_string("U 10 2010-03-01"),
    },
    {
        Component::from_string("U 10 2010-03-01"),
        Component::from_string("C 1 2100 2010-03-01"),
        Component::from_string("P 1 2000 2010-03-01"),
    },
    {
        Component::from_string("C 1 2100 2010-03-01"),
        Component::from_string("U 10 2010-03-01"),
        Component::from_string("P 1 2000 2010-03-01"),
    },
    {
        Component::from_string("P 1 2000 2010-03-01"),
        Component::from_string("C 1 2100 2010-03-01"),
        Component::from_string("U -10 2010-03-01"),
    },
    {
        Component::from_string("U -10 2010-03-01"),
        Component::from_string("C 1 2100 2010-03-01"),
        Component::from_string("P 1 2000 2010-03-01"),
    },
    {
        Component::from_string("C 1 2100 2010-03-01"),
        Component::from_string("P 1 2000 2010-03-01"),
        Component::from_string("U -10 2010-03-01"),
    },
    {
        Component::from_string("C 1 2000 2010-03-01"),
        Component::from_string("C -1 2100 2010-03-01"),
        Component::from_string("P -1 2000 2010-03-01"),
        Component::from_string("U -10 2010-03-01"),
    },
    {
        Component::from_string("U -10 2010-03-01"),
        Component::from_string("P -1 2000 2010-03-01"),
        Component::from_string("C -1 2100 2010-03-01"),
        Component::from_string("C 1 2000 2010-03-01"),
    },
    {
        Component::from_string("P -1 2000 2010-03-01"),
        Component::from_string("C -1 2100 2010-03-01"),
        Component::from_string("U -10 2010-03-01"),
        Component::from_string("C 1 2000 2010-03-01"),
    },
    {
        Component::from_string("P 1 2000 2010-03-01"),
        Component::from_string("P -1 1900 2010-03-01"),
        Component::from_string("C -1 2000 2010-03-01"),
        Component::from_string("U 10 2010-03-01"),
    },
    {
        Component::from_string("U 10 2010-03-01"),
        Component::from_string("C -1 2000 2010-03-01"),
        Component::from_string("P -1 1900 2010-03-01"),
        Component::from_string("P 1 2000 2010-03-01"),
    },
    {
        Component::from_string("P -1 1900 2010-03-01"),
        Component::from_string("U 10 2010-03-01"),
        Component::from_string("P 1 2000 2010-03-01"),
        Component::from_string("C -1 2000 2010-03-01"),
    },
    {
        Component::from_string("C 1 2000 2010-03-01"),
        Component::from_string("C -1 2100 2010-03-01"),
        Component::from_string("C -1 2200 2010-03-01"),
        Component::from_string("U 10 2010-03-01"),
    },
    {
        Component::from_string("U 10 2010-03-01"),
        Component::from_string("C -1 2200 2010-03-01"),
        Component::from_string("C -1 2100 2010-03-01"),
        Component::from_string("C 1 2000 2010-03-01"),
    },
    {
        Component::from_string("C -1 2200 2010-03-01"),
        Component::from_string("U 10 2010-03-01"),
        Component::from_string("C 1 2000 2010-03-01"),
        Component::from_string("C -1 2100 2010-03-01"),
    },
    {
        Component::from_string("C 1 2000 2010-03-01"),
        Component::from_string("C -1 2100 2010-03-01"),
        Component::from_string("C -1 2200 2010-03-01"),
        Component::from_string("U -10 2010-03-01"),
    },
    {
        Component::from_string("U -10 2010-03-01"),
        Component::from_string("C -1 2200 2010-03-01"),
        Component::from_string("C -1 2100 2010-03-01"),
        Component::from_string("C 1 2000 2010-03-01"),
    },
    {
        Component::from_string("C -1 2100 2010-03-01"),
        Component::from_string("C 1 2000 2010-03-01"),
        Component::from_string("C -1 2200 2010-03-01"),
        Component::from_string("U -10 2010-03-01"),
    },
    {
        Component::from_string("P -1 2000 2010-03-01"),
        Component::from_string("P -1 2100 2010-03-01"),
        Component::from_string("P 1 2200 2010-03-01"),
        Component::from_string("U 10 2010-03-01"),
    },
    {
        Component::from_string("U 10 2010-03-01"),
        Component::from_string("P 1 2200 2010-03-01"),
        Component::from_string("P -1 2100 2010-03-01"),
        Component::from_string("P -1 2000 2010-03-01"),
    },
    {
        Component::from_string("P 1 2200 2010-03-01"),
        Component::from_string("U 10 2010-03-01"),
        Component::from_string("P -1 2100 2010-03-01"),
        Component::from_string("P -1 2000 2010-03-01"),
    },
    {
        Component::from_string("P -1 2000 2010-03-01"),
        Component::from_string("P -1 2100 2010-03-01"),
        Component::from_string("P 1 2200 2010-03-01"),
        Component::from_string("U -10 2010-03-01"),
    },
    {
        Component::from_string("U -10 2010-03-01"),
        Component::from_string("P 1 2200 2010-03-01"),
        Component::from_string("P -1 2100 2010-03-01"),
        Component::from_string("P -1 2000 2010-03-01"),
    },
    {
        Component::from_string("U -10 2010-03-01"),
        Component::from_string("P -1 2000 2010-03-01"),
        Component::from_string("P 1 2200 2010-03-01"),
        Component::from_string("P -1 2100 2010-03-01"),
    },
    {
        Component::from_string("C -1 2000 2010-03-01"),
        Component::from_string("P 1 1900 2010-03-01"),
        Component::from_string("U 10 2010-03-01"),
    },
    {
        Component::from_string("U 10 2010-03-01"),
        Component::from_string("P 1 1900 2010-03-01"),
        Component::from_string("C -1 2000 2010-03-01"),
    },
    {
        Component::from_string("C -1 2000 2010-03-01"),
        Component::from_string("U 10 2010-03-01"),
        Component::from_string("P 1 1900 2010-03-01"),
    },
    {
        Component::from_string("C -1 2000 2010-03-01"),
        Component::from_string("C 1 2000 2010-03-02"),
        Component::from_string("U 10 2010-03-01"),
    },
    {
        Component::from_string("U 10 2010-03-01"),
        Component::from_string("C 1 2000 2010-03-02"),
        Component::from_string("C -1 2000 2010-03-01"),
    },
    {
        Component::from_string("C -1 2000 2010-03-01"),
        Component::from_string("U 10 2010-03-01"),
        Component::from_string("C 1 2000 2010-03-02"),
    },
    {
        Component::from_string("C -1 2000 2010-03-01"),
        Component::from_string("C 1 2000 2010-03-02"),
        Component::from_string("U -10 2010-03-01"),
    },
    {
        Component::from_string("U -10 2010-03-01"),
        Component::from_string("C 1 2000 2010-03-02"),
        Component::from_string("C -1 2000 2010-03-01"),
    },
    {
        Component::from_string("C -1 2000 2010-03-01"),
        Component::from_string("U -10 2010-03-01"),
        Component::from_string("C 1 2000 2010-03-02"),
    },
    {
        Component::from_string("P -1 2000 2010-03-01"),
        Component::from_string("P 1 2000 2010-03-02"),
        Component::from_string("U 10 2010-03-01"),
    },
    {
        Component::from_string("U 10 2010-03-01"),
        Component::from_string("P 1 2000 2010-03-02"),
        Component::from_string("P -1 2000 2010-03-01"),
    },
    {
        Component::from_string("P -1 2000 2010-03-01"),
        Component::from_string("U 10 2010-03-01"),
        Component::from_string("P 1 2000 2010-03-02"),
    },
    {
        Component::from_string("P -1 2000 2010-03-01"),
        Component::from_string("P 1 2000 2010-03-02"),
        Component::from_string("U -10 2010-03-01"),
    },
    {
        Component::from_string("U -10 2010-03-01"),
        Component::from_string("P 1 2000 2010-03-02"),
        Component::from_string("P -1 2000 2010-03-01"),
    },
    {
        Component::from_string("P 1 2000 2010-03-02"),
        Component::from_string("P -1 2000 2010-03-01"),
        Component::from_string("U -10 2010-03-01"),
    },
    {
        Component::from_string("C -1 2000 2010-03-01"),
        Component::from_string("C 2 2100 2010-03-01"),
        Component::from_string("U 10 2010-03-01"),
    },
    {
        Component::from_string("U 10 2010-03-01"),
        Component::from_string("C 2 2100 2010-03-01"),
        Component::from_string("C -1 2000 2010-03-01"),
    },
    {
        Component::from_string("C 2 2100 2010-03-01"),
        Component::from_string("U 10 2010-03-01"),
        Component::from_string("C -1 2000 2010-03-01"),
    },
    {
        Component::from_string("C -1 2000 2010-03-01"),
        Component::from_string("C 2 2100 2010-03-01"),
        Component::from_string("U -10 2010-03-01"),
    },
    {
        Component::from_string("U -10 2010-03-01"),
        Component::from_string("C 2 2100 2010-03-01"),
        Component::from_string("C -1 2000 2010-03-01"),
    },
    {
        Component::from_string("C 2 2100 2010-03-01"),
        Component::from_string("C -1 2000 2010-03-01"),
        Component::from_string("U -10 2010-03-01"),
    },
    {
        Component::from_string("P -1 2000 2010-03-01"),
        Component::from_string("P 2 1900 2010-03-01"),
        Component::from_string("U 10 2010-03-01"),
    },
    {
        Component::from_string("U 10 2010-03-01"),
        Component::from_string("P 2 1900 2010-03-01"),
        Component::from_string("P -1 2000 2010-03-01"),
    },
    {
        Component::from_string("P 2 1900 2010-03-01"),
        Component::from_string("U 10 2010-03-01"),
        Component::from_string("P -1 2000 2010-03-01"),
    },
    {
        Component::from_string("F 1 2010-03-03"),
        Component::from_string("C 1 2000 2010-03-03"),
        Component::from_string("O 1 2000 2010-03-03"),
        Component::from_string("P 1 2100 2010-03-01"),
        Component::from_string("U -10 2010-03-01"),
        Component::from_string(" -2 2000 2010-03-01")
    },
    {
        Component::from_string("P -1 2000 2010-03-01"),
        Component::from_string("P 2 1900 2010-03-01"),
        Component::from_string("U -10 2010-03-01"),
    },
    {
        Component::from_string("U -10 2010-03-01"),
        Component::from_string("P 2 1900 2010-03-01"),
        Component::from_string("P -1 2000 2010-03-01"),
    },
    {
        Component::from_string("P 2 1900 2010-03-01"),
        Component::from_string("P -1 2000 2010-03-01"),
        Component::from_string("U -10 2010-03-01"),
    },
    {
        Component::from_string("C 1 2000 2010-03-01"),
        Component::from_string("P -1 2000 2010-03-01"),
        Component::from_string("U -10 2010-03-01"),
    },
    {
        Component::from_string("U -10 2010-03-01"),
        Component::from_string("P -1 2000 2010-03-01"),
        Component::from_string("C 1 2000 2010-03-01"),
    },
    {
        Component::from_string("P -1 2000 2010-03-01"),
        Component::from_string("U -10 2010-03-01"),
        Component::from_string("C 1 2000 2010-03-01"),
    },
    {
        Component::from_string("P -1 2000 2010-03-01"),
        Component::from_string("C -1 2000 2010-03-01"),
        Component::from_string("P 1 2000 2010-03-02"),
        Component::from_string("C 1 2000 2010-03-02"),
        Component::from_string("U 10 2010-03-01"),
    },
    {
        Component::from_string("U 10 2010-03-01"),
        Component::from_string("C 1 2000 2010-03-02"),
        Component::from_string("P 1 2000 2010-03-02"),
        Component::from_string("C -1 2000 2010-03-01"),
        Component::from_string("P -1 2000 2010-03-01"),
    },
    {
        Component::from_string("C -1 2000 2010-03-01"),
        Component::from_string("P 1 2000 2010-03-02"),
        Component::from_string("P -1 2000 2010-03-01"),
        Component::from_string("C 1 2000 2010-03-02"),
        Component::from_string("U 10 2010-03-01"),
    },
    {
        Component::from_string("P -1 2000 2010-03-01"),
        Component::from_string("C -1 2000 2010-03-01"),
        Component::from_string("P 1 2000 2010-03-02"),
        Component::from_string("C 1 2000 2010-03-02"),
        Component::from_string("U -10 2010-03-01"),
    },
    {
        Component::from_string("U -10 2010-03-01"),
        Component::from_string("C 1 2000 2010-03-02"),
        Component::from_string("P 1 2000 2010-03-02"),
        Component::from_string("C -1 2000 2010-03-01"),
        Component::from_string("P -1 2000 2010-03-01"),
    },
    {
        Component::from_string("C 1 2000 2010-03-02"),
        Component::from_string("P 1 2000 2010-03-02"),
        Component::from_string("U -10 2010-03-01"),
        Component::from_string("C -1 2000 2010-03-01"),
        Component::from_string("P -1 2000 2010-03-01"),
    },
    {
        Component::from_string("C -1 2000 2010-03-01"),
        Component::from_string("C 1 2100 2010-03-02"),
        Component::from_string("U 10 2010-03-01"),
    },
    {
        Component::from_string("U 10 2010-03-01"),
        Component::from_string("C 1 2100 2010-03-02"),
        Component::from_string("C -1 2000 2010-03-01"),
    },
    {
        Component::from_string("U 10 2010-03-01"),
        Component::from_string("C -1 2000 2010-03-01"),
        Component::from_string("C 1 2100 2010-03-02"),
    },
    {
        Component::from_string("C -1 2000 2010-03-01"),
        Component::from_string("C 1 2100 2010-03-02"),
        Component::from_string("U -10 2010-03-01"),
    },
    {
        Component::from_string("U -10 2010-03-01"),
        Component::from_string("C 1 2100 2010-03-02"),
        Component::from_string("C -1 2000 2010-03-01"),
    },
    {
        Component::from_string("C 1 2100 2010-03-02"),
        Component::from_string("U -10 2010-03-01"),
        Component::from_string("C -1 2000 2010-03-01"),
    },
    {
        Component::from_string("P -1 2000 2010-03-01"),
        Component::from_string("P 1 2100 2010-03-02"),
        Component::from_string("U 10 2010-03-01"),
    },
    {
        Component::from_string("U 10 2010-03-01"),
        Component::from_string("P 1 2100 2010-03-02"),
        Component::from_string("P -1 2000 2010-03-01"),
    },
    {
        Component::from_string("P -1 2000 2010-03-01"),
        Component::from_string("U 10 2010-03-01"),
        Component::from_string("P 1 2100 2010-03-02"),
    },
    {
        Component::from_string("P -1 2000 2010-03-01"),
        Component::from_string("P 1 2100 2010-03-02"),
        Component::from_string("U -10 2010-03-01"),
    },
    {
        Component::from_string("U -10 2010-03-01"),
        Component::from_string("P 1 2100 2010-03-02"),
        Component::from_string("P -1 2000 2010-03-01"),
    },
    {
        Component::from_string("P -1 2000 2010-03-01"),
        Component::from_string("U -10 2010-03-01"),
        Component::from_string("P 1 2100 2010-03-02"),
    },
    {
        Component::from_string("C 1 2000 2010-03-01"),
        Component::from_string("P 1 2100 2010-03-01"),
        Component::from_string("U 10 2010-03-01"),
    },
    {
        Component::from_string("U 10 2010-03-01"),
        Component::from_string("P 1 2100 2010-03-01"),
        Component::from_string("C 1 2000 2010-03-01"),
    },
    {
        Component::from_string("U 10 2010-03-01"),
        Component::from_string("C 1 2000 2010-03-01"),
        Component::from_string("P 1 2100 2010-03-01"),
    },
    {
        Component::from_string("C 1 2000 2010-03-01"),
        Component::from_string("P 1 2100 2010-03-01"),
        Component::from_string("U -10 2010-03-01"),
    },
    {
        Component::from_string("U -10 2010-03-01"),
        Component::from_string("P 1 2100 2010-03-01"),
        Component::from_string("C 1 2000 2010-03-01"),
    },
    {
        Component::from_string("C 1 2000 2010-03-01"),
        Component::from_string("U -10 2010-03-01"),
        Component::from_string("P 1 2100 2010-03-01"),
    },
    {
        Component::from_string("F 1 2010-03-03"),
        Component::from_string("X 1 2000 2010-03-03"),
        Component::from_string("P 1 2000 2010-03-03"),
        Component::from_string("P 1 2100 2010-03-01"),
        Component::from_string("U -10 2010-03-01"),
        Component::from_string("P -2 2000 2010-03-01")
    },
    {
        Component::from_string("C 1 2000 2010-03-01"),
        Component::from_string("C -2 2100 2010-03-01"),
        Component::from_string("C 1 2200 2010-03-01"),
        Component::from_string("U 10 2010-03-01"),
    },
    {
        Component::from_string("U 10 2010-03-01"),
        Component::from_string("C 1 2200 2010-03-01"),
        Component::from_string("C -2 2100 2010-03-01"),
        Component::from_string("C 1 2000 2010-03-01"),
    },
    {
        Component::from_string("C 1 2200 2010-03-01"),
        Component::from_string("C -2 2100 2010-03-01"),
        Component::from_string("C 1 2000 2010-03-01"),
        Component::from_string("U 10 2010-03-01"),
    },
    {
        Component::from_string("C 1 2000 2010-03-01"),
        Component::from_string("C -2 2100 2010-03-01"),
        Component::from_string("C 1 2200 2010-03-01"),
        Component::from_string("U -10 2010-03-01"),
    },
    {
        Component::from_string("U -10 2010-03-01"),
        Component::from_string("C 1 2200 2010-03-01"),
        Component::from_string("C -2 2100 2010-03-01"),
        Component::from_string("C 1 2000 2010-03-01"),
    },
    {
        Component::from_string("C 1 2200 2010-03-01"),
        Component::from_string("U -10 2010-03-01"),
        Component::from_string("C 1 2000 2010-03-01"),
        Component::from_string("C -2 2100 2010-03-01"),
    },
    {
        Component::from_string("P 1 2000 2010-03-01"),
        Component::from_string("P -2 2100 2010-03-01"),
        Component::from_string("P 1 2200 2010-03-01"),
        Component::from_string("U 10 2010-03-01"),
    },
    {
        Component::from_string("U 10 2010-03-01"),
        Component::from_string("P 1 2200 2010-03-01"),
        Component::from_string("P -2 2100 2010-03-01"),
        Component::from_string("P 1 2000 2010-03-01"),
    },
    {
        Component::from_string("P 1 2000 2010-03-01"),
        Component::from_string("P 1 2200 2010-03-01"),
        Component::from_string("P -2 2100 2010-03-01"),
        Component::from_string("U 10 2010-03-01"),
    },
    {
        Component::from_string("P 1 2000 2010-03-01"),
        Component::from_string("P -2 2100 2010-03-01"),
        Component::from_string("P 1 2200 2010-03-01"),
        Component::from_string("U -10 2010-03-01"),
    },
    {
        Component::from_string("F 1 2010-03-03"),
        Component::from_string("C 1 2000 2010-03-03"),
        Component::from_string("f 1 2000 2010-03-03"),
        Component::from_string("P 1 2100 2010-03-01"),
        Component::from_string("U -10 2010-03-01"),
        Component::from_string("P -2 2000 2010-03-01")
    },
    {
        Component::from_string("U -10 2010-03-01"),
        Component::from_string("P 1 2200 2010-03-01"),
        Component::from_string("P -2 2100 2010-03-01"),
        Component::from_string("P 1 2000 2010-03-01"),
    },
    {
        Component::from_string("P 1 2200 2010-03-01"),
        Component::from_string("P 1 2000 2010-03-01"),
        Component::from_string("P -2 2100 2010-03-01"),
        Component::from_string("U -10 2010-03-01"),
    },
    {
        Component::from_string("P -1 2000 2010-03-01"),
        Component::from_string("P 1 2100 2010-03-01"),
        Component::from_string("C 1 2100 2010-03-01"),
        Component::from_string("C -1 2200 2010-03-01"),
        Component::from_string("U 10 2010-03-01"),
    },
    {
        Component::from_string("U 10 2010-03-01"),
        Component::from_string("C -1 2200 2010-03-01"),
        Component::from_string("C 1 2100 2010-03-01"),
        Component::from_string("P 1 2100 2010-03-01"),
        Component::from_string("P -1 2000 2010-03-01"),
    },
    {
        Component::from_string("C 1 2100 2010-03-01"),
        Component::from_string("C -1 2200 2010-03-01"),
        Component::from_string("P -1 2000 2010-03-01"),
        Component::from_string("P 1 2100 2010-03-01"),
        Component::from_string("U 10 2010-03-01"),
    },
    {
        Component::from_string("P -1 2000 2010-03-01"),
        Component::from_string("P 1 2100 2010-03-01"),
        Component::from_string("C 1 2100 2010-03-01"),
        Component::from_string("C -1 2200 2010-03-01"),
        Component::from_string("U -10 2010-03-01"),
    },
    {
        Component::from_string("U -10 2010-03-01"),
        Component::from_string("C -1 2200 2010-03-01"),
        Component::from_string("C 1 2100 2010-03-01"),
        Component::from_string("P 1 2100 2010-03-01"),
        Component::from_string("P -1 2000 2010-03-01"),
    },
    {
        Component::from_string("P 1 2100 2010-03-01"),
        Component::from_string("P -1 2000 2010-03-01"),
        Component::from_string("C -1 2200 2010-03-01"),
        Component::from_string("C 1 2100 2010-03-01"),
        Component::from_string("U -10 2010-03-01"),
    },
    {
        Component::from_string("P -1 2000 2010-03-01"),
        Component::from_string("C -1 2000 2010-03-01"),
        Component::from_string("P 1 2100 2010-03-02"),
        Component::from_string("C 1 2100 2010-03-02"),
        Component::from_string("U 10 2010-03-01"),
    },
    {
        Component::from_string("U 10 2010-03-01"),
        Component::from_string("C 1 2100 2010-03-02"),
        Component::from_string("P 1 2100 2010-03-02"),
        Component::from_string("C -1 2000 2010-03-01"),
        Component::from_string("P -1 2000 2010-03-01"),
    },
    {
        Component::from_string("C -1 2000 2010-03-01"),
        Component::from_string("C 1 2100 2010-03-02"),
        Component::from_string("U 10 2010-03-01"),
        Component::from_string("P 1 2100 2010-03-02"),
        Component::from_string("P -1 2000 2010-03-01"),
    },
    {
        Component::from_string("P -1 2000 2010-03-01"),
        Component::from_string("C -1 2000 2010-03-01"),
        Component::from_string("P 1 2100 2010-03-02"),
        Component::from_string("C 1 2100 2010-03-02"),
        Component::from_string("U -10 2010-03-01"),
    },
    {
        Component::from_string("U -10 2010-03-01"),
        Component::from_string("C 1 2100 2010-03-02"),
        Component::from_string("P 1 2100 2010-03-02"),
        Component::from_string("C -1 2000 2010-03-01"),
        Component::from_string("P -1 2000 2010-03-01"),
    },
    {
        Component::from_string("P 1 2100 2010-03-02"),
        Component::from_string("P -1 2000 2010-03-01"),
        Component::from_string("C -1 2000 2010-03-01"),
        Component::from_string("C 1 2100 2010-03-02"),
        Component::from_string("U -10 2010-03-01"),
    },
    {
        Component::from_string("C 1 2000 2010-03-01"),
        Component::from_string("C -1 2100 2010-03-01"),
        Component::from_string("C -1 2200 2010-03-01"),
        Component::from_string("C 1 2300 2010-03-01"),
        Component::from_string("U 10 2010-03-01"),
    },
    {
        Component::from_string("U 10 2010-03-01"),
        Component::from_string("C 1 2300 2010-03-01"),
        Component::from_string("C -1 2200 2010-03-01"),
        Component::from_string("C -1 2100 2010-03-01"),
        Component::from_string("C 1 2000 2010-03-01"),
    },
    {
        Component::from_string("U 10 2010-03-01"),
        Component::from_string("C 1 2000 2010-03-01"),
        Component::from_string("C -1 2200 2010-03-01"),
        Component::from_string("C -1 2100 2010-03-01"),
        Component::from_string("C 1 2300 2010-03-01"),
    },
    {
        Component::from_string("C 1 2000 2010-03-01"),
        Component::from_string("C -1 2100 2010-03-01"),
        Component::from_string("C -1 2200 2010-03-01"),
        Component::from_string("C 1 2300 2010-03-01"),
        Component::from_string("U -10 2010-03-01"),
    },
    {
        Component::from_string("F 1 2010-03-03"),
        Component::from_string("C 1 2000 2010-03-03"),
        Component::from_string("P 1 2100 2010-03-01"),
        Component::from_string("U -10 2010-03-01"),
        Component::from_string("P -2 2000 2010-03-01")
    },
    {
        Component::from_string("U -10 2010-03-01"),
        Component::from_string("C 1 2300 2010-03-01"),
        Component::from_string("C -1 2200 2010-03-01"),
        Component::from_string("C -1 2100 2010-03-01"),
        Component::from_string("C 1 2000 2010-03-01"),
    },
    {
        Component::from_string("C 1 2000 2010-03-01"),
        Component::from_string("C 1 2300 2010-03-01"),
        Component::from_string("U -10 2010-03-01"),
        Component::from_string("C -1 2100 2010-03-01"),
        Component::from_string("C -1 2200 2010-03-01"),
    },
    {
        Component::from_string("P 1 2000 2010-03-01"),
        Component::from_string("P -1 2100 2010-03-01"),
        Component::from_string("P -1 2200 2010-03-01"),
        Component::from_string("P 1 2300 2010-03-01"),
        Component::from_string("U 10 2010-03-01"),
    },
    {
        Component::from_string("U 10 2010-03-01"),
        Component::from_string("P 1 2300 2010-03-01"),
        Component::from_string("P -1 2200 2010-03-01"),
        Component::from_string("P -1 2100 2010-03-01"),
        Component::from_string("P 1 2000 2010-03-01"),
    },
    {
        Component::from_string("U 10 2010-03-01"),
        Component::from_string("P -1 2200 2010-03-01"),
        Component::from_string("P -1 2100 2010-03-01"),
        Component::from_string("P 1 2000 2010-03-01"),
        Component::from_string("P 1 2300 2010-03-01"),
    },
    {
        Component::from_string("P 1 2000 2010-03-01"),
        Component::from_string("P -1 2100 2010-03-01"),
        Component::from_string("P -1 2200 2010-03-01"),
        Component::from_string("P 1 2300 2010-03-01"),
        Component::from_string("U -10 2010-03-01"),
    },
    {
        Component::from_string("U -10 2010-03-01"),
        Component::from_string("P 1 2300 2010-03-01"),
        Component::from_string("P -1 2200 2010-03-01"),
        Component::from_string("P -1 2100 2010-03-01"),
        Component::from_string("P 1 2000 2010-03-01"),
    },
    {
        Component::from_string("U -10 2010-03-01"),
        Component::from_string("P -1 2200 2010-03-01"),
        Component::from_string("P -1 2100 2010-03-01"),
        Component::from_string("P 1 2300 2010-03-01"),
        Component::from_string("P 1 2000 2010-03-01"),
    },
    {
        Component::from_string("P -1 2000 2010-03-01"),
        Component::from_string("P 1 2100 2010-03-01"),
        Component::from_string("C 1 2200 2010-03-01"),
        Component::from_string("C -1 2300 2010-03-01"),
        Component::from_string("U 10 2010-03-01"),
    },
    {
        Component::from_string("U 10 2010-03-01"),
        Component::from_string("C -1 2300 2010-03-01"),
        Component::from_string("C 1 2200 2010-03-01"),
        Component::from_string("P 1 2100 2010-03-01"),
        Component::from_string("P -1 2000 2010-03-01"),
    },
    {
        Component::from_string("P 1 2100 2010-03-01"),
        Component::from_string("C -1 2300 2010-03-01"),
        Component::from_string("C 1 2200 2010-03-01"),
        Component::from_string("P -1 2000 2010-03-01"),
        Component::from_string("U 10 2010-03-01"),
    },
    {
        Component::from_string("P -1 2000 2010-03-01"),
        Component::from_string("P 1 2100 2010-03-01"),
        Component::from_string("C 1 2200 2010-03-01"),
        Component::from_string("C -1 2300 2010-03-01"),
        Component::from_string("U -10 2010-03-01"),
    },
    {
        Component::from_string("U -10 2010-03-01"),
        Component::from_string("C -1 2300 2010-03-01"),
        Component::from_string("C 1 2200 2010-03-01"),
        Component::from_string("P 1 2100 2010-03-01"),
        Component::from_string("P -1 2000 2010-03-01"),
    },
    {
        Component::from_string("C 1 2200 2010-03-01"),
        Component::from_string("U -10 2010-03-01"),
        Component::from_string("P -1 2000 2010-03-01"),
        Component::from_string("P 1 2100 2010-03-01"),
        Component::from_string("C -1 2300 2010-03-01"),
    },
    {
        Component::from_string("C 1 2000 2010-03-01"),
        Component::from_string("P -1 1900 2010-03-01"),
        Component::from_string("U -10 2010-03-01"),
    },
    {
        Component::from_string("U -10 2010-03-01"),
        Component::from_string("P -1 1900 2010-03-01"),
        Component::from_string("C 1 2000 2010-03-01"),
    },
    {
        Component::from_string("P -1 1900 2010-03-01"),
        Component::from_string("C 1 2000 2010-03-01"),
        Component::from_string("U -10 2010-03-01"),
    },
    {
        Component::from_string("C 1 2000 2010-03-01"),
        Component::from_string("P 1 2000 2010-03-01"),
        Component::from_string("C -2 2000 2010-03-02"),
        Component::from_string("P -2 2000 2010-03-02"),
        Component::from_string("C 1 2000 2010-03-03"),
        Component::from_string("P 1 2000 2010-03-03"),
        Component::from_string("U 10 2010-03-01"),
    },
    {
        Component::from_string("U 10 2010-03-01"),
        Component::from_string("P 1 2000 2010-03-03"),
        Component::from_string("C 1 2000 2010-03-03"),
        Component::from_string("P -2 2000 2010-03-02"),
        Component::from_string("C -2 2000 2010-03-02"),
        Component::from_string("P 1 2000 2010-03-01"),
        Component::from_string("C 1 2000 2010-03-01"),
    },
    {
        Component::from_string("C 1 2000 2010-03-03"),
        Component::from_string("P 1 2000 2010-03-01"),
        Component::from_string("P -2 2000 2010-03-02"),
        Component::from_string("C -2 2000 2010-03-02"),
        Component::from_string("P 1 2000 2010-03-03"),
        Component::from_string("U 10 2010-03-01"),
        Component::from_string("C 1 2000 2010-03-01"),
    },
    {
        Component::from_string("C 1 2000 2010-03-01"),
        Component::from_string("P 1 2000 2010-03-01"),
        Component::from_string("C -2 2000 2010-03-02"),
        Component::from_string("P -2 2000 2010-03-02"),
        Component::from_string("C 1 2000 2010-03-03"),
        Component::from_string("P 1 2000 2010-03-03"),
        Component::from_string("U -10 2010-03-01"),
    },
    {
        Component::from_string("U -10 2010-03-01"),
        Component::from_string("P 1 2000 2010-03-03"),
        Component::from_string("C 1 2000 2010-03-03"),
        Component::from_string("P -2 2000 2010-03-02"),
        Component::from_string("C -2 2000 2010-03-02"),
        Component::from_string("P 1 2000 2010-03-01"),
        Component::from_string("C 1 2000 2010-03-01"),
    },
    {
        Component::from_string("C -2 2000 2010-03-02"),
        Component::from_string("P 1 2000 2010-03-01"),
        Component::from_string("P 1 2000 2010-03-03"),
        Component::from_string("P -2 2000 2010-03-02"),
        Component::from_string("U -10 2010-03-01"),
        Component::from_string("C 1 2000 2010-03-03"),
        Component::from_string("C 1 2000 2010-03-01"),
    },
    {
        Component::from_string("C 2 2000 2010-03-01"),
        Component::from_string("C -3 2100 2010-03-01"),
        Component::from_string("C 2 2200 2010-03-01"),
        Component::from_string("U 10 2010-03-01"),
    },
    {
        Component::from_string("U 10 2010-03-01"),
        Component::from_string("C 2 2200 2010-03-01"),
        Component::from_string("C -3 2100 2010-03-01"),
        Component::from_string("C 2 2000 2010-03-01"),
    },
    {
        Component::from_string("U 10 2010-03-01"),
        Component::from_string("C 2 2000 2010-03-01"),
        Component::from_string("C 2 2200 2010-03-01"),
        Component::from_string("C -3 2100 2010-03-01"),
    },
    {
        Component::from_string("C 2 2000 2010-03-01"),
        Component::from_string("C -3 2100 2010-03-01"),
        Component::from_string("C 2 2200 2010-03-01"),
        Component::from_string("U -10 2010-03-01"),
    },
    {
        Component::from_string("U -10 2010-03-01"),
        Component::from_string("C 2 2200 2010-03-01"),
        Component::from_string("C -3 2100 2010-03-01"),
        Component::from_string("C 2 2000 2010-03-01"),
    },
    {
        Component::from_string("C -3 2100 2010-03-01"),
        Component::from_string("C 2 2200 2010-03-01"),
        Component::from_string("C 2 2000 2010-03-01"),
        Component::from_string("U -10 2010-03-01"),
    },
    {
        Component::from_string("P 2 2000 2010-03-01"),
        Component::from_string("P -3 2100 2010-03-01"),
        Component::from_string("P 2 2200 2010-03-01"),
        Component::from_string("U 10 2010-03-01"),
    },
    {
        Component::from_string("U 10 2010-03-01"),
        Component::from_string("P 2 2200 2010-03-01"),
        Component::from_string("P -3 2100 2010-03-01"),
        Component::from_string("P 2 2000 2010-03-01"),
    },
    {
        Component::from_string("U 10 2010-03-01"),
        Component::from_string("P 2 2000 2010-03-01"),
        Component::from_string("P 2 2200 2010-03-01"),
        Component::from_string("P -3 2100 2010-03-01"),
    },
    {
        Component::from_string("P 2 2000 2010-03-01"),
        Component::from_string("P -3 2100 2010-03-01"),
        Component::from_string("P 2 2200 2010-03-01"),
        Component::from_string("U -10 2010-03-01"),
    },
    {
        Component::from_string("U -10 2010-03-01"),
        Component::from_string("P 2 2200 2010-03-01"),
        Component::from_string("P -3 2100 2010-03-01"),
        Component::from_string("P 2 2000 2010-03-01"),
    },
    {
        Component::from_string("U -10 2010-03-01"),
        Component::from_string("P 2 2200 2010-03-01"),
        Component::from_string("P 2 2000 2010-03-01"),
        Component::from_string("P -3 2100 2010-03-01"),
    },
    {
        Component::from_string("P -2 2000 2010-03-01"),
        Component::from_string("P 3 1900 2010-03-01"),
        Component::from_string("U 10 2010-03-01"),
    },
    {
        Component::from_string("U 10 2010-03-01"),
        Component::from_string("P 3 1900 2010-03-01"),
        Component::from_string("P -2 2000 2010-03-01"),
    },
    {
        Component::from_string("P 3 1900 2010-03-01"),
        Component::from_string("P -2 2000 2010-03-01"),
        Component::from_string("U 10 2010-03-01"),
    },
    {
        Component::from_string("P -2 2000 2010-03-01"),
        Component::from_string("P 3 1900 2010-03-01"),
        Component::from_string("U -10 2010-03-01"),
    },
    {
        Component::from_string("U -10 2010-03-01"),
        Component::from_string("P 3 1900 2010-03-01"),
        Component::from_string("P -2 2000 2010-03-01"),
    },
    {
        Component::from_string("P 3 1900 2010-03-01"),
        Component::from_string("U -10 2010-03-01"),
        Component::from_string("P -2 2000 2010-03-01"),
    },
    {
        Component::from_string("C -2 2000 2010-03-01"),
        Component::from_string("C 3 2100 2010-03-01"),
        Component::from_string("U 10 2010-03-01"),
    },
    {
        Component::from_string("U 10 2010-03-01"),
        Component::from_string("C 3 2100 2010-03-01"),
        Component::from_string("C -2 2000 2010-03-01"),
    },
    {
        Component::from_string("C 3 2100 2010-03-01"),
        Component::from_string("U 10 2010-03-01"),
        Component::from_string("C -2 2000 2010-03-01"),
    },
    {
        Component::from_string("C -2 2000 2010-03-01"),
        Component::from_string("C 3 2100 2010-03-01"),
        Component::from_string("U -10 2010-03-01"),
    },
    {
        Component::from_string("U -10 2010-03-01"),
        Component::from_string("C 3 2100 2010-03-01"),
        Component::from_string("C -2 2000 2010-03-01"),
    },
    {
        Component::from_string("U -10 2010-03-01"),
        Component::from_string("C -2 2000 2010-03-01"),
        Component::from_string("C 3 2100 2010-03-01"),
    },
    {
        Component::from_string("C 1 2000 2010-03-01"),
        Component::from_string("C -1 2100 2010-03-01"),
        Component::from_string("C -1 2000 2010-03-02"),
        Component::from_string("C 1 2100 2010-03-02"),
        Component::from_string("U 10 2010-03-01"),
    },
    {
        Component::from_string("U 10 2010-03-01"),
        Component::from_string("C 1 2100 2010-03-02"),
        Component::from_string("C -1 2000 2010-03-02"),
        Component::from_string("C -1 2100 2010-03-01"),
        Component::from_string("C 1 2000 2010-03-01"),
    },
    {
        Component::from_string("C -1 2000 2010-03-02"),
        Component::from_string("C 1 2100 2010-03-02"),
        Component::from_string("U 10 2010-03-01"),
        Component::from_string("C -1 2100 2010-03-01"),
        Component::from_string("C 1 2000 2010-03-01"),
    },
    {
        Component::from_string("C 1 2000 2010-03-01"),
        Component::from_string("C -1 2100 2010-03-01"),
        Component::from_string("C -1 2000 2010-03-02"),
        Component::from_string("C 1 2100 2010-03-02"),
        Component::from_string("U -10 2010-03-01"),
    },
    {
        Component::from_string("U -10 2010-03-01"),
        Component::from_string("C 1 2100 2010-03-02"),
        Component::from_string("C -1 2000 2010-03-02"),
        Component::from_string("C -1 2100 2010-03-01"),
        Component::from_string("C 1 2000 2010-03-01"),
    },
    {
        Component::from_string("C -1 2100 2010-03-01"),
        Component::from_string("U -10 2010-03-01"),
        Component::from_string("C 1 2100 2010-03-02"),
        Component::from_string("C 1 2000 2010-03-01"),
        Component::from_string("C -1 2000 2010-03-02"),
    },
    {
        Component::from_string("P 1 2000 2010-03-01"),
        Component::from_string("P -1 1900 2010-03-01"),
        Component::from_string("P -1 2000 2010-03-02"),
        Component::from_string("P 1 1900 2010-03-02"),
        Component::from_string("U 10 2010-03-01"),
    },
    {
        Component::from_string("U 10 2010-03-01"),
        Component::from_string("P 1 1900 2010-03-02"),
        Component::from_string("P -1 2000 2010-03-02"),
        Component::from_string("P -1 1900 2010-03-01"),
        Component::from_string("P 1 2000 2010-03-01"),
    },
    {
        Component::from_string("P 1 1900 2010-03-02"),
        Component::from_string("U 10 2010-03-01"),
        Component::from_string("P -1 2000 2010-03-02"),
        Component::from_string("P -1 1900 2010-03-01"),
        Component::from_string("P 1 2000 2010-03-01"),
    },
    {
        Component::from_string("P 1 2000 2010-03-01"),
        Component::from_string("P -1 1900 2010-03-01"),
        Component::from_string("P -1 2000 2010-03-02"),
        Component::from_string("P 1 1900 2010-03-02"),
        Component::from_string("U -10 2010-03-01"),
    },
    {
        Component::from_string("U -10 2010-03-01"),
        Component::from_string("P 1 1900 2010-03-02"),
        Component::from_string("P -1 2000 2010-03-02"),
        Component::from_string("P -1 1900 2010-03-01"),
        Component::from_string("P 1 2000 2010-03-01"),
    },
    {
        Component::from_string("U -10 2010-03-01"),
        Component::from_string("P -1 2000 2010-03-02"),
        Component::from_string("P 1 2000 2010-03-01"),
        Component::from_string("P 1 1900 2010-03-02"),
        Component::from_string("P -1 1900 2010-03-01"),
    },
    {
        Component::from_string("P -1 2000 2010-03-01"),
        Component::from_string("C 1 2100 2010-03-01"),
        Component::from_string("P 1 2000 2010-03-02"),
        Component::from_string("C -1 2100 2010-03-02"),
        Component::from_string("U 10 2010-03-01"),
    },
    {
        Component::from_string("U 10 2010-03-01"),
        Component::from_string("C -1 2100 2010-03-02"),
        Component::from_string("P 1 2000 2010-03-02"),
        Component::from_string("C 1 2100 2010-03-01"),
        Component::from_string("P -1 2000 2010-03-01"),
    },
    {
        Component::from_string("C 1 2100 2010-03-01"),
        Component::from_string("P 1 2000 2010-03-02"),
        Component::from_string("U 10 2010-03-01"),
        Component::from_string("P -1 2000 2010-03-01"),
        Component::from_string("C -1 2100 2010-03-02"),
    },
    {
        Component::from_string("P -1 2000 2010-03-01"),
        Component::from_string("C 1 2100 2010-03-01"),
        Component::from_string("P 1 2000 2010-03-02"),
        Component::from_string("C -1 2100 2010-03-02"),
        Component::from_string("U -10 2010-03-01"),
    },
    {
        Component::from_string("U -10 2010-03-01"),
        Component::from_string("C -1 2100 2010-03-02"),
        Component::from_string("P 1 2000 2010-03-02"),
        Component::from_string("C 1 2100 2010-03-01"),
        Component::from_string("P -1 2000 2010-03-01"),
    },
    {
        Component::from_string("C -1 2100 2010-03-02"),
        Component::from_string("C 1 2100 2010-03-01"),
        Component::from_string("P -1 2000 2010-03-01"),
        Component::from_string("U -10 2010-03-01"),
        Component::from_string("P 1 2000 2010-03-02"),
    },
};

struct LoadTest : ::testing::Test
{
    const std::filesystem::path path{"etc/combinations.xml"};
    Combinations combinations;

    LoadTest()
    {
        combinations.load(path);
    }
};

} // anonymous namespace

TEST_F(LoadTest, many)
{
    const std::size_t N = 6, M = 250;
    std::mt19937_64 gen(std::random_device{}());
    std::vector<std::vector<std::vector<Component>>> sets;
    sets.reserve(N);
    for (std::size_t i = 0; i < N; ++i) {
        auto & set = sets.emplace_back(test_data);
        std::shuffle(set.begin(), set.end(), gen);
    }
    std::vector<std::thread> threads;
    threads.reserve(N);
    for (std::size_t i = 0; i < N; ++i) {
        threads.emplace_back([&data = sets[i], this] {
                for (std::size_t i = 0; i < M; ++i) {
                    for (const auto & components : data) {
                        std::vector<int> order;
                        combinations.classify(components, order);
                    }
                }
            });
    }
    for (auto & t : threads) {
        t.join();
    }
}
