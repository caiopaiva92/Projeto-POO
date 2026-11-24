#include "poo/Aplicacao.hpp"

#include <utility>

namespace poo {

Aplicacao::Aplicacao(std::string nome) : nome_(std::move(nome)) {}

const std::string& Aplicacao::getNome() const {
    return nome_;
}

std::ostream& operator<<(std::ostream& os, const Aplicacao& app) {
    return os << "== " << app.getNome() << " ==";
}

} // namespace poo