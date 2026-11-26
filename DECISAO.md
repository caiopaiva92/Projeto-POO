# Decisões do projeto

O projeto continua o sistema da Farmácia Bem-Estar que fiz na Unidade I. A ideia é a mesma: uma farmácia de bairro que controlava o estoque num caderno e agora passa a usar um sistema. Abaixo explico as principais escolhas que fiz e por quê.

## Organização e compilação

**Pastas.** Coloquei os cabeçalhos em `include/poo/` (um por classe) e as implementações em `src/`. Os includes usam o caminho do projeto, por exemplo `#include "poo/Produto.hpp"`, em vez de `../include/...`.

**Biblioteca separada.** As classes viram a biblioteca `poo` no CMake e o `main.cpp` é só o executável que usa essa biblioteca. Assim o modelo fica separado do programa de demonstração.

**Classes não imprimem.** Na Unidade I as classes tinham `cout` dentro. Agora nenhuma classe imprime nada: o `Produto` e o `Estoque` têm `operator<<` e quem decide o que mostrar na tela é o `main`.

**Portão de avisos.** A biblioteca compila com os mesmos avisos do laboratório da Unidade I e com `-Werror`. Para passar, precisei colocar `_` no fim dos atributos (o `-Wshadow` reclamava dos parâmetros com o mesmo nome) e usar `static_cast` quando converto `int` para `double`.

**Makefile.** O Makefile não compila nada sozinho, só chama o CMake. Fiz assim para não ter duas configurações diferentes de compilação. No `make verifica` tirei o `\r` da última linha porque no Windows a saída vinha com ele e a comparação com `vivos=0` falhava.

**.gitignore.** O modelo do GitHub ignorava qualquer arquivo chamado `Makefile`. Tirei essa linha, porque o meu Makefile foi escrito à mão e precisa estar no repositório.

## Hierarquia de classes

```
                  Produto (abstrata)          Escrituravel (interface)
               /          |          \               /
  MedicamentoIsento  MedicamentoSob-   MedicamentoControlado
                     Prescricao

  Estoque (herda de forma privada de vector<unique_ptr<Produto>>)
```

As três concretas são as três formas de venda que uma farmácia usa no dia a dia: sem receita, com receita e com receita retida.

### Produto (R5)

É a base de tudo que fica no estoque: nome, princípio ativo, quantidade, preço, lote e validade. Ela tem três funções puramente virtuais, `dispensar()`, `tarja()` e `condicaoDeVenda()`, porque essas coisas dependem do tipo de medicamento. Não faz sentido criar um "produto" genérico.

O destrutor é virtual porque o estoque apaga os medicamentos através de ponteiro para `Produto`. Também apaguei o construtor de cópia e o `operator=`, já que copiar uma classe base por valor cortaria a parte da classe filha.

### Escrituravel (R6)

Escolhi a escrituração das saídas de medicamentos controlados (receita retida, SNGPC) como contrato. A interface só tem `escriturar()`, `totalEscriturado()` e o destrutor virtual, sem nenhum atributo. Pensei nela como algo que o medicamento *faz* (escriturar), e não como algo que ele *é*.

### As três concretas (R7 e R8)

Todas são `final` e todas as funções sobrescritas têm `override`.

- `MedicamentoIsento` (MIP): dispensa sem pedir receita.
- `MedicamentoSobPrescricao` (tarja vermelha): só dispensa com receita, mas a receita não fica retida.
- `MedicamentoControlado`: só dispensa com receita e escritura a saída. Ele herda de `Produto` e de `Escrituravel`, e é o único lugar com herança múltipla. Isso não dá problema porque a interface não tem dados, então nada fica duplicado.

### Estoque (R9)

O estoque *usa* um vector por dentro, mas não *é* um vector. Por isso a herança é `private`. Ele guarda `unique_ptr<Produto>`, então é dono dos medicamentos: quando o estoque deixa de existir, os medicamentos também deixam.

Com `using` deixei visíveis só o `size` e o `empty`, porque "quantos produtos tem" e "está vazio" são perguntas que fazem sentido para a farmácia.

O que eu não deixei visível:

- `push_back`, `insert` e `emplace_back`, porque daria para colocar um produto nulo ou repetido. No lugar deles tem o `adicionar()`, que confere antes.
- `operator[]`, `at`, `front` e `back`, porque dariam acesso direto ao `unique_ptr` e alguém poderia trocar ou tirar o produto de dentro do estoque.
- `begin` e `end`, pelo mesmo motivo. Para listar, uso o `operator<<` do estoque.
- `erase`, `clear` e `pop_back`. A farmácia remove um medicamento pelo nome, então criei o `remover(nome)`.
- `resize`, `reserve` e `capacity`, que são detalhes do vector e não têm significado para a farmácia.

## Polimorfismo, posse e operadores

### Contêiner polimórfico (R10)

O vector dentro do `Estoque` guarda os três tipos de medicamento juntos, como `unique_ptr<Produto>`. Quando o estoque lista os produtos ou o `main` chama `dispensar()`, a chamada vai pelo ponteiro para `Produto` e cada medicamento responde do seu jeito. Não tem nenhum `if` perguntando o tipo e nenhum `dynamic_cast`.

Na versão anterior eu usava `dynamic_cast` para mostrar quanto do Clonazepam foi escriturado. Troquei pela função virtual `condicaoDeVenda()`: o controlado já informa a quantidade escriturada ali, então a informação aparece na listagem normal.

Todos os objetos são criados com `std::make_unique` e não existe nenhum `new` nem `delete` no código. Quem apaga os medicamentos é o `unique_ptr`.

### Moldura não virtual (R11)

A função `ficha()` do `Produto` não é virtual. Ela monta a linha de cada medicamento com os dados comuns e chama `tarja()` e `condicaoDeVenda()` para preencher a parte que muda. Assim o formato da linha é sempre o mesmo (a moldura é da base) e só o conteúdo muda em cada derivada. Nenhuma derivada reescreve a `ficha()`.

### Operadores (R12)

- `operator<<` é função livre, porque do lado esquerdo fica o `ostream`, que não é uma classe minha. O do `Produto` só chama a `ficha()`.
- `operator+=` é membro do `Produto` e serve para repor estoque: `*losartana += 50` aumenta a quantidade em 50. Ele altera o objeto da esquerda e devolve uma referência para ele, do mesmo jeito que o `+=` de um `int`. Escolhi esse porque repor estoque é uma operação que a farmácia faz de verdade.

### Contadores (R13)

Cada classe concreta tem `vivos` e `criados` estáticos. O construtor soma 1 nos dois e o destrutor diminui o `vivos`. Na versão anterior o contador ficava no `Produto`; mudei para as concretas porque assim dá para ver quantos objetos de cada tipo existem.

No fim do programa a soma dos três `vivos` dá zero, o que prova que os destrutores rodaram e nenhum medicamento ficou na memória. O `criados` do isento termina em 3, e não em 2, porque a Dipirona repetida chega a ser criada, é recusada pelo estoque e é destruída na hora.

## O que mudou em relação à Unidade I

A classe `Lote` virou dois atributos do `Produto` (`lote_` e `validade_`), porque neste projeto o lote não tem nenhum comportamento próprio. A classe `Farmacia` virou o `Estoque`, que faz o que ela fazia (guardar, buscar e somar o valor), agora sendo dona dos medicamentos.