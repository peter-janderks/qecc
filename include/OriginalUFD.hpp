//
// Created by lucas on 09/06/22.
//

#ifndef QUNIONFIND_IMPROVEDUF_HPP
#define QUNIONFIND_IMPROVEDUF_HPP
#include "Decoder.hpp"
class OriginalUFD: public Decoder {
public:
    using Decoder::Decoder;
    void decode(const std::vector<bool>& syndrome) override;
    void reset() override;
private:
    [[nodiscard]] bool                     isValidComponent(const std::unordered_set<std::size_t>& component, const std::unordered_set<std::size_t>& syndrome) const;
    bool                     containsInvalidComponents(const std::unordered_set<std::size_t>& components, const std::unordered_set<std::size_t>& syndrome,
                                                       std::vector<std::unordered_set<std::size_t>>& invalidComps) const;
    [[nodiscard]] std::vector<std::size_t> computeInteriorBitNodes(const std::unordered_set<std::size_t>& component) const;
    [[nodiscard]] std::unordered_set<std::size_t>    getEstimateForComponent(const std::unordered_set<std::size_t>& component, const std::unordered_set<std::size_t>& syndrome) const;
    void standardGrowth( std::unordered_set<std::size_t>& comps);
    void singleClusterSmallestFirstGrowth( std::unordered_set<std::size_t>& comps);
    void singleClusterRandomFirstGrowth( std::unordered_set<std::size_t>& comps);
    void singleQubitRandomFirstGrowth( std::unordered_set<std::size_t>& comps);
    [[nodiscard]] std::vector<std::unordered_set<std::size_t>>     getConnectedComps(const std::unordered_set<std::size_t>& nodes) const;
};
#endif //QUNIONFIND_IMPROVEDUF_HPP
