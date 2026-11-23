#ifndef POO_APLICACAO_HPP
#define POO_APLICACAO_HPP

#include <string>

namespace poo {

// Classe de entrada do programa: o main.cpp só cria e executa.
class Aplicacao {
public:
    explicit Aplicacao(std::string nome);

    int executar();

    const std::string& getNome() const;

private:
    std::string nome_;
};

} // namespace poo

#endif // POO_APLICACAO_HPP