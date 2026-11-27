# Projeto de POO em C++ – Farmácia Bem-Estar

Projeto da disciplina de Programação Orientada a Objetos, feito por Caio Paiva, aluno do 3º período de Ciência de Dados e Inteligência Artificial da UFPB.

## O tema

A Farmácia Bem-Estar é uma farmácia de bairro que controlava o estoque num caderno. Este sistema organiza esse estoque: cada medicamento tem nome, princípio ativo, quantidade, preço, lote e validade, e o estoque cadastra, busca, remove, repõe e calcula o valor total, sem aceitar nomes repetidos.

O ponto principal é que nem todo medicamento sai da farmácia do mesmo jeito. O isento de prescrição (MIP) é vendido sem receita, o de tarja vermelha só sai com receita, e o controlado só sai com receita, que fica retida e é escriturada. O projeto continua o sistema que fiz na Unidade I, agora usando classe abstrata, interface, herança e polimorfismo.

## Como compilar e rodar

É preciso ter CMake (3.16 ou mais novo), um compilador com C++17 e o make.

```bash
make            # configura e compila
make roda       # compila e roda a demonstração
make verifica   # compila com -Werror, roda e confere se a última linha é vivos=0
make limpa      # apaga a pasta build/
```

Também dá para usar o CMake direto:

```bash
cmake -S . -B build
cmake --build build
./build/app
```

## As classes

| Classe | Papel | Forma de herança |
|---|---|---|
| `Produto` | Base abstrata: o que todo medicamento do estoque tem; monta a ficha e repõe estoque (`+=`) | Base da hierarquia |
| `Escrituravel` | Interface: obrigação de escriturar as saídas com receita retida | Interface pura, sem dados |
| `MedicamentoIsento` | Medicamento que sai sem receita (MIP) | Pública de `Produto`, `final` |
| `MedicamentoSobPrescricao` | Medicamento de tarja vermelha, sai só com receita | Pública de `Produto`, `final` |
| `MedicamentoControlado` | Sai só com receita, que fica retida e escriturada | Múltipla: pública de `Produto` e de `Escrituravel`, `final` |
| `Estoque` | Guarda os medicamentos e é dono deles | Privada de `std::vector<std::unique_ptr<Produto>>` |

O arquivo `include/poo/contrato.hpp` tem `static_assert` que conferem essa hierarquia na compilação. As respostas sobre as escolhas do projeto estão no [DECISAO.md](DECISAO.md).

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