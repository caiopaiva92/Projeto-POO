// Farmacia Bem-Estar - demonstracao do sistema de estoque.
// So o main imprime; as classes usam apenas operator<<.

#include "poo/contrato.hpp"

#include "poo/Estoque.hpp"
#include "poo/MedicamentoControlado.hpp"
#include "poo/MedicamentoIsento.hpp"
#include "poo/MedicamentoSobPrescricao.hpp"

#include <iostream>
#include <memory>

using poo::Estoque;
using poo::MedicamentoControlado;
using poo::MedicamentoIsento;
using poo::MedicamentoSobPrescricao;
using poo::Produto;

namespace {

void mostrar(const char* acao, bool ok) {
    std::cout << "  " << acao << ": " << (ok ? "OK" : "RECUSADO") << '\n';
}

int totalVivos() {
    return MedicamentoIsento::vivos() + MedicamentoSobPrescricao::vivos() +
           MedicamentoControlado::vivos();
}

} 

int main() {
    {
        Estoque estoque;

        std::cout << "=== 1. o acervo polimorfico ===\n";
        estoque.adicionar(std::make_unique<MedicamentoIsento>(
            "Dipirona", "Dipirona sodica", 100, 4.50, "DP2026A", "12/2027"));
        estoque.adicionar(std::make_unique<MedicamentoSobPrescricao>(
            "Losartana", "Losartana potassica", 80, 9.75, "LS2026C", "08/2028"));
        estoque.adicionar(std::make_unique<MedicamentoControlado>(
            "Clonazepam", "Clonazepam", 30, 18.40, "CZ2026F", "06/2028", "preta"));
        mostrar("Cadastrar Dipirona de novo (nome repetido)",
                estoque.adicionar(std::make_unique<MedicamentoIsento>(
                    "Dipirona", "Dipirona sodica", 10, 4.50, "DP2026X", "01/2028")));

        Produto* dipirona = estoque.buscar("Dipirona");
        Produto* losartana = estoque.buscar("Losartana");
        Produto* clonazepam = estoque.buscar("Clonazepam");

        mostrar("Dipirona x20, sem receita", dipirona->dispensar(20, ""));
        mostrar("Losartana x30, sem receita", losartana->dispensar(30, ""));
        mostrar("Losartana x30, receita REC-010", losartana->dispensar(30, "REC-010"));
        mostrar("Clonazepam x2, receita B1-778", clonazepam->dispensar(2, "B1-778"));
        mostrar("Clonazepam x500, receita B1-779", clonazepam->dispensar(500, "B1-779"));
        std::cout << estoque << '\n';

        std::cout << "\n=== 2. os operadores ===\n";
        std::cout << "  operator<< : " << *losartana << '\n';
        *losartana += 50;
        std::cout << "  operator+= : Losartana += 50 -> Qtd " << losartana->getQuantidade()
                  << '\n';

        std::cout << "\n=== 3. os contadores ===\n";
        std::cout << "  dentro do escopo: MedicamentoIsento vivos="
                  << MedicamentoIsento::vivos() << " criados=" << MedicamentoIsento::criados()
                  << '\n'
                  << "  dentro do escopo: MedicamentoSobPrescricao vivos="
                  << MedicamentoSobPrescricao::vivos()
                  << " criados=" << MedicamentoSobPrescricao::criados() << '\n'
                  << "  dentro do escopo: MedicamentoControlado vivos="
                  << MedicamentoControlado::vivos()
                  << " criados=" << MedicamentoControlado::criados() << '\n';
    }

    std::cout << "  depois do escopo: MedicamentoIsento vivos=" << MedicamentoIsento::vivos()
              << '\n'
              << "  depois do escopo: MedicamentoSobPrescricao vivos="
              << MedicamentoSobPrescricao::vivos() << '\n'
              << "  depois do escopo: MedicamentoControlado vivos="
              << MedicamentoControlado::vivos() << '\n';
    std::cout << "vivos=" << totalVivos() << '\n';
    return 0;
}