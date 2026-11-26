#include "poo/MedicamentoControlado.hpp"

#include <utility>

namespace poo {

int MedicamentoControlado::vivos_ = 0;
int MedicamentoControlado::criados_ = 0;

MedicamentoControlado::MedicamentoControlado(std::string nome, std::string principioAtivo,
                                             int quantidade, double preco,
                                             std::string lote, std::string validade,
                                             std::string tarja)
    : Produto(std::move(nome), std::move(principioAtivo), quantidade, preco,
              std::move(lote), std::move(validade)),
      tarja_(std::move(tarja)),
      escriturado_(0) {
    ++vivos_;
    ++criados_;
}

MedicamentoControlado::~MedicamentoControlado() {
    --vivos_;
}

bool MedicamentoControlado::dispensar(int qtd, const std::string& receita) {
    if (receita.empty()) {
        return false;  // sem receita, nao dispensa
    }
    if (!retirar(qtd)) {
        return false;  // quantidade invalida ou estoque insuficiente
    }
    escriturar(qtd, receita);
    return true;
}

std::string MedicamentoControlado::tarja() const {
    return tarja_;
}

std::string MedicamentoControlado::condicaoDeVenda() const {
    return "receita retida, " + std::to_string(escriturado_) + " un. escriturada(s)";
}

void MedicamentoControlado::escriturar(int qtd, const std::string& receita) {
    escriturado_ += qtd;
    receitasRetidas_.push_back(receita);
}

int MedicamentoControlado::totalEscriturado() const {
    return escriturado_;
}

int MedicamentoControlado::vivos() { return vivos_; }
int MedicamentoControlado::criados() { return criados_; }

}   