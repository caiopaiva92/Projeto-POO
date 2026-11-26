#ifndef POO_MEDICAMENTOISENTO_HPP
#define POO_MEDICAMENTOISENTO_HPP

#include "poo/Produto.hpp"

#include <string>

namespace poo {

class MedicamentoIsento final : public Produto {
public:
    MedicamentoIsento(std::string nome, std::string principioAtivo, int quantidade,
                      double preco, std::string lote, std::string validade);
    ~MedicamentoIsento() override;

    bool dispensar(int qtd, const std::string& receita) override;
    std::string tarja() const override;
    std::string condicaoDeVenda() const override;

    static int vivos();
    static int criados();

private:
    static int vivos_;
    static int criados_;
};

} // namespace poo

#endif 