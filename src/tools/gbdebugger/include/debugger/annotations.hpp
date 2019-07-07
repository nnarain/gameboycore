
#pragma once

#include <cstdint>
#include <tuple>
#include <string>
#include <vector>

namespace utils
{
    struct BitRange
    {
        BitRange(int s, int e) : start{s}, end{e}{}
        BitRange() : BitRange{-1, -1} {}
        BitRange(int v) : BitRange(v, v) {}

        int start;
        int end;
    };

    // BitRange, Description, Value
    using Annotation = std::tuple<BitRange, std::string, std::string>;

    struct IoAnnotation
    {
        std::string io_description;
        std::vector<Annotation> annotations;

        IoAnnotation()
        {
        }

        IoAnnotation(const std::string& desc, const std::vector<Annotation>& annotations)
            : io_description{desc}
            , annotations{annotations}
        {
        }
    };

    IoAnnotation annotateIO(uint16_t address, uint8_t value);
}
