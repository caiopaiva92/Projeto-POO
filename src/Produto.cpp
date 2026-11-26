#include "poo/Produto.hpp"

#include <iomanip>
#include <sstream>
#include <utility>

namespace poo {

Produto::Produto(std::string nome, std::string principioAtivo, int quantidade,
                 double preco, std::string lote, std::string validade)
    : nome_(std::move(nome)),
      principioAtivo_(std::move(principioAtivo)),
      quantidade_(quantidade > 0 ? quantidade : 0),
      preco_(preco > 0.0 ? preco : 0.0),
      lote_(std::move(lote)),
      validade_(std::move(validade)) {}

std::string Produto::ficha() const {
    std::ostringstream os;
    os << std::left << std::setw(12) << nome_
       << " | " << std::setw(20) << principioAtivo_
       << " | Qtd: " << std::setw(4) << quantidade_
       << " | R$ " << std::fixed << std::setprecision(2) << preco_
       << " | Lote " << lote_ << " (val. " << validade_ << ")"
       << " | Tarja " << tarja()
       << " | " << condicaoDeVenda();
    return os.str();
}

Produto& Produto::operator+=(int qtd) {
    if (qtd > 0) {
        quantidade_ += qtd;
    }
    return *this;
}

const std::string& Produto::getNome() const { return nome_; }
const std::string& Produto::getPrincipioAtivo() const { return principioAtivo_; }
int Produto::getQuantidade() const { return quantidade_; }
double Produto::getPreco() const { return preco_; }
const std::string& Produto::getLote() const { return lote_; }
const std::string& Produto::getValidade() const { return validade_; }

bool Produto::reajustarPreco(double novoPreco) {
    if (novoPreco <= 0.0) {
        return false;
    }
    preco_ = novoPreco;
    return true;
}

double Produto::valorEmEstoque() const {
    return static_cast<double>(quantidade_) * preco_;
}

bool Produto::retirar(int qtd) {
    if (qtd <= 0 || qtd > quantidade_) {
        return false;
    }
    quantidade_ -= qtd;
    return true;
}

std::ostream& operator<<(std::ostream& os, const Produto& p) {
    return os << p.ficha();
}

} 