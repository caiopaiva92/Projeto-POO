# Projeto de POO em C++ – Farmácia Bem-Estar

Projeto da disciplina de Programação Orientada a Objetos, feito por Caio Paiva, aluno do 3º período de Ciência de Dados e Inteligência Artificial da UFPB.

## Sobre o projeto

A Farmácia Bem-Estar é uma farmácia de bairro que controlava o estoque num caderno. O sistema organiza esse estoque:

- medicamentos isentos de prescrição (MIP) podem ser vendidos sem receita;
- medicamentos controlados só saem com receita, e cada saída fica registrada;
- o estoque cadastra, busca, remove e calcula o valor total, sem aceitar nomes repetidos.

Este trabalho continua o sistema que fiz na Unidade I, agora usando herança, polimorfismo, classe abstrata e interface.

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

## Organização

```
include/poo/      cabeçalhos, um por classe
src/              implementações e o main.cpp
CMakeLists.txt    compilação (biblioteca poo + executável app)
Makefile          atalhos que chamam o CMake
DECISAO.md        explicação das escolhas do projeto
```

A pasta `build/` é criada na compilação e não vai para o repositório.

## Classes

| Classe | O que faz | Requisito |
|---|---|---|
| `Produto` | Classe abstrata com o que todo item do estoque tem; conta os objetos vivos | R5 |
| `Escrituravel` | Interface para escriturar as saídas com receita | R6 |
| `MedicamentoIsento` | Medicamento que sai sem receita | R7 |
| `MedicamentoControlado` | Medicamento que exige receita e escritura a saída | R7 e R8 |
| `Estoque` | Guarda os medicamentos (herança privada de `std::vector`) | R9 |

As explicações de cada escolha estão no [DECISAO.md](DECISAO.md).

## Uso de LLM

Usei o Claude (Anthropic) como apoio durante o projeto. Registro abaixo onde ele foi usado:

| Data | Onde usei | O que fiz com o resultado |
|---|---|---|
| 23/11/2026 | Estrutura de pastas, `CMakeLists.txt`, `Makefile` e `.gitignore` (R1 e R2) | Usei a estrutura, revisei e testei a compilação |
| 23/11/2026 | Ajustes do R3: biblioteca com `add_library`, portão com `-Werror` e `operator<<` no lugar do `cout` | Usei as alterações e compilei com o portão |

Todo o código foi lido, compilado e testado por mim antes de cada commit.