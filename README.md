# Projeto de POO em C++ – Farmácia Bem-Estar

Projeto da disciplina de Programação Orientada a Objetos. Autor: Caio Paiva, 3º período de Ciência de Dados e Inteligência Artificial (UFPB).

## O tema

A Farmácia Bem-Estar é uma farmácia de bairro que anotava o estoque num caderno. O sistema guarda os medicamentos com nome, princípio ativo, quantidade, preço, lote e validade. Dá para cadastrar, buscar, remover, repor e ver o valor total do estoque, e ele não aceita dois medicamentos com o mesmo nome. Cada tipo de medicamento sai de um jeito diferente. O isento (MIP) sai sem receita, o de tarja vermelha só sai com receita e o controlado só sai com receita, que fica retida e é escriturada. O projeto continua o sistema que fiz na Unidade I, agora com classe abstrata, interface, herança e polimorfismo.

## Como compilar e rodar

Precisa de CMake 3.16 ou mais novo, compilador com C++17 e make.

```bash
make            # configura e compila
make roda       # compila e roda a demonstração
make verifica   # compila com -Werror, roda e confere se a última linha é vivos=0
make limpa      # apaga a pasta build/
```

Ou direto pelo CMake:

```bash
cmake -S . -B build
cmake --build build
./build/app
```

## Classes

| Classe | Papel | Herança |
|---|---|---|
| `Produto` | Classe abstrata com os dados de todo medicamento; monta a ficha e repõe estoque (`+=`) | Base |
| `Escrituravel` | Interface para escriturar as saídas com receita retida | Interface pura, sem atributos |
| `MedicamentoIsento` | Sai sem receita | Pública de `Produto`, `final` |
| `MedicamentoSobPrescricao` | Tarja vermelha, sai só com receita | Pública de `Produto`, `final` |
| `MedicamentoControlado` | Sai só com receita, que fica retida e é escriturada | Múltipla: pública de `Produto` e de `Escrituravel`, `final` |
| `Estoque` | Guarda os medicamentos e é dono deles | Privada de `std::vector<std::unique_ptr<Produto>>` |

O `include/poo/contrato.hpp` tem os `static_assert` que conferem essa hierarquia quando compila. As respostas sobre as escolhas estão no [DECISAO.md](DECISAO.md).

## Saída do `make roda`

```
=== 1. o acervo polimorfico ===
  Cadastrar Dipirona de novo (nome repetido): RECUSADO
  Dipirona x20, sem receita: OK
  Losartana x30, sem receita: RECUSADO
  Losartana x30, receita REC-010: OK
  Clonazepam x2, receita B1-778: OK
  Clonazepam x500, receita B1-779: RECUSADO
  - Dipirona     | Dipirona sodica      | Qtd: 80   | R$ 4.50 | Lote DP2026A (val. 12/2027) | Tarja livre (MIP) | venda sem receita
  - Losartana    | Losartana potassica  | Qtd: 50   | R$ 9.75 | Lote LS2026C (val. 08/2028) | Tarja vermelha | venda com receita (sem retencao)
  - Clonazepam   | Clonazepam           | Qtd: 28   | R$ 18.40 | Lote CZ2026F (val. 06/2028) | Tarja preta | receita retida, 2 un. escriturada(s)
  Valor total do estoque: R$ 1362.70

=== 2. os operadores ===
  operator<< : Losartana    | Losartana potassica  | Qtd: 50   | R$ 9.75 | Lote LS2026C (val. 08/2028) | Tarja vermelha | venda com receita (sem retencao)
  operator+= : Losartana += 50 -> Qtd 100

=== 3. os contadores ===
  dentro do escopo: MedicamentoIsento vivos=1 criados=2
  dentro do escopo: MedicamentoSobPrescricao vivos=1 criados=1
  dentro do escopo: MedicamentoControlado vivos=1 criados=1
  depois do escopo: MedicamentoIsento vivos=0
  depois do escopo: MedicamentoSobPrescricao vivos=0
  depois do escopo: MedicamentoControlado vivos=0
vivos=0
```

## Uso de LLM

Usei o Claude (Anthropic) como apoio durante o projeto. Registro abaixo onde ele foi usado:

| Data | Onde usei | O que fiz com o resultado |
|---|---|---|
| 23/11/2026 | Estrutura de pastas, `CMakeLists.txt`, `Makefile` e `.gitignore` (R1 e R2) | Usei a estrutura, revisei e testei a compilação |
| 23/11/2026 | Ajustes do R3: biblioteca com `add_library`, portão com `-Werror` e `operator<<` no lugar do `cout` | Usei as alterações e compilei com o portão |

Todo o código foi lido, compilado e testado por mim antes de cada commit.