# Decisões do projeto

## 1. Por que a base é abstrata?

Porque a farmácia não sabe como dispensar um "produto" sem saber a categoria dele: o isento sai sem receita, o sob prescrição exige receita e o controlado exige receita e ainda precisa ser escriturado. Por isso `dispensar()`, `tarja()` e `condicaoDeVenda()` são puras. Se `dispensar()` tivesse um corpo padrão (por exemplo, liberar sem receita), um tipo novo de medicamento que esquecesse de sobrescrever seria vendido sem receita sem ninguém perceber, e o compilador não avisaria. Sendo pura, a classe nova simplesmente não compila até dizer como dispensa.

## 2. Por que cada herança é da forma que é?

**Pública:** todo medicamento *é um* produto do estoque, então qualquer um dos três pode ser guardado, listado e dispensado onde o estoque espera um `Produto`.

**Múltipla:** o medicamento controlado é um produto e, além disso, cumpre a obrigação de escriturar cada saída com a receita retida. Por isso ele herda de `Produto` e de `Escrituravel`. Como a interface não tem dados, nada fica duplicado.

**Privada:** o estoque *guarda* medicamentos num vector, mas não é uma lista qualquer que qualquer um pode mexer. Deixei visíveis só `size` e `empty`. Não expus `push_back`, `insert` e `emplace_back`, para que nenhum medicamento entre sem passar pela conferência de nome repetido do `adicionar()`. Não expus `operator[]`, `at`, `front`, `back`, `begin` e `end`, porque com eles alguém poderia trocar um medicamento ou tirá-lo da prateleira sem registro. Não expus `erase`, `clear` e `pop_back`, porque na farmácia um medicamento sai do estoque pelo nome, com `remover()`. E `resize`, `reserve` e `capacity` não significam nada para a farmácia.

## 3. Quem é dono de quê?

O `Estoque` é dono dos medicamentos, e isso está escrito no tipo: ele guarda `std::unique_ptr<Produto>`. Quando um medicamento é removido, ou quando o estoque deixa de existir no fim do escopo, o `unique_ptr` destrói o medicamento, e o destrutor virtual garante que rode o destrutor da classe certa (é isso que faz o `vivos` voltar a zero). Os `Produto*` que o `main` recebe do `buscar()` só emprestam o acesso e nunca apagam nada. Cada medicamento é dono dos próprios dados (nome, lote, validade), e o controlado também é dono da lista de receitas retidas.

## 4. Por que cada operador é membro ou livre?

O `operator<<` é livre porque do lado esquerdo fica o `std::ostream` (o `cout`), que não é uma classe minha, então não tenho como colocar um membro nele. O `operator+=` é membro do `Produto` porque do lado esquerdo fica o próprio medicamento que está sendo reposto: ele muda a quantidade desse medicamento e devolve ele mesmo, do mesmo jeito que o `+=` de um `int`.