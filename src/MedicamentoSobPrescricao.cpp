#include "poo/MedicamentoSobPrescricao.hpp"

#include <utility>

namespace poo {

int MedicamentoSobPrescricao::vivos_ = 0;
int MedicamentoSobPrescricao::criados_ = 0;

MedicamentoSobPrescricao::MedicamentoSobPrescricao(std::string nome,
                                                   std::string principioAtivo,
                                                   int quantidade, double preco,
                                                   std::string lote, std::string validade)
    : Produto(std::move(nome), std::move(principioAtivo), quantidade, preco,
              std::move(lote), std::move(validade)) {
    ++vivos_;
    ++criados_;
}

MedicamentoSobPrescricao::~MedicamentoSobPrescricao() {
    --vivos_;
}

bool MedicamentoSobPrescricao::dispensar(int qtd, const std::string& receita) {
    if (receita.empty()) {
        return false;  // sem receita, nao dispensa
    }
    return retirar(qtd);
}

std::string MedicamentoSobPrescricao::tarja() const {
    return "vermelha";
}

std::string MedicamentoSobPrescricao::condicaoDeVenda() const {
    return "venda com receita (sem retencao)";
}

int MedicamentoSobPrescricao::vivos() { return vivos_; }
int MedicamentoSobPrescricao::criados() { return criados_; }

} 