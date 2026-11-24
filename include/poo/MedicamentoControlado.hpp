#ifndef POO_MEDICAMENTOCONTROLADO_HPP
#define POO_MEDICAMENTOCONTROLADO_HPP

#include "poo/Escrituravel.hpp"
#include "poo/Produto.hpp"

#include <string>
#include <vector>

namespace poo {

class MedicamentoControlado final : public Produto, public Escrituravel {
public:
    MedicamentoControlado(std::string nome, std::string principioAtivo, int quantidade,
                          double preco, std::string lote, std::string validade,
                          std::string tarja);

    bool dispensar(int qtd, const std::string& receita) override;
    std::string tarja() const override;

    void escriturar(int qtd, const std::string& receita) override;
    int totalEscriturado() const override;

    const std::vector<std::string>& getReceitasRetidas() const;

private:
    std::string tarja_;
    int escriturado_;
    std::vector<std::string> receitasRetidas_;
};

} 

#endif // POO_MEDICAMENTOCONTROLADO_HPP