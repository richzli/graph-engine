#pragma once

#include "../../common.hpp"
#include "../../components/arrow.hpp"
#include "../../components/line.hpp"
#include "interactable.hpp"
#include "node.hpp"

class edge : public interactable {
public:
    edge(std::shared_ptr<node> src, std::shared_ptr<node> dst, bool directed);
    edge(std::shared_ptr<node> src, std::shared_ptr<node> dst);

    std::shared_ptr<node> get_src() const;
    std::shared_ptr<node> get_dst() const;

    void set_src(std::shared_ptr<node> src);
    void set_dst(std::shared_ptr<node> dst);

    void update_src();
    void update_dst();
protected:
    std::shared_ptr<node> src, dst;
    bool directed;

    std::unique_ptr<line> obj;
};