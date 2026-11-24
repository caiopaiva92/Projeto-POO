#ifndef POO_ESTOQUE_HPP
#define POO_ESTOQUE_HPP

#include "poo/Produto.hpp"

#include <memory>
#include <ostream>
#include <string>
#include <vector>

namespace poo {

class Estoque : private std::vector<std::unique_ptr<Produto>> {
    using Base = std::vector<std::unique_ptr<Produto>>;

public:
    using Base::size;
    using Base::empty;

    // Recusa produto nulo ou com nome repetido
    bool adicionar(std::unique_ptr<Produto> produto);
    bool remover(const std::string& nome);
    Produto* buscar(const std::string& nome) const;
    double valorTotal() const;

    friend std::ostream& operator<<(std::ostream& os, const Estoque& e);
};

std::ostream& operator<<(std::ostream& os, const Estoque& e);

} 

#endif 