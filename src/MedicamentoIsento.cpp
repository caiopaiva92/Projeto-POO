#include "poo/MedicamentoIsento.hpp"

#include <utility>

namespace poo {

int MedicamentoIsento::vivos_ = 0;
int MedicamentoIsento::criados_ = 0;

MedicamentoIsento::MedicamentoIsento(std::string nome, std::string principioAtivo,
                                     int quantidade, double preco,
                                     std::string lote, std::string validade)
    : Produto(std::move(nome), std::move(principioAtivo), quantidade, preco,
              std::move(lote), std::move(validade)) {
    ++vivos_;
    ++criados_;
}

MedicamentoIsento::~MedicamentoIsento() {
    --vivos_;
}

bool MedicamentoIsento::dispensar(int qtd, const std::string& /*receita*/) {
    // MIP: a receita nao e exigida
    return retirar(qtd);
}

std::string MedicamentoIsento::tarja() const {
    return "livre (MIP)";
}

std::string MedicamentoIsento::condicaoDeVenda() const {
    return "venda sem receita";
}

int MedicamentoIsento::vivos() { return vivos_; }
int MedicamentoIsento::criados() { return criados_; }

} 