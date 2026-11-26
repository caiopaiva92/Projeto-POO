#ifndef POO_MEDICAMENTOSOBPRESCRICAO_HPP
#define POO_MEDICAMENTOSOBPRESCRICAO_HPP

#include "poo/Produto.hpp"

#include <string>

namespace poo {

class MedicamentoSobPrescricao final : public Produto {
public:
    MedicamentoSobPrescricao(std::string nome, std::string principioAtivo, int quantidade,
                             double preco, std::string lote, std::string validade);
    ~MedicamentoSobPrescricao() override;

    bool dispensar(int qtd, const std::string& receita) override;
    std::string tarja() const override;
    std::string condicaoDeVenda() const override;

    static int vivos();
    static int criados();

private:
    static int vivos_;
    static int criados_;
};

} 

#endif 