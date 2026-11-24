// Farmacia Bem-Estar - demonstracao do sistema de estoque.
// So o main imprime; as classes usam apenas operator<<.

#include "poo/Estoque.hpp"
#include "poo/MedicamentoControlado.hpp"
#include "poo/MedicamentoIsento.hpp"

#include <iostream>
#include <memory>

using poo::Estoque;
using poo::MedicamentoControlado;
using poo::MedicamentoIsento;
using poo::Produto;

namespace {

void mostrar(const char* acao, bool ok) {
    std::cout << "  " << acao << ": " << (ok ? "OK" : "RECUSADO") << '\n';
}

} // namespace

int main() {
    std::cout << "===== FARMACIA BEM-ESTAR - SISTEMA DE ESTOQUE =====\n";

    {
        Estoque estoque;

        std::cout << "\n>> Cadastrando medicamentos\n";
        estoque.adicionar(std::make_unique<MedicamentoIsento>(
            "Dipirona", "Dipirona sodica", 100, 4.50, "DP2026A", "12/2027"));
        estoque.adicionar(std::make_unique<MedicamentoIsento>(
            "Paracetamol", "Paracetamol", 120, 5.20, "PC2026E", "10/2027"));
        estoque.adicionar(std::make_unique<MedicamentoControlado>(
            "Amoxicilina", "Amoxicilina", 40, 22.90, "AM2026B", "03/2027",
            "vermelha (retencao de receita)"));
        estoque.adicionar(std::make_unique<MedicamentoControlado>(
            "Clonazepam", "Clonazepam", 30, 18.40, "CZ2026F", "06/2028", "preta"));

        mostrar("Cadastrar Dipirona de novo (nome repetido)",
                estoque.adicionar(std::make_unique<MedicamentoIsento>(
                    "Dipirona", "Dipirona sodica", 10, 4.50, "DP2026X", "01/2028")));

        std::cout << "  Produtos no estoque: " << estoque.size()
                  << " | vivos=" << Produto::vivos() << '\n';

        std::cout << "\n=== Estoque inicial ===\n" << estoque << '\n';

        std::cout << "\n>> Atendimentos do dia (polimorfismo em dispensar)\n";
        Produto* dipirona = estoque.buscar("Dipirona");
        Produto* amoxicilina = estoque.buscar("Amoxicilina");
        Produto* clonazepam = estoque.buscar("Clonazepam");

        mostrar("Dipirona x20, sem receita", dipirona->dispensar(20, ""));
        mostrar("Amoxicilina x5, sem receita", amoxicilina->dispensar(5, ""));
        mostrar("Amoxicilina x5, receita REC-001", amoxicilina->dispensar(5, "REC-001"));
        mostrar("Clonazepam x2, receita B1-778", clonazepam->dispensar(2, "B1-778"));
        mostrar("Clonazepam x500, receita B1-779", clonazepam->dispensar(500, "B1-779"));
        mostrar("Reajustar Paracetamol para R$ 5,80",
                estoque.buscar("Paracetamol")->reajustarPreco(5.80));

        std::cout << "\n>> Escrituracao (contrato Escrituravel)\n";
        if (auto* controlado = dynamic_cast<MedicamentoControlado*>(clonazepam)) {
            std::cout << "  Clonazepam escriturado: " << controlado->totalEscriturado()
                      << " unidade(s), " << controlado->getReceitasRetidas().size()
                      << " receita(s) retida(s)\n";
        }

        std::cout << "\n=== Estoque apos atendimentos ===\n" << estoque << '\n';

        std::cout << "\n>> Retirando Paracetamol do estoque\n";
        mostrar("Remover Paracetamol", estoque.remover("Paracetamol"));
        std::cout << "  Produtos no estoque: " << estoque.size()
                  << " | vivos=" << Produto::vivos() << '\n';

        std::cout << "\n>> Fechando o estoque (destroi os produtos restantes)\n";
    }

    std::cout << "vivos=" << Produto::vivos() << '\n';
    return 0;
}