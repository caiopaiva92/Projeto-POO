#ifndef POO_PRODUTO_HPP
#define POO_PRODUTO_HPP

#include <ostream>
#include <string>

namespace poo {

class Produto {
public:
    Produto(std::string nome, std::string principioAtivo, int quantidade,
            double preco, std::string lote, std::string validade);
    virtual ~Produto();

    Produto(const Produto&) = delete;
    Produto& operator=(const Produto&) = delete;

    virtual bool dispensar(int qtd, const std::string& receita) = 0;
    virtual std::string tarja() const = 0;

    const std::string& getNome() const;
    const std::string& getPrincipioAtivo() const;
    int getQuantidade() const;
    double getPreco() const;
    const std::string& getLote() const;
    const std::string& getValidade() const;

    bool reajustarPreco(double novoPreco);
    double valorEmEstoque() const;

    static int vivos();

protected:
    bool retirar(int qtd);

private:
    std::string nome_;
    std::string principioAtivo_;
    int quantidade_;
    double preco_;
    std::string lote_;
    std::string validade_;

    static int vivos_;
};

std::ostream& operator<<(std::ostream& os, const Produto& p);

} // namespace poo

#endif // POO_PRODUTO_HPP