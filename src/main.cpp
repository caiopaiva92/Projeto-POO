// Farmacia Bem-Estar - demonstracao do sistema de estoque.

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

void mostrarContadores() {
    std::cout << "  Isento:         criados=" << MedicamentoIsento::criados()
              << " vivos=" << MedicamentoIsento::vivos() << '\n'
              << "  SobPrescricao:  criados=" << MedicamentoSobPrescricao::criados()
              << " vivos=" << MedicamentoSobPrescricao::vivos() << '\n'
              << "  Controlado:     criados=" << MedicamentoControlado::criados()
              << " vivos=" << MedicamentoControlado::vivos() << '\n';
}

} 

int main() {
    std::cout << "===== FARMACIA BEM-ESTAR - SISTEMA DE ESTOQUE =====\n";

    {
        Estoque estoque;

        std::cout << "\n>> Cadastrando medicamentos (tres tipos, todos com make_unique)\n";
        estoque.adicionar(std::make_unique<MedicamentoIsento>(
            "Dipirona", "Dipirona sodica", 100, 4.50, "DP2026A", "12/2027"));
        estoque.adicionar(std::make_unique<MedicamentoIsento>(
            "Paracetamol", "Paracetamol", 120, 5.20, "PC2026E", "10/2027"));
        estoque.adicionar(std::make_unique<MedicamentoSobPrescricao>(
            "Losartana", "Losartana potassica", 80, 9.75, "LS2026C", "08/2028"));
        estoque.adicionar(std::make_unique<MedicamentoControlado>(
            "Amoxicilina", "Amoxicilina", 40, 22.90, "AM2026B", "03/2027", "vermelha"));
        estoque.adicionar(std::make_unique<MedicamentoControlado>(
            "Clonazepam", "Clonazepam", 30, 18.40, "CZ2026F", "06/2028", "preta"));

        mostrar("Cadastrar Dipirona de novo (nome repetido)",
                estoque.adicionar(std::make_unique<MedicamentoIsento>(
                    "Dipirona", "Dipirona sodica", 10, 4.50, "DP2026X", "01/2028")));
        std::cout << "  Produtos no estoque: " << estoque.size()
                  << " | vivos=" << totalVivos() << '\n';

        std::cout << "\n=== Estoque inicial ===\n" << estoque << '\n';

        std::cout << "\n>> Atendimentos do dia (dispensar e virtual)\n";
        Produto* dipirona = estoque.buscar("Dipirona");
        Produto* losartana = estoque.buscar("Losartana");
        Produto* amoxicilina = estoque.buscar("Amoxicilina");
        Produto* clonazepam = estoque.buscar("Clonazepam");

        mostrar("Dipirona x20, sem receita", dipirona->dispensar(20, ""));
        mostrar("Losartana x30, sem receita", losartana->dispensar(30, ""));
        mostrar("Losartana x30, receita REC-010", losartana->dispensar(30, "REC-010"));
        mostrar("Amoxicilina x5, receita REC-001", amoxicilina->dispensar(5, "REC-001"));
        mostrar("Clonazepam x2, receita B1-778", clonazepam->dispensar(2, "B1-778"));
        mostrar("Clonazepam x500, receita B1-779", clonazepam->dispensar(500, "B1-779"));
        mostrar("Reajustar Paracetamol para R$ 5,80",
                estoque.buscar("Paracetamol")->reajustarPreco(5.80));

        std::cout << "\n>> Reposicao (operator+=)\n";
        *losartana += 50;
        std::cout << "  Losartana += 50 -> Qtd: " << losartana->getQuantidade() << '\n';

        std::cout << "\n=== Estoque apos atendimentos ===\n" << estoque << '\n';

        std::cout << "\n>> Retirando Paracetamol do estoque\n";
        mostrar("Remover Paracetamol", estoque.remover("Paracetamol"));
        mostrarContadores();

        std::cout << "\n>> Fechando o estoque (destroi os produtos restantes)\n";
    }

    mostrarContadores();
    std::cout << "vivos=" << totalVivos() << '\n';
    return 0;
}