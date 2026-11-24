# Projeto - Programação Orientada a Objetos (POO) em C++

---

## Sobre o Projeto
Bem-vindo ao repositório do Projeto de Programação Orientada a Objetos (POO).

Este repositório contém o código-fonte, a documentação e os artefatos do projeto prático da disciplina de POO. O objetivo principal do trabalho foi aplicar na prática os conceitos fundamentais do paradigma orientado a objetos, como: **Abstração**, **Encapsulamento**, **Herança** e **Polimorfismo**, na resolução de um problema real de engenharia de software utilizando **C++**.

O projeto é realizado pelo autor Caio Paiva que encontra-se no terceiro período do curso de Ciência de Dados e Inteligencia Artificial da Universidade Federal da Paraíba (UFPB) e nas seções a seguir, você encontrará a especificação dos requisitos implementados, as instruções para execução da aplicação e os detalhes da estrutura orientada a objetos.

---

## Tecnologias Utilizadas
- **Linguagem:** C++ (C++17 ou superior)
- **Compilador:** GCC / Clang / MSVC
- **IDE / Editor:** Visual Studio Code (VS Code)
- **Controle de Versão:** Git / GitHub

---

## Estrutura e Conceitos Aplicados
O projeto foi desenvolvido aplicando os pilares da Orientação a Objetos:
- **Abstração:** Mapeamento do domínio do problema em classes e objetos.
- **Encapsulamento:** Utilização de modificadores de acesso (`private`, `protected`, `public`) e métodos *getters* e *setters*.
- **Herança:** Derivação de classes para reaproveitamento de código e organização hierárquica.
- **Polimorfismo:** Uso de métodos virtuais (`virtual`) e sobrescrita para comportamentos dinâmicos.

---


---

## Estrutura de Pastas

```
include/poo/      cabeçalhos (.hpp), um por classe
src/              implementações (.cpp) e o main.cpp
CMakeLists.txt    build com CMake
Makefile          build com Make
README.md         este arquivo
DECISAO.md        decisões de projeto
.gitignore        ignora a pasta build/
```

A pasta `build/` é gerada na compilação e **não é versionada**.

---

## Como Compilar e Executar

### Com CMake

```bash
cmake -S . -B build
cmake --build build
./build/app
```

### Com Make

```bash
make        # compila
make run    # compila e executa
make clean  # apaga a pasta build/
```

---

## Uso de LLM

Este projeto utilizou modelo de linguagem (LLM) como apoio. Registro do uso:

| Data | Ferramenta | Para quê | O que foi aproveitado / alterado |
|------|-----------|----------|----------------------------------|
| 23/11/2026 | Claude (Anthropic) | Montar a estrutura de pastas, `CMakeLists.txt`, `Makefile`, `.gitignore` e seções do README conforme R1 e R2 | Estrutura e arquivos de build aproveitados; revisados e testados pelo autor |

Todo código gerado com apoio de LLM foi lido, compilado e testado pelo autor antes do commit.