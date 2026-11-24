# Decisões de Projeto

Registro das principais decisões tomadas durante o desenvolvimento e o motivo de cada uma.

---

## D1 · Organização em `include/poo/` e `src/`

**Decisão:** cabeçalhos em `include/poo/`, um arquivo por classe; implementações e `main.cpp` em `src/`.

**Motivo:** separa interface de implementação. Os cabeçalhos são incluídos pelo caminho do projeto (`#include "poo/Classe.hpp"`), sem caminhos relativos como `../include/`.

---

## D2 · Dois sistemas de build (CMake e Make)

**Decisão:** manter `CMakeLists.txt` e `Makefile`, ambos gerando o executável em `build/`.

**Motivo:** CMake é portátil (Linux, Windows, macOS); o Makefile permite compilar sem instalar CMake. Os dois usam C++17 e os avisos `-Wall -Wextra -Wpedantic`.

---

## D3 · `main.cpp` mínimo

**Decisão:** o `main` apenas cria um objeto `Aplicacao` e chama `executar()`.

**Motivo:** a lógica fica nas classes, o que facilita testar e evoluir o projeto sem mexer no ponto de entrada.

---

## D4 · Ajuste no `.gitignore`

**Decisão:** remover a regra `Makefile` que veio no modelo de `.gitignore` do GitHub.

**Motivo:** o modelo ignora Makefiles gerados pelo CMake, mas neste projeto o Makefile é escrito à mão e precisa ser versionado.


---

## D5 · Classes numa biblioteca separada do executável

**Decisão:** as classes formam a biblioteca `poo` (`add_library`); o `main.cpp` é um executável que liga nela.

**Motivo:** separa o modelo (classes) do programa que o usa, permitindo reaproveitar e testar a biblioteca sem o `main`.

---

## D6 · Classes não imprimem

**Decisão:** nenhuma classe usa `std::cout`; a saída é feita por `operator<<(std::ostream&, ...)`, e quem escolhe onde imprimir é o `main`.

**Motivo:** a classe não fica presa ao terminal — o mesmo operador serve para `std::cout`, arquivo ou `std::ostringstream`.

---

## D7 · Portão de avisos com `-Werror` na biblioteca

**Decisão:** a biblioteca compila com o portão da Unidade I (`-Wall -Wextra -Wpedantic -Wshadow -Wold-style-cast -Wcast-align -Wconversion -Wsign-conversion -Wnon-virtual-dtor -Wdouble-promotion -Wformat=2 -Werror`).

**Motivo:** qualquer aviso vira erro, obrigando o código das classes a ficar limpo (sem conversões implícitas, casts no estilo C, sombreamento etc.).