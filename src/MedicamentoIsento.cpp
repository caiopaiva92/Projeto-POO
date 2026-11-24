#include "poo/MedicamentoIsento.hpp"

#include <utility>

namespace poo {

MedicamentoIsento::MedicamentoIsento(std::string nome, std::string principioAtivo,
                                     int quantidade, double preco,
                                     std::string lote, std::string validade)
    : Produto(std::move(nome), std::move(principioAtivo), quantidade, preco,
              std::move(lote), std::move(validade)) {}

bool MedicamentoIsento::dispensar(int qtd, const std::string& /*receita*/) {
    // MIP: a receita nao e exigida
    return retirar(qtd);
}

std::string MedicamentoIsento::tarja() const {
    return "sem tarja (MIP)";
}

} 