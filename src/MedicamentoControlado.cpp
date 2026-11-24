#include "poo/MedicamentoControlado.hpp"

#include <utility>

namespace poo {

MedicamentoControlado::MedicamentoControlado(std::string nome, std::string principioAtivo,
                                             int quantidade, double preco,
                                             std::string lote, std::string validade,
                                             std::string tarja)
    : Produto(std::move(nome), std::move(principioAtivo), quantidade, preco,
              std::move(lote), std::move(validade)),
      tarja_(std::move(tarja)),
      escriturado_(0) {}

bool MedicamentoControlado::dispensar(int qtd, const std::string& receita) {
    if (receita.empty()) {
        return false;  
    }
    if (!retirar(qtd)) {
        return false;  
    }
    escriturar(qtd, receita);
    return true;
}

std::string MedicamentoControlado::tarja() const {
    return tarja_;
}

void MedicamentoControlado::escriturar(int qtd, const std::string& receita) {
    escriturado_ += qtd;
    receitasRetidas_.push_back(receita);
}

int MedicamentoControlado::totalEscriturado() const {
    return escriturado_;
}

const std::vector<std::string>& MedicamentoControlado::getReceitasRetidas() const {
    return receitasRetidas_;
}

} 