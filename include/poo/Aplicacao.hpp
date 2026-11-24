#ifndef POO_APLICACAO_HPP
#define POO_APLICACAO_HPP

#include <ostream>
#include <string>

namespace poo {

// Classe da biblioteca: não usa std::cout.
// Quem imprime é o main, por meio do operador de saída.
class Aplicacao {
public:
    explicit Aplicacao(std::string nome);

    const std::string& getNome() const;

private:
    std::string nome_;
};

std::ostream& operator<<(std::ostream& os, const Aplicacao& app);

} // namespace poo

#endif // POO_APLICACAO_HPP