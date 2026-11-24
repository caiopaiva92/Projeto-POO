#include "poo/Estoque.hpp"

#include <algorithm>
#include <iomanip>
#include <utility>

namespace poo {

bool Estoque::adicionar(std::unique_ptr<Produto> produto) {
    if (!produto || buscar(produto->getNome()) != nullptr) {
        return false;
    }
    push_back(std::move(produto));
    return true;
}

bool Estoque::remover(const std::string& nome) {
    auto it = std::find_if(begin(), end(), [&nome](const std::unique_ptr<Produto>& p) {
        return p->getNome() == nome;
    });
    if (it == end()) {
        return false;
    }
    erase(it);  // o unique_ptr destroi o produto aqui
    return true;
}

Produto* Estoque::buscar(const std::string& nome) const {
    for (const auto& p : *this) {
        if (p->getNome() == nome) {
            return p.get();
        }
    }
    return nullptr;
}

double Estoque::valorTotal() const {
    double total = 0.0;
    for (const auto& p : *this) {
        total += p->valorEmEstoque();
    }
    return total;
}

std::ostream& operator<<(std::ostream& os, const Estoque& e) {
    for (const auto& p : e) {
        os << "  - " << *p << '\n';
    }
    return os << "  Valor total do estoque: R$ " << std::fixed
              << std::setprecision(2) << e.valorTotal();
}

} 