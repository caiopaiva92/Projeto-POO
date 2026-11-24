#ifndef POO_ESCRITURAVEL_HPP
#define POO_ESCRITURAVEL_HPP

#include <string>

namespace poo {

class Escrituravel {
public:
    virtual ~Escrituravel() = default;

    virtual void escriturar(int qtd, const std::string& receita) = 0;
    virtual int totalEscriturado() const = 0;
};

} // namespace poo

#endif // POO_ESCRITURAVEL_HPP