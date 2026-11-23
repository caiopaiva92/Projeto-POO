#include "poo/Aplicacao.hpp"

#include <iostream>
#include <utility>

namespace poo {

Aplicacao::Aplicacao(std::string nome) : nome_(std::move(nome)) {}

int Aplicacao::executar() {
    std::cout << "== " << nome_ << " ==\n";
    return 0;
}

const std::string& Aplicacao::getNome() const {
    return nome_;
}

} // namespace poo